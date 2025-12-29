#include "Infermiere.h"
#include <iostream>
using namespace std;

Infermiere::Infermiere(string _nome,string _cognome,int _eta,string _codID,string _reparto,string _turno):
Persona(_nome, _cognome, _eta),codID(_codID),reparto(_reparto),turno(_turno){}

void Infermiere::stampaInfo()const{
	cout<<"INFERMIERE: "<<nome<<" "<<cognome 
         <<", codID: ("<<codID << "), "<<eta<<" anni" 
         <<", reparto: "<<reparto 
         <<", turno: "<<turno;
}