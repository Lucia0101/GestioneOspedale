#include "Stanza.h"
#include <iostream>
#include <string>
using namespace std;

Stanza::Stanza():numStanza(0),numLetti(0),reparto(""){}

Stanza::Stanza(int stanza,int letti,string rep):numStanza(stanza),numLetti(letti),reparto(move(rep)){}