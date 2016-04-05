#include "command.h"
#define inMem

using namespace std;

string Command::readString() {
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
int Command::readNumber() {
	if (conn->read() != Protocol::PAR_NUM) {
		cout << "err PAR_NUM" << endl;
	}
	return readNumberS();
}
int Command::readNumberS() {
	unsigned char byte1 = conn->read();
	unsigned char byte2 = conn->read();
	unsigned char byte3 = conn->read();
	unsigned char byte4 = conn->read();
	return (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
}

void Command::writeString(const string& msg) {
	conn->write(Protocol::PAR_STRING);
	writeNumberS(msg.length());
	for (unsigned char c : msg) {
		conn->write(c);
	}

}

void Command::writeNumberS(int value) {
	conn->write((value >> 24) & 0xFF);
	conn->write((value >> 16) & 0xFF);
	conn->write((value >> 8) & 0xFF);
	conn->write(value & 0xFF);
}

void Command::writeNumber(int value) {
	conn->write(Protocol::PAR_NUM);
	writeNumberS(value);
}

void Command::end() {
	if (conn->read() != Protocol::COM_END) {
		cout << "no COM_END" << endl;
		exit(1);
	}
}

void Command::handleCom() {
	cout << "handleCom " << endl;
	switch (conn->read())
	{
	case Protocol::COM_LIST_NG: {

		// vector<pair<int, string>> v;
		// v.push_back(make_pair(132542, "one"));
		// v.push_back(make_pair(2, "two"));
		end();
		cout << "COM_LIST_NG " << endl;
		conn->write(Protocol::ANS_LIST_NG);
		vector<pair<int, string>> v = data.listAllNewsgroups();

		writeNumber(v.size());
		for (auto i = v.begin(); i != v.end(); ++i)
		{
			writeNumber(i->first);
			cout << "NG nr " << i->first << endl;
			writeString(i->second);
			cout << "NG name " << i->second << endl;
		}


		break;
	}
	case Protocol::COM_CREATE_NG: {
		string s = readString();
		end();
		cout << "COM_CREATE_NG " << endl;
		conn->write(Protocol::ANS_CREATE_NG);
		if (data.createNewsgroup(s)) {
			conn->write(Protocol::ANS_ACK);
		} else {
			conn->write(Protocol::ANS_NAK);
			conn->write(Protocol::ERR_NG_ALREADY_EXISTS);
		}

		break;
	}
	case Protocol::COM_DELETE_NG: {
		cout << "COM_DELETE_NG1 " << endl;
		int nr  = readNumber();
		end();
		cout << "COM_DELETE_NG " << endl;
		conn->write(Protocol::ANS_DELETE_NG);
		if (data.deleteNewsgroup(nr)) {
			conn->write(Protocol::ANS_ACK);
		} else {
			conn->write(Protocol::ANS_NAK);
			conn->write(Protocol::ERR_NG_DOES_NOT_EXIST);
		}


		break;
	}
	case Protocol::COM_LIST_ART: {
		int nr  = readNumber();
		end();
		cout << "COM_LIST_ART " << endl;
		vector<pair<int, string>> v = data.listArticle(nr);
		conn->write(Protocol::ANS_LIST_ART);
		if (true) {
			cout << "COM_LIST_ART not null " << endl;
			conn->write(Protocol::ANS_ACK);
			writeNumber(v.size());
			for (auto i = v.begin(); i != v.end(); ++i)
			{
				writeNumber(i->first);
				cout << "A nr " << i->first << endl;
				writeString(i->second);
				cout << "A name " << i->second << endl;
			}

		} else {
			conn->write(Protocol::ANS_NAK);
			conn->write(Protocol::ERR_NG_DOES_NOT_EXIST);
		}

		break;
	}
	case Protocol::COM_CREATE_ART: {
		int nr  = readNumber();
		string title = readString();
		string authur = readString();
		string text = readString();
		end();
		cout << "COM_CREATE_ART " << endl;
		if (data.createArticle(nr, title, authur, text)) {
			conn->write(Protocol::ANS_ACK);
		} else {
			conn->write(Protocol::ANS_NAK);
			conn->write(Protocol::ERR_NG_DOES_NOT_EXIST);
		}

		break;
	}
	case Protocol::COM_DELETE_ART: {
		int gNr  = readNumber();
		int aNr  = readNumber();
		end();
		cout << "COM_DELETE_ART " << endl;
		int re = data.deleteArticle(gNr, aNr);
		if (re == 0) {
			conn->write(Protocol::ANS_ACK);
		} else if (re == 1) {
			conn->write(Protocol::ANS_NAK);
			conn->write(Protocol::ERR_NG_DOES_NOT_EXIST);
		} else {
			conn->write(Protocol::ANS_NAK);
			conn->write(Protocol::ERR_ART_DOES_NOT_EXIST);
		}

		break;
	}
	case Protocol::COM_GET_ART: {
		int gNr  = readNumber();
		int aNr  = readNumber();
		end();
		cout << "COM_GET_ART " << endl;
		vector<string> v = data.getArticle(gNr, aNr);
		if (v.size() == 3) {
			conn->write(Protocol::ANS_ACK);
			writeString(v[0]);
			writeString(v[1]);
			writeString(v[2]);
		} else if (v.size() == 1) {
			conn->write(Protocol::ANS_NAK);
			conn->write(Protocol::ERR_ART_DOES_NOT_EXIST);
		} else {
			conn->write(Protocol::ANS_NAK);
			conn->write(Protocol::ERR_NG_DOES_NOT_EXIST);
		}

		break;
	}
	default:
		cout << "unknown COM" << endl;
	}
	conn->write(Protocol::ANS_END);
	cout << "end " << endl;

}
