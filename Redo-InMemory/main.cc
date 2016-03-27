


#include<string>
#include "testClass.h"
#include<iostream>

int main(){

	string newsName = "Trump";

	TestClass test;
	bool b = test.createNewsgroup(newsName);

	cout << b << endl;

}
