#ifndef __MEDICO_H__
#define __MEDICO_H__
#include <string>
#include "Persona.h"

using namespace std;

class Medico:public Persona{ 
	private:
		string codID, specializzazione;
	
	public:
		Medico(string _nome, string _cognome, int _eta , string _codID, string _specializzazione);
		~Medico();
		friend ostream& operator << (ostream& os, const Medico& m);
		
		ostream& stampaoperator(ostream& os)const;
		void test(){}
};

ostream& operator << (ostream& os, const Medico& m);

#endif
