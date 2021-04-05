// NokiaInternShip.cpp: определяет точку входа для приложения.
//

#include "NokiaInternShip.h"

using namespace std;

const char delimiter = ',';

vector<vector<string>> loadFromFile(string);
void spaceDeleter(string &a);
void splitString(string &fullstr,vector<string> &elements, bool);
void findDuplicates(vector<string>);
void findDuplicates(string,set<string>&);

int main(int argc, char** argv)
{
	if (argc == 1) {
		cerr << "You should specify filename!"<<endl;
		return -1;
	}
	vector<vector<string>>table;
	string filename = argv[1];
	table = loadFromFile(filename);

	cout << "Hello CMake." << endl;

	system("pause");
	return 0;
}

vector<vector<string>> loadFromFile(string fileName) {
	vector<vector<string>> table;
	vector<string> strings;
	ifstream f;
	f.open(fileName);
	if (f.fail() || !f.is_open()) {
		f.close();
		cerr << "File not found!" << endl;
		system("pause");
		exit(-2);
	}
	string a;
	a.clear();
	getline(f, a);
	if (!a.empty()) {
		spaceDeleter(a);
		splitString(a, strings,true);
		findDuplicates(strings);
		table.push_back(strings);
		strings.clear();
	}
	else {
		if (f.eof()) {
			cerr << "File is empty!" << endl;
			exit(-3);
		}
		else {
			cerr << "First line is empty!" << endl;
			exit(-4);
		}
	}
	set<string> lineName;
	while (!f.eof()) {
		a.clear();
		getline(f, a);
		if (!a.empty()) {
			spaceDeleter(a);
			splitString(a, strings,false);
			findDuplicates(strings[0], lineName);
			table.push_back(strings);
			strings.clear();
		}
	}
	f.close();
	return table;
}

void spaceDeleter(string &str) {
		for (int i = 0; i < str.length(); i++) {
			if (str[i] == ' ') {
				str.erase(i, 1);
			}
		}
}

void splitString(string &fullstr,
	vector<string> &elements, bool thisIsFirstLine) {
	if (fullstr.length() == ',') {
		cerr << "Found a comma at the end of the line!" << endl;
		exit(-7);
	}
	string::size_type pos = 0;
	string::size_type lastpos = fullstr.find_first_of(delimiter, 0);
	if (thisIsFirstLine) {
		if (pos == lastpos) {
			pos = lastpos + 1;
			lastpos = fullstr.find_first_of(delimiter, pos);
		}
		else {
			cerr << "First symbol of the fisrt line should be empty!" << endl;
			exit(-5);
		}
	}
	

	while (string::npos != lastpos) {
		if (pos == lastpos) {
			cerr << "Empty column found!" << endl;
			exit(-8);
		}
		elements.push_back(fullstr.substr(pos, lastpos-pos));
		pos = lastpos+1;
		lastpos = fullstr.find_first_of(delimiter, pos);
	}
	elements.push_back(fullstr.substr(pos, fullstr.length()));
}

void findDuplicates(vector<string> splitString) {
	set<string>columns;
	for (auto i: splitString) {
		if (!columns.insert(i).second) {
			cerr << "Duplicate columns found!";
			columns.clear();
			exit(-6);
		}
	}
	columns.clear();
}

void findDuplicates(string lineName, set<string> &setOfNames) {
	if (!setOfNames.insert(lineName).second) {
		cerr << "Duplicate lines found!";
		exit(-6);
	}
}