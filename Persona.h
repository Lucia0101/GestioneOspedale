#ifndef __PERSONA_H__
#define __PERSONA_H__

#include <string>
using namespace std;

class Persona{
	private:
	protected:
		string nome;
		string cognome;
		int eta;
	
	public:
		Persona(string _nome,string _cognome,int _eta); 
    	Persona(const Persona& p);
    	Persona(Persona&& p) noexcept;
		virtual ~Persona();
		
		virtual void stampaInfo()const;
		friend ostream& operator << (ostream& os,const Persona& p);
		
		string getNome() const { return nome; }
        string getCognome() const { return cognome; }
        int getEta()const {return eta;}
				
};


#endif
