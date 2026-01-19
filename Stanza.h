#ifndef __STANZA_H__
#define __STANZA_H__
#include <string>
using namespace std;

class Stanza{
	private:
		int numStanza;
		int numLetti;
		int lettiOccupati;
		string reparto;
		
	public:
		Stanza();
		Stanza(int stanza,int letti,string rep);
		
		int getNumStanza()const{return numStanza;}
		
		bool isPiena() const{return lettiOccupati >= numLetti;};
		bool isVuota() const{return lettiOccupati == 0;};
		
		void occupaLetto(); //incrementa letti occupati
		void liberaLetto(); //decrementa letti occupato
		void azzeraLetti() { lettiOccupati = 0; }
		
		void stampaDettagli() const; 
				
		~Stanza(){}
};


#endif
