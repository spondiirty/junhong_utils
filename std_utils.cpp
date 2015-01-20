#include "std_utils.h"

using namespace std;

vector<string> utFile2Strings(string filename)
{
    fstream file;
    file.open(filename,ios::in);
	vector<string> ret;
	
	string line;
	if (file.is_open())	{ while(getline(file, line)) ret.push_back(line); }
	else				cout << "utFile2Strings::file open error" << endl; 
	
	return ret;
}

string utFile2String(string filename)
{
    fstream file;
    file.open(filename,ios::in);
    string ret;

    string line;
    if (file.is_open())	{ while(getline(file, line)) ret.append(line+"\n"); }
    else				cout << "utFile2Strings::file open error" << endl;

    return ret;
}
