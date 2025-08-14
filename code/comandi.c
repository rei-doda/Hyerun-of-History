#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utente.h"
#include "stanze.h"

void dividi_stringa(char **sottostringhe, char* parola, char t) {
  int i = 0;
  int current = 0;
  int j = 0;
  sottostringhe[current] = (char*)calloc(sizeof(char), 10);
  int stop = 0;
  while(!stop) {
    if (parola[i] != t && parola[i] != '\0'){
      sottostringhe[current][j] = parola[i];
      j++;
    } else {
      //printf("%s\n",substrings[current]);
      current++;
      j = 0;
      sottostringhe[current] = (char*)calloc(sizeof(char), 10);
      stop = 1;
    }
    i++;
  }
  j = 0;
  while(parola[i] != '\0') {
    
    sottostringhe[current][j] =  parola[i];
    //printf("%c",substrings[current][i] );
    i++;
    j++;
  }

}

int andare_direzione(stanza stanza_qualunque, player *utente, int id_direzione) {
  int esito;
  int stanza_attuale;
  int porta;

  stanza_attuale = get_current_room(*utente);
  porta = get_una_direzione(stanza_qualunque, id_direzione);

  if (porta == 0) {
    esito = 3*id_direzione;
  }
  else if (porta == 1) {
    if (id_direzione == 0) {
      set_current_room(utente, stanza_attuale-4);
    }
    else if (id_direzione == 1) {
      set_current_room(utente, stanza_attuale+4);
    }
    else if (id_direzione == 2) {
      set_current_room(utente, stanza_attuale+1);
    }
    else if (id_direzione == 3) {
      set_current_room(utente, stanza_attuale-1);
    }
    
    esito = 3*id_direzione + 1;
  }
  else {
    esito = 3*id_direzione + 2;
  }

  return esito;
}

int aprire_direzione(stanza *stanza_qualunque, int *inventario, int id_direzione) {
  int porta;
  int esito;

  porta = get_una_direzione(*stanza_qualunque, id_direzione);

  if (porta == 0) {
    esito = id_direzione*4; //non c'è la porta
  }
  else if (porta == 1) {
    esito = id_direzione*4 + 1; //la porta è già aperta
  }
  else {
    if (inventario[9+porta]) {
      set_una_direzione(stanza_qualunque, 1, id_direzione);
      esito = id_direzione*4 + 2; //hai con te la chiave giusta
    }
    else {
      esito = id_direzione*4 + 3; //non hai con te la chiave giusta
    }
  }
  return esito;
}

int presenza_baule_cassettiera(stanza stanza_qualunque) {
  int esito = 0;
  int i = 0;
  int temp;
  
  while (i<20) {
    temp = get_oggetto_raccoglibile(stanza_qualunque, i);
    if (temp>4 && temp<9) {
      esito = 1;
      i = 20;
    }
    else if (get_oggetto_raccoglibile(stanza_qualunque, i)>8) {
      esito = 2;
    }
    i++;
  }

  return esito;
}

void aprire_baule_cassettiera(stanza *stanza_qualunque, int parser, int esito) {
  int temp;
  int i = 0;

  if (esito == 1 && parser == 6) {
    while (i<20) {
      temp = get_oggetto_raccoglibile(*stanza_qualunque, i);
      if (temp>4 && temp<9) {
        set_oggetto_raccoglibile(stanza_qualunque, temp-4, i);
      }
      i++;
    }
  }
  else if (esito == 2 && parser == 7) {
    while (i<20) {
      temp = get_oggetto_raccoglibile(*stanza_qualunque, i);
      if (temp>8) {
        set_oggetto_raccoglibile(stanza_qualunque, temp-8, i);
      }
      i++;
    }
  }
}

int prendere_oggetto(stanza *stanza_qualunque, int *inventario, int id_oggetto) {
  int esito = 0;
  int i;
  int temp;

  temp = stanza_qualunque->oggetti_raccoglibili[id_oggetto];
  if (temp < 5 && temp != 0) {
    i = temp;
    while (temp > 0) {
      inventario[id_oggetto]++;
      esito++;
      set_oggetto_raccoglibile(stanza_qualunque, temp-1, id_oggetto);
      temp--;
    }
  }

  return esito;
}

int usare_scale(player *utente) {
  int esito = 0;
  int stanza_attuale;

  stanza_attuale = get_current_room(*utente);
  if (stanza_attuale == 9) {
    set_current_room(utente, 15);
    esito = 1;
  }
  else if (stanza_attuale == 15) {
    set_current_room(utente, 9);
    esito = 1;
  }
  else if (stanza_attuale == 13) {
    set_current_room(utente, 28);
    esito = 1;
  }
  else if (stanza_attuale == 28) {
    set_current_room(utente, 13);
    esito = 1;
  }
  else if (stanza_attuale == 1) {
    set_current_room(utente, 2);
    esito = 1;
  }
  else if (stanza_attuale == 2) {
    set_current_room(utente, 1);
    esito = 1;
  }

  return esito;
}

