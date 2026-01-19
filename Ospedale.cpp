#include "Ospedale.h"
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

Ospedale::Ospedale():nome(""){}

Ospedale::Ospedale(string n):nome(move(n)){	
	aggiungiReparto(make_shared<Reparto>("Cardiochirurgia",6,10,10,2,"Posizionamento pacemaker e Posizionamento valvola cardiaca"));
//	aggiungiReparto(make_shared<Reparto>("Cardiochirurgia",6,10,10,2,"Posizionamento valvola cardiaca"));
	aggiungiReparto(make_shared<Reparto>("Chirurgia Estetica",6,10,10,2,"Facciale, Rnoplastica, Mastoplastica riduttiva e additiva"));
//	aggiungiReparto(make_shared<Reparto>("Chirurgia estetica",6,10,10,2,"Rnoplastica"));
//	aggiungiReparto(make_shared<Reparto>("Chirurgia estetica",6,10,10,2,"Mastoplastica riduttiva"));
//	aggiungiReparto(make_shared<Reparto>("Chirurgia estetica",6,10,10,2,"Mastoplastica additiva"));
	aggiungiReparto(make_shared<Reparto>("Ortopedia",6,10,10,2,"Ginocchio, Anca e Braccio rotto"));
//	aggiungiReparto(make_shared<Reparto>("Ortopedia",6,10,10,2,"Anca"));
//	aggiungiReparto(make_shared<Reparto>("Ortopedia",6,10,10,2,"Braccio rotto"));
	aggiungiReparto(make_shared<Reparto>("Pediatria",6,10,10,2,"Cura bambini"));
	aggiungiReparto(make_shared<Reparto>("Geriatria",6,10,10,2,"Cura anziani"));
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

shared_ptr<Reparto> Ospedale::getReparto(string nomeReparto) {
    if (reparti.count(nomeReparto) > 0 && !reparti[nomeReparto].empty()) {
        return reparti[nomeReparto][0]; 
    }
    throw runtime_error("Il reparto '" + nomeReparto + "' non esiste in questo ospedale!");
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

//(formato AAAAMMGG)
int dataToIn(string data) {
    if (data == "" || data == "---" || data.length() < 10) return 0;
    int gg = stoi(data.substr(0, 2));
    int mm = stoi(data.substr(3, 2));
    int aaaa = stoi(data.substr(6, 4));
    return aaaa * 10000 + mm * 100 + gg;
}

void Ospedale::stampaPazientiFiltrati() const{
    string oggiStr = getDataAttuale(); // Prende la data di oggi: GG/MM/AAAA
    int oggi = dataToIn(oggiStr);     // Diventa AAAAMMGG
    
    for (auto const& element : reparti) {
        for (auto& r : element.second) {
            r->svuotaLetti();
        }
    }
    
    
	cout << endl;
    cout << "========== (Oggi: " << oggiStr << ") ==========" << endl;
    cout << endl;

    // 1. DA RICOVERARE
    cout << "PAZIENTI PRENOTATI" << endl;
    for (auto p : pazienti) {
        if (dataToIn(p->getDataRicovero()) > oggi) {
            p->stampaInfo();
        }
    }
    // 2. ATTUALMENTE RICOVERATI
    cout << endl;
    cout << "PAZIENTI RICOVERATI" << endl;
    for (auto p : pazienti) {
        int dRic = dataToIn(p->getDataRicovero());
        int dDim = dataToIn(p->getDataDimissioni());
        
        // Se oggi entra il paziente
        if (dRic <= oggi && dRic != 0 && (dDim > oggi || dDim == 0 || p->getDataDimissioni() == "---")) {
            auto rep = const_cast<Ospedale*>(this)->getReparto(p->getReparto());
            if(rep) {
                int stanzaTemporanea;
                rep->assegnaLetto(stanzaTemporanea); 
            }
            p->stampaInfo();
        }
    }

    // 3. DIMESSI 
    cout << endl;
    cout << "PAZIENTI DIMESSI" << endl;
    for (auto p : pazienti) {
        if (dataToIn(p->getDataDimissioni()) <= oggi && dataToIn(p->getDataDimissioni()) != 0) {
            string infoOp = "Nessuna operazione registrata";
            for(const auto& op : registroOperazioni) {
                // Confrontiamo i Codici Fiscali
                // Nota: Assicurati che Operazione abbia getCFPaziente() 
                // e Paziente abbia getCF() (o accedi a p->getCF())
                if(op.getCFPaziente() == p->getCF()) {
                    infoOp = "Intervento: " + op.getTipo() + " (Data op: " + op.getData() + ")";
                    break;
                }
            }
            p->stampaPerDimessi(infoOp);
        }
    }
}
Ospedale::~Ospedale(){
    for(auto medico : medici) delete medico;
    for(auto infermiere : infermieri) delete infermiere;
    for(auto paziente : pazienti) delete paziente;
}
