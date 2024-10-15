#pragma once
#include "utils.h"
#include "chat.h"

// NOTE: clase statica para poder usarlas desde todo el codigo
class clientManager
{
	public:
		static inline std::map<std::string,int> clients; //NOTE: para var estatica siempre poner inline
		static inline bool exit=false;
		
		static void addClient(std::string name,int clientId);
		static void broadcastMessage(std::string name,std::string message);
		static void attendConnection(int clientId);
		static void packTextMessage(
					std::vector<unsigned char> &buffer,
					std::string name,std::string message);
		static void unpackTextMessage(
					std::vector<unsigned char> &buffer,
					std::string &name,std::string &message);

		
		
};