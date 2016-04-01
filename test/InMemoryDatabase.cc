#include "InMemoryDatabase.h"
#include <utility>
#include<iostream>
#include<algorithm>

using namespace std;

/*
 *
 */
bool InMemoryDatabase::createNewsgroup(const std::string& newsGroupName){

	auto it = find_if(newsGroups.begin(), newsGroups.end(), [&newsGroupName] (NewsGroup& ng)
			{ return ng.name == newsGroupName; } );
	if(it!= newsGroups.end()){
		return false;
	}

	NewsGroup ng(newsGroupName);
	newsGroups.push_back(ng);

	return true;
}

/*
 *
 *
 */

bool InMemoryDatabase::deleteNewsgroup(const int& newsGroupId){

	auto it = find_if(newsGroups.begin(), newsGroups.end(), [&newsGroupId] (NewsGroup& ng)
				{ return ng.id == newsGroupId; } );

	if(it == newsGroups.end()){
		return false;
	}

	newsGroups.erase(remove_if(newsGroups.begin(), newsGroups.end(), [&newsGroupId] (NewsGroup& ng)
			{ return ng.id == newsGroupId; }
	));

	return true;
}

/*
 *
 */
vector<pair<int,string>> InMemoryDatabase::listAllNewsgroups(){

	vector<pair<int,string>> vec;
	cout << "before sort" << endl;
	sort(newsGroups.begin(), newsGroups.end());
	cout << "Before For_each" << endl;
	for_each(newsGroups.begin(), newsGroups.end(), [&vec] (NewsGroup ngs)
	{
		vec.push_back(make_pair(ngs.id, ngs.name));
	});
	cout << "after For_each" << endl;
	return vec;
}

/*
 *
 */
bool InMemoryDatabase::createArticle(const int& newsGroupId, std::string title, std::string author, std::string text){

	auto it = find_if(newsGroups.begin(), newsGroups.end(), [&newsGroupId] (NewsGroup& ng)
					{ return ng.id == newsGroupId; } );

	if( it == newsGroups.end()){
		return false;
	}

	it -> insertArticle(title, author, text);

	return true;
}

bool InMemoryDatabase::deleteArticle(const int& newsGroupId, const int& artId){

	auto it = find_if(newsGroups.begin(), newsGroups.end(), [&newsGroupId] (NewsGroup& ng)
					{ return ng.id == newsGroupId; } );

	if( it == newsGroups.end()){
		return false;
	}

	bool deleted = it -> deleteArticle(artId);

	return deleted;
}

string InMemoryDatabase::getArticle(const int& newsGroupId, const int& artId){
	auto it = find_if(newsGroups.begin(), newsGroups.end(), [&newsGroupId] (NewsGroup& ng)
					{ return ng.id == newsGroupId; } );

	if( it == newsGroups.end()){
		return "No NewsGroup with this ID";
	}

	string str = it -> getArticleString(artId);
	return str;
}


vector<std::pair<int,std::string>> InMemoryDatabase::listArticle(const int& newsGroupId){
	auto it = find_if(newsGroups.begin(), newsGroups.end(), [&newsGroupId] (NewsGroup& ng)
					{ return ng.id == newsGroupId; } );

	vector<pair<int,string>> vec;
	if( it == newsGroups.end()){
		return vec;
	}

	vec = it -> sortAndReturnArticles();
	return vec;
}


