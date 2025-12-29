#include "Infermiere.h"
#include <iostream>
using namespace std;

Infermiere::Infermiere(string _nome, string _cognome, int _eta , string _codID, string _reparto, string _turno):
Persona(_nome, _cognome, _eta){
	codID = _codID;
	reparto = _reparto;
	turno = _turno;
//	cout << "Infermiere creato: " << *this << endl;
}

Infermiere::~Infermiere(){
//	cout << "Infermiere distrutto: " << *this << endl;
	
}

ostream& Infermiere::stampaoperator(ostream& os) const{
	os << "INFERMIERE: " << nome << " " << cognome << ", codID: [" << codID  << "], di " << eta << " anni, lavora in: " << reparto << ". Turno: " << turno;
	return os;
}


ostream& operator << (ostream& os, const Infermiere& i){
	return i.stampaoperator(os); 
}
