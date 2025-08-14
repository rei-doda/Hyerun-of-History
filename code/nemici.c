#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nemici.h"


char *get_nome_nemico(nemico nemico_qualunque) {
  return nemico_qualunque.nome_nemico;
}

void set_nome_nemico(nemico nemico_qualunque, char *nome) {
  strcpy(nemico_qualunque.nome_nemico, nome);
}

int get_max_hp_nemico(nemico nemico_qualunque) {
  return nemico_qualunque.max_hp;
}

void set_max_hp_nemico(nemico *nemico_qualunque, int num) {
  nemico_qualunque->max_hp = num;
}

int get_current_hp_nemico(nemico nemico_qualunque) {
  return nemico_qualunque.current_hp;
}

void set_current_hp_nemico(nemico *nemico_qualunque, int num) {
  nemico_qualunque->current_hp = num;
}

int get_danno_nemico(nemico nemico_qualunque) {
  return nemico_qualunque.danno_nemico;
}

void set_danno_nemico(nemico *nemico_qualunque, int num) {
  nemico_qualunque->danno_nemico = num;
}

int get_classe(nemico nemico_qualunque) {
  return nemico_qualunque.classe;
}

void set_classe(nemico *nemico_qualunque, int num) {
  nemico_qualunque->classe = num;
}

int get_room(nemico nemico_qualunque) {
  return nemico_qualunque.room;
}

void set_room(nemico *nemico_qualunque, int num) {
  nemico_qualunque->room = num;
}

void carica_nemici(nemico *nemico_qualunque, FILE *savefile) {
  int num_temp;
  char *nome_temp;
  int i = 0;

  while (i<NEMICI) {
    nome_temp = calloc(30, sizeof(char));

    fgets(nome_temp, 30, savefile);
    nome_temp[strcspn(nome_temp, "\n")] = 0;
    set_nome_nemico(nemico_qualunque[i], nome_temp);

    fscanf(savefile, "%d", &num_temp);
    set_max_hp_nemico(&nemico_qualunque[i], num_temp);

    fscanf(savefile, "%d", &num_temp);
    set_current_hp_nemico(&nemico_qualunque[i], num_temp);

    fscanf(savefile, "%d", &num_temp);
    set_danno_nemico(&nemico_qualunque[i], num_temp);

    fscanf(savefile, "%d", &num_temp);
    set_classe(&nemico_qualunque[i], num_temp);

    fscanf(savefile, "%d \n", &num_temp);
    set_room(&nemico_qualunque[i], num_temp);
    i++;
  }
}

void salva_nemico(nemico nemico_qualunque, FILE *savefile) {
  int num;
  char *temp;

  fputs(get_nome_nemico(nemico_qualunque), savefile);
  fputs("\n", savefile);

  num = get_max_hp_nemico(nemico_qualunque);
  fprintf(savefile, "%d\n", num);

  num = get_current_hp_nemico(nemico_qualunque);
  fprintf(savefile, "%d\n", num);

  num = get_danno_nemico(nemico_qualunque);
  fprintf(savefile, "%d\n", num);

  num = get_classe(nemico_qualunque);
  fprintf(savefile, "%d\n", num);

  num = get_room(nemico_qualunque);
  fprintf(savefile, "%d\n", num);
}