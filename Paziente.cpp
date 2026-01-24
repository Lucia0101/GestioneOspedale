#include "Paziente.h"
#include "Reparto.h"
#include "Ospedale.h"

#include <iostream>
#include <utility> 
#include <ctime>  
#include <iomanip> 
#include <sstream> 

//determino il reparto in base all'età
string determinaRepartoPerEta(int eta, string repartoOperazione) {
    if (eta < 18) {
        return "Pediatria";
    } else if (eta >= 65) {
        return "Geriatria";
    } else {
        return repartoOperazione;
    }
}

//funzione che cattura la data del giorno
string getDataAttuale() {
	//conta i secondi dal 1/01/1970
    time_t t = time(0);
    //conversione timestamp in gg/mm/aa
    struct tm * now = localtime(&t);
    stringstream ss;
    //setfill(0) aggiunge 0 davanti a un numero a una cifra
    //now->tm_mon +1: i mesi vanno da 0 a 11 quindi faccio +1
    //now->tm_mon + 1900: conta anni trascorsi da 1900 a 2026
    ss << setfill('0') << setw(2) << now->tm_mday << "/"
       << setfill('0') << setw(2) << (now->tm_mon + 1) << "/"
       << (now->tm_year + 1900);
    return ss.str();
}

using namespace std;

//costruttore specifico
Paziente::Paziente(string _nome,string _cognome,int _eta ,string _cf,string _allergie,string _reparto,string _dataRicovero,string _dataDimissioni,int _numStanza):
Persona(_nome,_cognome,_eta){
	cf=_cf;
	allergie=_allergie;
	reparto=_reparto;
	dataRicovero=_dataRicovero;
	dataDimissioni= _dataDimissioni;
	numStanza=_numStanza;
	numFarmaci = 0;
	listaFarmaci = nullptr;
}

//costruttore di copia
Paziente::Paziente(const Paziente& paz):Persona(paz){ 
	cf = paz.cf;
	allergie = paz.allergie;
	reparto = paz.reparto;
	dataRicovero = paz.dataRicovero;
	dataDimissioni = paz.dataDimissioni;
	numStanza = paz.numStanza;
	
	numFarmaci = paz.numFarmaci;
	if(paz.listaFarmaci != nullptr){
		listaFarmaci = new string[numFarmaci];
		for (int i = 0; i < numFarmaci; i++){
			listaFarmaci[i] = paz.listaFarmaci[i];
		}
	}else{
		listaFarmaci = nullptr;
	}
	cout << "Copiato: " << cf << endl;
}


//costrutore di spostamento
Paziente::Paziente(Paziente&& paz) noexcept:Persona(move(paz)){
	cf = move(paz.cf);
	allergie = move(paz.allergie);
	reparto = move(paz.reparto);
	dataRicovero = move(paz.dataRicovero);
	dataDimissioni = move(paz.dataDimissioni);
	numStanza = move (paz.numStanza);
	
	listaFarmaci = paz.listaFarmaci;
	numFarmaci = paz.numFarmaci;
	
	paz.listaFarmaci = nullptr;
	paz.numFarmaci = 0;
	
	cout << "Spostato: " << cf << endl;
}

//distruttore
Paziente::~Paziente() {
    if (listaFarmaci != nullptr) {
        delete[] listaFarmaci;
    }
}

//stampa dati del paziente
void Paziente::stampaInfo()const{
    if (cf.empty()) {
        cout << "OGGETTO NON VALIDO: Questo Paziente e' stato spostato altrove." << endl;
        return;
    }
    
    //determina il reparto in base all'età
    string repartoFinale = determinaRepartoPerEta(eta, reparto);
    
    cout<<"PAZIENTE: "<<cognome<<" "<<nome<<", CF: ["<<cf<<"], "<<eta<<" anni"<<endl;
    cout<<"Data ricovero: dal  "<<dataRicovero<<" al "<<dataDimissioni<<endl;
    cout<<"Reparto assegnato (per eta): "<<repartoFinale;
    
    //se il reparto è diverso da quello dell'operazione, mostra anche il reparto dell'operazione
    if (repartoFinale != reparto) {
        cout << " | (Operazione in: " << reparto << ")";
    }
    cout << endl;
    
    if(numStanza != -1){
        cout<<"Stanza: "<<numStanza<<endl;
    }
    
    cout<<"Allergie: "<<allergie<<endl;
    
    stampaTerapie();
}

//metodop per stampa terapie
void Paziente::stampaTerapie() const {
    if (numFarmaci > 0 && listaFarmaci != nullptr) {
        cout << "Terapie prescritte: ";
        for(int i = 0; i < numFarmaci; i++) {
            cout << listaFarmaci[i];
            if(i < numFarmaci - 1) cout << ", ";
        }
        cout << endl;
    }
}

//metodo per aggiunta di un farmaco
void Paziente::prestiviFarmaco(string nomeFarmaco){
	string* temp = new string[numFarmaci + 1];
    for (int i = 0; i < numFarmaci; i++) {
        temp[i] = listaFarmaci[i];
    }
    temp[numFarmaci] = nomeFarmaco;
    
    if (listaFarmaci != nullptr) delete[] listaFarmaci;
    listaFarmaci = temp;
    numFarmaci++;
}

//metodo per assegnazione del letto 
void Paziente::ricovera(Reparto& rep) {
    string oggiStr = getDataAttuale();
    int oggi = dataToIn(oggiStr);
    int dRic = dataToIn(this->dataRicovero);

    //occupo se la data di ricovero è oggi o passata, e non è ancora stato dimesso
    if (dRic <= oggi && dRic != 0 && (dataToIn(dataDimissioni) > oggi || dataDimissioni == "---")) {
        int stanzaAssegnata = -1;
        if (rep.assegnaLetto(stanzaAssegnata)) {
            this->numStanza = stanzaAssegnata;
            this->reparto = rep.getNome(); 
        }
    } else {
        //se è una prenotazione futura, non occupo il letto
        this->numStanza = -1; 
        this->reparto = rep.getNome();
    }
}

//metodo per dimissione del paziente
void Paziente::dimetti(Reparto& rep) {
    if (numStanza != -1) {
        rep.liberaLetto(numStanza);
        this->dataDimissioni = getDataAttuale();
    }
}

//metodo per stampa pazienti dimessi
void Paziente::stampaPerDimessi(string infoOperazione) const {
    cout << "PAZIENTE: " <<cognome<< " " <<nome<< ", CF: " << cf << endl;
    cout << "Ricovero: " <<dataRicovero << " | Dimissione: " << dataDimissioni << endl;
    cout << "" << infoOperazione << endl;
}

//metodo per ordinamento per cognome
void Paziente::ordinaPerCognome(list<Paziente*>& pazienti) {
    pazienti.sort([](Paziente* a, Paziente* b) {
        return a->getCognome() < b->getCognome();
    });
}