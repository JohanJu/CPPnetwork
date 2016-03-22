#ifndef COMMAND_H
#define COMMAND_H
#include "protocol.h"
#include "connection.h"
#include "connectionclosedexception.h"

class Command{
public:
	Command(std::shared_ptr<Connection>& c):conn(c){}
	void handleCom();

private:
std::shared_ptr<Connection>& conn;


};

#endif