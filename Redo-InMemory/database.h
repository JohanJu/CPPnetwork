

#ifndef TEST_DATABASE_H_
#define TEST_DATABASE_H_

#include <string>
#include<utility>
#include <vector>
class Database{
public:
	Database();
	virtual ~Database();

	virtual bool createNewsgroup(const std::string& newsGroupName);

	virtual bool deleteNewsgroup(const int& newsGroupId);

	virtual std::vector<std::pair<int,std::string>> listAllNewsgroups();

	virtual bool createArticle(const int& newsGroupId, std::string title, std::string author, std::string text);

	virtual bool deleteArticle(const int& newsGroupId, const int& artId);

	virtual std::vector<std::pair<int,std::string>> listArticle(const int& newsGroupId);

	virtual std::string getArticle(const int& newsGroupId, const int& artId);




};
#endif
