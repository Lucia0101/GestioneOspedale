#ifndef __PERSONA_H__
#define __PERSONA_H__
#include <string>

using namespace std;

class Persona{
	private:
	protected:
		string nome, cognome;
		int eta;
	
	public:
		// costruttore specifico
		Persona(string _nome, string _cognome, int _eta); 
		
		// distruttore
		virtual ~Persona();
		
		// stampa
		virtual ostream& stampaoperator(ostream& os)const;
		
		friend ostream& operator << (ostream& os, const Persona& p);
		
		virtual void test()=0;//rende la classe virtuale (quindi non si può direttamente creare nel main una persona p, dà errore)

};

ostream& operator << (ostream& os, const Persona& p);

#endif
