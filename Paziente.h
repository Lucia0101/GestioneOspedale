#ifndef __PAZIENTE_H__
#define __PAZIENTE_H__

#include <string>
#include <list>

#include "Persona.h"
using namespace std;

class Reparto;
class Ospedale; 

string getDataAttuale();

class Paziente: public Persona{
	private: 
		string allergie, cf, reparto, dataRicovero, dataDimissioni;
		int numStanza;
		string* listaFarmaci;
		int numFarmaci;
	
	public:
		Paziente(string _nome,string _cognome,int _eta,string _cf,string _allergie,string _reparto,string dataRicovero,string _dataDimissioni,int _numStanza);
		Paziente(const Paziente& paz); 
		Paziente(Paziente&& paz) noexcept; 
		virtual ~Paziente();
		
		virtual void stampaInfo()const;
		void stampaTerapie() const; 
		void prestiviFarmaco(string nomeFarmaco); 
		void ricovera(Reparto& rep);
		void dimetti(Reparto& rep);
		void stampaPerDimessi(string infoOperazione) const;
		static void ordinaPerCognome(list<Paziente*>& pazienti);
		
		string getReparto() const { return reparto; }
		int getNumStanza() const { return numStanza; }
		string getDataRicovero() const { return dataRicovero; }
		string getDataDimissioni() const { return dataDimissioni; }
		string getCF() const { return cf; }
		string getAllergie()const{return allergie;}
		string getRepartoOriginale() const { return reparto; }

		void setNome(const string& nuovoNome) { nome = nuovoNome; }
	    void setCognome(const string& nuovoCognome) { cognome = nuovoCognome; }
	    void setEta(int nuovaEta) { eta = nuovaEta; }
	    void setAllergie(const string& nuoveAllergie) { allergie = nuoveAllergie; }
	    void setStanza(int nuovaStanza) { numStanza = nuovaStanza; }
	   
};

#endif
