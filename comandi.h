#ifndef COMANDI_H
#define COMANDI_H

char comandi_primario[14][15] = {"andare", "guardare", "aprire", "prendere", "usare", "parlare", "leggere", "salvare", "continuare", "uscire", "comandi", "inventario", "si", "no"};

char comandi_secondario[34][20] = {"nord", "sud", "est", "ovest",  "stanza", "dipinti", "baule", "cassettiera", "pozione", "elmo di bronzo", "elmo di ferro", "busto di bronzo", "busto di ferro", "gambali di bronzo", "gambali di ferro", "spada di bronzo", "spada di ferro", "spada di platino", "monete", "chiave a E", "chiave ornata", "chiave semplice", "pergamena1", "pergamena2", "pergamena3", "vestito", "scarpe", "Torgard", "scale", "fabbro", "alchimista", "dama", "re", "libro"};

char comandi_combattimento[4][15] = {"schivare", "parare", "attaccare", "usare pozione"};

char esito_andare_direzioni[12][36] = {"Non c'è una porta a nord.", "Sei andato a nord.", "La porta a nord è chiusa a chiave.", "Non c'è una porta a sud.", "Sei andato a sud.", "La porta a sud è chiusa a chiave.", "Non c'è una porta a est.", "Sei andato a est.", "La porta a est è chiusa a chiave.", "Non c'è una porta a ovest.",  "Sei andato a ovest.",  "La porta a ovest è chiusa a chiave."};

char esito_aprire_direzioni[16][36] = {"Non c'è una porta a nord.", "La porta a nord è già aperta.", "Hai aperto la porta a nord.", "Non hai con te la chiave giusta.", "Non c'è una porta a sud.", "La porta a sud è già aperta.", "Hai aperto la porta a sud.", "Non hai con te la chiave giusta.", "Non c'è una porta a est.", "La porta a est è già aperta.", "Hai aperto la porta a est.", "Non hai con te la chiave giusta.", "Non c'è una porta a ovest.", "La porta a ovest è già aperta.", "Hai aperto la porta a ovest.", "Non hai con te la chiave giusta."};

char esito_aprire_baule_cassettiera[4][40] = {"Non c'è un baule nella stanza.", "Non c'è una cassettiera nella stanza.", "Hai aperto il baule. ", "Hai aperto la cassiera."};

char conversazioni_npc[6][1000] = {"FABBRO: Salve, sono Ferthdoc, sono un fabbro che aiuta i pazzi che osano varcare le porte di questo inferno. Attraverso il mio lavoro, dietro compenso, potrai migliorare la tua ferraglia. Se col tuo occhio da segugio troverai le parti di armature nel castello, io le renderò utilizzabili. Ti consiglio di trovarle, giovane pazzo, ci sono bestie mostruose in questo castello! Ma nel frattempo, vuoi fare acquisti?" , "FABBRO: Oh sei ancora vivo, amico mio! Sei tornato per fare affari?" , "ALCHIMISTA: Salve, sono Ley’isum, sono un alchimista e vendo pozioni curative. Piccolo guerriero, con solo un piccolo dono monetario potrai ricevere la mia saggezza sotto forma di elisir curativo. Ti consiglio di acquistarne qualcuna, ci sono bestie mostruose in questo castello! Vuoi comprarne una?" , "ALCHIMISTA: Salve mio piccolo amico, le mie pozioni sono sempre qui. La mia commissione è di 2 monete, vuoi procedere all’acquisto?" , "DAMA: Ti ringrazio per avermi salvata, mio eroe, quegli orribili goblin mi hanno rapita. Mi hanno portata in questo orribile castello e mi hanno denudata e dio solo sa cosa avevano in mente di farmi dopo. Per favore non guardarmi. Potresti per favore portarmi dei vestiti? Ti ricompenserò." , "RE: Tu chi sei? Un ladro venuto a saccheggiare ciò che rimane nel castello o un eroe pronto a sacrificarsi per finire la battaglia che iniziai tanto tempo fa? Sei un ladro, hai detto? Come osi girovagare per il mio castello! Però se sei arrivato fin qui vuol dire che non sei da buttare, furfante. Ascoltami bene e se farai ciò che ti dico di renderò ricco. Trova le pergamene sparse per questo piano e portamele."};


void dividi_stringa(char **sottostringhe, char* parola, char t);

int andare_direzione(stanza stanza_qualunque, player *utente, int id_direzione);

int aprire_direzione(stanza *stanza_qualunque, int *inventario, int id_direzione);

int presenza_baule_cassettiera(stanza stanza_qualunque);
void aprire_baule_cassettiera(stanza *stanza_qualunque, int parser, int esito);

int prendere_oggetto(stanza *stanza_qualunque, int *inventario, int id_oggetto);

int usare_scale(player *utente);


#endif