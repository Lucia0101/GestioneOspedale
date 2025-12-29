#include "Paziente.h"
#include <iostream>
using namespace std;

Paziente::Paziente(string _nome, string _cognome, int _eta , string _CF, string _allergie, string _reparto, string _dataRicovero, string _dataDimissioni, int _numStanza):
Persona(_nome, _cognome, _eta){
	CF = _CF;
	allergie = _allergie;
	reparto = _reparto;
	dataRicovero = _dataRicovero;
	dataDimissioni =  _dataDimissioni;
	numStanza = _numStanza;
//	cout << "Paziente creato: " << *this << endl;
}

Paziente::~Paziente(){
//	cout << "Paziente distrutto: " << *this << endl;
	
}

ostream& Paziente::stampaoperator(ostream& os) const{
	os << "PAZIENTE: " << nome << " " << cognome << ", CF: [" << CF  << "], di " << eta << " anni, ricoverato in " << reparto << " dal " << dataRicovero << " al " << dataDimissioni << "."<< endl;
	cout <<"Numero stanza: " << numStanza << ". Allergie: " << allergie;
	return os;
}


ostream& operator << (ostream& os, const Paziente& p){
	return p.stampaoperator(os); 
}
