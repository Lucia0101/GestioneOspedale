#include "Persona.h"
#include <iostream>
using namespace std;

Persona::Persona(string _nome, string _cognome, int _eta){
	nome = _nome;
	cognome = _cognome;
	eta = _eta;
		//cout << "Persona creata: " << *this << endl;

}


Persona::~Persona(){
//	cout << "Persona distrutta: " << *this << endl;
}

ostream& Persona::stampaoperator(ostream& os) const{
	os << " " << nome << " " << cognome << " di eta': " << eta;
	return os;
}

ostream& operator << (ostream& os, const Persona& p){
	return p.stampaoperator(os);
}









