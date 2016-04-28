/* myclient.cc: sample client program */
#include "connection.h"
#include "connectionclosedexception.h"
#include "protocol.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>

using namespace std;

Connection *conn;



int readNumberS() {
	unsigned char byte1 = conn->read();
	unsigned char byte2 = conn->read();
	unsigned char byte3 = conn->read();
	unsigned char byte4 = conn->read();
	return (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
}
int readNumber() {
	if (conn->read() != Protocol::PAR_NUM) {
		cout << "err PAR_NUM" << endl;
	}
	return readNumberS();
}


void writeNumberS(int value) {
	conn->write((value >> 24) & 0xFF);
	conn->write((value >> 16) & 0xFF);
	conn->write((value >> 8) & 0xFF);
	conn->write(value & 0xFF);
}

void writeNumber(int value) {
	conn->write(Protocol::PAR_NUM);
	writeNumberS(value);
}

void writeString(const string& msg) {
	conn->write(Protocol::PAR_STRING);
	writeNumberS(msg.length());
	for (unsigned char c : msg) {
		conn->write(c);
	}

}

string readString() {
	if (conn->read() != Protocol::PAR_STRING) {
		cout << "err PAR_STRING" << endl;
	}
	string re;
	unsigned char c = 0;
	int n = readNumberS();
	for (int i = 0; i < n; ++i)
	{
		c = conn->read();
		re += c;
	}
	return re;
}

void pMenu(){
	cout << "1. List newsgroups." << endl;
	cout << "2. Create a newsgroup. The title of the group is sent as a parameter." << endl;
	cout << "3. Delete a newsgroup. The identification number of the group is sent as a parameter." << endl;
	cout << "4. List articles in a newsgroup. The identification number of the group is sent as a parameter." << endl;
	cout << "5. Create an article. The identification number of the group is sent as a parameter, followed by the article title, author and text." << endl;
	cout << "6. Delete an article. The group and article identification numbers are sent as parameters." << endl;
	cout << "7. Get an article.  The group and article identification numbers are sent as parameters." << endl;
	cout << "8. Exit" << endl;
}

void handleCom(int com) {
	cout << endl;
	switch (com)
	{
	case 1: {
		conn->write(Protocol::COM_LIST_NG);
		conn->write(Protocol::COM_END);
		conn->read();
		int n = readNumber();
		cout << "nnr: " << n << endl;
		for (int i = 0; i < n; ++i)
		{
			cout << "nr: " << readNumber();
			cout << " name: "<< readString() << endl;
		}
		conn->read();
		break;
	}
	case 2: {
		conn->write(Protocol::COM_CREATE_NG);
		cout << "title: ";
		string s;
		cin >> s;
		writeString(s);
		conn->write(Protocol::COM_END);
		conn->read();
		char c = conn->read();
		if(c == Protocol::ANS_ACK)
			cout << "OK" << endl;
		else{
			cout << "NG exist" << endl;
			conn->read();
		}
		conn->read();
		break;
	}
	case 3: {
		conn->write(Protocol::COM_DELETE_NG);
		cout << "nr: ";
		int s;
		cin >> s;
		writeNumber(s);
		conn->write(Protocol::COM_END);
		conn->read();
		char c = conn->read();
		if(c == Protocol::ANS_ACK)
			cout << "OK" << endl;
		else{
			cout << "NG not exist" << endl;
			conn->read();
		}
		conn->read();
		break;
	}
	case 4: {
		conn->write(Protocol::COM_LIST_ART);
		cout << "nr: ";
		int s;
		cin >> s;
		writeNumber(s);
		conn->write(Protocol::COM_END);
		conn->read();
		char c = conn->read();
		if(c == Protocol::ANS_ACK){
			int n = readNumber();
			for (int i = 0; i < n; ++i)
			{
				cout << "nr: " << readNumber();
				cout << " name: "<< readString() << endl;
			}
		}else{
			cout << "NG not exist" << endl;
			conn->read();
		}
		conn->read();
		break;
	}
	case 5: {
		conn->write(Protocol::COM_CREATE_ART);
		cout << "nr: ";
		int s;
		cin >> s;
		cout << "title: ";
		string ss;
		cin >> ss;
		cout << "author: ";
		string sss;
		cin >> sss;
		cout << "text: ";
		string ssss;
		cin >> ssss;
		writeNumber(s);
		writeString(ss);
		writeString(sss);
		writeString(ssss);
		conn->write(Protocol::COM_END);
		conn->read();
		char c = conn->read();
		if(c == Protocol::ANS_ACK)
			cout << "OK" << endl;
		else{
			cout << "NG not exist" << endl;
			conn->read();
		}
		conn->read();
		break;
	}
	case 6: {
		conn->write(Protocol::COM_DELETE_ART);
		cout << "gnr: ";
		int s;
		cin >> s;
		cout << "anr: ";
		int ss;
		cin >> ss;
		writeNumber(s);
		writeNumber(ss);
		conn->write(Protocol::COM_END);
		conn->read();
		char c = conn->read();
		if(c == Protocol::ANS_ACK){
			cout << "OK" << endl;
		}else{
			c = conn->read();
			if(c == Protocol::ERR_NG_DOES_NOT_EXIST)
				cout << "NG not exist" << endl;
			else
				cout << "ART not exist" << endl;
		}
		conn->read();
		break;
	}
	case 7: {
		conn->write(Protocol::COM_GET_ART);
		cout << "gnr: ";
		int s;
		cin >> s;
		cout << "anr: ";
		int ss;
		cin >> ss;
		writeNumber(s);
		writeNumber(ss);
		conn->write(Protocol::COM_END);
		conn->read();
		char c = conn->read();
		if(c == Protocol::ANS_ACK){

			cout << " title: "<< readString();
			cout << " author: "<< readString();
			cout << " text: "<< readString() << endl;
		}else{
			c = conn->read();
			if(c == Protocol::ERR_NG_DOES_NOT_EXIST)
				cout << "NG not exist" << endl;
			else
				cout << "ART not exist" << endl;
		}
		conn->read();
		break;
	}

	default: {
		cout << "unknown COM" << endl;
	}
	}
	cout << endl;

}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cerr << "Usage: myclient host-name port-number" << endl;
		exit(1);
	}
	
	int port = -1;
	try {
		port = stoi(argv[2]);
	} catch (exception& e) {
		cerr << "Wrong port number. " << e.what() << endl;
		exit(1);
	}
	
	Connection c(argv[1], port);
	conn = &c;
	if (!conn->isConnected()) {
		cerr << "Connection attempt failed" << endl;
		exit(1);
	}
	
	pMenu();
	cout << "Type a number: ";
	int nbr;
	while (cin >> nbr && nbr !=8) {
			handleCom(nbr);
			pMenu();
			cout << "Type a number: ";
	}
}


