#ifndef COMBATTIMENTO_H
#define COMBATTIMENTO_H


void attaccare(player *utente, nemico *nemico_qualunque ,int id_temp);
void schivare(player *utente, nemico *nemico_qualunque ,int id_temp);
void parare(player *utente, nemico *nemico_qualunque ,int id_temp);

int usare_pozione(player *utente);
int mossa_mostro();
void penitenza(player *utente, nemico *nemico_qualunque, int id_temp);
int riesci_a_schivare(nemico nemico_qualunque);


#endif
