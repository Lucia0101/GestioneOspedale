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
	
	public:
		Operazione();
		Operazione(string d,string cf,string typ,string cu);
		~Operazione();
		
		string getData() const { return data; }
		string getCFPaziente() const { return cf_paz; }
		string getTipo() const { return tipo; }
		string getEsito()const{return esito;}
		string getCura() const { return cura; }
		
		void stampaInfo()const;
		void aggiungiMedico(shared_ptr<Medico> m);
};

#endif
