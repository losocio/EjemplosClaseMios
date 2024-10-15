#include "persona.h"

int main(int arg, char** argv)
{
	Persona p1("Marcos", 18);
	
	cout<<"Nombre:"<<p1.getNombre()<<"\n"<<"Edad:"<<p1.getEdad()<<endl;
	
	return 0;
}