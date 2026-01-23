#include "Ospedale.h"
#include "Persona.h"
#include "Stampa.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <mutex>
#include <thread>
#include <atomic>
using namespace std;

Ospedale::Ospedale():nome(""){}

Ospedale::Ospedale(string n):nome(move(n)){	
	aggiungiReparto(make_shared<Reparto>("Cardiochirurgia",6,10,10,2,"Posizionamento pacemaker e Posizionamento valvola cardiaca"));
	aggiungiReparto(make_shared<Reparto>("Chirurgia Estetica",6,10,10,2,"Facciale, Rinoplastica, Mastoplastica riduttiva e additiva"));
	aggiungiReparto(make_shared<Reparto>("Ortopedia",6,10,10,2,"Ginocchio, Anca e Braccio rotto"));
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
	cout<<"OSPEDALE: "<<nome<<endl<<endl;
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
	cout<<"======== OPERAZIONI REGISTRATE ========"<<endl;
	for(const auto& o :registroOperazioni){
        o.stampaInfo();
        cout<<endl;
    }
}

void Ospedale::stampaReparti() const {
	cout<<"======== REPARTI DELL'OSPEDALE ========"<<endl;
    for (auto it=reparti.begin();it!=reparti.end();++it) {
        const string& nome=it->first;
        const vector<shared_ptr<Reparto>>& listaReparti=it->second;

        for(size_t i=0;i<listaReparti.size();++i) {
            listaReparti[i]->stampaDettagli();
            cout<<endl;
        }
    }
}

void Ospedale::stampaMediciOrdinati(){
	stampaPerCognome(medici, "");
}

void Ospedale::stampaInfermieriOrdinati(){
	stampaPerCognome(infermieri, "");
}

