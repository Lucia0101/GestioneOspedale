#include "Infermiere.h"

#include <iostream>
#include <algorithm>
using namespace std;

Infermiere::Infermiere(string _nome,string _cognome,int _eta,string _codID,string _reparto,string _turno):
Persona(_nome, _cognome, _eta),codID(_codID),reparto(_reparto),turno(_turno){ }


void Infermiere::ordinaPerCognome(vector<Infermiere*>& infermieri) {
    sort(infermieri.begin(), infermieri.end(),
        [](Infermiere* a, Infermiere* b) {
            return a->getCognome() < b->getCognome();
        });
}


void Infermiere::stampaInfo()const{
	cout<<"INFERMIERE: "<<cognome<<" "<<nome<<", codID ("<<codID << "), "<<eta<<" anni"<<endl;
	cout<<"Reparto: "<<reparto<<endl;
	cout<<"Turno: "<<turno<<endl;
}
