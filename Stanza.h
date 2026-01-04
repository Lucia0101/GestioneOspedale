#ifndef __STANZA_H__
#define __STANZA_H__
#include <string>
using namespace std;

class Stanza{
	private:
		int numStanza;
		int numLetti;
		string reparto;
		
	public:
		Stanza();
		Stanza(int stanza,int letti,string rep);
		
		int getNumStanza()const{return numStanza;}
		int getNumLetti()const{return numLetti;}
				
		~Stanza(){}
};


#endif
