
#ifndef TEST_ARTICLE_H_
#define TEST_ARTICLE_H_

class Article {

public:


	Article(std::string title, std::string author, std::string text):
		title(title), author(author), text(text) {}

	int id;
	std::string title;
	std::string author;
	std::string text;


};
#endif
