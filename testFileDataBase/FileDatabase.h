/*
 * FileDatabase.h
 *
 *  Created on: Apr 1, 2016
 *      Author: carl
 */

#ifndef FILEDATABASE_FILEDATABASE_H_
#define FILEDATABASE_FILEDATABASE_H_

#include <vector>
#include <algorithm>
#include<utility>
#include<iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include<sys/types.h>
#include<dirent.h>
#include<unistd.h>
#include<unordered_set>
#include <fstream>
#include <string>




namespace std {

class FileDatabase {

public:

	FileDatabase();

	bool createNewsgroup(const string& newsGroupName);

	bool deleteNewsgroup(const int& newsGroupId);

	vector<pair<int,string>> listAllNewsgroups();

	bool createArticle(const int& newsGroupId, std::string title, std::string author, std::string text);

	int deleteArticle(const int& newsGroupId, const int& artId);

	vector<std::pair<int,string>> listArticle(const int& newsGroupId,int &noll);

	vector<string> getArticle(const int& newsGroupId, const int& artId);





private:
	bool standardCheck(const int& newsGroupId);

	bool exists(const string& name);

	void listAllFiles();

	string findNewsgroupName(const int& newsgroupName);
	void removeProcedure();
	string databaseFolder = "Database/";
	int unique_newsgroup_id;
	unordered_set<string> filesInFolder;
	string artEnd = "<ArtEnd/>";


};

} /* namespace std */

#endif /* FILEDATABASE_FILEDATABASE_H_ */
