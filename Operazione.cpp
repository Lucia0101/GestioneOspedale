#include "Operazione.h"
#include "Medico.h"

#include <iostream>
#include <string>
using namespace std;

Operazione::Operazione(){
	data="";
	cf_paz="";
	tipo="";
	esito="";
	cura="";
}

Operazione::Operazione(string d,string cf,string type,string e,string cu){
	data=d;
	cf_paz=cf;
	tipo=type;
	esito=e;
	cura=cu;	
}

void Operazione::stampaInfo()const{
	cout<<"Operazione: "<<tipo<<endl;
	cout<<"Data: "<<data<<endl;
	cout<<"Paziente CF: "<<cf_paz<<endl;
	cout<<"Esito: "<<esito<<endl;
	cout<<"Cura: "<<cura<<endl;
}

void Operazione::aggiungiMedico(shared_ptr<Medico> m){
	if(teamMedico.size()>=6) throw runtime_error("Team medico completo");
    if(m->isOccupato(this->data)) {
        throw runtime_error("Il medico " + m->getCognome() + " e' gia' impegnato il giorno " + this->data);
    }
    
    teamMedico.push_back(m);
    m->aggiungiImpegno(this->data);
}
