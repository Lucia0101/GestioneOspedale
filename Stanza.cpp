#include "Stanza.h"

#include <iostream>
#include <string>
using namespace std;

//costruttore di default
Stanza::Stanza():numStanza(0),numLetti(0),reparto(""){}

//costruttore specifico
Stanza::Stanza(int stanza,int letti,string rep):numStanza(stanza),numLetti(letti), lettiOccupati(0), reparto(rep){}

//distruttore
Stanza::~Stanza(){}

//metodo per aggiunta letto se è occupato
void Stanza::occupaLetto(){
	if(!isPiena()) lettiOccupati++;
}

//metodo per togliere il letto se si libera
void Stanza::liberaLetto(){
	if(!isVuota()) lettiOccupati--;
}

//stampa dettagli della stanza
void Stanza::stampaDettagli() const{
	cout << " | Stanza " << numStanza << " | Letti: " << lettiOccupati << "/" << numLetti;
	if (isPiena()) cout << " STANZA PIENA";
	cout << endl;
}