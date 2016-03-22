
#ifndef TEST_ARTICLE_H_
#define TEST_ARTICLE_H_

class Article {

public:
	static int unique_id;

	Article(std::string title, std::string author, std::string text):
		title(title), author(author), text(text), id(unique_id++){}

	int id;
	std::string title;
	std::string author;
	std::string text;


};
