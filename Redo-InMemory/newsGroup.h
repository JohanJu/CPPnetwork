
#ifndef TEST_NEWSGROUP_H_
#define TEST_NEWSGROUP_H_

#include<string>
#include<algorithm>
#include<vector>
#include "article.h"

using namespace std;
class NewsGroup{




public:

	NewsGroup(const std::string& name):  name(name) {
		id = 5;
		sysTime = time(0);
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
	std::vector<pair<int,std::string>> sortAndReturnArticles(){

		vector<pair<int,string>> vec;
		for_each(articles.begin(),articles.end(),[&vec](Article art){
			vec.push_back(make_pair(art.id, art.title));
		});

		return vec;
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

		std::string totalArt = "Title: " + title + " | Author: " + author +" | Text: " + text;

		return totalArt;
	}

	bool operator<(const NewsGroup& ng){
		return sysTime < ng.sysTime;
	}

	int id;
	std::string name;
	long double sysTime;

private:



	std::vector<Article> articles;


};

#endif
