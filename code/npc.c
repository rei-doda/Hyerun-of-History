#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utente.h"
#include "npc.h"

char *get_nome_npc(npc npc_qualunque) {
  return npc_qualunque.nome_npc;
}
void set_nome_npc(npc npc_qualunque, char *nome) {
  strcpy(npc_qualunque.nome_npc, nome);
}

int get_stato_quest(npc npc_qualunque) {
  return npc_qualunque.stato_quest;
}
void set_stato_quest(npc *npc_qualunque, int num) {
  npc_qualunque->stato_quest = num;
}

void carica_npc(npc *npc_qualunque, FILE *savefile) {
  char *nome_npc;
  int num_temp;
  int i = 0;
  while (i<NPC) {
    nome_npc = calloc(15, sizeof(char));
     
    fgets(nome_npc, 15, savefile);
    nome_npc[strcspn(nome_npc, "\n")] = 0;
    set_nome_npc(npc_qualunque[i], nome_npc);

    fscanf(savefile, "%d\n", &num_temp);
    set_stato_quest(&npc_qualunque[i], num_temp);
    i++;
  }  
}

void salva_npc(npc npc_qualunque, FILE *savefile) {
  int num;

  fputs(get_nome_npc(npc_qualunque), savefile);
  fputs("\n", savefile);

  num = get_stato_quest(npc_qualunque);
  fprintf(savefile, "%d\n", num);
}

int compara_esito_npc(int npc, int stato_parser) {
  int risultato;

  if (npc == 0) {
    risultato = 0;
  }
  else if (npc == (stato_parser)) {
    risultato = 1;
  }

  return risultato;
}

int controllo_armatura(player utente, int *inventario) {
  int esito = 0;
  int armor_temp;

  armor_temp = get_armor_type(utente);

  if (inventario[1] && inventario[3] && inventario[5]) {
    esito = 1; //puoi comprare armatura di bronzo
  }
  
  if (armor_temp == 1 && inventario[2] && inventario[4] && inventario[6]) {
    esito = 2; //puoi acquistare armatura di ferro
  }
  if (armor_temp == 0 && inventario[2] && inventario[4] && inventario[6]) {
    esito = 3; //devi prima acquistare l'armatura di bronzo
  }

  return esito;
}

int controllo_monete(int id_npc, int *inventario) {
  int esito = 0;

  if (id_npc == 1) {
    if (inventario[10]>8) {
      esito = 1;
    }
  }
  if (id_npc == 2) {
    if (inventario[10]>1) {
      esito = 1;
    }
  }

  return esito;
}

int parlare_npc(npc *npc_qualunque, int id_npc) {
  int esito = 8;
  int stato_quest;

  stato_quest = get_stato_quest(*npc_qualunque);

  if (id_npc == 1) {
    if (stato_quest == 0) {
      esito = 0; //prima volta con il fabbro
      set_stato_quest(npc_qualunque, 1);
    }
    else if (stato_quest == 1) {
      esito = 1; //seconda volta e via
    }
  }
  else if (id_npc == 2) {
    if (stato_quest == 0) {
      esito = 2; //prima volta con l'alchimista
      set_stato_quest(npc_qualunque, 1);
    }
    else if (stato_quest == 1) {
      esito = 3; //seconda volta e via
    }
  }
  else if(id_npc == 3){
    if(stato_quest == 0){
      esito = 4; //prima volta
      set_stato_quest(npc_qualunque, 1);
    }
    else if(stato_quest == 1){
      esito = 5; //seconda volta
    }
  }
  else if(id_npc == 4){
    if(stato_quest == 0){
      esito = 6;
      set_stato_quest(npc_qualunque, 1);
    }
    else if(stato_quest == 1){
      esito = 7;
    }
  }

  return esito;
}

int acquistare_oggetto(player *utente, int *inventario, int id_npc) {
  int armatura;
  int monete;
  int esito = 0;
  int vita_temp1;
  int vita_temp2;

  monete = controllo_monete(id_npc, inventario);

  if (monete) {
    if (id_npc == 1) {
      armatura = controllo_armatura(*utente, inventario);
      if (armatura == 1) {
        inventario[10] = inventario[10] - 9;
        set_armor_type(utente, 1);
        vita_temp1 = get_max_hp_utente(*utente);
        vita_temp2 = vita_temp1 + 8;
        set_max_hp_utente(utente, vita_temp2);
        set_current_hp_utente(utente, vita_temp2);
        esito = 1; //comprata armatura bronzo
      }
      else if (armatura == 2) {
        inventario[10] = inventario[10] - 9;
        set_armor_type(utente, 2);
        vita_temp1 = get_max_hp_utente(*utente);
        vita_temp2 = vita_temp1 + 8;
        set_max_hp_utente(utente, vita_temp2);
        set_current_hp_utente(utente, vita_temp2);
        esito = 2; //comprata armatura ferro
      }
      else if (armatura == 3) {
        esito = 3; //devi prima trovare armatura di bronzo
      }
    }
    else if (id_npc == 2) {
      inventario[10] = inventario[10] - 2;
      inventario[0]++;
      esito = 4; //pozione acquistata
    }
  }
  return esito;
}

int controllo_vestiti(int *inventario){
 int esito = 0;
  
  if (inventario[17] == 1 && inventario[18] == 1) {
    inventario[17]=0;
    inventario[18]=0;
    esito = 1;
  }
  else{
    esito = 2;
  }

  return esito;
}

int controllo_pergamene(int *inventario){
  int esito=0;

  if (inventario[14] == 1 && inventario[15] == 1 && inventario[16] == 1) {
    inventario[14]=0;
    inventario[15]=0;
    inventario[16]=0;
    esito = 1;
  }
  else{
    esito =2;
  }
  
  return esito;
}

int controllo_stato_quest(int *inventario, int id_npc){
int esito;
if(id_npc == 3){
  esito = controllo_vestiti(inventario);
}
else if(id_npc == 4){
  esito = controllo_pergamene(inventario);
}

return esito;
}