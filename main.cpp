#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <string>
#include <limits>
#include <thread>
#include <chrono>
#include <mutex>

#include "Ospedale.h"
#include "Operazione.h"
#include "Paziente.h"
#include "Medico.h"
#include "Infermiere.h"
#include "Stampa.h"
using namespace std;

void caricaMedici(Ospedale& osp, const string& filename);
void caricaInfermieri(Ospedale& osp, const string& filename);
void caricaPazienti(Ospedale& osp, const string& filename);
void caricaOperazioni(Ospedale& osp, const string& filename);
void simulaOperazioni(Ospedale& osp);
void simulaThreadOperazioni(Ospedale& osp);

//funzioni del menu
void menu(Ospedale& osp);
void visualizzaMedici(Ospedale& osp);
void visualizzaInfermieri(Ospedale& osp);
void visualizzaPazienti(Ospedale& osp);
void reportGiornaliero(Ospedale& osp);
void pazientiProgrammati(Ospedale& osp); 
void pazientiDimessi(Ospedale& osp);
void visualizzaReparti(Ospedale& osp);
void ricercaModificaPaziente(Ospedale& osp);
void stampaSituazioneOspedale(Ospedale& osp);


int main(int argc, char** argv) {
    Ospedale osp("OSPEDALE PROGRAMMAZIONE AVANZATA");

    try{
        cout<<"--- CARICAMENTO DATI ---"<<endl;
        caricaMedici(osp,"medici.txt");
        cout<<"Medici caricati."<<endl;
        
        caricaInfermieri(osp,"infermieri.txt");
        cout<<"Infermieri caricati."<<endl;
        
        caricaPazienti(osp,"pazienti.txt");
        cout<<"Pazienti caricati e ricoverati."<<endl;
        
        caricaOperazioni(osp,"operazioni.txt");
        cout<<"Operazioni caricate."<<endl;

        simulaOperazioni(osp);  
        cout<<"Operazioni simulate."<<endl;

    }catch(const exception& e){
        cout<<"Errore critico durante il caricamento: "<<e.what()<<endl;
        return 1;
    }
	
	
	system("pause");
	
	//avvio del menu
    menu(osp); 

    return 0;
}

//simulazione di due operazioni simultanee
void simulaThreadOperazioni(Ospedale& osp) {
    cout << "\n=== SIMULAZIONE THREAD: OPERAZIONI SIMULTANEE ===" << endl;
    
    //per sincronizzare l'output
    static mutex mtx; 
    
    //funzione per stampare con mutex
    auto stampaSicura = [&mtx](const string& msg) {
    	lock_guard<mutex> lock(mtx);
        cout << msg << endl;
    };
    
    //prima operazione simulata
    auto operazioneCardio = [&osp, &stampaSicura]() {
        stampaSicura("[THREAD 1] Inizio bypass cardiaco in Cardiochirurgia");
        this_thread::sleep_for(chrono::seconds(3)); 
        stampaSicura("[THREAD 1] Bypass cardiaco completato con successo!");
        
        //aggiunge l'operazione al registro
        try {
            Operazione op(getDataAttuale(), "MSSSIGN123","Bypass cardiaco (simulato)","Monitoraggio cardiaco");
            osp.aggiungiOperazione(op);
        } catch (const exception& e) {
            stampaSicura(string("[THREAD 1] Errore: ") + e.what());
        }
    };
    
    //seconda operazione simulata
    auto operazioneOrtopedia = [&osp, &stampaSicura]() {
        stampaSicura("[THREAD 2] Inizio riduzione frattura in Ortopedia");
        this_thread::sleep_for(chrono::seconds(2)); 
        stampaSicura("[THREAD 2] Frattura ridotta con successo!");
        
        //aggiunge l'operazione al registro
        try {
            Operazione op(getDataAttuale(), "MARFERR123", "Riduzione frattura scomposta (simulato)", "Fisioterapia");
            osp.aggiungiOperazione(op);
        } catch (const exception& e) {
            stampaSicura(string("[THREAD 2] Errore: ") + e.what());
        }
    };
    
    //creazione dei thread
    thread thread1(operazioneCardio);
    thread thread2(operazioneOrtopedia);
    
    stampaSicura("[MAIN] Thread avviati - operazioni in corso simultaneamente...");
    
    thread1.join();
    thread2.join();
    
    stampaSicura("[MAIN] Entrambe le operazioni completate!");
    cout << "=============================================" << endl;
}


