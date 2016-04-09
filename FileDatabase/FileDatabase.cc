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
			of << "0\n";
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
//		cout << "manualMap added" << endl;
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
		add.close();

		//Adds to the manualMap
		add.open(databaseFolder + "manualMap", std::ios::app);
		b = add.good();
//		cout << b << endl;
		add << str << " " << newsGroupName;
		add << "\n";
		in.open(databaseFolder + "manualMap");
		string temp;
		while(getline(in,temp)){
	//		cout << str << endl;
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
		while(in >> strId >> strName){
			if(stoi(strId) == newsGroupId){
				in.close();
				string strTemp = databaseFolder + strName;
				remove(strTemp.c_str());
				filesInFolder.clear();
				listAllFiles();
				removeProcedure();
			}
	}
	return true;
}

vector<pair<int,string>> FileDatabase::listAllNewsgroups(){
	ifstream in(databaseFolder + "manualMap");
	string newsGroupName;
	int id;
	vector<pair<int,string>> pairs;
	while(in >> id >> newsGroupName){
		pairs.push_back(make_pair(id,newsGroupName));
	}
	return pairs;
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

void FileDatabase::removeProcedure(){
	ifstream in(databaseFolder + "manualMap");
	string newsGroupName;
	string id;
	ofstream of(databaseFolder + "manualMapTemp");
	while(in >> id >> newsGroupName){
		auto it = filesInFolder.find(newsGroupName);
		if(it != filesInFolder.end()){
			of << id << " " << newsGroupName;
			of << "\n";
		} else{
			//			cout << "Newsgroup removed from manualMap, id: " << id << endl;
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

			if ( file == "." || file == ".." )    // skip these
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
