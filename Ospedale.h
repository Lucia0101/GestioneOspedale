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
	
		void aggiungiMedico(Medico* m){medici.push_back(m);}
		void aggiungiInfermiere(Infermiere* i){infermieri.push_back(i);}
		void aggiungiPaziente(Paziente* p){pazienti.push_back(p);}
		
		vector<Medico*> getMedici() const { return medici;  } 
		vector<Infermiere* > getInfermieri()const {return infermieri;} 
		list<Paziente* > getPazienti()const {return pazienti;}
	
	    void aggiungiReparto(shared_ptr<Reparto> r);
	    void aggiungiOperazione(const Operazione& op);
	    
	    shared_ptr<Reparto> getReparto(string nomeReparto);
	    
	    void stampaDati()const;
	    void stampaReparti()const;
	    void stampaOperazioni()const;
	    void stampaMediciOrdinati(); 
	    void stampaInfermieriOrdinati();
	    void stampaPazientiOrdinati();
	    
	    Paziente& findCFpaziente(const string& cf);
	   
	    void stampaPazientiFiltrati() const; 
	    void stampaPazientiProgrammati() const;
	    void stampaPazientiDimessi() const;
	    
	    Medico* findMedicoByID(const string& id);
	    const map<string, vector<shared_ptr<Reparto>>>& getReparti() const { return reparti; }
	    
	    ~Ospedale();
};

#endif