//caricamento i medici
void caricaMedici(Ospedale& osp,const string& filename){
    ifstream file(filename);
    if(!file.is_open()) throw runtime_error("Impossibile aprire " + filename);

    string linea;
    while(getline(file,linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        string nome,cognome,etaStr,id,spec;
        
        //nel csv ogni parametro è diviso con ;
        getline(ss, nome, ';');
        getline(ss, cognome, ';');
        getline(ss, etaStr, ';');
        getline(ss, id, ';');
        getline(ss, spec, ';');

        osp.aggiungiMedico(new Medico(nome,cognome,stoi(etaStr),id,spec));
    }
    file.close();
}

//carica gli infermieri
void caricaInfermieri(Ospedale& osp,const string& filename){
    ifstream file(filename);
    if(!file.is_open()) throw runtime_error("Impossibile aprire " + filename);

    string linea;
    while(getline(file, linea)){
        if (linea.empty()) continue;
        stringstream ss(linea);
        string nome,cognome,etaStr,id,rep,turno;
        
        //nel csv ogni parametro è diviso con ;
        getline(ss,nome,';');
        getline(ss,cognome,';');
        getline(ss,etaStr,';');
        getline(ss,id,';');
        getline(ss,rep,';');
        getline(ss,turno,';');

        osp.aggiungiInfermiere(new Infermiere(nome,cognome,stoi(etaStr),id,rep,turno));
    }
    file.close();
}

//carica i pazienti
void caricaPazienti(Ospedale& osp,const string& filename){
    ifstream file(filename);
    if(!file.is_open()) throw runtime_error("Impossibile aprire " + filename);

    string linea;
    while(getline(file, linea)){
        if (linea.empty()) continue;
        stringstream ss(linea);
        string nome,cognome,etaStr,cf,allergie,reparto,dRic,dDim;
        
        //nel csv ogni parametro è diviso con ;
        getline(ss,nome,';');
        getline(ss,cognome,';');
        getline(ss,etaStr,';');
        getline(ss,cf,';');
        getline(ss,allergie,';');
        getline(ss,reparto,';');
        getline(ss,dRic,';');
        getline(ss,dDim,';');

        Paziente* p=new Paziente(nome,cognome,stoi(etaStr),cf,allergie,reparto,dRic,dDim,-1);
        osp.aggiungiPaziente(p);
        
        //ricovero automatico nel reparto corretto
        try {
            auto repPtr=osp.getReparto(reparto);
            if(repPtr){
                p->ricovera(*repPtr);
            }
        } catch (...) {
            //ignora errori di reparto non trovato
        }
    }
    file.close();
}

//carica le operazioni
void caricaOperazioni(Ospedale& osp,const string& filename) {
    ifstream file(filename);
    if(!file.is_open()) throw runtime_error("Impossibile aprire " + filename);

    string linea;
    while(getline(file, linea)){
        if(linea.empty()) continue;
        stringstream ss(linea);
        string data, cf, tipo, esito, cura;
        
        //nel csv ogni parametro è diviso con ;
        getline(ss,data,';');
        getline(ss,cf,';');
        getline(ss,tipo,';');
        getline(ss,esito,';');
        getline(ss,cura,';');
        
        Operazione op(data,cf,tipo,cura);
        
        //cerco il paziente e assegno i farmaci se è necessario
        try{
            Paziente& paziente=osp.findCFpaziente(cf);
            
            //assegna automaticamente la cura principale
            if(!cura.empty()){
                paziente.prestiviFarmaco(cura);
            }
            
            osp.aggiungiOperazione(op);
            
        }catch(const exception& e){
            cout<<"Attenzione: Paziente con CF "<<cf<<" non trovato per l'operazione del "<<data<<endl;
            osp.aggiungiOperazione(op);
        }
    }
    file.close();
}

//simulazione operazioni per popolazione dell'ospedale
void simulaOperazioni(Ospedale& osp){
    cout<<endl;
    cout<<"--- SIMULAZIONE INTERVENTI CHIRURGICI ---"<<endl;
    
    //operazione 1: cardiochirurgia
    try{
        //controlla se questa operazione esiste già
        Paziente& paziente=osp.findCFpaziente("ALFSIGN123");
        cout << " [INFO] Paziente Signorini trovato, operazione bypass gia' nel file operazioni.txt" << endl;
    }catch(const exception& e){
        //paziente non trovato, quindi procedo con la simulazione
        try{
            Medico* capoEquipe=osp.findMedicoByID("M001");
            Medico* assistente=osp.findMedicoByID("M006");
            Paziente& paziente=osp.findCFpaziente("ALFSIGN123");

            if(capoEquipe && assistente){
                Operazione op("21/01/2026","ALFSIGN123","Bypass cardiaco","Monitoraggio intensivo");

                shared_ptr<Medico> sp1(capoEquipe, [](Medico*){});
                shared_ptr<Medico> sp2(assistente, [](Medico*){});
                
                op.aggiungiMedico(sp1);
                op.aggiungiMedico(sp2);

                capoEquipe->completaOperazione(&paziente,op,{"Eparina","Morfina","Antibiotico"});

                osp.aggiungiOperazione(op);
                cout<<" [OK] Bypass cardiaco registrato per paziente Signorini."<<endl;
            }
        }catch(const exception& e){
            cout<<"[ERR] Operazione 1 fallita: "<<e.what()<<endl;
        }
    }

    //operazione 2: ortopedia
    try{
        Paziente& paziente=osp.findCFpaziente("MARFERR123");
        cout << " [INFO] Paziente Ferrari trovato, operazione frattura gia' nel file operazioni.txt" << endl;
    }catch(...){

        try{
            Medico* ortopedico = osp.findMedicoByID("M002");
            Paziente& paziente = osp.findCFpaziente("MARFERR123");

            if (ortopedico) {
                Operazione op("15/05/2026", "MARFERR123", "Frattura scomposta", "Fisioterapia");
                
                shared_ptr<Medico> sp(ortopedico, [](Medico*){});
                op.aggiungiMedico(sp);

                ortopedico->completaOperazione(&paziente, op, {"Tachipirina 1000", "Gesso"});
                
                osp.aggiungiOperazione(op);
                cout << " [OK] Intervento frattura registrato per paziente Ferrari." << endl;
            }
        } catch (const exception& e) {
            cout << " [ERR] Operazione 2 fallita: " << e.what() << endl;
        }
    }

    //operazione 3: chirurgia estetica 
    try{
        Paziente& paziente=osp.findCFpaziente("MAGOL123");
        cout << " [INFO] Paziente Golia trovato, rinoplastica gia' nel file operazioni.txt" << endl;
    }catch(...){
        
		try {
            Medico* chirurgo = osp.findMedicoByID("M003");
            Paziente& paziente = osp.findCFpaziente("MAGOL123");

            if (chirurgo) {
                Operazione op("19/01/2026", "MAGOL123","Rinoplastica", "Riposo assoluto");
                
                shared_ptr<Medico> sp(chirurgo, [](Medico*){});
                op.aggiungiMedico(sp);

                chirurgo->completaOperazione(&paziente, op, {"Antidolorifico","Ghiaccio"});
                
                osp.aggiungiOperazione(op);
                cout << " [OK] Rinoplastica registrata per paziente Golia." << endl;
            }
        } catch (const exception& e) {
            cout << " [ERR] Operazione 3 fallita: " << e.what() << endl;
        }
    }

    //operazione 4: test errore
    try {
        Paziente& paziente = osp.findCFpaziente("NONESISTE123");
    } catch (const exception& e) {
        cout << " [INFO] Test sicurezza superato: Impossibile operare paziente inesistente." << endl;
    }
}

//stampa dati generali dell'ospedale
void stampaSituazioneOspedale(Ospedale& osp) {
    cout << "\n--- SITUAZIONE OSPEDALE ---" << endl;
    osp.stampaDati();
    cout << endl;
}

//visualizzazione e funzionalità menu
void menu(Ospedale& osp) {
    int scelta;
    char continua;
    
    do {
        system("cls");
        
        stampaSituazioneOspedale(osp);
        
        cout << "========================================" << endl;
        cout << "          MENU PRINCIPALE" << endl;
        cout << "========================================" << endl;
        cout << "1) Visualizzazione medici" << endl;
        cout << "2) Visualizzazione infermieri" << endl;
        cout << "3) Visualizzazione pazienti" << endl;
        cout << "4) Report giornaliero" << endl;
        cout << "5) Visualizza pazienti programmati" << endl;
        cout << "6) Visualizza pazienti dimessi" << endl;
        cout << "7) Visualizzazione reparti" << endl;
        cout << "8) Simulazione thread operazioni" << endl;
        cout << "9) Esci dal programma" << endl;
        cout << "========================================" << endl;
        cout << "Scegli un'opzione (1-9): ";
        
        //controllo dell'input
        if (!(cin >> scelta)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input non valido. Riprova." << endl;
            system("pause");
            continue;
        }
        
        //pulisce il buffer
        cin.ignore(); 
        
        //costrutto di condizione per il menù
        switch(scelta) {
            case 1:
                visualizzaMedici(osp);
                break;
            case 2:
                visualizzaInfermieri(osp);
                break;
            case 3:
                visualizzaPazienti(osp);
                break;
            case 4:
                reportGiornaliero(osp);
                break;
            case 5:
                pazientiProgrammati(osp);
                break;
            case 6:
		        pazientiDimessi(osp);
                break;
            case 7:
                visualizzaReparti(osp);
                break;
            case 8:
		        system("cls");
		        simulaThreadOperazioni(osp);  
		        system("pause");
		        break;
    		case 9:  
        		cout << "Uscita dal programma..." << endl;
        		return;
            default:
                cout << "Opzione non valida. Riprova." << endl;
        }
        
        if (scelta != 9) {
        	cout<<endl;
            cout << "========================================" << endl;
            cout << "Vuoi tornare al menu principale? (S/N): ";
            cin >> continua;
            cin.ignore();
            
        if (continua == 'N' || continua == 'n') {
            cout << "Uscita dal programma..." << endl;
            break;
        }
        }
        
    } while (true);
}

//visualizza lista medici
void visualizzaMedici(Ospedale& osp) {
    system("cls"); 
    
    cout<<endl;
    cout << "========================================" << endl;
    cout << "          LISTA MEDICI" << endl;
    cout << "========================================" << endl;
    osp.stampaMediciOrdinati();
    
    cout<<endl;
    cout << "========================================" << endl;
    system("pause");
}

//visualizza lista infermieri
void visualizzaInfermieri(Ospedale& osp) {
    system("cls");
    
    cout<<endl;
    cout << "========================================" << endl;
    cout << "          LISTA INFERMIERI" << endl;
    cout << "========================================" << endl;
    
    osp.stampaInfermieriOrdinati();
    cout << "\n========================================" << endl;
    system("pause");
}

//visualizza lista pazienti
void visualizzaPazienti(Ospedale& osp) {
    system("cls");
    
    cout<<endl;
    cout << "========================================" << endl;
    cout << "          LISTA PAZIENTI" << endl;
    cout << "========================================" << endl;
    
   osp.stampaPazientiOrdinati();
    cout << "\n========================================" << endl;
    
    char scelta;
    cout<<endl;
    cout << "Vuoi ricercare un paziente per codice fiscale? (S/N): ";
    cin >> scelta;
    cin.ignore();
    
    if (scelta == 'S' || scelta == 's') {
        ricercaModificaPaziente(osp);
    }
    
    system("pause");
}

//ricerca per cf e modifica dati del paziente
void ricercaModificaPaziente(Ospedale& osp) {
    string cf;
    cout << "\nInserisci il codice fiscale del paziente: ";
    getline(cin, cf);
    
    try {
        Paziente& pazienteTrovato = osp.findCFpaziente(cf);
        cout << endl << "========================================" << endl;
        cout << "       CARTELLA PAZIENTE TROVATA" << endl;
        cout << "========================================" << endl;
        pazienteTrovato.stampaInfo();
        
        char modifica;
        cout << "\n========================================" << endl;
        cout << "Vuoi modificare la cartella? (S/N): ";
        cin >> modifica;
        cin.ignore();
        
        if(modifica == 'S' || modifica == 's') {
            cout << endl;
            cout << "========================================" << endl;
            cout << "     MODIFICA CARTELLA PAZIENTE" << endl;
            cout << "========================================" << endl;

            string input;
            int valoreInt;
            
            cout << "Nome attuale: " << pazienteTrovato.getNome() << endl;
            cout << "Nuovo nome (premi Invio per mantenere): ";
            getline(cin, input);
            if (!input.empty()) {
                pazienteTrovato.setNome(input);
            }
            
            cout << endl;
            cout << "Cognome attuale: " << pazienteTrovato.getCognome() << endl;
            cout << "Nuovo cognome (premi Invio per mantenere): ";
            getline(cin, input);
            if (!input.empty()) {
                pazienteTrovato.setCognome(input);
            }
            
            cout << endl;
            cout << "Eta attuale: " << pazienteTrovato.getEta() << " anni" << endl;
            cout << "Nuova eta' (inserisci 0 per mantenere): ";
            cin >> valoreInt;
            cin.ignore();
            if(valoreInt > 0) {
                pazienteTrovato.setEta(valoreInt);
            }
            
            cout << endl;
            cout << "Allergie attuali: " << pazienteTrovato.getAllergie() << endl;
            cout << "Nuove allergie (premi Invio per mantenere): ";
            getline(cin, input);
            if(!input.empty()) {
                pazienteTrovato.setAllergie(input);
            }
            
            cout << "\n========================================" << endl;
            cout << "       MODIFICA COMPLETATA!" << endl;
            cout << "========================================" << endl;
            cout << "CARTELLA MODIFICATA: " << endl;
            pazienteTrovato.stampaInfo();
            
        } else {
            cout << "\nModifica annullata." << endl;
        }
        
    } catch(const exception& e) {
        cout << "\n>>> ERRORE: " << e.what() << endl;
        cout << "Codice fiscale non trovato nel sistema." << endl;
    }
}

//visualizzazione report giornaliero
void reportGiornaliero(Ospedale& osp) {
    system("cls");
    
    osp.stampaPazientiFiltrati();
    
    cout << "\n========================================" << endl;
    system("pause");
}

//visualizzazione pazienti con prenotazione ma non ricoverati
void pazientiProgrammati(Ospedale& osp){
    system("cls");
    
    cout << endl;
    cout << "===============================================" << endl;
    cout << "          LISTA PAZIENTI PROGRAMMATI" << endl;
    cout << "===============================================" << endl;
    
    list<Paziente*> pazientiProg = osp.getPazientiProgrammati();
    
    if (pazientiProg.empty()) {
        cout << "Nessun paziente programmato." << endl;
    } else {
        stampaPerCognome<list<Paziente*>>(pazientiProg, "");
    }
    
    cout << "\n========================================" << endl;
    
    //ricerca del paziente se ci sono dei pazienti
    if (!pazientiProg.empty()) {
        char scelta;
        cout << "Vuoi ricercare un paziente per codice fiscale? (S/N): ";
        cin >> scelta;
        cin.ignore();
        
        if (scelta == 'S' || scelta == 's') {
            ricercaModificaPaziente(osp);
        }
    }
    
    cout << endl;
    cout << "========================================" << endl;
    system("pause");
}

//visualizzazione pazienti dimessi
void pazientiDimessi(Ospedale& osp){
    system("cls");
    
    cout << endl;
    cout << "===============================================" << endl;
    cout << "          LISTA PAZIENTI DIMESSI" << endl;
    cout << "===============================================" << endl;
    
    list<Paziente*> pazientiDim = osp.getPazientiDimessi();
    
    if (pazientiDim.empty()) {
        cout << "Nessun paziente dimesso (storico)." << endl;
    } else {
        stampaPerCognome<list<Paziente*>>(pazientiDim, "");
    }
    
    cout << "\n========================================" << endl;
    
    if (!pazientiDim.empty()) {
        char scelta;
        cout << "Vuoi ricercare un paziente per codice fiscale? (S/N): ";
        cin >> scelta;
        cin.ignore();
        
        if (scelta == 'S' || scelta == 's') {
            ricercaModificaPaziente(osp);
        }
    }
    
    cout << endl; 
    cout << "========================================" << endl;
    system("pause");
}

//visualizzazione dei reparti
void visualizzaReparti(Ospedale& osp) {
    system("cls");
    
    cout << "\n========================================" << endl;
    cout << "          VISUALIZZAZIONE REPARTI" << endl;
    cout << "========================================" << endl;
    cout << "1) Cardiochirurgia" << endl;
    cout << "2) Chirurgia Estetica" << endl;
    cout << "3) Ortopedia" << endl;
    cout << "4) Pediatria" << endl;
    cout << "5) Geriatria" << endl;
    cout << "6) Tutti i reparti" << endl;
    cout << "========================================" << endl;
    cout << "Scegli un reparto (1-6): ";
    
    int scelta;
    cin >> scelta;
    cin.ignore();
    
    system("cls");
    
    string repartiNomi[] = {"Cardiochirurgia", "Chirurgia Estetica", "Ortopedia", "Pediatria", "Geriatria"};
    string nomeReparto;
    
    //costrutto switch per scelta del reparto
    switch(scelta) {
        case 1:
            nomeReparto = "Cardiochirurgia";
            break;
        case 2:
            nomeReparto = "Chirurgia Estetica";
            break;
        case 3:
            nomeReparto = "Ortopedia";
            break;
        case 4:
            nomeReparto = "Pediatria";
            break;
        case 5:
            nomeReparto = "Geriatria";
            break;
        case 6:
            cout << "\n========================================" << endl;
            cout << "           TUTTI I REPARTI" << endl;
            cout << "========================================" << endl;
            
            for(int idx = 0; idx < 5; idx++) {
                cout << "\n----------------------------------------" << endl;
                cout << "REPARTO: " << repartiNomi[idx] << endl;
                cout << "----------------------------------------" << endl;
                
                //stampa il nome reparto
                auto repartiMap = osp.getReparti();
                auto it = repartiMap.find(repartiNomi[idx]);
                if (it != repartiMap.end() && !it->second.empty()) {
                    shared_ptr<Reparto> rep = it->second[0];
                    rep->stampaNome();
                    
                    //conta i medici 
                    int countMedici = 0;
                    auto mediciOsp = osp.getMedici();
                    for (auto m : mediciOsp) {
                        if (m->getSpecializzazione() == repartiNomi[idx]) {
                            countMedici++;
                        }
                    }
                    
                    //conta gli infermieri
                    int countInfermieri = 0;
                    auto infermieriOsp = osp.getInfermieri();
                    for (auto infermiere : infermieriOsp) {
                        if (infermiere->getReparto() == repartiNomi[idx]) {
                            countInfermieri++;
                        }
                    }
                    
                    cout << "[Staff medico: " << countMedici << " medici] | " << "[Staff infermieri: " << countInfermieri << " infermieri]" << endl;
                    
                    //stampa letti
                    rep->stampaLetti();
                    
                } else {
                    cout << "Reparto non trovato!" << endl;
                }
                
                //stampa elenco medici
                cout << "\nELENCO MEDICI:" << endl;
                cout << "----------------------------------------" << endl;
                auto mediciOsp = osp.getMedici();
                bool trovatiMedici = false;
                for (auto m : mediciOsp) {
                    if (m->getSpecializzazione() == repartiNomi[idx]) {
                        m->stampaInfo();
                        cout << endl;
                        trovatiMedici = true;
                    }
                }
                if (!trovatiMedici) {
                    cout << "Nessun medico assegnato." << endl;
                }
                
                //stampa elenco infermieri
                cout << "\nELENCO INFERMIERI:" << endl;
                cout << "----------------------------------------" << endl;
                auto infermieriOsp = osp.getInfermieri();
                bool trovatiInfermieri = false;
                for (auto infermiere : infermieriOsp) {
                    if (infermiere->getReparto() == repartiNomi[idx]) {
                        infermiere->stampaInfo();
                        cout << endl;
                        trovatiInfermieri = true;
                    }
                }
                if (!trovatiInfermieri) {
                    cout << "Nessun infermiere assegnato." << endl;
                }
            }
            
            cout << "\n========================================" << endl;
            system("pause");
            return;
        default:
            cout << "Scelta non valida!" << endl;
            system("pause");
            return;
    }
    
    cout << "\n========================================" << endl;
    cout << "         REPARTO: " << nomeReparto << endl;
    cout << "========================================" << endl;
    
    //stampa singolo reparto
    auto repartiMap = osp.getReparti();
    auto it = repartiMap.find(nomeReparto);
    if (it != repartiMap.end() && !it->second.empty()) {
        shared_ptr<Reparto> rep = it->second[0];
        
        //stampa nome del reparto
        rep->stampaNome();
        
        //conta e stampa medici
        int countMedici = 0;
        auto mediciOsp = osp.getMedici();
        for (auto m : mediciOsp) {
            if (m->getSpecializzazione() == nomeReparto) {
                countMedici++;
            }
        }
        
        //conta e stampa infermieri
        int countInfermieri = 0;
        auto infermieriOsp = osp.getInfermieri();
        for (auto infermiere : infermieriOsp) {
            if (infermiere->getReparto() == nomeReparto) {
                countInfermieri++;
            }
        }
        
        cout << "[Staff medico: " << countMedici << " medici] | "<< "[Staff infermieri: " << countInfermieri << " infermieri]" << endl;
        
        //stampa dettagli letti e stanze
        rep->stampaLetti();
        
    } else {
        cout << "Reparto non trovato!" << endl;
    }
    
    //stampa elenco medici
    cout << "\nELENCO MEDICI:" << endl;
    cout << "----------------------------------------" << endl;
    auto mediciOsp = osp.getMedici();
    bool trovatiMedici = false;
    for (auto m : mediciOsp) {
        if (m->getSpecializzazione() == nomeReparto) {
            m->stampaInfo();
            cout << endl;
            trovatiMedici = true;
        }
    }
    if (!trovatiMedici) {
        cout << "Nessun medico assegnato." << endl;
    }
    
    //atampa elenco infermieri
    cout << "\nELENCO INFERMIERI:" << endl;
    cout << "----------------------------------------" << endl;
    auto infermieriOsp = osp.getInfermieri();
    bool trovatiInfermieri = false;
    for (auto infermiere : infermieriOsp) {
        if (infermiere->getReparto() == nomeReparto) {
            infermiere->stampaInfo();
            cout << endl;
            trovatiInfermieri = true;
        }
    }
    if (!trovatiInfermieri) {
        cout << "Nessun infermiere assegnato." << endl;
    }
    
    cout << "\n========================================" << endl;
    system("pause");
}