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
		cout << "test " << readString() << endl;
		end();
		cout << "end ok" << endl;
		vector<pair<int, string>> v;
		v.push_back(make_pair(132542, "one"));
		v.push_back(make_pair(2, "two"));
		conn->write(Protocol::ANS_LIST_NG);
		writeNumber(v.size());
		cout << "l " << v.size() << endl;
		for (auto i = v.begin(); i != v.end(); ++i)
		{
			writeNumber(i->first);
			cout << "nr " << i->first << endl;
			writeString(i->second);
			cout << "name " << i->second << endl;
		}
		conn->write(Protocol::ANS_END);
		// data.listAllNewsgroups();
		break;
	}
	case Protocol::COM_CREATE_NG:
		data.createNewsgroup(readString());
		end();
		break;
	case Protocol::COM_DELETE_NG:
		data.deleteNewsgroup(readNumber());
		end();
		break;
	case Protocol::COM_LIST_ART:
		data.listArticle(readNumber());
		end();
		break;
	case Protocol::COM_CREATE_ART:
		data.createArticle(readNumber(), readString(), readString(), readString());
		end();
		break;
	case Protocol::COM_DELETE_ART:
		data.deleteArticle(readNumber(), readNumber());
		end();
		break;
	case Protocol::COM_GET_ART:
		data.getArticle(readNumber(), readNumber());
		end();
		break;
	default:
		cout << "unknown COM" << endl;
	}

}