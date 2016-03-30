#include "command.h"
#define inMem

using namespace std;

string Command::readString() {
	string re;
	unsigned char c = 0;
	while (true) {
		c = conn->read();
		if (c == 0) {
			break;
		}
		re += c;
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

void Command::writeString(const string& msg) {
	for (unsigned char c : msg) {
		conn->write(c);
	}
	conn->write(0);
}

void Command::writeNumber( int value) {
	conn->write((value >> 24) & 0xFF);
	conn->write((value >> 16) & 0xFF);
	conn->write((value >> 8) & 0xFF);
	conn->write(value & 0xFF);
}

void Command::end() {
	if (conn->read() != Protocol::COM_END) {
		cout << "no COM_END" << endl;
		exit(1);
	}
}

void Command::handleCom() {
	switch (conn->read())
	{
	case Protocol::COM_LIST_NG: {

		// vector<pair<int, string>> v;
		// v.push_back(make_pair(132542, "one"));
		// v.push_back(make_pair(2, "two"));

		vector<pair<int, string>> v = data.listAllNewsgroups();
		conn->write(Protocol::ANS_LIST_NG);
		// writeNumber(v.size());
		// for (auto i = v.begin(); i != v.end(); ++i)
		// {
		// 	writeNumber(i->first);
		// 	cout << "nr " << i->first << endl;
		// 	writeString(i->second);
		// 	cout << "name " << i->second << endl;
		// }
		conn->write(Protocol::ANS_END);

		break;
	}
	case Protocol::COM_CREATE_NG: {
		end();
		conn->write(Protocol::ANS_CREATE_NG);
		if (data.createNewsgroup(readString())) {
			conn->write(Protocol::ANS_ACK);
		} else {
			conn->write(Protocol::ANS_NAK);
			conn->write(Protocol::ERR_NG_ALREADY_EXISTS);
		}
		conn->write(Protocol::ANS_END);

		break;
	}
	case Protocol::COM_DELETE_NG: {
		int nr  = readNumber();
		end();
		if (data.deleteNewsgroup(nr)) {
			conn->write(Protocol::ANS_ACK);
		} else {
			conn->write(Protocol::ANS_NAK);
			conn->write(Protocol::ERR_NG_DOES_NOT_EXIST);
		}
		conn->write(Protocol::ANS_END);

		break;
	}
	case Protocol::COM_LIST_ART: {
		int nr  = readNumber();
		end();
		vector<pair<int, string>> v = data.listArticle(nr);
		conn->write(Protocol::ANS_LIST_NG);
		if (v.size() != 0) {
			writeNumber(v.size());
			for (auto i = v.begin(); i != v.end(); ++i)
			{
				writeNumber(i->first);
				cout << "nr " << i->first << endl;
				writeString(i->second);
				cout << "name " << i->second << endl;
			}
			
		}else{
			
		}
		conn->write(Protocol::ANS_END);
		break;
	}
	case Protocol::COM_CREATE_ART: {
		int nr  = readNumber();
		string title = readString();
		string authur = readString();
		string text = readString();
		end();
		data.createArticle(nr, title, authur, text);
		break;
	}
	case Protocol::COM_DELETE_ART: {
		int gNr  = readNumber();
		int aNr  = readNumber();
		end();
		data.deleteArticle(gNr, aNr);
		break;
	}
	case Protocol::COM_GET_ART: {
		int gNr  = readNumber();
		int aNr  = readNumber();
		end();
		data.getArticle(gNr, aNr);
		break;
	}
	default:
		cout << "unknown COM" << endl;
	}

}