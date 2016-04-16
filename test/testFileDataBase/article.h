
#ifndef TEST_ARTICLE_H_
#define TEST_ARTICLE_H_

class Article {

public:


	Article(std::string title, std::string author, std::string text, int unique_id):
		title(title), author(author), text(text), id(unique_id) {

	}

	int id;
	std::string title;
	std::string author;
	std::string text;


};
#endif
