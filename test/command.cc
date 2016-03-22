#include "command.h"
#include <iostream>
#define inMem

using namespace std;

string Command::readString() {
	string re = "";
	unsigned char c = 0;
	cout << "readString" << endl;
	while (true) {
		c = conn->read();
		if(c==0){
			break;
		}
		re+=c;
	}
	return re;
}
int Command::readNumber() {
	unsigned char byte1 = conn->read();
	unsigned char byte2 = conn->read();
	unsigned char byte3 = conn->read();
	unsigned char byte4 = conn->read();
	return (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
}

void Command::handleCom() {
	switch (conn->read())
	{
	case Protocol::COM_LIST_NG:
		cout << "test " << readString() << endl;
		// data.listAllNewsgroups();
		break;
	case Protocol::COM_CREATE_NG:
		data.createNewsgroup(readString());
		break;
	case Protocol::COM_DELETE_NG:
		data.deleteNewsgroup(readNumber());
		break;
	case Protocol::COM_LIST_ART:
		data.listArticle(readNumber());
		break;
	case Protocol::COM_CREATE_ART:
		data.createArticle(readNumber(), readString(),readString(),readString());
		break;
	case Protocol::COM_DELETE_ART:
		data.deleteArticle(readNumber(), readNumber());
		break;
	case Protocol::COM_GET_ART:
		data.getArticle(readNumber(), readNumber());
		break;
	default:
		 ;
	}
}