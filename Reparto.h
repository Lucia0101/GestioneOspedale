#ifndef __REPARTO_H__
#define __REPARTO_H__
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <mutex>
#include "Stanza.h"
using namespace std;

class Reparto{
	private:
		string nome;
		int numMedici;
		int numInfermieri;
		int numStanze;
		int lettiPerStanza;
		string specializzazione;
		int numLettiLiberi;
		int numLettiOccupati; 
		vector<Stanza> stanze;
		int contaInfermieri; 
		mutable mutex mtx; 
		
		
	public:
		Reparto();
		Reparto(string n, int numM, int numInf, int numStanz, int letStanz, string spec);
		
		string getNome() const { return nome; }
		
		bool assegnaLetto(int& stanzaAssegnata);
		void liberaLetto(int numeroStanza);
		void svuotaLetti();
		void stampaDettagli() const; 
		
		~Reparto(){}
};

#endif
