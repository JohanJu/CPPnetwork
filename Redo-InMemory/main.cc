


#include<string>
#include "InMemoryDatabase.h"
#include<iostream>
#include "database.h"

int main(){

	string newsName = "Trump";

	InMemoryDatabase db;

	/*
	 * Test createNewsgroup
	 */
	bool b = db.createNewsgroup(newsName);
	cout << "createNewsgroup(return 1 for correct): " << b << endl;

	b = db.createNewsgroup(newsName);
	cout << "createNewsgroup(return 0 for correct): " << b << endl;

	/*
	 *Test deleteNewsgroup, id hardcoded to 5
	 */
	int id = 5;
	bool c = db.deleteNewsgroup(id);
	cout << "deleteNewsgroup(return 1 for correct): " << c << endl;
	c = db.deleteNewsgroup(id);
	cout << "deleteNewsgroup(return 0 for correct): " << c << endl;

	/*
	 * Testing listAllNewsgroups, Should return "id : name"
	 */
	db.createNewsgroup(newsName);
	vector<pair<int,string>> vec = db.listAllNewsgroups();
	cout << vec[0].first << " : " << vec[0].second <<endl;


	/*
	 * Creating article
	 */
	string title = "How to compile C++ code";
	string author = "Founders United";
	string description = "One does not simply compile C++ code";
	bool d = db.createArticle(id,title,author,description);
	cout << "Created article? " << d << endl;

	/*
	 * DeleteArticle, artId hardcoded to 5
	 */
	int artId = 5;
	d = db.deleteArticle(id,artId);
	cout << "Deleted article: " << d << endl;

	/*
	 * getArticle,
	 */
	db.createArticle(id,title,author,description);
	string str = db.getArticle(id,artId);
	cout << str << endl;
}
