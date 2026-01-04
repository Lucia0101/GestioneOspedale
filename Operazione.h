#ifndef __OPERAZIONE_H__
#define __OPERAZIONE_H__
#include <string>
#include <vector>
#include <memory>
using namespace std;

class Medico;

class Operazione{
	private:
		string data;
		string cf_paz;
		string tipo;
		string esito;
		string cura;
		
		vector<shared_ptr<Medico>> teamMedico;
	
	public:
		Operazione();
		Operazione(string d,string cf,string type,string es,string cu);
		
		void stampaInfo()const;
		void aggiungiMedico(shared_ptr<Medico> m);
		
		~Operazione(){}
	
};


#endif
