#include <iostream>
#include <memory>
#include<vector>

#include "Ospedale.h"
#include "Operazione.h"
#include "Paziente.h"
#include "Medico.h"
#include "Infermiere.h"
using namespace std;


int main(int argc, char** argv) {
	Ospedale osp("*PRAVA*");
	
	//(nome, cognome, anni, codice, specializzazione)
	Medico* m1=new Medico("Mario","Rossi",45,"M001","Cardiochirurgia");
	Medico* m2=new Medico("Luigi","Verdi",50,"M002","Ortopedia");
	Medico* m3=new Medico("Giulia","Pecora",34,"M003","Chirurgia Estetica");
	Medico* m4=new Medico("Chiara","Faccioli",40,"M004","Cardiochirurgia");
	Medico* m5=new Medico("Luisa","Bertelli",33,"M005","Ortopedia");
	Medico* m6=new Medico("Giulia","Pecora",34,"M006","Ortopedia");
	Medico* m7=new Medico("Roberta","Rossi",29,"M007","Cardiochirurgia");
	Medico* m8=new Medico("Lorenzo","Adami",60,"M008","Chirurgia estetica");
	Medico* m9=new Medico("Marco","Vercillo",55,"M009","Chirurgia Estetica");
	
	//(nome, cognome, anni, codice, reparto, turno)
	Infermiere* i1=new Infermiere("Anna","Bianchi",32,"I001","Cardiochirurgia","Notte");
	Infermiere* i2=new Infermiere("Paolo","Neri",28,"I002","Ortopedia","Giorno");
	Infermiere* i3=new Infermiere("Anna","Soave",55,"I003","Ortopedia","Notte");
	Infermiere* i4=new Infermiere("Francesco","Mazzola",32,"I004","Chirurgia Estetica","Giorno");
	Infermiere* i5=new Infermiere("Lucia","Pecora",24,"I005","Pediatria","Notte");
	Infermiere* i6=new Infermiere("Beatrice","Faccioli",22,"I006","Ortopedia","Giorno");
	Infermiere* i7=new Infermiere("Umberto","Sommavilla",43,"I007","Geriatria","Notte");
	Infermiere* i8=new Infermiere("Francesca","Adamo",39,"I008","Cardiochirurgia","Giorno");

	//(nome, cognome, anni, CF, allergia, reparto, data ricovero, data dimissioni, stanza)
	Paziente* p1=new Paziente("Alfonso","Signorini",69,"ALFSIGN123","Nessuna","Cardiochirurgia","10/05/2026","20/05/2026",-1);
	Paziente* p2=new Paziente("Marco","Ferrari",35,"MARFERR123","Nessuno","Ortopedia","12/05/2026","25/05/2026",-1);
	Paziente* p3=new Paziente("Mattia","Ruffo",16,"MARFFO123","Nessuna","Ortopedia","29/12/2025","04/01/2026",-1);
	Paziente* p4=new Paziente("Marta","Golia",24,"MAGOL123","Pennicillina","Chirurgia Estetica","12/01/2026","25/01/2026",-1);
	Paziente* p5=new Paziente("Alessandra","Felice",69,"ALSSDFlI123","Nessuna","Chirurgia Estetica","19/01/2026","25/01/2026",-1);
	Paziente* p6=new Paziente("Giovanni","Delaini",78,"GOVNDLIN123","Nessuna","Cardiochirurgia","19/01/2026","25/01/2026",-1);
	Paziente* p7=new Paziente("Giovanna","Strazzer",88,"GOVNSTZ123","Nessuna","Cardiochirurgia","19/01/2026","25/01/2026",-1);
	
	//aggiunta farmaci
	vector<string> farmaciExtra1 = {"Antidolorifico", "Ghiaccio spray"};
	vector<string> farmaciExtra2 = {"Tachipirina 1000"};
	vector<string> farmaciExtra3 = {"Tachipirina 1000"};
	vector<string> farmaciExtra4 = {"Tachipirina 1000"};
	vector<string> farmaciExtra5 = {" "};
	vector<string> farmaciExtra6 = {"Eparina"};
	vector<string> farmaciExtra7 = {"Eparina"};

	//(data operazione, CF, nome operazione, esito, Terapia)
	Operazione op1("15/05/2026","ALFSIGN123","Bypass cardiaco","Riuscita","Terapia anticoagulante");
	Operazione op2("17/05/2026","MARFERR123","Operazione al ginocchio","Risucita","Terapia riabilitativa");
	Operazione op3("02/01/2026","MARFFO123","Braccio rotto","Riuscita","Terapia riabilitativa");
	Operazione op4("17/01/2026","MAGOL123","Rinoplastica","Risucita","Terapia anticoagulante");
	Operazione op5("20/01/2026","ALSSDFlI123","Rinoplastica","Riuscita","Terapia anticoagulante");
	Operazione op6("20/01/2026", "GOVNDLIN123", "Posizionamento valvola cardiaca", "Riuscita", "Terapia anticoagulante");
	Operazione op7("20/01/2026", "GOVNSTZ123", "Posizionamento valvola cardiaca", "Riuscita", "Terapia anticoagulante");

	m1->completaOperazione(p1, op1, farmaciExtra1);
	m2->completaOperazione(p2, op2, farmaciExtra2);
	m2->completaOperazione(p3, op3, farmaciExtra3);
	m3->completaOperazione(p4, op4, farmaciExtra4);
	m4->completaOperazione(p5, op5, farmaciExtra5);
	m5->completaOperazione(p5, op5, farmaciExtra5);
	m7->completaOperazione(p6, op6, farmaciExtra6);
	m7->completaOperazione(p7, op7, farmaciExtra7);

	osp.aggiungiMedico(m1);
    osp.aggiungiMedico(m2);
    osp.aggiungiMedico(m3);
    osp.aggiungiMedico(m4);
    osp.aggiungiMedico(m5);
    osp.aggiungiMedico(m6);
    osp.aggiungiMedico(m7);
    osp.aggiungiMedico(m8);
    osp.aggiungiMedico(m9);
    
    osp.aggiungiInfermiere(i1);
    osp.aggiungiInfermiere(i2);
    osp.aggiungiInfermiere(i3);
    osp.aggiungiInfermiere(i4);
    osp.aggiungiInfermiere(i5);
    osp.aggiungiInfermiere(i6);
    osp.aggiungiInfermiere(i7);
    osp.aggiungiInfermiere(i8);
    
    osp.aggiungiPaziente(p1);
    osp.aggiungiPaziente(p2);
    osp.aggiungiPaziente(p3);
    osp.aggiungiPaziente(p4);
    osp.aggiungiPaziente(p5);
    osp.aggiungiPaziente(p6);
    osp.aggiungiPaziente(p7);
    
    osp.aggiungiOperazione(op1); 
    osp.aggiungiOperazione(op2); 
    osp.aggiungiOperazione(op3); 
    osp.aggiungiOperazione(op4); 
    osp.aggiungiOperazione(op5);
    osp.aggiungiOperazione(op6);
    osp.aggiungiOperazione(op7);
    
    shared_ptr<Medico> sm1(m1, [](Medico*){});
    shared_ptr<Medico> sm2(m2, [](Medico*){});
    shared_ptr<Medico> sm3(m3, [](Medico*){});
    shared_ptr<Medico> sm4(m4, [](Medico*){});
    shared_ptr<Medico> sm5(m5, [](Medico*){});
    shared_ptr<Medico> sm6(m6, [](Medico*){});
    shared_ptr<Medico> sm7(m7, [](Medico*){});
    shared_ptr<Medico> sm8(m8, [](Medico*){});
    shared_ptr<Medico> sm9(m9, [](Medico*){});
	
	try {
        // --- RICOVERI GESTITI DA ECCEZIONI ---
        p1->ricovera(*(osp.getReparto("Cardiochirurgia")));
        p2->ricovera(*(osp.getReparto("Ortopedia")));
        p3->ricovera(*(osp.getReparto("Ortopedia")));
        p4->ricovera(*(osp.getReparto("Chirurgia Estetica")));
        p5->ricovera(*(osp.getReparto("Chirurgia Estetica")));
        p6->ricovera(*(osp.getReparto("Cardiochirurgia")));
        p7->ricovera(*(osp.getReparto("Cardiochirurgia")));

        // --- AGGIUNTA MEDICI ALLE OPERAZIONI ---
        op1.aggiungiMedico(sm1);
        op2.aggiungiMedico(sm2);
        op4.aggiungiMedico(sm3);
        op3.aggiungiMedico(sm2);
        op5.aggiungiMedico(sm8);
        op5.aggiungiMedico(sm9);
        op6.aggiungiMedico(sm7);
        op7.aggiungiMedico(sm7); // Dovrebbe fallire per stessa data

    } catch(const exception& e) {
        cerr << "\n>>> ERRORE DI GESTIONE: " << e.what() << endl;
    }
    
    cout << endl;
    osp.stampaDati();
    osp.stampaPersonale(); cout<<endl;
    osp.stampaPazientiFiltrati();
    
    cout << endl;
    cout << "======== SITUAZIONE REPARTI AGGIORNATA ========" << endl;
    osp.stampaReparti(); cout<<endl; 
    
    osp.stampaOperazioni();
	
	return 0;
}
