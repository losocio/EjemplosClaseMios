#include "clientManager.h"

void clientManager::packTextMessage(
			std::vector<unsigned char> &buffer,
			std::string name,std::string message)
{
			pack<char>(buffer,CHAT_MESSAGE);
			//empaquetar tam name, name
			pack<int>(buffer,(int)name.size());
			packv<unsigned char>(buffer,(unsigned char*)name.data(),
								(int)name.size());
			
			//empaquetar tam message, message
			pack<int>(buffer,(int)message.size());
			packv<unsigned char>(buffer,(unsigned char*)message.data(),
								(int)message.size());
}

void clientManager::unpackTextMessage(
			std::vector<unsigned char> &buffer,
			std::string &name,std::string &message)
{
	/*
	char typeMSG= unpack<char>(buffer);
	
	// algo falta
	if(typeMSG!=CHAT_MESSAGE){
		std::cout<<"ERROR: Message type does not match "<<__LINE__<<" "<<__FILE__<<"\n";
	}*/

	//unpack tam name
	int tam=unpack<int>(buffer);
	//unpack name
	name.resize(tam);
	unpackv<unsigned char>(buffer, (unsigned char*)name.data(),tam);

	//unpack tam message
	tam=unpack<int>(buffer);
	//unpack message
	message.resize(tam);
	unpackv<unsigned char>(buffer, (unsigned char*)message.data(),tam);
}

void clientManager::addClient(std::string name,int clientId){
	clients[name]=clientId;
}

void clientManager::broadcastMessage(std::string name,std::string message){
	std::vector<unsigned char> buffer;
	
	packTextMessage(buffer,name,message);
	
	for(auto &par: clients)
	{
		if(par.first!=name)
		{
			sendMSG(par.second,buffer);
			
		}
	}
}

//void atiendeConexion(int clientId)
void clientManager::attendConnection(int clientId){
	bool conexionCerrada=false;
	
	std::vector<unsigned char> buffer; //NOTE: unsigned char es el equivalente al byte
	std::string name,message;
	
	//mientras no cierre conexion
	while(!conexionCerrada)
	{
		//atender mensaje
			//recibir mesaje
			recvMSG(clientId, buffer);
			char tipo=unpack<char>(buffer);
			//si no es conn cerrada
			if(tipo==CHAT_MESSAGE)
			{
				unpackTextMessage(buffer,name, message);
				addClient(name,clientId);
				std::cout<<"MENSAJE RECIBIDO:"<<name<<":"<<message<<"\n\n";
				broadcastMessage(name, message);
			}
			if(tipo==CHAT_CLOSED)
			{
				conexionCerrada=true;
			}
	}
	//cerrar conexion cliente
	closeConnection(clientId);
	clients.erase(name);
}