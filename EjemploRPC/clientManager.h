#pragma once
#include "utils.h"
#include "persona.h"

typedef enum{
	
	requestOK,
	requestNoOK,
	constructor1, //defecto
	constructor2, //params nombre,edad
	destructor,
	fsetNombre,
	fgetNombre,
	fsetEdad,
	fgetEdad
}personaFuncs;

class clientManager // NOTE: clase statica para poder usarlas desde todo el codigo
{
	public:
		static inline connection_t serverConn;
		static inline std::map<int, Persona> clients; //NOTE: para var estatica siempre poner inline
		static inline bool exit=false;
		
		static void attendConnection(int clientId);
};