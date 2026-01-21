#include "Stanza.h"

#include <iostream>
#include <string>
using namespace std;

Stanza::Stanza():numStanza(0),numLetti(0),reparto(""){}

Stanza::Stanza(int stanza,int letti,string rep):numStanza(stanza),numLetti(letti), lettiOccupati(0), reparto(rep){}

void Stanza::occupaLetto(){
	if(!isPiena()) lettiOccupati++;
}

void Stanza::liberaLetto(){
	if(!isVuota()) lettiOccupati--;
}

void Stanza::stampaDettagli() const{
	cout << " | Stanza " << numStanza << " | Letti: " << lettiOccupati << "/" << numLetti;
	if (isPiena()) cout << " STANZA PIENA";
	cout << endl;
}
