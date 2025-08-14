#ifndef NEMICI_H
#define NEMICI_H

#define NEMICI 13

typedef struct {
  char *nome_nemico;
  int max_hp;
  int current_hp;
  int danno_nemico;
  int classe;
  int room;
} nemico;

char *get_nome_nemico(nemico nemico_qualunque);
void set_nome_nemico(nemico nemico_qualunque, char *nome);

int get_max_hp_nemico(nemico nemico_qualunque);
void set_max_hp_nemico(nemico *nemico_qualunque, int num);

int get_current_hp_nemico(nemico nemico_qualunque);
void set_current_hp_nemico(nemico *nemico_qualunque, int num);

int get_danno_nemico(nemico nemico_qualunque);
void set_danno_nemico(nemico *nemico_qualunque, int num);

int get_classe(nemico nemico_qualunque);
void set_classe(nemico *nemico_qualunque, int num);

int get_room(nemico nemico_qualunque);
void set_room(nemico *nemico_qualunque, int num);

void carica_nemici(nemico *nemico_qualunque, FILE *savefile);
void salva_nemico(nemico nemico_qualunque, FILE *savefile);

#endif