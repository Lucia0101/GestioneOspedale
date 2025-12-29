#ifndef __INFERMIERE_H__
#define __INFERMIERE_H__
#include <string>
#include "Persona.h"

using namespace std;

class Infermiere: public Persona{ 
	private:
		string codID;
		string reparto;
		string turno;
	
	public:
		Infermiere(string _nome,string _cognome,int _eta,string _codID,string _reparto,string _turno);
		virtual ~Infermiere(){};

		virtual void stampaInfo()const;
};

#endif
