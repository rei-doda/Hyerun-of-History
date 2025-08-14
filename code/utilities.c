#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utente.h"
#include "npc.h"
#include "nemici.h"
#include "stanze.h"
#include "globali.h"

void carica_da_file(FILE *savefile) {
  int i=0;

  carica_utente(&utente, savefile);
  
  //fseek(savefile, 14, SEEK_SET);

  carica_nemici(nemico_qualunque, savefile);
  
  carica_npc(npc_qualunque, savefile);
   
  carica_stanza(stanza_qualunque, savefile);
}

void salva_su_file(FILE *savefile) {
  int i = 0;

  salva_utente(utente, savefile);

  while(i<NEMICI) {
    salva_nemico(nemico_qualunque[i], savefile);
    i++;
  }
  i = 0;

  while (i<NPC) {
    salva_npc(npc_qualunque[i], savefile);
    i++;
  }
  i = 0;

  while (i<STANZE) {
    salva_stanza(stanza_qualunque[i], savefile);
    i++;
  }
}

nemico *alloca_nemici(nemico *nemico_qualunque) {
  int i=0;
  nemico_qualunque = calloc(NEMICI, sizeof(nemico));
  while (i<NEMICI) {
    nemico_qualunque[i].nome_nemico = calloc(40, sizeof(char));
    i++;
  }
  return nemico_qualunque;
}

npc *alloca_npc(npc *npc_qualunque) {
  int i = 0;

  npc_qualunque = calloc(NPC, sizeof(npc));
  while (i<NPC) {
    npc_qualunque[i].nome_npc = calloc(15, sizeof(char));
    i++;
  }

  return npc_qualunque;
}


void alloca_memoria() {
  int i=0;
  
  stanza_qualunque = calloc(STANZE, sizeof(stanza));
  while (i<STANZE) {
    stanza_qualunque[i].nome_stanza = calloc(100, sizeof(char));
    stanza_qualunque[i].direzioni = calloc(5, sizeof(int));
    stanza_qualunque[i].dipinto = calloc(1000, sizeof(char));
    stanza_qualunque[i].libro = calloc(600, sizeof(char));
    stanza_qualunque[i].oggetti_raccoglibili = calloc(20, sizeof(int));
    i++;
  }
  
  i=0;
  nemico_qualunque = calloc(NEMICI, sizeof(nemico));
  while (i<NEMICI) {
    nemico_qualunque[i].nome_nemico = calloc(40, sizeof(char));
    i++;
  }

  i=0;
  npc_qualunque = calloc(NPC, sizeof(npc));
  while (i<NPC) {
    npc_qualunque[i].nome_npc = calloc(15, sizeof(char));
    i++;
  }
}

void libera_memoria(stanza *stanza_qualunque, nemico *nemico_qualunque, npc *npc_qualunque) {
  int i=0;
  
  while (i<STANZE) {
    free(stanza_qualunque[i].nome_stanza);
    free(stanza_qualunque[i].direzioni);
    free(stanza_qualunque[i].dipinto);
    free(stanza_qualunque[i].libro);
    free(stanza_qualunque[i].oggetti_raccoglibili);
    i++;
  }

  i=0;
  
  while (i<NEMICI) {
    free(nemico_qualunque[i].nome_nemico);
    i++;
  }

  i=0;
  
  while (i<NPC) {
    free(npc_qualunque[i].nome_npc);
    i++;
  }
}


void metti_a_capo(char *stringa){
  int i=0;
  int j=1;
  while(stringa[i]!='\0'){
    printf("%c", stringa[i]);
    if(i>70*j ){
      if(stringa[i]==' '){
        printf("\n");
        j++;
      }
    }
    i++;
    
  }
  

}

void carica_storia(FILE *documento){

  int i;
  int j;
  int len;
  int counter;
  char **mon = (char**) malloc(sizeof(char*)*2600);
  char segno = '_';

  i=0;
  j=0;
  do {
    mon[i] = (char*)malloc(sizeof(char)*1000);
    fgets(mon[i],2600,documento);
    len = strlen(mon[i]);
    i++;  
  }while(mon[i-1][len-1] != segno );
  
  counter=i;
  i = 0; 
  while(i<counter){
    metti_a_capo(mon[i]);
  i++;
}
}

char *carica_intro_stanza(FILE *savefile, int stanza_attuale) {
  char * stringa_temp;
  int i=0;

  stringa_temp = calloc(200, sizeof(char));
  fseek(savefile, 0, SEEK_SET);

  while (i<stanza_attuale+1) {
    
    fgets(stringa_temp, 200, savefile);
    i++;
  }
  
  return stringa_temp;
}

