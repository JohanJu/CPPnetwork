




class Database{
public:
	Database();

	bool createNewsgroup(const std::string& newsGroupName);

	bool deleteNewsgroup(const int& newsGroupId);

	std::string listAllNewsgroups();

	bool createArticle(const int& newsGroupId, std::string title, std::string author, std::string text);

	bool deleteArticle(const int& newsGroupId, const int& artId);

	std::string listArticle(const int& newsGroupId);

	std::string getArticle(const int& newsGroupId, const int& artId);


};