void Ospedale::stampaPazientiOrdinati(){
	stampaPerCognome(pazienti, "");
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

    cout << endl;
    cout << "========== SITUAZIONE OSPEDALE (Oggi: " << oggiStr << ") ==========" << endl;
    cout << endl;

    // SOLO PAZIENTI RICOVERATI OGGI
    cout << "*PAZIENTI RICOVERATI*" << endl;
    bool trovatiRicoverati = false;
    
    for (auto p : pazienti) {
        int dRic = dataToIn(p->getDataRicovero());
        int dDim = dataToIn(p->getDataDimissioni());
        
        // Paziente è ricoverato se:
        // 1. Data ricovero <= oggi
        // 2. Data ricovero non è 0 (valida)
        // 3. Data dimissioni > oggi OPPURE data dimissioni non è ancora impostata (0 o "---")
        if (dRic <= oggi && dRic != 0 && (dDim > oggi || dDim == 0 || p->getDataDimissioni() == "---")) {
            // Determina il reparto finale in base all'età (logica inline)
            string repartoOriginale = p->getReparto();
            string repartoFinale = repartoOriginale;
            
            if (p->getEta() < 18) {
                repartoFinale = "Pediatria";
            } else if (p->getEta() >= 65) {
                repartoFinale = "Geriatria";
            }
            
            // Assegna stanza se non assegnata
            if (p->getNumStanza() == -1) {
                try {
                    auto rep = const_cast<Ospedale*>(this)->getReparto(repartoFinale);
                    if (rep) {
                        int stanzaAssegnata;
                        if (rep->assegnaLetto(stanzaAssegnata)) {
                            const_cast<Paziente*>(p)->setStanza(stanzaAssegnata);
                        }
                    }
                } catch (const exception& e) {
                    // Reparto non trovato, continua comunque
                }
            }
            
            // Stampa info paziente
            cout << "PAZIENTE: " << p->getCognome() << " " << p->getNome() 
                 << ", CF: [" << p->getCF() << "], " << p->getEta() << " anni" << endl;
            cout << "Data ricovero: dal " << p->getDataRicovero() 
                 << " al " << p->getDataDimissioni() << endl;
            cout << "Reparto: " << repartoFinale;
            
            // Se diverso dal reparto dell'operazione
            if (repartoFinale != repartoOriginale) {
                cout << " | (Operazione in: " << repartoOriginale << ")";
            }
            cout << endl;
            
            if (p->getNumStanza() != -1) {
                cout << "Stanza: " << p->getNumStanza() << endl;
            }
            
            cout << "Allergie: " << p->getAllergie() << endl;
            
            // Cerca informazioni sull'operazione
            bool operazioneTrovata = false;
            for(const auto& op : registroOperazioni) {
                if(op.getCFPaziente() == p->getCF()) {
                    int dataOp = dataToIn(op.getData());
                    if(dataOp <= oggi) {
                        // Operazione già effettuata
                        cout << "Operazione: " << op.getTipo() << endl;
                        cout << "Data operazione: " << op.getData() << endl;
                        cout << "Esito: " << op.getEsito() << endl;
                    } else {
                        // Operazione programmata
                        cout << "Operazione programmata: " << op.getTipo() << endl;
                        cout << "Data prevista: " << op.getData() << endl;
                    }
                    operazioneTrovata = true;
                    break;
                }
            }
            
            if(!operazioneTrovata) {
                cout << "Nessuna operazione registrata." << endl;
            }
            
            // Stampa terapie se presenti
            p->stampaTerapie();
            
            cout << endl;
            trovatiRicoverati = true;
        }
    }
    
    if (!trovatiRicoverati) {
        cout << "Nessun paziente attualmente ricoverato." << endl;
    }

    // PAZIENTI DIMESSI OGGI
    cout << endl;
    cout << "*PAZIENTI DIMESSI OGGI (" << oggiStr << ")*" << endl;
    bool trovatiDimessi = false;
    
    for (auto p : pazienti) {
        int dDim = dataToIn(p->getDataDimissioni());
        
        // Paziente dimesso oggi se:
        // 1. Data dimissioni == oggi
        // 2. Data dimissioni non è 0 (valida)
        if (dDim == oggi && dDim != 0) {
            string infoOp = "Nessuna operazione registrata";
            string esitoOp = "";
            
            for(const auto& op : registroOperazioni) {
                if(op.getCFPaziente() == p->getCF()) {
                    infoOp = "Operazione: " + op.getTipo() + " (Data: " + op.getData() + ")";
                    esitoOp = op.getEsito();
                    break;
                }
            }
            
            cout << "PAZIENTE: " << p->getCognome() << " " << p->getNome() 
                 << ", CF: [" << p->getCF() << "]" << endl;
            cout << "Ricovero: " << p->getDataRicovero() 
                 << " | Dimissione: " << p->getDataDimissioni() << endl;
            cout << infoOp << endl;
            
            if (!esitoOp.empty()) {
                cout << "Esito: " << esitoOp << endl;
            }
            
            cout << endl;
            trovatiDimessi = true;
        }
    }
    
    if (!trovatiDimessi) {
        cout << "Nessun paziente dimesso oggi." << endl;
    }
    
    cout << "=============================================" << endl;
}


Paziente& Ospedale::findCFpaziente(const string& cf){
	auto it = find_if(pazienti.begin(), pazienti.end(),
        [&cf](Paziente* p) {
            return p->getCF() == cf;
        });
    
    if(it == pazienti.end()) {
        throw runtime_error("Paziente con CF '" + cf + "' non trovato!");
    }
    
    return **it; //dereferenzia due volte: iteratore, puntatore, riferimetno
}


Ospedale::~Ospedale(){
    for(auto medico : medici) delete medico;
    for(auto infermiere : infermieri) delete infermiere;
    for(auto paziente : pazienti) delete paziente;
}

Medico* Ospedale::findMedicoByID(const string& id) {
    for (auto m : medici) {
        if (m->getID() == id) { 
            return m;
        }
    }
    return nullptr;
}