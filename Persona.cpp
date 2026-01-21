#include "Persona.h"

#include <iostream>
using namespace std;

Persona::Persona(string _nome,string _cognome,int _eta){
	nome=_nome;
	cognome=_cognome;
	eta=_eta;
}

void Persona::stampaInfo()const{
	cout<<cognome<<" "<<nome<<", "<<eta<<" anni"<<endl;
}

ostream& operator << (ostream& os, const Persona& p){
	p.stampaInfo();
	return os;
}