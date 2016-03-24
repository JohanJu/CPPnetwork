


#include "database.h"
#include "newsGroup.h"
#include "article.h"
#include<string>
#include "InMemoryDatabase.h"

int main(){

	string newsName = "Trump";

	InMemoryDatabase* db = new InMemoryDatabase();
	bool b = db -> createNewsgroup(newsName);

}
