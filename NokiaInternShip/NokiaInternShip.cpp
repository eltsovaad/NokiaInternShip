// NokiaInternShip.cpp: определяет точку входа для приложения.
//TBD: убрать systempause, убрать кавычки перед выводом

#include "NokiaInternShip.h"

using namespace std;

const char delimiter = ',';

vector<vector<string>> loadFromFile(string);
void spaceDeleter(string &a);
void splitString(string &fullstr,vector<string> &elements, bool);
void findDuplicates(vector<string>);
void findDuplicates(string,set<string>&);
void lineParser(vector<vector<string>>&);
void sizeChecker(vector<vector<string>>);
void parseLine(string, vector<vector<string>>&);
string findExpression(vector<vector<string>>);

int main(int argc, char** argv)
{
	if (argc == 1) {
		cerr << "You should specify filename!"<<endl;
		exit(-1);
	}
	vector<vector<string>>table;
	string filename = argv[1];
	table = loadFromFile(filename);
	lineParser(table);
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
	string::size_type space = str.find_first_of(" \t", 0);
	while (string::npos != space) {
		if (string::npos != space)
			str.erase(space, 1);
		space = str.find_first_of(" \t", 0);
	}
}

void splitString(string &fullstr, vector<string> &elements, bool thisIsFirstLine) {
	if (fullstr.length() == ',') {
		cerr << "Found a comma at the end of the line!" << endl;
		exit(-7);
	}
	string::size_type pos = 0;
	string::size_type lastpos = fullstr.find_first_of(delimiter, 0);
	string::size_type openQuote = fullstr.find_first_of('"', 0);
	string::size_type openDoubleQuote = fullstr.find("\"\"", 0);
	string::size_type closeDoubleQuote = fullstr.find("\"\"", openDoubleQuote+2);
	string::size_type closeQuote = fullstr.find_first_of('"', openQuote + 1);
	if ((openQuote == openDoubleQuote)||(closeQuote == openDoubleQuote)) {
		closeQuote = fullstr.find_first_of('"', closeDoubleQuote + 2);
	}

	if (thisIsFirstLine) {
		if (pos == lastpos) {
			pos = lastpos + 1;
			lastpos = fullstr.find_first_of(delimiter, pos);
			if (lastpos > openQuote) {
				if (closeQuote != string::npos) {
					lastpos= fullstr.find_first_of(delimiter, closeQuote);
				}
				else {
					cerr << "You haven't closed quotes!" << endl;
					exit(-15);
				}
				openQuote= fullstr.find_first_of('"', closeQuote+1);
				closeQuote = fullstr.find_first_of('"', openQuote+1);
				openDoubleQuote = fullstr.find("\"\"", closeDoubleQuote + 2);
				closeDoubleQuote = fullstr.find("\"\"", openDoubleQuote + 2);
				if ((openQuote == openDoubleQuote) || (closeQuote == openDoubleQuote)) {
					closeDoubleQuote = fullstr.find("\"\"", openDoubleQuote + 2);
					closeQuote = fullstr.find_first_of('"', closeDoubleQuote + 2);
				}
			}
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
		if ((lastpos > openQuote)&&(lastpos<closeQuote)) {
			if (closeQuote != string::npos) {
				lastpos = fullstr.find_first_of(delimiter, closeQuote);
			}
			else {
				cerr << "You haven't closed quotes!" << endl;
				exit(-15);
			}
			openQuote = fullstr.find_first_of('"', closeQuote+1);
			openDoubleQuote = fullstr.find("\"\"", closeDoubleQuote + 2);
			closeDoubleQuote = fullstr.find("\"\"", openDoubleQuote + 2);
			closeQuote = fullstr.find_first_of('"', openQuote+1);
			if ((openQuote == openDoubleQuote) || (closeQuote == openDoubleQuote)) {
				closeDoubleQuote = fullstr.find("\"\"", openDoubleQuote+2);
				closeQuote = fullstr.find_first_of('"', closeDoubleQuote + 2);
			}
		}
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

void sizeChecker(vector<vector<string>> table) {
	if (table.size() < 2) {
		cerr << "You should have at least 2 lines at the table!" << endl;
		exit(-10);
	}
	if (table[0].size() < 1) {
		cerr << "You should have at least 1 column at the table!" << endl;
		exit(-11);
	}
	set<size_t>sizes;
	bool flag = false;
	for (auto vec : table) {
		sizes.insert(vec.size());
		if ((flag)&& (vec.size() == *sizes.begin())) {
			cerr << "Found lines with different length!" << endl;
			exit(-12);
		}
		flag = true;
	}
	if (sizes.size() > 2) {
		cerr << "Found lines with different length!" << endl;
		exit(-12);
	}
	if ((*sizes.begin() + 1) != (*(++sizes.begin()))) {
		cerr << "Number of columns doesn't match number of column names!" << endl;
		exit(-13);
	}
}

void lineParser(vector<vector<string>> &table) {
	sizeChecker(table);
	for (auto i : table) {
		if (i != table[0]) {
			for (auto j : i) {
				if (j != i[0]) {
					try {
						stod(j);
					}
					catch (const invalid_argument& ia) {
						if (j[0] == '=') {
							parseLine(j, table);
						}
						else {
							cerr << "Invalid expression found!" << endl;
							exit(-14);
						}
					}
				}
				else {
					try {
						stoi(j);
					}
					catch (const invalid_argument& ia) {
						cerr << "Found not integer line name!" << endl;
						exit(-16);
					}
				}

			}
		}
	}
}

void parseLine(string a, vector<vector<string>> &table) {
	string::size_type operation = a.find_first_of("+*/-", 0);
	if (operation != string::npos) {
		a = findExpression(table);
	}
	else {

	}
}