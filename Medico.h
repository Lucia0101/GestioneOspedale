#ifndef __MEDICO_H__
#define __MEDICO_H__
#include <string>
#include <atomic>

#include "Persona.h"
using namespace std;

class Medico: public Persona{ 
	private:
		string codID;
		string specializzazione;
		bool occupato;
	
	public:
		Medico(string _nome,string _cognome,int _eta,string _codID,string _specializzazione);
		virtual ~Medico(){};
		
		bool isOccupato()const{return occupato;}
		void setOccupato(bool v){occupato=v;}
		
		virtual void stampaInfo() const;
};

#endif
