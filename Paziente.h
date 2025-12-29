#ifndef __PAZIENTE_H__
#define __PAZIENTE_H__
#include <string>

#include "Persona.h"
using namespace std;

class Paziente: public Persona{
	private: 
		string allergie,cf,reparto,dataRicovero,dataDimissioni;
		int numStanza;
	
	public:
		Paziente(string _nome,string _cognome,int _eta,string _cf,string _allergie,string _reparto,string dataRicovero,string _dataDimissioni,int _numStanza);
		virtual ~Paziente(){};
		
		virtual void stampaInfo()const;
	
};

#endif
