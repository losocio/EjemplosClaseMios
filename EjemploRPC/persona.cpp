#include "persona.h"


Persona::Persona(string nombre, int edad):nombre(nombre),edad(edad){}
	
Persona::Persona():nombre(""),edad(0){}

Persona::~Persona(){}
	
void Persona::setEdad(int edad){this->edad=edad;}
int Persona::getEdad(){return edad;}
	
void Persona::setNombre(string nombre){this->nombre=nombre;}
string Persona::getNombre(){return nombre;}