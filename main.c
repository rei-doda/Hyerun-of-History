#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stanze.h"
#include "utente.h"
#include "npc.h"
#include "nemici.h"
#include "utilities.h"
#include "comandi.h"
#include "globali.h"
#include "combattimento.h"


int main(void) {
  
  int stanze[37] = {1, 0, 3, 0, 5, 6, 7, 8, 9, 10, 11, 0, 13, 0, 15, 16, 17, 18, 19, 0,21, 22, 23, 24, 0, 0, 27, 28, 0, 30, 31, 32, 0, 34, 35, 36};

  int inventario[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  char *comando_utente; //riceve da tastiera il comando completo
  char *sottostringhe[2]; //mantiene temporaneamente verbo e oggetto del comando
  char *comando_verbo; //verbo del comando
  char *comando_oggetto; //oggetto del comando  

  int i = 0; //contatore per ciclare tra i comandi primari o combattimento
  int j = 0; //contatore per ciclare tra i comandi secondari
  int stato1 = 104; //indica il comando primario o combattimento
  int stato2 = 104; //indica il comando secondario
  int esito_quest;
  int esito_parser; //da dare in input alle funzioni che escono dal parser
  int quit = 0;
  int stanza_attuale;
  int lavoro; //eventuale variabile di lavoro all'interno del parser
  int id_npc; //per mantenere con chi si sta parlando
  int stanza_aggiornata = 0;
  char *intro;
  int danni_inflitti;
  int nemico_attuale;
  int contatore_vite = 4;
   
  FILE *savefile;
  FILE *newgame;
  FILE *introduzione;
  FILE *elenco_comandi; 
  FILE *storia;
  FILE *pergamene;

  intro = calloc(200, sizeof(char));
  
  alloca_memoria();

  savefile = fopen("savefile.txt", "r+");
  newgame = fopen("newgame.txt", "r");
  introduzione = fopen("introduzione.txt", "r");
  storia = fopen("storia.txt","r");
  pergamene = fopen("pergamene.txt", "r");
  elenco_comandi = fopen("elenco_comandi.txt","r");

  carica_da_file(newgame);

  while (quit == 0) {

    if (contatore_vite == 4) { /*La descrizione viene mostrata solo la prima                                  volta*/
      contatore_vite--;
      carica_storia(introduzione);
      printf("\n\n");
    }

    stanza_attuale = get_current_room(utente);
     if (stanza_aggiornata != stanza_attuale) {
        printf("%s\n",get_nome_stanza(stanza_qualunque[stanza_attuale]));
        intro = carica_intro_stanza(storia, stanza_attuale);
        metti_a_capo(intro);
        printf("\n");
        stanza_aggiornata = stanza_attuale;
      }
      
    if (get_nemici(stanza_qualunque[stanza_attuale]) == 0) {

      lavoro = 0;
      comando_utente = calloc(30, sizeof(char));
      comando_verbo = calloc(15, sizeof(char));
      comando_oggetto = calloc(15, sizeof(char));

      fgets(comando_utente, 30, stdin);
      comando_utente[strcspn(comando_utente, "\n")] = '\0';

      printf("\n");
  
      dividi_stringa(sottostringhe, comando_utente,' ');
    
      comando_verbo = sottostringhe[0];
      comando_oggetto = sottostringhe[1];

      while (i<15 && stato1 == 104) {
        if (!strcmp(comandi_primario[i], comando_verbo)) {
          stato1 = i;
        }
        i++;
      }

      if (stato1 == 0) { //ANDARE
        while (j<4 && stato2 == 104) {
          if (!strcmp(comandi_secondario[j], comando_oggetto)) {
            stato2 = j;
            esito_parser=andare_direzione(stanza_qualunque[stanza_attuale], &utente, stato2);
            printf("%s\n\n", esito_andare_direzioni[esito_parser]);
          }
          j++;
        }
        if (stato2 == 104) {
          printf("Impara l’italiano e scrivi un comando decente.\n\n");
        }
      }
      else if (stato1 == 1) { //GUARDARE
        j = 4;
        if (!strcmp(comandi_secondario[j], comando_oggetto)) {
          stato2 = j;
          printf("%s\n", get_nome_stanza(stanza_qualunque[stanza_attuale]));
          esito_parser = 0;
          printf("Attorno a te vedi: ");

          while (esito_parser<4) {
            
            if (get_una_direzione(stanza_qualunque[stanza_attuale], esito_parser)) {
              printf("una porta a %s, ", comandi_secondario[esito_parser]);
            }

            esito_parser++;
          } 

          if (stanza_attuale == 9 || stanza_attuale == 15 || stanza_attuale == 13 || stanza_attuale == 28) {
            printf("delle scale, ");
          }

          if (!strcmp(get_dipinto(stanza_qualunque[stanza_attuale]), "0\n")) {
            printf("dei dipinti, ");
          }
          if (!strcmp(get_libro(stanza_qualunque[stanza_attuale]), "0\n")) {
            printf("un libro, ");
          }

          esito_parser = presenza_baule_cassettiera(stanza_qualunque[stanza_attuale]);

          if (esito_parser==1) {
            printf("un baule, ");
          }
          else if (esito_parser==2) {
            printf("una cassettiera, ");
          }
          
          esito_parser = 0;
          while (esito_parser<20) {
            lavoro = get_oggetto_raccoglibile(stanza_qualunque[stanza_attuale], esito_parser);
            if (lavoro != 0 && lavoro < 5) {
              printf("%d %s, ", lavoro, comandi_secondario[esito_parser+8]);
            }

            esito_parser++;
          } 

          esito_parser = 0;          
            
          lavoro = get_npc(stanza_qualunque[stanza_attuale]);
          if (lavoro) {
            printf("%s, ", comandi_secondario[lavoro+28]);
          }

          printf("e nient'altro.\n\n");

        }
        else if (!strcmp(comandi_secondario[j+1], comando_oggetto)) {
          stato2 = j+1;
          if (!strcmp(get_dipinto(stanza_qualunque[stanza_attuale]), "0\n")) {
            metti_a_capo(get_dipinto(stanza_qualunque[stanza_attuale]));
            printf("\n");
          }
          else {
            printf("Non ci sono dipinti in questa stanza.\n\n");
          }
          
        }
        else if (stato2 == 104) {
          printf("Impara l’italiano e scrivi un comando decente.\n\n");
        }
      }
      else if (stato1 == 2) { //APRIRE
        j = 0;
        while (j<4 && stato2 == 104) { //direzioni
          if (!strcmp(comandi_secondario[j], comando_oggetto)) {
            stato2 = j;
            esito_parser = aprire_direzione(&stanza_qualunque[stanza_attuale], inventario, stato2);
            printf("%s\n\n", esito_aprire_direzioni[esito_parser]);
          }
          j++;
        }
        if (stato2 == 104) {
          j = 6;
          while (j<8 && stato2 == 104) { //baule o cassettiera
            if (!strcmp(comandi_secondario[j], comando_oggetto)) {
              stato2 = j;
              esito_parser = presenza_baule_cassettiera(stanza_qualunque[stanza_attuale]);

              if ((esito_parser == 1 && stato2 == 6) || (esito_parser == 2 && stato2 == 7)) {
                printf("%s\n\n", esito_aprire_baule_cassettiera[esito_parser+1]);
                aprire_baule_cassettiera(&stanza_qualunque[stanza_attuale], stato2, esito_parser);
                esito_parser = 0;
                printf("All'interno hai trovato:\n");
                while (esito_parser<20) {
                  lavoro = get_oggetto_raccoglibile(stanza_qualunque[stanza_attuale], esito_parser);
                  if (lavoro != 0 && lavoro < 5) {
                    printf("%d %s, ", lavoro, comandi_secondario[esito_parser+8]);
                  }

                  esito_parser++;
                } 
                printf("e nient'altro.\n\n");

                esito_parser = 0;
              } 
              else {
                printf("%s\n\n", esito_aprire_baule_cassettiera[esito_parser]);
              }             
            }
            j++;
          }
        }
        if (stato2 == 104) {
          printf("Impara l’italiano e scrivi un comando decente.\n");
        }
      }
      else if (stato1 == 3) { //PRENDERE
        j = 8;
        while (j<28 && stato2 == 104) {
          if (!strcmp(comandi_secondario[j], comando_oggetto)) {
            stato2 = j;
            esito_parser = prendere_oggetto(&stanza_qualunque[stanza_attuale], inventario, stato2-8);
            if (esito_parser != 0) {
              prendere_spada(&utente, stato2);
              printf("Hai raccolto %d %s ",esito_parser,comandi_secondario[stato2]);
              if (stato2 == 15 || stato2 == 16 || stato2 == 17) {
                printf("e ora infliggi %d danni per colpo, ", get_danni_inflitti(utente));
              }
              printf("\n\n");
            }
            else {
              printf("%s non è presente nella stanza.\n\n", comandi_secondario[stato2]);
            }
          }
          j++;
        }
        if (stato2 == 104) {
          printf("Impara l’italiano e scrivi un comando decente.\n\n");
        }
      }
      else if (stato1 == 4) { //USARE
        j = 8;
        if (!strcmp(comandi_secondario[j], comando_oggetto)) {
          stato2 = j;
          if (inventario[0]) {
            inventario[0]--;
            esito_parser = usare_pozione(&utente);
            printf("Hai recuperato %d punti vita.\n", esito_parser);
            printf(" (vita: %d)\n\n",get_current_hp_utente(utente));
              
          }
          else {
            printf("-Non hai pozioni da poter usare!\n\n");
          }
        }
        else if (!strcmp(comandi_secondario[j+20], comando_oggetto)) {
          stato2 = j + 20;
          esito_parser = usare_scale(&utente);
          if (esito_parser == 0) {
            printf("Non ci sono scale nella stanza.\n");
          }
          else {
            printf("Hai usato le scale.\n\n");
          }
        }
        else if (stato2 == 104) {
          printf("Impara l’italiano e scrivi un comando decente.\n");
        }
      }
      else if (stato1 == 5) { //PARLARE
        j = 29;

        while (j<31 && stato2 == 104) {//Fabbro o Alchimista
       
          if (!strcmp(comandi_secondario[j], comando_oggetto)) {
            stato2 = j - 28; //traduciamo input in un numero da 1 a 4
            id_npc = get_npc(stanza_qualunque[stanza_attuale]);
            if (!compara_esito_npc(id_npc, stato2)) {
              printf("%s non è presente nella stanza.\n\n", comandi_secondario[stato2+28]);
            }
            else {
              esito_parser = parlare_npc(&npc_qualunque[stato2-1], stato2);
              
              metti_a_capo((conversazioni_npc[esito_parser]));
              printf("\n\n");
              
              stato1 = 104;

              while (stato1 == 104) {
                i = 12;
                comando_utente = calloc(30, sizeof(char));
                fgets(comando_utente, 30, stdin);
                comando_utente[strcspn(comando_utente, "\n")] = '\0';

                while (i<14 && stato1 == 104) { // si o no
                  if (!strcmp(comandi_primario[i], comando_utente)) {
                    stato1 = i;
                  }
                  i++;

                  if (stato1 == 12) { //si
                    esito_parser = acquistare_oggetto(&utente, inventario, stato2);

                    printf("\n");

                    if (!esito_parser) { //acquisto non riuscito
                      
                      if (stato2 == 1 ) {
                        printf("FABBRO: Mi dispiace scricciolo, non hai tutti i pezzi e/o le monete per migliorare quella ferraglia che ti ritrovi sul petto.");
                      }
                      else if (stato2 == 2 ) {
                        printf("ALCHIMISTA: Piccolo guerriero, non hai abbastanza monete per l’acquisto.");
                      }                    
                    }
                    else { //acquisto riuscito

                      if (stato2 == 1 ) {
                        printf("FABBRO: È un piacere fare affari con te.\n\n");
                        if(get_armor_type(utente)==1){
                          printf("-Ora indossi l'armatura di bronzo e hai 24 hp.\n\n");
                        }
                        else{
                          printf("-Ora indossi l'armatura di ferro e hai 32 hp.\n\n");
                        }
                       
                      }
                      else if (stato2 == 2) {
                        printf("ALCHIMISTA: Ooh, monete scintillanti!\n\n");
                        printf("-Nuova pozione aggiunta al tuo inventario.\n");
                        printf(" Pozioni in tuo possesso: %d\n\n",inventario[0]);
                      }  
                    }
                  }

                  else if (stato1 == 13) {

                    printf("\n");

                    if (stato2 == 1) {
                      printf("FABBRO: Oh-oh, dannato pazzo finirai per ammazzarti se non usi la ferraglia giusta.\n\n");
                    }
                    else if (stato2 == 2) {
                      printf("ALCHIMISTA: Come vuoi, ma attento: la morte è dietro l’angolo.\n\n");
                    } 
                  }
                }
                if (stato1 == 104) {
                  printf("Impara l’italiano e scrivi un comando decente (sì o no).\n\n");
                }
              }
            }
          }
          j++;
        }

        while (j<33 && stato2 == 104) { //Dama o Re
          if (!strcmp(comandi_secondario[j], comando_oggetto)) {
            stato2 = j - 28; //traduciamo input in un numero da 1 a 4

            id_npc = get_npc(stanza_qualunque[stanza_attuale]);
            if (!compara_esito_npc(id_npc, stato2)) {
              printf("%s non è presente nella stanza.\n\n", comandi_secondario[stato2+28]);
            }
            else {
              esito_parser = parlare_npc(&npc_qualunque[stato2-1], id_npc);
              
              if (esito_parser == 4){ //prima volta con la dama
                metti_a_capo((conversazioni_npc[id_npc+1]));
                printf("\n\n");
              }
              else if (esito_parser == 6){ //prima volta il re
                metti_a_capo((conversazioni_npc[id_npc+1]));
                printf("\n\n");
              }
              else if (esito_parser == 5) {
                esito_quest = controllo_stato_quest(inventario, id_npc);
                if (esito_quest == 1) {
                  printf("DAMA: Ti ringrazio per il tuo aiuto, spero ci rincontreremo presto, magari in un luogo meno tenebroso, per poterci conoscere meglio e aprirci l’un altro.\n\n");

                  printf("Narratore: Il cavaliere, attratto focosamente dalla dama, subisce un passionale bacio da quest’ultima che finisce in un amplesso che rivitalizza il giocatore donandogli un bonus permanente di +2 hp di vita.\n\n");

                  lavoro = get_max_hp_utente(utente);
                  set_max_hp_utente(&utente, lavoro+2);
                  set_current_hp_utente(&utente, lavoro+2);
                }
                else if(esito_quest == 2){
                  printf("DAMA: Ti ho detto di non guardarmi! Per favore fa' presto nel trovarmi qualcosa da indossare.\n");
                }
              }
              else if (esito_parser == 7) { 
                esito_quest = controllo_stato_quest(inventario, id_npc);
                if (esito_quest == 1) {

                  carica_storia(pergamene);

                  printf("\n\n");

                  printf("RE: Ora sai tutta la storia, hai letto quel che ho fatto, con un motivo deplorevole sei entrato in questo castello, ma ora hai compreso che la strada del ladro non fa per te. Con la saggezza racchiusa in Torgard, apri la porta a nord e purifica ciò che rimane di questo regno. Coraggio mio Re!\n\n" );

                  printf("Il nostro cavaliere, ora diventato re, esce dunque dal castello, volendo rimediare agli errori del vecchio re e riportare la pace in tutta Hyerun.\n\n");

                  carica_da_file(newgame);
                  salva_su_file(savefile);

                  quit = 1;
                }
                else if (esito_quest == 2) {
                  printf("RE: Non hai ancora recuperato le pergamene che ti ho chiesto. Torna quando le avrai trovate.\n\n");
                }
              }
            }
          }
          j++;
        }
        if (stato2 == 104) {
          printf("Impara l’italiano e scrivi un comando decente.\n\n");
        }
      }
      else if (stato1 == 6) { //LEGGERE
        j = 33;
        if (!strcmp(comandi_secondario[j], comando_oggetto)) {
          stato2 = j;
         
          printf("%s\n", get_libro(stanza_qualunque[stanza_attuale]));
          
        }
        else if (stato2 == 104) {
          printf("Impara l’italiano e scrivi un comando decente.\n\n");
        }
      }
      else if (stato1 == 7) { //SALVARE
        if (!strcmp(comando_oggetto, "\0")) {
          printf("Salvataggio riuscito.\n\n");
          salva_su_file(savefile);
        }
        else {
          printf("Devi scrivere di meno, intellettuale dei miei fondelli.\n\n");
        }
      }
      else if (stato1 == 8) { //CONTINUARE
        if (!strcmp(comando_oggetto, "\0")) {
          carica_da_file(savefile);
          printf("caricato un precedente salvataggio\n\n");
        }
        else {
          printf("Devi scrivere di meno, intellettuale dei miei fondelli.\n\n");
        }
      }
      else if (stato1 == 9) { //USCIRE
        if (!strcmp(comando_oggetto, "\0")) {
          quit = 1;
          printf("Arrivederci, cavaliere.\n\n");
        }
        else {
          printf("Devi scrivere di meno, intellettuale dei miei fondelli.\n\n");
        }
      }
      else if (stato1 == 10) { //COMANDI
        if (!strcmp(comando_oggetto, "\0")) {
          carica_storia(elenco_comandi);
          printf("\n\n");
        }
        else {
          printf("Devi scrivere di meno, intellettuale dei miei fondelli.\n\n");
        }
      }
      else if (stato1 == 11) { //INVENTARIO
        if (!strcmp(comando_oggetto, "\0")) {
          printf("Nell'inventario hai ");
          while (lavoro<20) {
            if (inventario[lavoro]) {
              printf("| %d %s ", inventario[lavoro], comandi_secondario[lavoro+8]);
              i = 0;
            }
              
            lavoro++;
          }
          if (i) {
            printf("solo polvere.\n");
            }
          else {
            printf("\n");
          }
        }
        else {
          printf("Devi scrivere di meno, intellettuale dei miei fondelli.\n");
        }
      }
      else if (stato1 == 104) {
        printf("Impara l’italiano e scrivi un comando decente.\n\n");
      }
      else {
        printf("unexpected error\n\n");
      }
      j = 0;
    }
//////////////////////////////////////////////////////////

    else { //PARSER COMBATTIMENTO

      nemico_attuale = get_nemici(stanza_qualunque[stanza_attuale]);
      lavoro = mossa_mostro();

      danni_inflitti=get_danni_inflitti(utente);
      printf("---------------------\n");
      printf("(Vita giocatore: %d)\n",get_current_hp_utente(utente));
      printf("(vita %s: %d)\n",get_nome_nemico(nemico_qualunque[nemico_attuale]),get_current_hp_nemico(nemico_qualunque[nemico_attuale]));
      printf("---------------------\n");

      if(get_current_hp_utente(utente)>0 && get_current_hp_nemico(nemico_qualunque[nemico_attuale])>0){

        
        attaccare(&utente,&nemico_qualunque[nemico_attuale],0);
        
        printf("-%s ti sta attaccando.\n Puoi parare o schivare l'attacco, a te la scelta:\n\n", get_nome_nemico(nemico_qualunque[get_nemici(stanza_qualunque[stanza_attuale])]));
       
        while(stato1 == 104 && get_current_hp_utente(utente)>0){
         
          comando_utente = malloc(30*sizeof(char));
          fgets(comando_utente, 30, stdin);
          comando_utente[strcspn(comando_utente, "\n")] = '\0'; //rimuove \n dalla stringa input

          i=0;
          printf("\n");
          while (i<2 && stato1 == 104) {
            if (!strcmp(comandi_combattimento[i], comando_utente)) {
              stato1 = i;
            }
            i++;
          }
          if (stato1 == 0) {
            
            schivare(&utente,&nemico_qualunque[nemico_attuale], 0);
            
            lavoro = riesci_a_schivare(nemico_qualunque[nemico_attuale]);

            if (lavoro == 0) {
              penitenza(&utente, &nemico_qualunque[nemico_attuale],0);
              printf("-Non sei riuscito a schivare il colpo di %s e hai preso %d danni. Ora è il tuo turno.\n Puoi attaccare o curarti, a te la scelta:\n", get_nome_nemico(nemico_qualunque[nemico_attuale]), get_danno_nemico(nemico_qualunque[nemico_attuale]));
            }
            else if (lavoro == 1) {
              printf("-Hai schivato l'attacco di %s. Congratulazioni, ora è il tuo turno.\n Puoi attaccare o curarti, a te la scelta:\n", get_nome_nemico(nemico_qualunque[nemico_attuale]));
            }
            else if (lavoro == 2) {
              parare(&utente,&nemico_qualunque[nemico_attuale], 0);
              printf("-Non hai schivato completamente il colpo di %s e hai preso %d danni.\n Ora è il tuo turno. Puoi attaccare o curarti, a te la scelta:\n", get_nome_nemico(nemico_qualunque[nemico_attuale]), get_danno_nemico(nemico_qualunque[nemico_attuale])/2);
            }
          }
          else if (stato1 == 1) {
            parare(&utente,&nemico_qualunque[nemico_attuale], 0);
            printf("-Hai parato l'attacco di %s. Congratulazioni, ora è il tuo turno.\n Puoi attaccare o curarti, a te la scelta:\n",get_nome_nemico(nemico_qualunque[nemico_attuale]));
          } 
          else if (stato1 == 104) {
            penitenza(&utente, &nemico_qualunque[nemico_attuale],0);
            printf("-A causa della tua goffaggine ti sei procurato %d danni. Ritenta:\n",get_danno_nemico(nemico_qualunque[nemico_attuale]));
          }
          else {
            printf("-Unexpected error\n");
          } 

          printf(" (Vita giocatore: %d)\n\n",get_current_hp_utente(utente));
        }
        stato1=104;
        while(stato1 == 104 && get_current_hp_utente(utente)>0){
          
          comando_utente = malloc(30*sizeof(char));
          fgets(comando_utente, 30, stdin);
          comando_utente[strcspn(comando_utente, "\n")] = '\0'; //rimuove \n dalla stringa input

          printf("\n");
          i=2;
          while (i<4 && stato1 == 104) {
            if (!strcmp(comandi_combattimento[i], comando_utente)) {
              stato1 = i;
            }
            i++;
          }
          if (stato1 == 2) {
            attaccare(&utente,&nemico_qualunque[nemico_attuale], 0);
          }
          else if (stato1 == 3) {
            
            if (inventario[0]) {
              inventario[0]--;
              danni_inflitti=usare_pozione(&utente);
              printf("-Hai recuperato %d punti vita.\n",danni_inflitti);
              printf(" (vita: %d)\n\n",get_current_hp_utente(utente));
              
            }
            else {
              printf("-Non hai pozioni da poter usare!\n\n");
            }
            
          } 
          else if (stato1 == 104) {
            penitenza(&utente, &nemico_qualunque[nemico_attuale],0);
            printf("-A causa della tua goffaggine ti sei procurato %d danni.\n",danni_inflitti);
          }
          else {
            printf("-Unexpected error\n");
          } 
        }
        if(lavoro==0 && stato1 == 2 && get_current_hp_utente(utente)>0){
          get_danni_inflitti(utente);
          penitenza(&utente,&nemico_qualunque[nemico_attuale],1);
          
          printf("-%s Ha subito tutto il tuo attacco.\n", get_nome_nemico(nemico_qualunque[nemico_attuale])); 
          printf(" (vita: %d)\n",get_current_hp_nemico(nemico_qualunque[nemico_attuale]));
          
        }
        else if(lavoro==1 && stato1 == 2 && get_current_hp_utente(utente)>0){
          schivare(&utente, &nemico_qualunque[nemico_attuale],1);
          printf("-%s ha schivato il tuo attacco.\n",get_nome_nemico(nemico_qualunque[nemico_attuale]));
          
          printf(" (vita: %d)\n",get_current_hp_nemico(nemico_qualunque[nemico_attuale]));
         
        } 
        else if(lavoro==2 && stato1 == 2 && get_current_hp_utente(utente)>0){
          parare(&utente, &nemico_qualunque[nemico_attuale],1);
          printf("-%s Ha parato il tuo attacco.\n", get_nome_nemico(nemico_qualunque[nemico_attuale]));
          
          printf(" (vita: %d)\n",get_current_hp_nemico(nemico_qualunque[nemico_attuale]));
          
        }
        printf("\n");
      }
   
      else if(get_current_hp_utente(utente)<=0){
        contatore_vite--;
        if (contatore_vite) { //puoi tentare di nuovo dal tuo ultimo salvataggio
          printf("Sei morto! Riprova dall'ultimo salvataggio.\n");
          carica_da_file(savefile);
          if (contatore_vite == 1) {
            printf("Hai %d vita rimasta.\n\n", contatore_vite);
          }
          else {
            printf("Hai %d vite rimaste.\n\n", contatore_vite);
          }
        }
        else {
          contatore_vite = 4;
          printf("Hai perso tutte e 3 le vite a tua disposizione, ricomincia da capo!\n\n");
          carica_da_file(newgame);
          salva_su_file(savefile);
        }
      }
      else if (get_current_hp_nemico(nemico_qualunque[nemico_attuale])<=0){
        
        printf("Hai ucciso %s. Congratulazioni! + %d HP. Ora puoi esplorare la stanza.\n\n", get_nome_nemico(nemico_qualunque[nemico_attuale]), usare_pozione(&utente));
        set_nemici(&stanza_qualunque[stanza_attuale], 0);
        printf("%s\n",get_nome_stanza(stanza_qualunque[stanza_attuale]));
        intro = carica_intro_stanza(storia, stanza_attuale);
        metti_a_capo(intro);
        printf("\n");
      }
    }
    i = 0;
    stato1 = 104;
    stato2 = 104;
  }
  

  libera_memoria();

  fclose(newgame);
  fclose(savefile);
  fclose(introduzione);
  fclose(storia);
  fclose(pergamene);
  fclose(elenco_comandi);

  return 0;
}