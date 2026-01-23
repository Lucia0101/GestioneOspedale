#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <string>


#include "Ospedale.h"
#include "Operazione.h"
#include "Paziente.h"
#include "Medico.h"
#include "Infermiere.h"

using namespace std;

// Funzioni di utilità per il caricamento
void caricaMedici(Ospedale& osp, const string& filename);
void caricaInfermieri(Ospedale& osp, const string& filename);
void caricaPazienti(Ospedale& osp, const string& filename);
void caricaOperazioni(Ospedale& osp, const string& filename);
void ricercaPaziente(Ospedale& osp);

void simulaOperazioni(Ospedale& osp);

int main(int argc, char** argv) {
    Ospedale osp("*PRAVA*");

    try {
        cout << "--- CARICAMENTO DATI ---" << endl;
        caricaMedici(osp, "medici.txt");
        cout << "Medici caricati." << endl;
        
        caricaInfermieri(osp, "infermieri.txt");
        cout << "Infermieri caricati." << endl;
        
        caricaPazienti(osp, "pazienti.txt");
        cout << "Pazienti caricati e ricoverati." << endl;
        
        caricaOperazioni(osp, "operazioni.txt");
        cout << "Operazioni caricate." << endl;

        // Simulazione Operazioni (collega i dati caricati)
        simulaOperazioni(osp);
        cout << "Operazioni simulate." << endl;

    } catch (const exception& e) {
        cerr << "ERRORE CRITICO DURANTE IL CARICAMENTO: " << e.what() << endl;
        return 1;
    }


    // --- STAMPE E INTERAZIONI ---
    cout << endl << "--- SITUAZIONE OSPEDALE ---" << endl;
    osp.stampaDati();

    cout << endl << endl;
    osp.stampaPazientiOrdinati();
    cout << endl;
    osp.stampaMediciOrdinati();
    cout << endl;
    osp.stampaInfermieriOrdinati();

    cout << endl;
    osp.stampaPazientiFiltrati();

    cout << endl;
    osp.stampaReparti();
    cout << endl;
    osp.stampaOperazioni();
    cout << endl;

    // INTERAZIONE
    ricercaPaziente(osp);
    
    // Ristampa per vedere modifiche
    osp.stampaPazientiOrdinati();

    return 0;
}


// --- IMPLEMENTAZIONE FUNZIONI DI CARICAMENTO ---
void caricaMedici(Ospedale& osp, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) throw runtime_error("Impossibile aprire " + filename);

    string linea;
    while (getline(file, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        string nome, cognome, etaStr, id, spec;
        
        getline(ss, nome, ';');
        getline(ss, cognome, ';');
        getline(ss, etaStr, ';');
        getline(ss, id, ';');
        getline(ss, spec, ';');

        osp.aggiungiMedico(new Medico(nome, cognome, stoi(etaStr), id, spec));
    }
    file.close();
}


void caricaInfermieri(Ospedale& osp, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) throw runtime_error("Impossibile aprire " + filename);

    string linea;
    while (getline(file, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        string nome, cognome, etaStr, id, rep, turno;
        
        getline(ss, nome, ';');
        getline(ss, cognome, ';');
        getline(ss, etaStr, ';');
        getline(ss, id, ';');
        getline(ss, rep, ';');
        getline(ss, turno, ';');

        osp.aggiungiInfermiere(new Infermiere(nome, cognome, stoi(etaStr), id, rep, turno));
    }
    file.close();
}


void caricaPazienti(Ospedale& osp, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) throw runtime_error("Impossibile aprire " + filename);

    string linea;
    while (getline(file, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        string nome, cognome, etaStr, cf, allergie, reparto, dRic, dDim;
        
        getline(ss, nome, ';');
        getline(ss, cognome, ';');
        getline(ss, etaStr, ';');
        getline(ss, cf, ';');
        getline(ss, allergie, ';');
        getline(ss, reparto, ';');
        getline(ss, dRic, ';');
        getline(ss, dDim, ';');

        Paziente* p = new Paziente(nome, cognome, stoi(etaStr), cf, allergie, reparto, dRic, dDim, -1);
        osp.aggiungiPaziente(p);
        
        // Tenta il ricovero automatico nel reparto corretto
        try {
            auto repPtr = osp.getReparto(reparto);
            if(repPtr) {
                p->ricovera(*repPtr);
            }
        } catch (...) {
            // Ignora errori di reparto non trovato
        }
    }
    file.close();
}

void caricaOperazioni(Ospedale& osp, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) throw runtime_error("Impossibile aprire " + filename);

    string linea;
    while (getline(file, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        string data, cf, tipo, esito, cura;
        
        getline(ss, data, ';');
        getline(ss, cf, ';');
        getline(ss, tipo, ';');
        getline(ss, esito, ';');
        getline(ss, cura, ';');
        
        // Creare l'operazione
        Operazione op(data, cf, tipo, esito, cura);
        
        // Cercare il paziente e assegnare farmaci se necessario
        try {
            Paziente& paziente = osp.findCFpaziente(cf);
            
            // Assegna automaticamente la cura principale
            if (!cura.empty()) {
                paziente.prestiviFarmaco(cura);
            }
            
            // Aggiungi l'operazione all'ospedale
            osp.aggiungiOperazione(op);
            
        } catch (const exception& e) {
            cerr << "Attenzione: Paziente con CF " << cf << " non trovato per l'operazione del " << data << endl;
            // Carica comunque l'operazione senza assegnare farmaci
            osp.aggiungiOperazione(op);
        }
    }
    file.close();
}


