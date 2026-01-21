#ifndef __STAMPA_H__
#define __STAMPA_H__

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

//template base per stampare elementi ordinati per cognome dei vector
template<typename Contenitore>
void stampaPerCognome(const Contenitore& container,const string& titolo) { //<- funzione template
    //crea una copia ordinabile del contenitore
    using TipoPuntatore=typename Contenitore::value_type;
    using TipoOggetto=typename remove_pointer<TipoPuntatore>::type;
    
    vector<TipoPuntatore> copiaOrdinata;
    
    //copia gli elementi
    for(const auto& elem : container) {
        copiaOrdinata.push_back(elem);
    }
    
    //ordina per cognome
    sort(copiaOrdinata.begin(),copiaOrdinata.end(),
        [](TipoPuntatore a, TipoPuntatore b){
            return a->getCognome() < b->getCognome();
        });
    
    //stampa il titolo
    cout<<"\n"<<titolo<<endl;
    
    //stampa gli elementi ordinati
    for (const auto& elem : copiaOrdinata) {
        elem->stampaInfo();
        cout << endl;
    }
}

//specializzazione per list<Paziente*> perché uso list (sort è diverso in list)
template<>
void stampaPerCognome<list<Paziente*>>(const list<Paziente*>& container,const string& titolo) {
    //crea una copia ordinabile
    list<Paziente*> copiaOrdinata=container;
    
    //usa il sort specifico per list
    copiaOrdinata.sort([](Paziente* a,Paziente* b){
        return a->getCognome() < b->getCognome();
    });
    
    //stampa il titolo
	cout<<"\n"<<titolo<<endl;
    
    //stampa gli elementi ordinati
    for(const auto& elem : copiaOrdinata) {
        elem->stampaInfo();
        cout<<endl;
    }
}

#endif
