#include "Medico.h"
#include "Operazione.h"
#include "Paziente.h"

#include <iostream>
#include <algorithm>
using namespace std;

Medico::Medico(string _nome,string _cognome,int _eta,string _codID,string _specializzazione):
Persona(_nome, _cognome, _eta),codID(_codID),specializzazione(_specializzazione){ }

void Medico::stampaInfo()const{
	cout<<"MEDICO: "<<cognome<<" "<<nome<<", codID ("<<codID << "), "<<eta<<" anni"<<endl;
	cout<<"Specializzazione: "<<specializzazione<<endl; 
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

void Medico::completaOperazione(Paziente* p, Operazione& op, initializer_list<string> farmaciSupporto) {
    string curaPrincipale = op.getCura(); //medico aggiunge la cura post operatoria
    if (!curaPrincipale.empty()) {
        p->prestiviFarmaco(curaPrincipale);
    }
    for (const string& farmaco : farmaciSupporto) { //medico aggiunge farmaci
    	if(!farmaco.empty()){
    		p->prestiviFarmaco(farmaco);
		}
    }
}

void Medico::ordinaPerCognome(vector<Medico*>& medici) {
    sort(medici.begin(), medici.end(),
        [](Medico* a, Medico* b) {
            return a->getCognome() < b->getCognome();
        });
}
