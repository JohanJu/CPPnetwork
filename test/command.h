#ifndef COMMAND_H
#define COMMAND_H
#include "protocol.h"
#include "connection.h"
#include "connectionclosedexception.h"
#include "database.h"
// #include "InMemoryDatabase.h" //added
#include <memory>
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>

class Command {
public:
	Command(std::shared_ptr<Connection>& c, Database* d): conn(c), data(*d) {}
	void handleCom();

private:
	std::string readString();
	int readNumber();
	std::shared_ptr<Connection>& conn;
	Database& data;

};

#endif