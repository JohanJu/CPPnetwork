

#ifndef TEST_CLASS_H
#define TEST_CLASS_H

#include <vector>

#include <algorithm>
#include<utility>

using namespace std;

class TestClass {

public:

	bool createNewsgroup(const std::string& newsGroupName){
		newsGroups.push_back(newsGroupName);
		return true;
	}

	bool deleteNewsgroup(const int& newsGroupId);

	vector<pair<int,string>> listAllNewsgroups();

	bool createArticle(const int& newsGroupId, std::string title, std::string author, std::string text);

	bool deleteArticle(const int& newsGroupId, const int& artId);

	std::string listArticle(const int& newsGroupId);

	std::string getArticle(const int& newsGroupId, const int& artId);

	bool standardCheck(const int& newsGroupId);

private:
	vector<string> newsGroups;


};




#endif /* TEST_INMEMORYDATABASE_H_ */
