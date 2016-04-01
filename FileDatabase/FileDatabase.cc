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

	bool b = exists(databaseFolder + "unique_newsgroup_id");
	if (!b){
		ofstream of(databaseFolder + "unique_newsgroup_id");
			of << "0\n";
			of.close();
			unique_newsgroup_id = 0;
	} else{
		ifstream in(databaseFolder + "unique_newsgroup_id");
		string str;
		getline(in,str);
		cout << "Read unique_newsgroup_id: " << str << endl;
	}
}


bool FileDatabase::createNewsgroup(const string& newsGroupName){

	bool b  = exists("Database/"+newsGroupName);
	cout << "Does the file exist? (1 yes, 0 no): " << b << endl;

	if( !b ){
		ofstream of ("Database/"+newsGroupName);
	}
	return true;

}

bool FileDatabase::deleteNewsgroup(const int& newsGroupId){

	//bool b = exists(newsGroupId)
}











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


} /* namespace std */
