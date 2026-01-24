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

//costruttore di default
Ospedale::Ospedale():nome(""){}

//costruttore specifico
Ospedale::Ospedale(string n):nome(move(n)){	
	aggiungiReparto(make_shared<Reparto>("Cardiochirurgia",6,10,10,2,"Posizionamento pacemaker e Posizionamento valvola cardiaca"));
	aggiungiReparto(make_shared<Reparto>("Chirurgia Estetica",6,10,10,2,"Facciale, Rinoplastica, Mastoplastica riduttiva e additiva"));
	aggiungiReparto(make_shared<Reparto>("Ortopedia",6,10,10,2,"Ginocchio, Anca e Braccio rotto"));
	aggiungiReparto(make_shared<Reparto>("Pediatria",6,10,10,2,"Cura bambini"));
	aggiungiReparto(make_shared<Reparto>("Geriatria",6,10,10,2,"Cura anziani"));
}

//distruttore
Ospedale::~Ospedale(){
    for(auto medico : medici) delete medico;
    for(auto infermiere : infermieri) delete infermiere;
    for(auto paziente : pazienti) delete paziente;
}

//cerca il nome del reparto e lo restituisce
shared_ptr<Reparto> Ospedale::getReparto(string nomeReparto) {
    if (reparti.count(nomeReparto) > 0 && !reparti[nomeReparto].empty()) {
        return reparti[nomeReparto][0]; 
    }
    throw runtime_error("Il reparto '" + nomeReparto + "' non esiste in questo ospedale!");
}

//metodo che ritorna i pazienti con una prenotazione
list<Paziente*> Ospedale::getPazientiProgrammati() const {
    list<Paziente*> pazientiProgrammati;
    string oggiStr = getDataAttuale();
    int oggi = dataToIn(oggiStr);
    
    for (const auto& p : pazienti) {
        int dIn = dataToIn(p->getDataRicovero());
        //se la data di inizio è dopo oggi, il paziente è "programmato"
        if (dIn > oggi) {
            pazientiProgrammati.push_back(p);
        }
    }
    
    return pazientiProgrammati;
}

//metodo che ritorna i pazienti dimessi
list<Paziente*> Ospedale::getPazientiDimessi() const {
    list<Paziente*> pazientiDimessi;
    string oggiStr = getDataAttuale();
    int oggi = dataToIn(oggiStr);
    
    for (const auto& p : pazienti) {
        int dOut = dataToIn(p->getDataDimissioni());
        //un paziente è dimesso se la data fine è passata ed è valida 
        if (dOut != 0 && dOut < oggi) {
            pazientiDimessi.push_back(p);
        }
    }
    
    return pazientiDimessi;
}

//metodo per aggiungere un reparto
void Ospedale::aggiungiReparto(shared_ptr<Reparto> r){
	reparti[r->getNome()].push_back(r);
}

//metodo per aggiungere un'operazione
void Ospedale::aggiungiOperazione(const Operazione& op){
	registroOperazioni.push_back(op);
}

//metodo per stampa dati dell'ospedale
void Ospedale::stampaDati()const{
	cout<<"OSPEDALE: "<<nome<<endl<<endl;
	cout<<"PAZIENTI TOTALI: "<<pazienti.size()<<endl;
    cout<<"MEDICI: "<<medici.size()<<endl;
    cout<<"INFERMIERI: "<<infermieri.size()<<endl;
    cout<<"REPARTI: "<<reparti.size()<<endl;
    cout<<"OPERAZIONI REGISTRATE: "<<registroOperazioni.size()<<endl;
}

//metodo che stampa i reparti
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

//metodo che stampa le operazioni
void Ospedale::stampaOperazioni()const{
	cout<<"======== OPERAZIONI REGISTRATE ========"<<endl;
	for(const auto& o :registroOperazioni){
        o.stampaInfo();
        cout<<endl;
    }
}

//metodo che stampa in ordine per cognome i medici
void Ospedale::stampaMediciOrdinati(){
	stampaPerCognome(medici, "");
}

//metodo che stampa in ordine per cognome gli infermieri
void Ospedale::stampaInfermieriOrdinati(){
	stampaPerCognome(infermieri, "");
}

//metodo che stampa in ordine per cognome i pazienti
void Ospedale::stampaPazientiOrdinati(){
	stampaPerCognome(pazienti, "");
}

