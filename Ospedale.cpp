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
/*	vector<Medico* > mediciOrdinati=getMedici();
	Medico::ordinaPerCognome(mediciOrdinati);
	
	for(const auto& medico: mediciOrdinati){
		cout<<"- ";
		medico->stampaInfo();
		cout<<endl;
	}*/
	stampaPerCognome(medici, "======== MEDICI (ordinati per cognome) ========");
}

void Ospedale::stampaInfermieriOrdinati(){
/*	vector<Infermiere* > infermieriOrdinati=getInfermieri();
	Infermiere::ordinaPerCognome(infermieriOrdinati);
	
	for(const auto& infermieri: infermieriOrdinati){
		infermieri->stampaInfo();
		cout<<endl;
	}*/
	stampaPerCognome(infermieri, "======== INFERMIERI (ordinati per cognome) ========");
}

void Ospedale::stampaPazientiOrdinati(){
/*	list<Paziente*> pazientiOrdinati = pazienti; // Copia
    Paziente::ordinaPerCognome(pazientiOrdinati);
    
    for(const auto& paziente : pazientiOrdinati) {
        paziente->stampaInfo();
        cout << endl;
    }*/
    stampaPerCognome(pazienti, "======== PAZIENTI (ordinati per cognome) ========");
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

    //DA RICOVERARE
    cout << "*PAZIENTI CON PRENOTAZIONE*" << endl;
    for (auto p : pazienti) {
        if (dataToIn(p->getDataRicovero()) > oggi) {
            p->stampaInfo();
            cout<<endl;
        }
    }
    
    //ATTUALMENTE RICOVERATI
    cout << endl;
    cout << "*PAZIENTI RICOVERATI*" << endl;
    for (auto p : pazienti) {
        int dRic = dataToIn(p->getDataRicovero());
        int dDim = dataToIn(p->getDataDimissioni());
        
        // Se oggi entra il paziente
        if (dRic <= oggi && dRic != 0 && (dDim > oggi || dDim == 0 || p->getDataDimissioni() == "---")) {
        auto rep = const_cast<Ospedale*>(this)->getReparto(p->getReparto());
        if(rep) {
            int stanzaAssegnata;
            if (rep->assegnaLetto(stanzaAssegnata)) {
                p->setStanza(stanzaAssegnata); 
            }
        }
        p->stampaInfo();
        cout<<endl;
        }
    }

    //DIMESSI 
    cout << endl;
    cout << "*PAZIENTI DIMESSI*" << endl;
    for (auto p : pazienti) {
        if (dataToIn(p->getDataDimissioni()) <= oggi && dataToIn(p->getDataDimissioni()) != 0) {
            string infoOp = "Nessuna operazione registrata";
            for(const auto& op : registroOperazioni) {
                // Confrontiamo i Codici Fiscali
                if(op.getCFPaziente() == p->getCF()) {
                    infoOp = "Intervento: " + op.getTipo() + " (Data op: " + op.getData() + ")";
                    break;
                }
            }
            p->stampaPerDimessi(infoOp);
            cout<<endl;
        }
    }
}

void Ospedale::statistichePazienti(){
	int etaMedia=0;
	int conteggio=pazienti.size();
	
	if(conteggio>0){
		auto sommaEta = accumulate(pazienti.begin(), pazienti.end(), 0,
            [](int somma, Paziente* p) {
                return somma + p->getEta(); 
            });
		
		etaMedia=sommaEta/conteggio;
		cout<<"Eta' media pazienti "<<etaMedia<<" anni"<<endl;
	}
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