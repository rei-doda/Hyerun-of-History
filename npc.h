#ifndef NPC_H
#define NPC_H

#define NPC 4

typedef struct {
  char *nome_npc;
  int stato_quest;
} npc;

char *get_nome_npc(npc npc_qualunque);
void set_nome_npc(npc npc_qualunque, char *nome);

int get_stato_quest(npc npc_qualunque);
void set_stato_quest(npc *npc_qualunque, int num);

void carica_npc(npc *npc_qualunque, FILE *savefile);
void salva_npc(npc npc_qualunque, FILE *savefile);

int compara_esito_npc(int npc, int stato_parser);

int controllo_armatura(player utente, int *inventario);
int controllo_monete(int id_npc, int *inventario);
int parlare_npc(npc *npc_qualunque, int id_npc);

int acquistare_oggetto(player *utente, int *inventario, int id_npc);


int controllo_vestiti(int *inventario);
int controllo_pergamene(int *inventario);
int controllo_stato_quest(int *inventario, int id_npc);

#endif