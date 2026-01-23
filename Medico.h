#ifndef __MEDICO_H__
#define __MEDICO_H__
#include <string>
#include <vector>

#include "Persona.h"
using namespace std;

class Paziente;
class Operazione;

class Medico: public Persona{ 
	private:
		string codID;
		string specializzazione;
		vector<string> dateOccupate;
	
	public:
		Medico(string _nome,string _cognome,int _eta,string _codID,string _specializzazione);
		Medico(Medico&& m) noexcept;
		virtual ~Medico(){};
		
		bool isOccupato(string data) const;
		void aggiungiImpegno(string data);
		void completaOperazione(Paziente* p, Operazione& op, initializer_list<string> farmaciSupporto = {});
		
		static void ordinaPerCognome(vector<Medico* >& medici);
		
		virtual void stampaInfo() const;
		
		string getID()const{return codID;}		
};

#endif
