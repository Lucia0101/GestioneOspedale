#include "Operazione.h"
#include "Medico.h"

#include <iostream>
#include <string>
#include <ctime>
using namespace std;

//costruttore di defualt
Operazione::Operazione(){
	data="";
	cf_paz="";
	tipo="";
	esito="";
	cura="";
}

//costruttore specifico
Operazione::Operazione(string d,string cf,string type,string cu){
	data=d;
	cf_paz=cf;
	tipo=type;
	esito = "Riuscita";
	cura=cu;	
}

//distruttore
Operazione::~Operazione(){}

//stampa dettagli dell'operazione
void Operazione::stampaInfo()const{
	cout<<"Operazione: "<<tipo<<endl;
	cout<<"Data: "<<data<<endl;
	cout<<"Paziente CF: "<<cf_paz<<endl;
	
	time_t t = time(0);
    struct tm* now = localtime(&t);
    long oggiVal = (now->tm_year + 1900) * 10000 + (now->tm_mon + 1) * 100 + now->tm_mday;
    long opVal = 0;
    if (data.length() >= 10) { //controllo che la stringa sia valida "DD/MM/AAAA"
    //stoi: converte il gg/mm/aaaa in int da stringa
        int gg = stoi(data.substr(0, 2));
        int mm = stoi(data.substr(3, 2));
        int aa = stoi(data.substr(6, 4));
        
        opVal = aa * 10000 + mm * 100 + gg;
    }
     if (opVal < oggiVal) {
        cout << "Esito: " << esito << endl;
        cout << "Cura prescritta: " << cura << endl;
    }
}

//metodo per aggiunta medico 
void Operazione::aggiungiMedico(shared_ptr<Medico> m){
    if(m->isOccupato(this->data)) {
        throw runtime_error("Il medico " + m->getCognome() + " e' gia' impegnato il giorno " + this->data);
    }
    m->aggiungiImpegno(this->data);
}
