#include <iostream>
#include "Persona.h"
#include "Medico.h"
#include "Infermiere.h"
#include "Paziente.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	
	Medico m("Lucia", "Pecora", 24, "LP01", "Pediatria");
	cout << m << endl;
	
	Infermiere i("Fiaba", "Roncoletta", 24, "FR01", "Geriatria", "Notte");
	cout << i << endl;
	
	Paziente p("Beatrice", "Faccioli", 22, "BF04R81", "Pennicillina", "Chirurgia Estetica", "8/11/25", "12/11/25", 5);
	cout << p << endl;
	
	return 0;
		
}





