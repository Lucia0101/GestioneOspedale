#include "Reparto.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>
using namespace std;

//costruttore di default
Reparto::Reparto() {
    nome = "";
    numMedici = 0;
    numInfermieri = 0;
    numStanze = 10;
    lettiPerStanza = 2;
    specializzazione = "";
    numLettiOccupati = 0;
    
	numLettiLiberi = numStanze * lettiPerStanza;
    for(int i = 1; i <= numStanze; i++) {
        stanze.push_back(Stanza(i, lettiPerStanza, nome));
    }
}

//costruttore specifico
Reparto::Reparto(string n, int numM, int numInf, int numStanz, int letStanz, string spec)
    : nome(move(n)), 
      numMedici(numM), 
      numInfermieri(numInf),
      numStanze(numStanz),       
      lettiPerStanza(letStanz),  
      specializzazione(move(spec)) 
{
    numLettiOccupati = 0; 
    numLettiLiberi = numStanz * letStanz; 
    for(int i = 1; i <= numStanz; i++) {
        stanze.push_back(Stanza(i, letStanz, nome));
    }
}

//distruttore
Reparto::~Reparto(){}

//metodo per assegnazione del letto
bool Reparto::assegnaLetto(int& stanzaAssegnata) {
    lock_guard<mutex> lock(mtx); 
    for(auto& stanza : stanze) {
        if(!stanza.isPiena()) {
            stanza.occupaLetto(); 
            stanzaAssegnata = stanza.getNumStanza();
            
            numLettiOccupati++;
            if(numLettiLiberi > 0) numLettiLiberi--;
            
            return true; 
        }
    }
    stanzaAssegnata = -1;
    return false; 
}

//metodo per aggiunta letto libero
void Reparto::liberaLetto(int numeroStanza) {
    lock_guard<mutex> lock(mtx);
    
    for(auto& stanza : stanze) {
        if(stanza.getNumStanza() == numeroStanza) {
            stanza.liberaLetto();
            
            if(numLettiOccupati > 0) numLettiOccupati--;
            numLettiLiberi++;
            return;
        }
    }
}

//metodo per liberare i letti
void Reparto::svuotaLetti() {
    lock_guard<mutex> lock(mtx);
    numLettiOccupati = 0;
    numLettiLiberi = numStanze * lettiPerStanza;
    for(auto& stanza : stanze) {
        stanza.azzeraLetti();
    }
}

//metodo per stampa nome del reparto e specializzazione
void Reparto::stampaNome() const {
    lock_guard<mutex> lock(mtx);
    cout << "REPARTO: " << nome << " (" << specializzazione << ")" << endl;
}

//metodo per stampa letti
void Reparto::stampaLetti() const {
    lock_guard<mutex> lock(mtx);
    cout << "[Letti totali: " << numLettiLiberi + numLettiOccupati 
         << " | Liberi: " << numLettiLiberi 
         << " | Occupati: " << numLettiOccupati << "]" << endl;
    
    for(const auto& s : stanze) {
        s.stampaDettagli();
    }
}

//metodo per stampare nome e letti del reparto
void Reparto::stampaDettagli() const {
    stampaNome();
    stampaLetti();
}