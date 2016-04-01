#include "InMemoryDatabase.h"
#include<utility>
#include<iostream>

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

	newsgroup_unique_id++;

	NewsGroup ng(newsGroupName,newsgroup_unique_id);

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
	sort(newsGroups.begin(), newsGroups.end());
	for_each(newsGroups.begin(), newsGroups.end(), [&vec] (NewsGroup ngs)
	{
		vec.push_back(make_pair(ngs.id, ngs.name));
	});

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
/*
 * 0 = deleted, 1 = didnt find newsgroup, 2 = didnt find article
 */
int InMemoryDatabase::deleteArticle(const int& newsGroupId, const int& artId){

	auto it = find_if(newsGroups.begin(), newsGroups.end(), [&newsGroupId] (NewsGroup& ng)
					{ return ng.id == newsGroupId; } );

	if( it == newsGroups.end()){
		return 1;
	}

	bool deleted = it -> deleteArticle(artId);
	if(deleted == false){
		return 2;
	}
	return 0;
}
/*
 *  Cannot find newsgroup = return empty vector;
 *  Cannot fint article = return with title = "fuck you johan"
 *  Found article, return vector {title, author, text}
 */

vector<string> InMemoryDatabase::getArticle(const int& newsGroupId, const int& artId){
	auto it = find_if(newsGroups.begin(), newsGroups.end(), [&newsGroupId] (NewsGroup& ng)
					{ return ng.id == newsGroupId; } );

	vector<string> vec;
	if( it == newsGroups.end()){
		return vec;
	}

	vec = it -> getArticleString(artId);
	return vec;
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