//metodo per ottenere la data di oggi
int dataToIn(string data) {
    if (data == "" || data == "---" || data.length() < 10) return 0;
    int gg = stoi(data.substr(0, 2));
    int mm = stoi(data.substr(3, 2));
    int aaaa = stoi(data.substr(6, 4));
    return aaaa * 10000 + mm * 100 + gg;
}

//stampa dei pazienti in base a varie condizioni
void Ospedale::stampaPazientiFiltrati() const{
	//prende la data di oggi
    string oggiStr = getDataAttuale(); 
    //converte la data in aaaammgg
    int oggi = dataToIn(oggiStr);

    cout << endl;
    cout << "========== SITUAZIONE OSPEDALE (Oggi: " << oggiStr << ") ==========" << endl;
    cout << endl;

	//pazienti ricovertati oggi
    cout << "---- PAZIENTI RICOVERATI ----" << endl;
    bool trovatiRicoverati = false;
    
    for (auto p : pazienti) {
        int dRic = dataToIn(p->getDataRicovero());
        int dDim = dataToIn(p->getDataDimissioni());
        
        //paziente è ricoverato se:
        if (dRic <= oggi && dRic != 0 && (dDim > oggi || dDim == 0 || p->getDataDimissioni() == "---")) {
            //determina il reparto finale in base all'età
            string repartoOriginale = p->getReparto();
            string repartoFinale = repartoOriginale;
            
            if (p->getEta() < 18) {
                repartoFinale = "Pediatria";
            } else if (p->getEta() >= 65) {
                repartoFinale = "Geriatria";
            }
            
            //assegna la stanza se non è assegnata
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
                    //reparto non trovato; continua comunque
                }
            }
            
            //stampa informazioni del paziente
            cout << "PAZIENTE: " << p->getCognome() << " " << p->getNome() 
                 << ", CF: [" << p->getCF() << "], " << p->getEta() << " anni" << endl;
            cout << "Data ricovero: dal " << p->getDataRicovero() 
                 << " al " << p->getDataDimissioni() << endl;
            cout << "Reparto: " << repartoFinale;
            
            //se è diverso dal reparto dell'operazione
            if (repartoFinale != repartoOriginale) {
                cout << " | (Operazione in: " << repartoOriginale << ")";
            }
            cout << endl;
            
            if (p->getNumStanza() != -1) {
                cout << "Stanza: " << p->getNumStanza() << endl;
            }
            
            cout << "Allergie: " << p->getAllergie() << endl;
            
            //cerca informazioni sull'operazione
            bool operazioneTrovata = false;
            for(const auto& op : registroOperazioni) {
                if(op.getCFPaziente() == p->getCF()) {
                    int dataOp = dataToIn(op.getData());
                    if(dataOp <= oggi) {
                        //operazione già effettuata
                        cout << "Operazione: " << op.getTipo() << endl;
                        cout << "Data operazione: " << op.getData() << endl;
                        cout << "Esito: " << op.getEsito() << endl;
                    } else {
                        //operazione programmata
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
            
            //stampa terapie se presenti
            p->stampaTerapie();
            
            cout << endl;
            trovatiRicoverati = true;
        }
    }
    
    if (!trovatiRicoverati) {
        cout << "Nessun paziente attualmente ricoverato." << endl;
    }

	//pazienti dimessi oggi
    cout << endl;
    cout << "---- PAZIENTI DIMESSI OGGI (" << oggiStr << ") ----" << endl;
    bool trovatiDimessi = false;
    
    for (auto p : pazienti) {
        int dDim = dataToIn(p->getDataDimissioni());
        
        //paziente dimesso oggi se:
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
            
            //stampo dati paziente
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
}

//metodo per ricerca paziente tramite CF con find_if
Paziente& Ospedale::findCFpaziente(const string& cf){
	//confronto CF di ogni paziente con quello cercato
	auto it = find_if(pazienti.begin(), pazienti.end(),
        [&cf](Paziente* p) {
            return p->getCF() == cf;
        });
    
    if(it == pazienti.end()) {
        throw runtime_error("Paziente con CF '" + cf + "' non trovato!");
    }
    
    return **it; 
}

//metodo per ricerca medico tramite ID
Medico* Ospedale::findMedicoByID(const string& id) {
    for (auto m : medici) {
        if (m->getID() == id) { 
            return m;
        }
    }
    return nullptr;
}