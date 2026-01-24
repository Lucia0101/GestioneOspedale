#include "Medico.h"
#include "Operazione.h"
#include "Paziente.h"

#include <iostream>
#include <algorithm>
using namespace std;

//costruttore specifico
Medico::Medico(string _nome,string _cognome,int _eta,string _codID,string _specializzazione): 
	Persona(_nome, _cognome, _eta),codID(_codID),specializzazione(_specializzazione){}

//distruttore
Medico::~Medico(){}

//metodo per la stampa dettagli del medico
void Medico::stampaInfo()const{
	cout<<"MEDICO: "<<cognome<<" "<<nome<<", codID ("<<codID << "), "<<eta<<" anni"<<endl;
	cout<<"Specializzazione: "<<specializzazione<<endl; 
}

//metodo per aggiunta operazione al medico
void Medico::aggiungiImpegno(string data){
	dateOccupate.push_back(data);
}

//metodo booleano per verificare se il medico è già occupato un certo giorno
bool Medico::isOccupato(string data) const{
	for(const auto& d : dateOccupate) {
		if(d == data) return true;
	}
	return false;
}

//metodo per aggiunta cura post operatoria e farmaci
void Medico::completaOperazione(Paziente* p, Operazione& op, initializer_list<string> farmaciSupporto) {
	//il medico aggiunge la cura post operatoria
    string curaPrincipale = op.getCura(); 
    if (!curaPrincipale.empty()) {
        p->prestiviFarmaco(curaPrincipale);
    }
    
    //il medico aggiunge farmaci
    for (const string& farmaco : farmaciSupporto) { 
    	if(!farmaco.empty()){
    		p->prestiviFarmaco(farmaco);
		}
    }
}

//metodo per ordinamento per cognome dei medici
void Medico::ordinaPerCognome(vector<Medico*>& medici) {
    sort(medici.begin(), medici.end(),
        [](Medico* a, Medico* b) {
            return a->getCognome() < b->getCognome();
        });
}