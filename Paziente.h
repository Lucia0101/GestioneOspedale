#ifndef __PAZIENTE_H__
#define __PAZIENTE_H__
#include <string>
#include "Persona.h"

using namespace std;

class Paziente:public Persona{
	private: 
		string allergie, CF, reparto, dataRicovero, dataDimissioni;
		int numStanza;
	public:
		Paziente(string _nome, string _cognome, int _eta , string _CF, string _allergie, string _reparto, string dataRicovero, string _dataDimissioni, int _numStanza);
		~Paziente();
		friend ostream& operator << (ostream& os, const Paziente& p);
		
		ostream& stampaoperator(ostream& os)const;
		void test(){}
	
};

#endif
