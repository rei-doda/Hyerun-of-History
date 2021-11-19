#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stanze.h"


char *get_nome_stanza(stanza stanza_qualunque) {
 return stanza_qualunque.nome_stanza;
}

void set_nome_stanza(stanza stanza_qualunque, char *nome) {
  strcpy(stanza_qualunque.nome_stanza, nome);
}

int *get_direzioni(stanza stanza_qualunque) {
  return stanza_qualunque.direzioni;
}

void set_direzioni(stanza stanza_qualunque, int *direzione) {
  stanza_qualunque.direzioni = direzione;
}

int get_una_direzione(stanza stanza_qualunque, int pos) {
  return stanza_qualunque.direzioni[pos];
}

void set_una_direzione(stanza *stanza_qualunque, int direzione, int pos) {
  stanza_qualunque->direzioni[pos] = direzione;
}

int get_npc(stanza stanza_qualunque) {
  return stanza_qualunque.npc;
}

void set_npc(stanza *stanza_qualunque, int id_npc) {
  stanza_qualunque->npc = id_npc;
}

int get_nemici(stanza stanza_qualunque) {
  return stanza_qualunque.nemici;
}

void set_nemici(stanza *stanza_qualunque, int id_nemici) {
  stanza_qualunque->nemici = id_nemici;
}

char *get_dipinto(stanza stanza_qualunque) {
 return stanza_qualunque.dipinto;
}

void set_dipinto(stanza stanza_qualunque, char *dipinto) {
  strcpy(stanza_qualunque.dipinto, dipinto);
}

char *get_libro(stanza stanza_qualunque) {
 return stanza_qualunque.libro;
}

void set_libro(stanza stanza_qualunque, char *libro) {
  strcpy(stanza_qualunque.libro, libro);
}

int *get_oggetti_raccoglibili(stanza stanza_qualunque) {
  return stanza_qualunque.oggetti_raccoglibili;
}

void set_oggetti_raccoglibili(stanza stanza_qualunque, int *oggetti) {
  stanza_qualunque.oggetti_raccoglibili = oggetti;
}

int get_oggetto_raccoglibile(stanza stanza_qualunque, int id_oggetto) {
  return stanza_qualunque.oggetti_raccoglibili[id_oggetto];
}

void set_oggetto_raccoglibile(stanza *stanza_qualunque, int num_ogg, int id_oggetto) {
  stanza_qualunque->oggetti_raccoglibili[id_oggetto] = num_ogg;
}

void carica_stanza(stanza *stanza_qualunque, FILE *savefile) {
  char *temp;
  char *dipint;
  char *libr;
  int num_temp;
  int temp_num;
  int i=0;
  int j=0;
  int k=0;

  temp = calloc(100, sizeof(char));
  dipint = calloc(1000,sizeof(char));
  libr = calloc(600, sizeof(char));

  while(i<STANZE) {
    fgets(temp, 100, savefile);
    temp[strcspn(temp, "\n")] = '\0';
    set_nome_stanza(stanza_qualunque[i], temp);

    fgets(dipint, 1000, savefile);
    dipint[strcspn(dipint, "\n")] = '\0';
    set_dipinto(stanza_qualunque[i], dipint);
    
    fgets(libr, 600, savefile);
    libr[strcspn(libr, "\n")] = '\0';
    set_libro(stanza_qualunque[i], libr);
   
    while(j<4) {
      fscanf(savefile, "%d", &num_temp);
      set_una_direzione(&stanza_qualunque[i], num_temp, j);
      j++;
    }
    j=0;
    
    fscanf(savefile, "%d", &num_temp);
    set_npc(&stanza_qualunque[i], num_temp);

    fscanf(savefile, "%d \n", &num_temp);
    set_nemici(&stanza_qualunque[i], num_temp);

    while(k<19) {
      fscanf(savefile, "%d", &temp_num);
      set_oggetto_raccoglibile(&stanza_qualunque[i], temp_num, k);
      k++;
    }
    fscanf(savefile, "%d \n", &temp_num);
    set_oggetto_raccoglibile(&stanza_qualunque[i], temp_num, k);
    k=0;
    
    i++;
  } 
}

void salva_stanza(stanza stanza_qualunque, FILE *savefile) { 
  char *temp;
  char *dipint;
  char *libr;
  int *dir_temp;
  int num_temp;
  int *ogg_temp;
  int j=0;
  int k=0;

  
  temp = get_nome_stanza(stanza_qualunque);
  fputs(temp, savefile);
  fputs("\n", savefile);

  dipint = get_dipinto(stanza_qualunque);
  fputs(dipint, savefile);
  fputs("\n", savefile);

  libr = get_libro(stanza_qualunque);
  fputs(libr, savefile);
  fputs("\n", savefile);

  dir_temp = get_direzioni(stanza_qualunque);
  while (j<4) {
    fprintf(savefile, "%d ", dir_temp[j]);
    j++;
  }
  j=0;

  fprintf(savefile, "\n");
    
  num_temp = get_npc(stanza_qualunque);
  fprintf(savefile, "%d\n", num_temp);
    

  num_temp = get_nemici(stanza_qualunque);
  fprintf(savefile, "%d\n", num_temp);

  ogg_temp = get_oggetti_raccoglibili(stanza_qualunque);
  while(k<20) {
    fprintf(savefile, "%d ", ogg_temp[k]);
    k++;
  }
  k=0;
  fprintf(savefile, "\n");
}