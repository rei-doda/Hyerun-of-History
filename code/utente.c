#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utente.h"


int get_max_hp_utente(player utente) {
  return utente.max_hp;
}

void set_max_hp_utente(player *utente, int num) {
  utente->max_hp = num;
}

int get_current_hp_utente(player utente) {
  return utente.current_hp;
}

void set_current_hp_utente(player *utente, int num) {
  utente->current_hp = num;
}

int get_armor_type(player utente) {
  return utente.armor_type;
}

void set_armor_type(player *utente, int num) {
  utente->armor_type = num;
}

int get_sword_type(player utente) {
  return utente.sword_type;
}

void set_sword_type(player *utente, int num) {
  utente->sword_type = num;
}

int get_danni_inflitti(player utente) {
  return utente.danni_inflitti;
}

void set_danni_inflitti(player *utente, int num) {
  utente->danni_inflitti = num;
}

int get_current_room(player utente) {
  return utente.current_room;
}

void set_current_room(player *utente, int num) {
  utente->current_room = num;
}

void carica_utente(player *utente, FILE *savefile) {
  int num;

  fseek(savefile, 0, SEEK_SET);

  fscanf(savefile, "%d", &num);
  set_max_hp_utente(utente, num);

  fscanf(savefile, "%d", &num);
  set_current_hp_utente(utente, num);

  fscanf(savefile, "%d", &num);
  set_armor_type(utente, num);

  fscanf(savefile, "%d", &num);
  set_sword_type(utente, num);

  fscanf(savefile, "%d", &num);
  set_danni_inflitti(utente, num);

  fscanf(savefile, "%d\n", &num);
  set_current_room(utente, num);
}

void salva_utente(player utente, FILE *savefile) {
  int num;

  fseek(savefile, 0, SEEK_SET);

  num = get_max_hp_utente(utente);
  fprintf(savefile, "%d\n", num);

  num = get_current_hp_utente(utente);
  fprintf(savefile, "%d\n", num);

  num = get_armor_type(utente);
  fprintf(savefile, "%d\n", num);

  num = get_sword_type(utente);
  fprintf(savefile, "%d\n", num);

  num = get_danni_inflitti(utente);
  fprintf(savefile, "%d\n", num);

  num = get_current_room(utente);
  fprintf(savefile, "%d\n", num);
}

void prendere_spada(player *utente, int spada) {
  if (spada == 15) {
    set_sword_type(utente, 1);
    set_danni_inflitti(utente, 4);
  }
  if (spada == 16) {
    set_sword_type(utente, 2);
    set_danni_inflitti(utente, 6);
  }
  if (spada == 17) {
    set_sword_type(utente, 3);
    set_danni_inflitti(utente, 8);
  }
}