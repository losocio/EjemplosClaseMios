#include "utils.h"
#include <iostream>
#include <string>
#include <thread>
#include <list>
#include "clientManager.h"


int main(int argc, char** argv)
{
	//server:
	//iniciar server
	// Buffer de llegada
	int serverSocket=initServer(8080);
	
	//esperar conexion
	std::cout<<"Server inniciado"<<"\n";
	
	while(1){ //Para testing, Habra que salir usando CTRL+C
		//mientras no hay cliente
		while(!checkClient())
			usleep(100);
		//esperar
		if(checkClient()){
		//atender conexion
			int clientId=getLastClientID();
			std::cout<<"Conectado el cliente: "<<clientId<<"\n";
			
			std::thread* th=new std::thread(clientManager::attendConnection,clientId); // pasarle al thread la func a ejecutar y despues los parametros de dicha func
		}
	}	
	
	//cerrar server
	close(serverSocket);
	
	return 0;
}
