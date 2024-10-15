#include "persona.h"
#include "utils.h"
#include "clientManager.h"

Persona::Persona(string nombre, int edad):nombre(nombre),edad(edad){ //NOTE: Lo de ":nombre(nombre),edad(edad)" no lo tinen el profe en el codigo pasado. POSIBILIDAD de ERROR
	
	clientManager::serverConn=initClient("127.0.0.1",8080);
	//crear persona
	vector<unsigned char> buffer;
	//crear buffer
	//insertar request
		//tipo msg
	pack(buffer,constructor2);
	pack(buffer,(int)nombre.size());
	packv(buffer,(char*)nombre.data(), nombre.size());
	pack(buffer,(int)edad);
	
	//send request
	sendMSG(clientManager::serverConn.serverId,buffer);
	//recv ok
	buffer.clear();
	recvMSG(clientManager::serverConn.serverId,buffer);
	auto ok = unpack<personaFuncs>(buffer);
	if(ok!=requestOK)
		cout<<"ERROR constructor persona "<<__FILE__<<":"<<__LINE__<<"\n"; //TODO: el final de la linea no lo puedo ver
}
	
Persona::Persona(){
	
	clientManager::serverConn=initClient("127.0.0.1",8080);
	//crear persona
		vector<unsigned char> buffer;
		//crear buffer
		//insertar request
			//tipo msg
		pack(buffer,constructor1);
		//send request
		sendMSG(clientManager::serverConn.serverId,buffer);
		//recv ok
		buffer.clear();
		recvMSG(clientManager::serverConn.serverId,buffer);
		auto ok = unpack<personaFuncs>(buffer);
		if(ok!=requestOK)
			cout<<"ERROR constructor persona "<<__FILE__<<":"<<__LINE__<<"\n"; //TODO: el final de la linea no lo puedo ver
	
}

Persona::~Persona(){
	//crear persona
		vector<unsigned char> buffer;
		//crear buffer
		//insertar request
			//tipo msg
		pack(buffer,destructor);
		//send request
		sendMSG(clientManager::serverConn.serverId,buffer);
		//recv ok
		buffer.clear();
		recvMSG(clientManager::serverConn.serverId,buffer);
		auto ok = unpack<personaFuncs>(buffer);
		if(ok!=requestOK)
			cout<<"ERROR destructor persona "<<__FILE__<<":"<<__LINE__<<"\n";  //TODO: el final de la linea no lo puedo ver
		
		closeConnection(clientManager::serverConn.serverId);
	
}
	
void Persona::setEdad(int edad){
	
	vector<unsigned char> buffer;
	//crear buffer
	//insertar request
		//tipo msg
	pack(buffer,fsetEdad);
	pack(buffer,(int)edad);
	
	sendMSG(clientManager::serverConn.serverId,buffer);
	//recv ok
	buffer.clear();
	recvMSG(clientManager::serverConn.serverId,buffer);
	auto ok=unpack<personaFuncs>(buffer);
	if(ok!=requestOK)
			cout<<"ERROR setEdad persona "<<__FILE__<<":"<<__LINE__<<"\n";
}

int Persona::getEdad(){
	vector<unsigned char> buffer;
	//crear buffer
	//insertar request
		//tipo msg
	pack(buffer,fgetEdad);
	
	sendMSG(clientManager::serverConn.serverId,buffer);
	
	buffer.clear();
	recvMSG(clientManager::serverConn.serverId,buffer);
	auto ok = unpack<personaFuncs>(buffer);
	if(ok!=requestOK)
		cout<<"ERROR getEdad persona "<<__FILE__<<":"<<__LINE__<<"\n";  //TODO: el final de la linea no lo puedo ver
	
	return unpack<int>(buffer);
}
	
void Persona::setNombre(string nombre){
	vector<unsigned char> buffer;
	//crear buffer
	//insertar request
		//tipo msg
	pack(buffer,fsetNombre);
	
	pack(buffer,(int)nombre.size());
	packv(buffer,(char*)nombre.data(),nombre.size());
	
	sendMSG(clientManager::serverConn.serverId,buffer);
	//recv ok
	buffer.clear();
	recvMSG(clientManager::serverConn.serverId,buffer);
	auto ok=unpack<personaFuncs>(buffer);
	if(ok!=requestOK)
			cout<<"ERROR setNombre persona "<<__FILE__<<":"<<__LINE__<<"\n";

}

string Persona::getNombre(){
	
	vector<unsigned char> buffer;
	//crear buffer
	//insertar request
		//tipo msg
	pack(buffer,fgetNombre);
	
	sendMSG(clientManager::serverConn.serverId,buffer);
	
	buffer.clear();
	recvMSG(clientManager::serverConn.serverId,buffer);
	auto ok = unpack<personaFuncs>(buffer);
	if(ok!=requestOK)
		cout<<"ERROR getNombre persona "<<__FILE__<<":"<<__LINE__<<"\n";  //TODO: el final de la linea no lo puedo ver
	string nombre;

	nombre.resize(unpack<int>(buffer));
	unpackv<char>(buffer,(char*)nombre.data(),nombre.size());
	
	return nombre;
}

