#ifndef __MEDICO_H__
#define __MEDICO_H__
#include <string>
#include <atomic>
#include<vector>

#include "Persona.h"

class Paziente;
class Operazione;

using namespace std;

class Medico: public Persona{ 
	private:
		string codID;
		string specializzazione;
		vector<string> dateOccupate;
	
	public:
		Medico(string _nome,string _cognome,int _eta,string _codID,string _specializzazione);
		virtual ~Medico(){};
		
		bool isOccupato(string data) const;
		
		void aggiungiImpegno(string data);
		
		virtual void stampaInfo() const;
		
		void completaOperazione(Paziente* p, Operazione& op, vector<string> farmaciSupporto);
};

#endif
