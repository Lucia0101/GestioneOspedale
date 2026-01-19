#include "Medico.h"
#include "Operazione.h"
#include "Paziente.h"
#include <iostream>
using namespace std;

Medico::Medico(string _nome,string _cognome,int _eta,string _codID,string _specializzazione):
Persona(_nome, _cognome, _eta),codID(_codID),specializzazione(_specializzazione){ }

void Medico::stampaInfo()const{
	 cout<<"MEDICO: "<<nome<<" "<<cognome 
        <<", codID ("<<codID << "), "<<eta<<" anni" 
        <<", specializzazione: "<<specializzazione;
}

bool Medico::isOccupato(string data) const{
	for(const auto& d : dateOccupate) {
		if(d == data) return true;
	}
	return false;
}

void Medico::aggiungiImpegno(string data){
	dateOccupate.push_back(data);
}

void Medico::completaOperazione(Paziente* p, Operazione& op, vector<string> farmaciSupporto) {
    string curaPrincipale = op.getCura(); //medico aggiunge la cura post operatoria
    if (curaPrincipale != "") {
        p->prestiviFarmaco(curaPrincipale);
    }
    for (const string& farmaco : farmaciSupporto) { //medico aggiunge farmaci
        p->prestiviFarmaco(farmaco);
    }
}
