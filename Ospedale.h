#ifndef __OSPEDALE_H__
#define __OSPEDALE_H__
#include <string>
#include <vector>
#include <map>
#include <list>

#include "Reparto.h"
#include "Operazione.h"
#include "Medico.h"
#include "Infermiere.h"
#include "Paziente.h"
using namespace std;

class Ospedale{
	private:
		string nome;

		map<string, vector<shared_ptr<Reparto>>> reparti;
    	vector<Operazione> registroOperazioni;
    
	    vector<Medico*> medici;
	    vector<Infermiere*> infermieri;
	    list<Paziente*> pazienti; 
	    
	    /*vector<shared_ptr<Medico>> medici;
		vector<shared_ptr<Infermiere>> infermieri;
		list<shared_ptr<Paziente>> pazienti;*/

			    
	   	
	public:
		Ospedale();
	    Ospedale(string n);
	
		void aggiungiMedico(Medico* m){medici.push_back(m);}
		void aggiungiInfermiere(Infermiere* i){infermieri.push_back(i);}
		void aggiungiPaziente(Paziente* p){pazienti.push_back(p);}
		
		/*void aggiungiMedico(shared_ptr<Medico> m){ medici.push_back(m); }
		void aggiungiInfermiere(shared_ptr<Infermiere> i){ infermieri.push_back(i); }
		void aggiungiPaziente(shared_ptr<Paziente> p){ pazienti.push_back(p); }*/

		
	    void aggiungiReparto(shared_ptr<Reparto> r);
	    void aggiungiOperazione(const Operazione& op);
	    
	    void stampaDati()const;
	    void stampaReparti()const;
	    void stampaOperazioni()const;
	    void stampaPersonale();
	    void stampaPazienti();
	    
	    
	    ~Ospedale();
};

#endif
