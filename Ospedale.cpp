#include "Ospedale.h"
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

Ospedale::Ospedale():nome(""){}

Ospedale::Ospedale(string n):nome(move(n)){	
	aggiungiReparto(make_shared<Reparto>("Cardiochirurgia",6,10,20,0,"Posizionamento pacemaker"));
	aggiungiReparto(make_shared<Reparto>("Cardiochirurgia",6,10,20,0,"Posizionamento valvola cardiaca"));
	aggiungiReparto(make_shared<Reparto>("Chirurgia estetica",6,10,20,0,"Facciale"));
	aggiungiReparto(make_shared<Reparto>("Chirurgia estetica",6,10,20,0,"Rnoplastica"));
	aggiungiReparto(make_shared<Reparto>("Chirurgia estetica",6,10,20,0,"Mastoplastica riduttiva"));
	aggiungiReparto(make_shared<Reparto>("Chirurgia estetica",6,10,20,0,"Mastoplastica additiva"));
	aggiungiReparto(make_shared<Reparto>("Chirurgia estetica",6,10,20,0,"Ginocchio"));
	aggiungiReparto(make_shared<Reparto>("Ortopedia",6,10,20,0,"Anca"));
	aggiungiReparto(make_shared<Reparto>("Ortopedia",6,10,20,0,"Braccio rotto"));
	aggiungiReparto(make_shared<Reparto>("Pediatria",6,10,20,0,"Cura bambini"));
	aggiungiReparto(make_shared<Reparto>("Geriatria",6,10,20,0,"Cura anziani"));
	
}


void Ospedale::aggiungiOperazione(const Operazione& op){
	registroOperazioni.push_back(op);
}

void Ospedale::aggiungiReparto(shared_ptr<Reparto> r){
	reparti[r->getNome()].push_back(r);
}


void Ospedale::stampaDati()const{
	cout<<"OSPEDALE: "<<nome<<endl;
	cout<<"PAZIENTI TOTALI: "<<pazienti.size()<<endl;
    cout<<"MEDICI: "<<medici.size()<<endl;
    cout<<"INFERMIERI: "<<infermieri.size()<<endl;
    cout<<"REPARTI: "<<reparti.size()<<endl;
    cout<<"OPERAZIONI REGISTRATE: "<<registroOperazioni.size()<<endl;
}

void Ospedale::stampaOperazioni()const{
	cout<<"OPERAZIONI REGISTRATE: "<<endl;
	for(const auto& o :registroOperazioni){
        o.stampaInfo();
        cout<<endl;
    }
}

void Ospedale::stampaReparti() const {
	cout<<"REPARTI DELL'OSPEDALE"<<endl;
    for (auto it=reparti.begin();it!=reparti.end();++it) {
        const string& nome=it->first;
        const vector<shared_ptr<Reparto>>& listaReparti=it->second;

        //stampo tutti i reparti con lo stesso nome
        for(size_t i=0;i<listaReparti.size();++i) {
            listaReparti[i]->stampaDettagli();
            cout<<endl;
        }
    }
}

void Ospedale::stampaPersonale(){
	cout<<endl;
	cout<<"PERSONALE MEDICO"<<endl;
    for(const auto& medico : medici){
        if(medico){
            cout<<*medico<<endl;
        }
    }
    cout<<endl;
    
    cout<<"PERSONALE INFERMIERISTICO"<<endl;
    for(const auto& infermiere : infermieri) {
        if(infermiere){
            cout<<*infermiere<<endl;
        }
    }
}

void Ospedale::stampaPazienti(){
    cout<<"PAZIENTI RICOVERATI"<<endl;
    
    if(pazienti.empty()){
        cout<<"Nessun paziente ricoverato"<<endl;
        return;
    }
    
    for(const auto& paziente : pazienti) {
        if(paziente){
            cout<<*paziente<<endl;
        }
    }
    
}

Ospedale::~Ospedale(){
    for(auto medico : medici) delete medico;
    for(auto infermiere : infermieri) delete infermiere;
    for(auto paziente : pazienti) delete paziente;
}