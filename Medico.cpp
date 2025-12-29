#include "Medico.h"
#include <iostream>
using namespace std;

Medico::Medico(string _nome,string _cognome,int _eta,string _codID,string _specializzazione):
Persona(_nome, _cognome, _eta),codID(_codID),specializzazione(_specializzazione),occupato(false){}

void Medico::stampaInfo()const{
	 cout<<"MEDICO: "<<nome<<" "<<cognome 
        <<", codID ("<<codID << "), "<<eta<<" anni" 
        <<", specializzazione: "<<specializzazione;
}