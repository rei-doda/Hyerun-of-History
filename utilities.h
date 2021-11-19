#ifndef UTILITIES_H
#define UTILITIES_H

void carica_da_file(FILE *savefile);
void salva_su_file(FILE *savefile);

void alloca_memoria();
void libera_memoria();

nemico *alloca_nemici(nemico *nemico_qualunque);
npc *alloca_npc(npc *npc_qualunque);
stanza *alloca_stanze(stanza *stanza_qualunque);

void metti_a_capo(char *stringa);
void carica_storia(FILE *documento);

char *carica_intro_stanza(FILE *savefile, int stanza_attuale);

#endif