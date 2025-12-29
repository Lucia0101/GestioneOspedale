#include <iostream>
#include <memory>

#include "Ospedale.h"
#include "Operazione.h"
#include "Paziente.h"
#include "Medico.h"
#include "Infermiere.h"
using namespace std;


int main(int argc, char** argv) {
	Ospedale osp("*PRAVA*");
	
	Medico* m1=new Medico("Mario","Rossi",45,"M001","Cardiochirurgia");
	Medico* m2=new Medico("Luigi","Verdi",50,"M002","Ortopedia");
	
	Infermiere* i1=new Infermiere("Anna","Bianchi",32,"I001","Cardiochirurgia","Notte");
	Infermiere* i2=new Infermiere("Paolo","Neri",28,"I002","Ortopedia","Giorno");
	 
	Paziente* p1=new Paziente("Alfonso","Signorini",69,"ALFSIGN123","Nessuna","Cardiochirurgia","10/05/25","20/05/25",3);
	Paziente* p2=new Paziente("Marco","Ferrari",35,"MARFERR123","Nessuno","Ortopedia","12/05/25","25/05/25",5);
	
//	auto m1=make_shared<Medico>("Mario","Rossi",45,"M001","Cardiochirurgia");
//FORSE DOBBIAMO FARE COSI?(non mi sembra troppo dai lab, ma controlla semmai) se così si usano le robe commentate in ospedale
	
	
	Operazione op1("15/05/2025","ALFSIGN123","Bypass cardiaco","Riuscita","Terapia anticoagulante");
	Operazione op2("17/05/25","MARFERR123","Operazione al ginocchio","Risucita","Terapia riabilitativa");
	
	
	osp.aggiungiMedico(m1);
    osp.aggiungiMedico(m2);
    
    osp.aggiungiInfermiere(i1);
    osp.aggiungiInfermiere(i2);
    
    osp.aggiungiPaziente(p1);
    osp.aggiungiPaziente(p2);
    
    osp.aggiungiOperazione(op1); cout<<endl;
    osp.aggiungiOperazione(op2); 
    
    osp.stampaDati();
    
    
	
	shared_ptr<Medico> sm1(m1);
    shared_ptr<Medico> sm2(m2);
	
	try{
        op1.aggiungiMedico(sm1);
        op1.aggiungiMedico(sm2);
    }catch(const exception& e){
        cerr<<"Errore operazione: "<<e.what()<<endl;
    }
    
        
    osp.stampaPersonale(); cout<<endl;
    osp.stampaPazienti(); cout<<endl;
    osp.stampaReparti(); cout<<endl;
    osp.stampaOperazioni();
	
	return 0;
}