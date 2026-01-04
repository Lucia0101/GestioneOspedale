#ifndef __REPARTO_H__
#define __REPARTO_H__
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <mutex>

#include "Stanza.h"
using namespace std;

class Reparto{
	private:
		string nome;
		int numMedici;
		int numInfermieri;
		int numLettiLiberi;
		int numLettiOccupati;
		string specializzazione;
		
		//composizione: reparto possiede le stanze
		vector<Stanza> stanze;
		mutable mutex mtx;
		
	public:
		Reparto();
		Reparto(string n,int numM,int numInf,int LL,int LO,string spec);
		
		void stampaInfo()const;
		void stampaDettagli()const;
		
		bool occupaLetto(){
        	lock_guard<mutex>lock(mtx);
        	if(numLettiLiberi>0) {
          	  	numLettiLiberi--;
           		numLettiOccupati++;
           	 	return true;
        	}
        	return false;
    	}
    	
    	string getNome()const{return nome;}
		
		~Reparto(){}
		
};


#endif
