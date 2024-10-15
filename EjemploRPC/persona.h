#pragma once
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Persona{
	private:
		string nombre;
		int edad;
		
	public:
		Persona(string nombre, int edad);
		Persona();
		
		~Persona();
		
		void setEdad(int edad);
		int getEdad();
		
		void setNombre(string nombre);
		string getNombre();
		
};