#include "Medico.h"
#include <iostream>
using namespace std;

Medico::Medico(string _nome, string _cognome, int _eta , string _codID, string _specializzazione):
Persona(_nome, _cognome, _eta){
	codID = _codID;
	specializzazione = _specializzazione;
	//cout << "Medico creato: " << *this << endl;
}

Medico::~Medico(){
//	cout << "Medico distrutto: " << *this << endl;
	
}

ostream& Medico::stampaoperator(ostream& os) const{
	os << "MEDICO: " << nome << " " << cognome << ", codID [" << codID  << "], di " << eta << " anni, con specializzazione in " << specializzazione;
	return os;
}


ostream& operator << (ostream& os, const Medico& m){
	return m.stampaoperator(os); 
}
