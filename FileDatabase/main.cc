
#include<string>
#include<iostream>
#include <algorithm>
#include <utility>
#include <cstdlib>
#include "FileDatabase.h"
#include<sys/types.h>
#include<dirent.h>
#include<unistd.h>

// Documentation of reading all files, http://pubs.opengroup.org/onlinepubs/7908799/xsh/dirent.h.html

using namespace std;




int main(){


	FileDatabase db;

	db.createNewsgroup("Putin");
	db.createNewsgroup("Tamm");
	db.createNewsgroup("Zuma");

	vector<pair<int,string>> vec = db.listAllNewsgroups();
	for_each(vec.begin(), vec.end(), [](pair<int,string>& p) { cout <<
		p.first << " " << p.second << endl;});

//	int ngId;
//	cin >> ngId;
//	cout << endl;
//	int artId;
//	cout << "artId: ";
//	cin >> artId;
//	cout << endl;
//	db.createArticle(ngId,"Peter Pan", "Don Juan", "One more down the chimney");
//	db.createArticle(ngId,"Compile C++","Carl R", "One does simply not compile C++ code" );

	vec = db.listArticle(6);
	for_each(vec.begin(), vec.end(), [](pair<int,string>& p) { cout <<
		p.first << " " << p.second << endl;});



}
