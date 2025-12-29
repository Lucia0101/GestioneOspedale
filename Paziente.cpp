#include "Paziente.h"
#include <iostream>
using namespace std;

Paziente::Paziente(string _nome,string _cognome,int _eta ,string _cf,string _allergie,string _reparto,string _dataRicovero,string _dataDimissioni,int _numStanza):
Persona(_nome,_cognome,_eta){
	cf=_cf;
	allergie=_allergie;
	reparto=_reparto;
	dataRicovero=_dataRicovero;
	dataDimissioni= _dataDimissioni;
	numStanza=_numStanza;
}

void Paziente::stampaInfo()const{
	cout<<"PAZIENTE: "<<nome<<" "<<cognome 
         <<", CF: ["<<cf<<"], "<<eta<<" anni" 
         <<", ricoverato in "<<reparto 
         <<" dal "<<dataRicovero<<" al "<<dataDimissioni 
         <<", stanza "<<numStanza 
         <<", allergie: "<<allergie;
}