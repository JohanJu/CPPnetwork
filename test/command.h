#ifndef COMMAND_H
#define COMMAND_H
#include "protocol.h"
#include "connection.h"
#include "connectionclosedexception.h"
#include "database.h"

class Command{
public:
	Command(std::shared_ptr<Connection>& c, Database* d):conn(c),data(*d){}
	void handleCom();

private:
std::shared_ptr<Connection>& conn;
Database& data;

};

#endif