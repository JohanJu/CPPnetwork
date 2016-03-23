/*
 * InMemoryDatabase.h
 *
 *  Created on: Mar 22, 2016
 *      Author: carl
 */

#ifndef TEST_INMEMORYDATABASE_H_
#define TEST_INMEMORYDATABASE_H_

#include "database.h"
#include <vector>
#include "newsGroup.h"
#include "article.h"

namespace std {

class InMemoryDatabase: public Database {

public:
	InMemoryDatabase();
	~InMemoryDatabase();

	bool createNewsgroup(const std::string& newsGroupName);

	bool deleteNewsgroup(const int& newsGroupId);

	std::string listAllNewsgroups();

	bool createArticle(const int& newsGroupId, std::string title, std::string author, std::string text);

	bool deleteArticle(const int& newsGroupId, const int& artId);

	std::string listArticle(const int& newsGroupId);

	std::string getArticle(const int& newsGroupId, const int& artId);

	bool standardCheck(const int& newsGroupId);

private:
	vector<NewsGroup> newsGroups;


};



} /* namespace std */

#endif /* TEST_INMEMORYDATABASE_H_ */
