#ifndef UTENTE_H
#define UTENTE_H


typedef struct {
  int max_hp;
  int current_hp;
  int armor_type;
  int sword_type;
  int danni_inflitti;
  int current_room;
} player;

int get_max_hp_utente(player utente);
void set_max_hp_utente(player *utente, int num);

int get_current_hp_utente(player utente);
void set_current_hp_utente(player *utente, int num);

int get_armor_type(player utente);
void set_armor_type(player *utente, int num);

int get_sword_type(player utente);
void set_sword_type(player *utente, int num);

int get_danni_inflitti(player utente);
void set_danni_inflitti(player *utente, int num);

int get_current_room(player utente);
void set_current_room(player *utente, int num);

void carica_utente(player *utente, FILE *savefile);
void salva_utente(player utente, FILE *savefile);

void prendere_spada(player *utente, int spada);

#endif