#include "Persona.h"

#include <iostream>
using namespace std;

//costruttore specifico
Persona::Persona(string _nome, string _cognome, int _eta) : nome(_nome), cognome(_cognome), eta(_eta) {}

//costruttore di copia
Persona::Persona(const Persona& p): nome(p.nome), cognome(p.cognome), eta(p.eta) {}

//costruttore di spostamento
Persona::Persona(Persona&& p) noexcept : nome(move(p.nome)), cognome(move(p.cognome)), eta(p.eta) {p.eta=0;}

//distruttore
Persona::~Persona(){}

//funzione di stampa
void Persona::stampaInfo()const{
	cout<<cognome<<" "<<nome<<", "<<eta<<" anni"<<endl;
}

//ridefinizione operatore <<
ostream& operator << (ostream& os, const Persona& p){
	p.stampaInfo();
	return os;
}