void simulaOperazioni(Ospedale& osp) {
    cout << endl << "--- SIMULAZIONE INTERVENTI CHIRURGICI ---" << endl;

    // OPERAZIONE 1: Cardiochirurgia
    try {
        Medico* capoEquipe = osp.findMedicoByID("M001");
        Medico* assistente = osp.findMedicoByID("M006");
        Paziente& paziente = osp.findCFpaziente("ALFSIGN123");

        if (capoEquipe && assistente) {
            Operazione op("21/01/2026", "ALFSIGN123", "Bypass Aortocoronarico", "Riuscita", "Monitoraggio intensivo");

            shared_ptr<Medico> sp1(capoEquipe, [](Medico*){});
            shared_ptr<Medico> sp2(assistente, [](Medico*){});
            
            op.aggiungiMedico(sp1);
            op.aggiungiMedico(sp2);

            capoEquipe->completaOperazione(&paziente, op, {"Eparina", "Morphina", "Antibiotico"});

            osp.aggiungiOperazione(op);
            cout << " [OK] Bypass cardiaco registrato per paziente Signorini." << endl;
        }
    } catch (const exception& e) {
        cerr << " [ERR] Operazione 1 fallita: " << e.what() << endl;
    }

    // OPERAZIONE 2: Ortopedia
    try {
        Medico* ortopedico = osp.findMedicoByID("M002");
        Paziente& paziente = osp.findCFpaziente("MARFERR123");

        if (ortopedico) {
            Operazione op("15/05/2026", "MARFERR123", "Riduzione frattura scomposta", "Riuscita", "Fisioterapia");
            
            shared_ptr<Medico> sp(ortopedico, [](Medico*){});
            op.aggiungiMedico(sp);

            ortopedico->completaOperazione(&paziente, op, {"Tachipirina 1000", "Gesso"});
            
            osp.aggiungiOperazione(op);
            cout << " [OK] Intervento frattura registrato per paziente Ferrari." << endl;
        }
    } catch (const exception& e) {
        cerr << " [ERR] Operazione 2 fallita: " << e.what() << endl;
    }

    // OPERAZIONE 3: Chirurgia Estetica
    try {
        Medico* chirurgo = osp.findMedicoByID("M003");
        Paziente& paziente = osp.findCFpaziente("MAGOL123");

        if (chirurgo) {
            Operazione op("19/01/2026", "MAGOL123", "Rinoplastica", "Riuscita", "Riposo assoluto");
            
            shared_ptr<Medico> sp(chirurgo, [](Medico*){});
            op.aggiungiMedico(sp);

            chirurgo->completaOperazione(&paziente, op, {"Antidolorifico leggero", "Ghiaccio"});
            
            osp.aggiungiOperazione(op);
            cout << " [OK] Rinoplastica registrata per paziente Golia." << endl;
        }
    } catch (const exception& e) {
        cerr << " [ERR] Operazione 3 fallita: " << e.what() << endl;
    }

    // OPERAZIONE 4: Test errore
    try {
        Paziente& paziente = osp.findCFpaziente("NONESISTE123");
    } catch (const exception& e) {
        cout << " [INFO] Test sicurezza superato: Impossibile operare paziente inesistente." << endl;
    }
}

void ricercaPaziente(Ospedale& osp){
    char risposta;
    cout << "RICERCA PAZIENTE PER CODICE FISCALE" << endl;
    cout << "Ricercare codice fiscale di un paziente? (S/N): ";
    cin >> risposta;
    cin.ignore(); 
    
    if(risposta=='S' || risposta=='s'){
        string cf;
        cout << "Inserisci il codice fiscale del paziente: ";
        getline(cin, cf);
        
        try{
            Paziente& pazienteTrovato = osp.findCFpaziente(cf);
            cout << endl << "CARTELLA PAZIENTE TROVATA" << endl;
            pazienteTrovato.stampaInfo();
            
            char modifica;
            cout << "\nModificare la cartella? (S/N): ";
            cin >> modifica;
            cin.ignore();
            
            if(modifica=='S' || modifica=='s'){
                cout << endl;
                cout << "\n--- MODIFICA CARTELLA PAZIENTE ---" << endl;
    
                string input;
                int valoreInt;
                
                cout << "Nome attuale: " << pazienteTrovato.getNome() << endl;
                cout << "Nuovo nome (premi Invio per mantenere): ";
                getline(cin, input);
                if (!input.empty()){
                    pazienteTrovato.setNome(input);
                }
                
                cout << endl;
                cout << "Cognome attuale: " << pazienteTrovato.getCognome() << endl;
                cout << "Nuovo cognome (premi Invio per mantenere): ";
                getline(cin, input);
                if (!input.empty()){
                    pazienteTrovato.setCognome(input);
                }
                
                cout << endl;
                cout << "Eta attuale: " << pazienteTrovato.getEta() << " anni" << endl;
                cout << "Nuova eta' (inserisci 0 per mantenere): ";
                cin >> valoreInt;
                cin.ignore();
                if(valoreInt > 0){
                    pazienteTrovato.setEta(valoreInt);
                }
                
                cout << endl;
                cout << "Allergie attuali: " << pazienteTrovato.getAllergie() << endl;
                cout << "Nuove allergie (premi Invio per mantenere): ";
                getline(cin, input);
                if(!input.empty()){
                    pazienteTrovato.setAllergie(input);
                }
                
                cout << "\nModifica completata!" << endl;
                cout << "CARTELLA MODIFICATA: " << endl;
                pazienteTrovato.stampaInfo();
                
            } else {
                cout << "\nModifica annullata." << endl;
            }
            
        } catch(const exception& e){
            cerr << "\n>>> ERRORE: " << e.what() << endl;
            cerr << "Codice fiscale non trovato nel sistema." << endl;
        }
    } else {
        cout << "\nRicerca annullata." << endl;
    }
}