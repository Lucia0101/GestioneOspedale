#ifndef __INFERMIERE_H__
#define __INFERMIERE_H__
#include <string>
#include "Persona.h"

using namespace std;

class Infermiere:public Persona{ 
	private:
		string codID, reparto, turno;
	
	public:
		Infermiere(string _nome, string _cognome, int _eta , string _codID, string _reparto, string _turno);
		~Infermiere();
		friend ostream& operator << (ostream& os, const Infermiere& i);
		
		ostream& stampaoperator(ostream& os)const;
		void test(){}
};

ostream& operator << (ostream& os, const Infermiere& i);


#endif
