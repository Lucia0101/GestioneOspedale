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

int dataToIn(string data);

class Ospedale{
	private:
		string nome;

		map<string, vector<shared_ptr<Reparto>>> reparti;
    	vector<Operazione> registroOperazioni;
    
	    vector<Medico*> medici;
	    vector<Infermiere*> infermieri;
	    list<Paziente*> pazienti; 
	    
	public:
		Ospedale();
	    Ospedale(string n);
	    ~Ospedale();
	
		void aggiungiMedico(Medico* m){medici.push_back(m);}
		void aggiungiInfermiere(Infermiere* i){infermieri.push_back(i);}
		void aggiungiPaziente(Paziente* p){pazienti.push_back(p);}
		
		vector<Medico*> getMedici() const { return medici;  } 
		vector<Infermiere* > getInfermieri()const {return infermieri;} 
		list<Paziente* > getPazienti()const {return pazienti;}
		const map<string, vector<shared_ptr<Reparto>>>& getReparti() const { return reparti; }
		
		shared_ptr<Reparto> getReparto(string nomeReparto);
		list<Paziente*> getPazientiProgrammati()const;
	    list<Paziente*> getPazientiDimessi()const;
	
	    void aggiungiReparto(shared_ptr<Reparto> r);
	    void aggiungiOperazione(const Operazione& op);
	    
	    void stampaDati()const;
	    void stampaReparti()const;
	    void stampaOperazioni()const;
	    void stampaMediciOrdinati(); 
	    void stampaInfermieriOrdinati();
	    void stampaPazientiOrdinati();
	    void stampaPazientiFiltrati() const;
	    
	    Paziente& findCFpaziente(const string& cf);
	    Medico* findMedicoByID(const string& id);
};

#endif
