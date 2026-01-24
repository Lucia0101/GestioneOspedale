#ifndef __STAMPA_H__
#define __STAMPA_H__

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

//template per stampa in ordine di cognome di un contenitore
template<typename Contenitore>
void stampaPerCognome(const Contenitore& container,const string& titolo) { 
	//ricava tipo di dato
    using TipoPuntatore=typename Contenitore::value_type;
    
    vector<TipoPuntatore> copiaOrdinata;
    
    for(const auto& elem : container) {
        copiaOrdinata.push_back(elem);
    }
    
    //funzione lambda per confronto dei cognomi
    sort(copiaOrdinata.begin(),copiaOrdinata.end(),
        [](TipoPuntatore a, TipoPuntatore b){
            return a->getCognome() < b->getCognome();
        });
    
    cout<<"\n"<<titolo<<endl;
    
    for (const auto& elem : copiaOrdinata) {
        elem->stampaInfo();
        cout << endl;
    }
}

//specializzazione di stampa per list<Paziente*> perché uso list 
template<>
void inline stampaPerCognome<list<Paziente*>>(const list<Paziente*>& container,const string& titolo) {
    //crea una copia ordinabile
    list<Paziente*> copiaOrdinata=container;
    
    //usa il sort specifico per list
    copiaOrdinata.sort([](Paziente* a,Paziente* b){
        return a->getCognome() < b->getCognome();
    });
    
	cout<<"\n"<<titolo<<endl;
    
    //stampa gli elementi ordinati
    for(const auto& elem : copiaOrdinata) {
        elem->stampaInfo();
        cout<<endl;
    }
}

#endif
