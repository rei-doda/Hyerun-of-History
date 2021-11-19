#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "nemici.h"
#include "utente.h"
#include "combattimento.h"

//attacare    
void attaccare(player *utente, nemico *nemico_qualunque ,int id_temp){
  int vita_temp;
  
  int danno=get_danno_nemico(*nemico_qualunque);
  int danno_ply=get_danni_inflitti(*utente);

  if (id_temp==0){
    vita_temp = get_current_hp_utente(*utente);
    set_current_hp_utente(utente, vita_temp);
    }
  else if (id_temp==1){
    vita_temp = get_current_hp_nemico(*nemico_qualunque);
    set_current_hp_nemico(nemico_qualunque,vita_temp);
  }
}

void schivare(player *utente, nemico *nemico_qualunque ,int id_temp){
int vita_temp;
  //utente schiva nemico 
  if (id_temp==0){
    vita_temp = get_current_hp_utente(*utente);
    set_current_hp_utente(utente, vita_temp);
    
  }
  //nemico schiva utente
  else if (id_temp==1){
    vita_temp = get_current_hp_nemico(*nemico_qualunque);
    set_current_hp_nemico(nemico_qualunque, vita_temp);
  }
  
}

//Parare
void parare(player *utente, nemico *nemico_qualunque ,int id_temp){
int vita_temp;
int danno; 
  //utent para enemico 
  if (id_temp==0){
    danno = get_danno_nemico(*nemico_qualunque)/2;
    vita_temp = get_current_hp_utente(*utente);
    vita_temp = vita_temp - danno;
    set_current_hp_utente(utente, vita_temp);
  }
  //nemico para utente
  else if (id_temp==1){
    danno = get_danni_inflitti(*utente)/2;
    vita_temp = get_current_hp_nemico(*nemico_qualunque);
    vita_temp = vita_temp - danno;
    set_current_hp_nemico(nemico_qualunque, vita_temp);
  }
}

//Usare Posizioni
int usare_pozione(player *utente){
  int vita_temp;
  int vita_temp1;
  int esito;
    vita_temp1 = get_current_hp_utente(*utente);
    vita_temp = get_current_hp_utente(*utente);
    vita_temp = vita_temp + get_max_hp_utente(*utente)/2;
      if(vita_temp>get_max_hp_utente(*utente)){
        vita_temp=get_max_hp_utente(*utente);
      }
  esito= vita_temp-vita_temp1;
  set_current_hp_utente(utente, vita_temp);
  return esito;
}

//mossa mostro
int mossa_mostro(){
  int a;

	srand(time(0));
  a=rand()%3; 
	return a;
}


void penitenza(player *utente, nemico *nemico_qualunque, int id_temp){
 
  int vita_temp;
  int danno=get_danno_nemico(*nemico_qualunque);
  int danno_ply=get_danni_inflitti(*utente);
  //utente->nemico 
  if (id_temp==0){
    vita_temp = get_current_hp_utente(*utente);
    vita_temp = vita_temp - danno;
    set_current_hp_utente(utente, vita_temp);
    
    }
  else if (id_temp==1){
    vita_temp = get_current_hp_nemico(*nemico_qualunque);
    vita_temp = vita_temp - danno_ply;
    set_current_hp_nemico(nemico_qualunque,vita_temp);
    
  }
  
}

int riesci_a_schivare(nemico nemico_qualunque) {
  int esito;
  int a;

	srand(time(0));
  a=rand()%17;

  if ( a < get_danno_nemico(nemico_qualunque)){
    esito = 0; 
  }
	else if (a > get_danno_nemico(nemico_qualunque)) { 
    esito = 1; //riesci a schivare
  }
  else if (a == get_danno_nemico(nemico_qualunque)) {
    esito = 2;
  }


  return esito;
}