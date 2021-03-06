/*
 * FileDatabase.cc
 *
 *  Created on: Apr 1, 2016
 *      Author: carl
 */

#include "FileDatabase.h"

namespace std {


FileDatabase::FileDatabase(){
	const int dir_err = system("mkdir -p Database");
	if (-1 == dir_err)
	{
	    cout << "Error creating directory!" << endl;
	    exit(1);
	}
	//Checks after the unique_newgroup_id file and adds it if it does not exist
	bool b = exists(databaseFolder + "unique_newsgroup_id");
	if (!b){
		ofstream of(databaseFolder + "unique_newsgroup_id");
			of << "0";
			of.close();
	}
	//Checks what files are in the folder and adds them into a
	//unordered_set, in case a file has been deleted manualy...
	listAllFiles();
	// Together with the above listAllFiles(), checks that the database is in the right state
	b = exists(databaseFolder + "manualMap");
	if(!b){
		ofstream of(databaseFolder + "manualMap");
		of.close();

	}
	/*
	 * If the file exists, it writes every line in to another temp document, then reads the lines
	 * back in
	 * to Newsgroups. NewsGroup file not existing => removed from ManualMap
	 */
	else{
		removeProcedure();

	}
}



bool FileDatabase::createNewsgroup(const string& newsGroupName){

	bool b  = exists("Database/"+newsGroupName);
	if( !b ){
		// Fetches unique_newsgroup_id from the file
		ifstream in(databaseFolder + "unique_newsgroup_id");
		string str;
		getline(in,str);
		in.close();

		//Creates the new file with id = str, and newsGroupName
		ofstream add(databaseFolder + newsGroupName);
		add << str + "\n";
		add << "0";
		add.close();

		//Adds to the manualMap
		add.open(databaseFolder + "manualMap", std::ios::app);
		b = add.good();
		add << str << " " << newsGroupName;
		add << "\n";
		in.open(databaseFolder + "manualMap");
		string temp;
		while(getline(in,temp)){
		}

		//Updates the value for the next unique_newsgroup_id
		ofstream of(databaseFolder + "unique_newsgroup_id");
		int next_id;
		istringstream buffer(str);
		buffer >> next_id;
		next_id++;
		of << next_id;
		of.close();

	} else {
		return false;

	}
	return true;

}

bool FileDatabase::deleteNewsgroup(const int& newsGroupId){
	ifstream in(databaseFolder + "manualMap");
	string strId;
	string strName;
	string str;
	while(getline(in,str)){
		strId = str.substr(0,1);
		strName = str.substr(2,str.size() - 1);
		if(stoi(strId) == newsGroupId){
			in.close();
			string strTemp = databaseFolder + strName;
			remove(strTemp.c_str());
			filesInFolder.clear();
			listAllFiles();
			removeProcedure();
			return true;
		}
	}

	return false;
}

vector<pair<int,string>> FileDatabase::listAllNewsgroups(){
	ifstream in(databaseFolder + "manualMap");
	string newsGroupName;
	string tempId;
	int id;
	string str;
	vector<pair<int,string>> pairs;
	while(getline(in,str)){
		tempId = str.substr(0,1);
		id = stoi(tempId);
		newsGroupName = str.substr(2,str.size() - 1);
		pairs.push_back(make_pair(id,newsGroupName));
	}

	cout << pairs.size() << endl;
	return pairs;
}

bool FileDatabase::createArticle(const int& newsGroupId, string title, string author,string text){

	string newsgroupName = findNewsgroupName(newsGroupId);
	if(newsgroupName == ""){
		return false;
	}
	string tempNewsgroupName = "temp"+ newsgroupName;

	ifstream in(databaseFolder + newsgroupName);
	ofstream of(databaseFolder + tempNewsgroupName);
	int next_art_id;
	in >> next_art_id;
	of << next_art_id;
	of << "\n";
	in >> next_art_id;
	next_art_id++;
	of << next_art_id;
	of << "\n";
	string temp;
	while(getline(in,temp)){
		of << temp;
		of <<"\n";
	}
	of <<"\n";

	string first = "<artId>" + to_string(next_art_id) + "</artId>" + "\n";
	of << first;
	of << title + "\n";
	of << author + "\n";
	of << text;
	of << artEnd + "\n";

	of.close();
	in.close();

	of.open(databaseFolder + newsgroupName);
	in.open(databaseFolder + tempNewsgroupName);

	while(getline(in,temp)){
		of << temp;
		of << "\n";
	}
	of.close();
	in.close();
	remove((databaseFolder + tempNewsgroupName).c_str());
	return true;
}

int FileDatabase::deleteArticle(const int& newsGroupId, const int& artId){
	string newsgroupName = findNewsgroupName(newsGroupId);
	if(newsgroupName == ""){
		return 1;
	}
	cout << newsgroupName << endl;
	string tempNewsgroupName = "temp"+ newsgroupName;
	ifstream in(databaseFolder + newsgroupName);
	ofstream of(databaseFolder + tempNewsgroupName);
	string temp;
	string toFind = "<artId>"+to_string(artId)+ "</artId>";
	bool deleteMarker = false;
	bool isFound = false;
	while(getline(in,temp)){

		if(deleteMarker){
			size_t found = temp.find("<artId>");
			if(found!=std::string::npos){
				deleteMarker = false;

				of << temp;
				of <<"\n";

			}
		} else {
			size_t found = temp.find(toFind);
			if (found!=std::string::npos)
			{

				deleteMarker = true;
				isFound = true;
			} else {
				of << temp;
				of <<"\n";
			}
		}

	}
	of << "\n";
	of.close();
	in.close();

	of.open(databaseFolder + newsgroupName);
	in.open(databaseFolder + tempNewsgroupName);

	while(getline(in,temp)){
		of << temp;
		of << "\n";
	}
	of.close();
	in.close();
	remove((databaseFolder + tempNewsgroupName).c_str());
	if(isFound){
		return 0;
	} else {
		return 2;
	}
}

vector<std::pair<int,string>> FileDatabase::listArticle(const int& newsGroupId, int &noll){
	string newsgroupName = findNewsgroupName(newsGroupId);
	vector<std::pair<int,string>> pairs;
	if(newsgroupName != ""){
		noll = 1;
		ifstream in(databaseFolder + newsgroupName);
		string findFirst = "<artId>";
		string findLast = "</artId>";
		string temp;
		while(getline(in,temp)){
			size_t foundFirst = temp.find(findFirst);
			if (foundFirst!=std::string::npos){
				size_t foundLast = temp.find(findLast);
				string tempId(temp,7, 1);
				int id = stoi(tempId);
				string title;
				getline(in,title);
				pairs.push_back(make_pair(id,title));
			}
		}
	} else {
		noll = 0;
	}
	return pairs;
}


vector<string> FileDatabase::getArticle(const int& newsGroupId, const int& artId){
	string newsgroupName = findNewsgroupName(newsGroupId);
	vector<string> artInfo;
	ifstream in(databaseFolder + newsgroupName);
	string find = "<artId>"+to_string(artId)+"</artId>";
	string temp;
	while(getline(in,temp)){
		size_t foundFirst = temp.find(find);
		if (foundFirst!=std::string::npos){
			string title;
			getline(in,title);
			cout << "Articletitle: " << title << endl;
			artInfo.push_back(title);
			string author;
			getline(in,author);
//			cout << "ArticleAuthor: " << author << endl;
			artInfo.push_back(author);
			string text;
			string str;
			while(getline(in,str)){
				cout << str << endl;
				size_t foundText = str.find(artEnd);
				if(foundText == std::string::npos){
					text += str;
					text += "\n";
				} else {
					text += str.substr(0, str.size() - artEnd.size());
					break;
				}
			}
//			getline(in,text);
			artInfo.push_back(text);
			break;
		}
	}
	if(artInfo.size() < 2){
		artInfo.push_back("Nothing");
	}
	cout << artInfo.size() << endl;
	return artInfo;
}







/*
 * Below are private helping methods
 */

bool FileDatabase::exists(const string& name) {
    ifstream f(name);
    if (f.good()) {
        f.close();
        return true;
    } else {
        f.close();
        return false;
    }
}



string FileDatabase::findNewsgroupName(const int& newsgroupId){
	ifstream in(databaseFolder + "manualMap");
	string strId;
	string strName;
	string str;
	while(getline(in, str)){
		strId = str.substr(0,1);
		strName = str.substr(2,str.size() - 1);
		if(stoi(strId) == newsgroupId){
			return strName;
		}
	}
	return "";
}


void FileDatabase::removeProcedure(){
	ifstream in(databaseFolder + "manualMap");
	string newsGroupName;
	string id;
	ofstream of(databaseFolder + "manualMapTemp");
	string temp;
	while(getline(in,temp)){
		id = temp.substr(0,1);
		newsGroupName = temp.substr(2,temp.size() - 1);
		auto it = filesInFolder.find(newsGroupName);
		if(it != filesInFolder.end()){
			of << id << " " << newsGroupName;
			of << "\n";
		}
	}

	in.close();
	of.close();
	of.open(databaseFolder + "manualMap");
	in.open(databaseFolder + "manualMapTemp");
	string str;
	while(getline(in,str)){
		of << str;
		of << "\n";
	}
	of.close();
	in.close();
	remove("Database/manualMapTemp");
}

void FileDatabase::listAllFiles()
{
	string dirName = databaseFolder;
	DIR *dirp = opendir( dirName.c_str() );

	if ( dirp )
	{
		struct dirent *dp = NULL;

		while ( (dp = readdir( dirp )) != NULL )
		{
			std::string file( dp->d_name );

			if ( file == "." || file == ".." )
				continue;

			if ( dp->d_type & DT_DIR )
			{
			}
			else
			{
				filesInFolder.insert(file);
			}
		}
		closedir( dirp );
	}
}


} /* namespace std */
