#include "utils.h"
#include <string>
#include <iostream>
#include <string>
//#include "chat.h"
#include "clientManager.h"

void receiveTextMessageFromServer(int serverId){


	while(!clientManager::exit){
		std::string name,message;
		std::vector<unsigned char> buffer;
		
		recvMSG(serverId,buffer);
		char messageType=unpack<char>(buffer);
		if(messageType==CHAT_MESSAGE){
			clientManager::unpackTextMessage(buffer,name,message);
			std::cout<<"MENSAJE>> "<<name<<":"<<message<<"\n";
		}
		if(messageType==CHAT_CLOSED){
			clientManager::exit=true;
		}
	}
}

int main(int argc,char** argv)
{
	//iniciar cliente
	connection_t serverConn=initClient("127.0.0.1",8080); //NOTE: struct con datos de la conexion
	
	std::thread *th =new std::thread(receiveTextMessageFromServer,serverConn.serverId);
	
	std::vector<unsigned char> buffer;
	
	//pedir nombre usuario
	std::string nombre,msg;
	std::cout<<"Introduzca nombre de usuario:\n";
	//almacenar nombre
	std::cin>>nombre;
	do{
	//bucle leer mensajes
		//leer linea
		std::cin>>msg;
		//Limpiar buffer
		buffer.clear();
		//si linea != "exit"
		if(msg!="exit")
		{
			clientManager::packTextMessage(buffer, nombre,msg);
			sendMSG(serverConn.serverId,buffer);
		}
		else{
		//else
			//enviar mensaje cierre conexion
			pack<char>(buffer,CHAT_CLOSED);
			sendMSG(serverConn.serverId,buffer);
			//salir bucle
		}
	}while(msg!="exit");
	
	closeConnection(serverConn.serverId);
    return 0;
}
