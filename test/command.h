#ifndef COMMAND_H
#define COMMAND_H
#include "protocol.h"
#include "connection.h"
#include "connectionclosedexception.h"
#include "InMemoryDatabase.h"
#include <memory>
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <vector>

class Command {
public:
	Command(std::shared_ptr<Connection>& c, InMemoryDatabase* d): conn(c), data(*d) {}
	void handleCom();

private:
	std::string readString();
	int readNumber();
	int readNumberS();
	void writeString(const std::string&);
	void writeNumber(int);
	void writeNumberS(int);
	void end();
	std::shared_ptr<Connection>& conn;
	InMemoryDatabase& data;
};

#endif