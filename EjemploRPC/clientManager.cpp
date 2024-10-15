#include "clientManager.h"

void clientManager::attendConnection(int clientId){
	bool conexionCerrada=false;
	
	std::vector<unsigned char> buffer; //NOTE: unsigned char es el equivalente al byte
	//std::string nombre,message; //TODO: antes era name, no nombre
	
	//mientras no cierre conexion
	while(!conexionCerrada)
	{
		//atender mensaje
			//recibir mesaje
			recvMSG(clientId, buffer);
			auto tipo=unpack<personaFuncs>(buffer);
			switch(tipo){
				case requestOK:{
				
				}break;
				case requestNoOK:{
					
				}break;
				case constructor1:{
				//crear persona defecto
					Persona p;
				//insertar en lista clientes
					clients[clientId]=p;
				//send OK
					buffer.clear();
					pack(buffer, requestOK);
				
				}break;
				case constructor2:{
				//crear persona defecto
					int edad;
					string nombre;
					
					nombre.resize(unpack<int>(buffer));
					unpackv<char>(buffer, (char*)nombre.data(),nombre.size());
					edad=unpack<int>(buffer);
					Persona p(nombre,edad);
				//insertar en lista clientes
					clients[clientId]=p;
				//send OK
					buffer.clear();
					pack(buffer, requestOK);
				}break;
				case destructor:{
					clients.erase(clientId);
					buffer.clear();
					pack(buffer, requestOK);
					
					conexionCerrada=true;
				}break;		
				case fsetNombre:{
					//desempacar
					string nombre;
					
					nombre.resize(unpack<int>(buffer));
					unpackv<char>(buffer, (char*)nombre.data(),nombre.size());
					
					//acceder metodo
					clients[clientId].setNombre(nombre);
					//send OK
					buffer.clear();
					pack(buffer, requestOK);
				}break;
				case fgetNombre:{
				//send OK	
					buffer.clear();
					pack(buffer, requestOK);
					
					string nombre=clients[clientId].getNombre();
					pack(buffer,(int)nombre.size());
					packv(buffer,(char*)nombre.data(),nombre.size());
				
				}break;
				case fsetEdad:{
					clients[clientId].setEdad(unpack<int>(buffer));
				//send OK
					buffer.clear();
					pack(buffer, requestOK);
				}break;
				case fgetEdad:{
				buffer.clear();
					pack(buffer, requestOK);
					pack(buffer, clients[clientId].getEdad());

				}break;
			};
			sendMSG(clientId,buffer);
	}
	//cerrar conexion cliente
	closeConnection(clientId);
}


/*
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
*/
/*
void clientManager::unpackTextMessage(
			std::vector<unsigned char> &buffer,
			std::string &name,std::string &message)
{
	
	//char typeMSG= unpack<char>(buffer);
	//
	// //algo falta
	//if(typeMSG!=CHAT_MESSAGE){
	//	std::cout<<"ERROR: Message type does not match "<<__LINE__<<" "<<__FILE__<<"\n";
	//}

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
*/
/*
void clientManager::addClient(std::string name,int clientId){
	clients[name]=clientId;
}
*/
/*
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
*/