#ifndef STANZE_H
#define STANZE_H

#define STANZE 38

typedef struct {
  char *nome_stanza;
  int *direzioni;
  int npc;
  int nemici;
  char *dipinto;
  char *libro;
  int *oggetti_raccoglibili;
} stanza;

char *get_nome_stanza(stanza stanza_qualunque);
void set_nome_stanza(stanza stanza_qualunque, char *nome);

int *get_direzioni(stanza stanza_qualunque);
void set_direzioni(stanza stanza_qualunque, int *direzione);

int get_una_direzione(stanza stanza_qualunque, int pos);
void set_una_direzione(stanza *stanza_qualunque, int direzione, int pos);

int get_npc(stanza stanza_qualunque);
void set_npc(stanza *stanza_qualunque, int id_npc);

int get_nemici(stanza stanza_qualunque);
void set_nemici(stanza *stanza_qualunque, int id_nemici);

char *get_dipinto(stanza stanza_qualunque);
void set_dipinto(stanza stanza_qualunque, char *dipinto);

char *get_libro(stanza stanza_qualunque);
void set_libro(stanza stanza_qualunque, char *libro);

int *get_oggetti_raccoglibili(stanza stanza_qualunque);
void set_oggetti_raccoglibili(stanza stanza_qualunque, int *oggetti);

int get_oggetto_raccoglibile(stanza stanza_qualunque, int id_oggetto);
void set_oggetto_raccoglibile(stanza *stanza_qualunque, int num_ogg, int id_oggetto);

void carica_stanza(stanza *stanza_qualunque, FILE *savefile);
void salva_stanza(stanza stanza_qualunque, FILE *savefile);

#endif