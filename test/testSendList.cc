/* myclient.cc: sample client program */
#include "connection.h"
#include "connectionclosedexception.h"

#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>

using namespace std;

/*
 * Send an integer to the server as four bytes.
 */

/*
 * Read a string from the server.
 */
string readString(const Connection& conn) {
	string s;
	char ch;
	while ((ch = conn.read()) != '$') {
		s += ch;
	}
	return s;
}

int main(int argc, char* argv[]) {

	Connection conn("localhost", 2222);
	if (!conn.isConnected()) {
		cerr << "Connection attempt failed" << endl;
		exit(1);
	}
	try {
		conn.write(1);
		string s = "hej";
		for (unsigned char c : s) {
			conn.write(c);
		}
		conn.write(0);
	} catch (ConnectionClosedException&) {
		cout << " no reply from server. Exiting." << endl;
		exit(1);
	}

}

