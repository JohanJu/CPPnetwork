
#ifndef TEST_NEWSGROUP_H_
#define TEST_NEWSGROUP_H_
#include<string>

class NewsGroup{


using namespace std;

public:
	static int unique_id;
	NewsGroup(const std::string& name): id(unique_id++), name(name) {}

	void insertArticle(std::string title, std::string author, std::string text){

		Article art = new Article(title,author,text);
		articles.push_back(art);

	}

	bool deleteArticle(const int& artId){

		auto it = find_if(articles.begin(), articles.end(), [&artId] (Article art)
				{
			return art.id == artId;
				});
		if(it == articles.end()){
			return false;
		}

		articles.erase(remove_if(articles.begin(), articles.end(), [&artId] (Article art)
				{
			return art.id == artId;
				}));

		return true;
	}

	// sorts articles and returns a string with articles in order
	std::string sortAndReturnArticles(){

		return "";
	}

	std::string getArticleString(int artId){
		auto it = find_if(articles.begin(), articles.end(), [&artId] (Article art)
				{
			return art.id == artId;
				});
		if(it == articles.end()){
			return "No article with this ID";
		}

		std::string totalArt = "Title: " + (it -> title) + ", Author: " (it -> author) +", Text: " + (it -> text);

		return totalArt;
	}


	int id;
	std::string name;

private:


	std::vector<Article> articles;


};

#endif
