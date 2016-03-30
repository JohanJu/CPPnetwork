/*
 * InMemoryDatabase.h
 *
 *  Created on: Mar 22, 2016
 *      Author: carl
 */

#ifndef TEST_INMEMORYDATABASE_H_
#define TEST_INMEMORYDATABASE_H_


#include <vector>
#include <algorithm>
#include<utility>
#include"newsGroup.h"

using namespace std;

class InMemoryDatabase {

public:
	InMemoryDatabase(){};
	~InMemoryDatabase(){};


	bool createNewsgroup(const std::string& newsGroupName);

	bool deleteNewsgroup(const int& newsGroupId);

	vector<pair<int,string>> listAllNewsgroups();

	bool createArticle(const int& newsGroupId, std::string title, std::string author, std::string text);

	bool deleteArticle(const int& newsGroupId, const int& artId);

	std::vector<std::pair<int,std::string>> listArticle(const int& newsGroupId);

	std::string getArticle(const int& newsGroupId, const int& artId);

	bool standardCheck(const int& newsGroupId);

private:
	vector<NewsGroup> newsGroups;


};




#endif /* TEST_INMEMORYDATABASE_H_ */
