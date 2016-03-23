/* myclient.cc: sample client program */
#include "connection.h"
#include "connectionclosedexception.h"
#include "protocol.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>

using namespace std;


string readString(const Connection& conn) {
	string re;
	unsigned char c = 0;
	while (true) {
		c = conn.read();
		if (c == 0) {
			break;
		}
		re += c;
	}
	return re;
}
int readNumber(const Connection& conn) {
	unsigned char byte1 = conn.read();
	unsigned char byte2 = conn.read();
	unsigned char byte3 = conn.read();
	unsigned char byte4 = conn.read();
	return (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
}

int main() {

	Connection conn("localhost", 2222);
	if (!conn.isConnected()) {
		cerr << "Connection attempt failed" << endl;
		exit(1);
	}
	try {
		conn.write(Protocol::COM_LIST_NG);
		string s = "hej";
		for (unsigned char c : s) {
			conn.write(c);
		}
		conn.write(0);
		conn.write(Protocol::COM_END);

		if (conn.read() != Protocol::ANS_LIST_NG)
			cerr << "err Protocol::ANS_LIST_NG" << endl;
		int totNr = readNumber(conn);
		cout << "totNr " << totNr << endl;
		for (int i = 0; i < totNr; ++i)
		{
			cout << "nr " << readNumber(conn) <<  endl;
			cout << "name " << readString(conn) << endl;
		}
		if (conn.read() != Protocol::ANS_END)
			cerr << "err Protocol::ANS_END" << endl;

		cout << "ok " << endl;



	} catch (ConnectionClosedException&) {
		cout << " no reply from server. Exiting." << endl;
		exit(1);
	}

}

