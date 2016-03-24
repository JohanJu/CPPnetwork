
#ifndef TEST_NEWSGROUP_H_
#define TEST_NEWSGROUP_H_

#include<string>
#include<algorithm>
#include<vector>
#include "article.h"

using namespace std;
class NewsGroup{




public:
	static int unique_id;
	NewsGroup(const std::string& name):  name(name) {
		id = unique_id++;
	}

	void insertArticle(std::string title, std::string author, std::string text){

		Article art(title,author,text);
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
		string title = it -> title;
		string author = it -> author;
		string text = it -> text;

		std::string totalArt = "Title: " + title + ", Author: " + author +", Text: " + text;

		return totalArt;
	}


	int id;
	std::string name;

private:


	std::vector<Article> articles;


};

#endif
