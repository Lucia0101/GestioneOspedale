#include "Reparto.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

Reparto::Reparto(){
	nome="";
	numMedici=0;
	numInfermieri=0;
	numLettiLiberi=0;
	numLettiOccupati=0;
	specializzazione="";
}

Reparto::Reparto(string n,int numM,int numInf,int LL,int LO,string spec):nome(move(n)),specializzazione(move(spec)){
	numMedici=numM;
	numInfermieri=numInf;
	numLettiLiberi=LL;
	numLettiOccupati=LO;
	
	for(int i=0;i<10;++i){
		stanze.emplace_back(i,2,nome);
	}
	numLettiLiberi=10*2;
	
}

void Reparto::stampaInfo()const{
	cout<<"Reparto: "<<nome<<" | Specializzazione: "<<specializzazione<<endl;
}

void Reparto::stampaDettagli()const{
	stampaInfo();
	
	cout<<"Medici: "<<numMedici<<" | Infermieri: "<<numInfermieri<<endl;
	cout<<"Letti liberi: "<<numLettiLiberi<<" | Letti occupati: "<<numLettiOccupati<<endl;
	
	for(const auto& s:stanze){
		cout<<" Stanza "<<s.getNumStanza()<<" | Letti: "<<s.getNumLetti()<<endl;
	}
}