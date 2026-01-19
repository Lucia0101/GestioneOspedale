#ifndef __PAZIENTE_H__
#define __PAZIENTE_H__
#include <string>
#include <iostream>

#include "Persona.h"
#include "Ospedale.h"
using namespace std;

class Reparto;

string getDataAttuale();

class Paziente: public Persona{
	private: 
		string allergie,cf,reparto,dataRicovero,dataDimissioni;
		int numStanza;
		string* listaFarmaci;
		int numFarmaci;
	
	public:
		Paziente(string _nome,string _cognome,int _eta,string _cf,string _allergie,string _reparto,string dataRicovero,string _dataDimissioni,int _numStanza);
		virtual ~Paziente(); //ho modificato le {}, bisogna eliminare la Lista di Farmaci
		
		virtual void stampaInfo()const;
		
		Paziente(const Paziente& paz); //costruttore copia
		Paziente(Paziente&& paz) noexcept; //move semantics
		void prestiviFarmaco(string nomeFarmaco); //per aggiungere un farmaco
		void ricovera(Reparto& rep);
		void dimetti(Reparto& rep);
		
		string getReparto() const { return reparto; }
		
		int getNumStanza() const { return numStanza; }
		string getDataRicovero() const { return dataRicovero; }
		string getDataDimissioni() const { return dataDimissioni; }
		
		string getCF() const { return cf; }
		void stampaPerDimessi(string infoOperazione) const;
	
		
};

#endif

