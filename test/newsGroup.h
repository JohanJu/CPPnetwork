
#ifndef TEST_NEWSGROUP_H_
#define TEST_NEWSGROUP_H_

#include<string>
#include<algorithm>
#include<vector>
#include "article.h"

using namespace std;
class NewsGroup{




public:

	NewsGroup(const std::string& name, int unique_id):  name(name), id(unique_id) {


		sysTime = time(0);
	}

	void insertArticle(std::string title, std::string author, std::string text){
		article_unique_id++;
		Article art(title,author,text, article_unique_id);
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

	std::vector<std::string> getArticleString(int artId){
		auto it = find_if(articles.begin(), articles.end(), [&artId] (Article art)
				{
			return art.id == artId;
				});
		vector<string> vec;
		if(it == articles.end()){
			vec.push_back("Fuck you Johan");
			return vec;
		}
		string title = it -> title;
		string author = it -> author;
		string text = it -> text;

		vec.push_back(title);
		vec.push_back(author);
		vec.push_back(text);

		return vec;
	}

	bool operator<(const NewsGroup& ng){
		return sysTime < ng.sysTime;
	}

	int id;
	std::string name;
	long double sysTime;

private:


	int article_unique_id;
	std::vector<Article> articles;


};

#endif
