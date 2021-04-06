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
void evalFormula(string&,int,int, vector<vector<string>>, set<pair<int,int>>);
string findExpression(vector<vector<string>>);
bool findInTable(string&, int, int, vector<vector<string>>, set<pair<int, int>>);
void tableViewer(vector<vector<string>>);

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
	tableViewer(table);
	system("pause");
	return 0;
}

vector<vector<string>> loadFromFile(string fileName) {
	//loads table from file
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
	//Deletes spaces and tabs
	string::size_type space = str.find_first_of(" \t", 0);
	while (string::npos != space) {
		if (string::npos != space)
			str.erase(space, 1);
		space = str.find_first_of(" \t", 0);
	}
}

void splitString(string &fullstr, vector<string> &elements, bool thisIsFirstLine) {
	//splits fullstr into a vector of string (elements)
	//thisIsFirstLine should be true for a title line (first)
	if (fullstr[fullstr.length()-1] == ',') {
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
			if (lastpos > openQuote) {//working with commas inside quotes
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
			cerr << "Empty cell found!" << endl;
			exit(-8);
		}
		elements.push_back(fullstr.substr(pos, lastpos-pos));
		pos = lastpos+1;
		lastpos = fullstr.find_first_of(delimiter, pos);
		if ((lastpos >= openQuote)&&(lastpos<closeQuote)) {//working with commas inside quotes
			if ((lastpos > openDoubleQuote) && (lastpos < closeDoubleQuote)) {
				if (closeDoubleQuote != string::npos) {
					lastpos = fullstr.find_first_of(delimiter, closeQuote);
					openDoubleQuote = fullstr.find("\"\"", closeDoubleQuote + 2);
					closeDoubleQuote = fullstr.find("\"\"", openDoubleQuote + 2);
				}
				else {
					cerr << "You haven't closed quotes!" << endl;
					exit(-15);
				}
			}
			if (closeQuote != string::npos) {
				lastpos = fullstr.find_first_of(delimiter, closeQuote);
			}
			else {
				cerr << "You haven't closed quotes!" << endl;
				exit(-15);
			}
			openQuote = fullstr.find_first_of('"', closeQuote+1);
			closeQuote = fullstr.find_first_of('"', openQuote+1);
			if ((openQuote == openDoubleQuote) || (closeQuote == openDoubleQuote)) {
				closeDoubleQuote = fullstr.find("\"\"", openDoubleQuote+2);
				closeQuote = fullstr.find_first_of('"', closeDoubleQuote + 2);
			}
		}
	}
	if (pos != openQuote) {
		elements.push_back(fullstr.substr(pos, fullstr.length()));
	}
	else {
		cerr << "You haven't closed quotes!" << endl;
		exit(-15);
	}
	
}

void findDuplicates(vector<string> splitString) {
	//finds duplicates in the title line
	set<string>columns;
	for (auto i: splitString) {
		if (i.find_first_of("1234567890") != string::npos) {
			cerr << "Numbers in columnnames found!";
			columns.clear();
			exit(-23);
		}
		if (!columns.insert(i).second) {
			cerr << "Duplicate columns found!";
			columns.clear();
			exit(-6);
		}
	}
	columns.clear();
}

void findDuplicates(string lineName, set<string> &setOfNames) {
	//finds duplicates in linenames
	if (!setOfNames.insert(lineName).second) {
		cerr << "Duplicate lines found!";
		exit(-6);
	}
}

void sizeChecker(vector<vector<string>> table) {
	//checks length of lines and compares
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
	//first stage of cell parsing - searching for formulas in cells
	sizeChecker(table);
	for (int i = 1; i < table.size();i++) {
			for (int j = 0; j < table[i].size(); j++) {
				if (j != 0) {
					try {
						stod(table[i][j]);
					}
					catch (const invalid_argument& ia) {
						if (table[i][j][0] == '=') {//if formula is found
							set<pair<int, int>> history;
							evalFormula(table[i][j],i,j, table, history);
						}
						else {
							cerr << table[0][j] << table[i][0] << ": Invalid expression found!" << endl;
							exit(-14);
						}
					}
				}
				else {//checks linenames
					try {
						stoul(table[i][j]);
					}
					catch (const invalid_argument& ia) {
						cerr << table[0][j] << table[i][0] << ": Found not integer line name!" << endl;
						exit(-16);
					}
				}

			}
	}
}

void evalFormula(string &a, int line, int column,vector<vector<string>> table, set<pair<int,int>> history) {
	//evaluating formula with args found by findInTable(). Copies hystory in MyHistory and inserts only to a copy
	string::size_type operation = a.find_first_of("+*/-", 0);
	set<pair<int, int>> MyHistory(history);
	if (operation == string::npos) {//if there are no operations
		try {
			a.erase(0,1);//erasing '=' as a first digit of formula
			stod(a);
		}
		catch (const invalid_argument& ia) {
			if (MyHistory.insert(pair<int, int>(line, column)).second) {
				if (!findInTable(a, line, column, table, MyHistory)) {
					cerr << table[0][column-1]<<table[line][0]<<": Couldn't find cell!!" << endl;
					exit(-18);
				}
			}
			else {
				cerr << table[0][column-1] << table[line][0] << ": A loop in links found!" << endl;
				exit(-17);
			}
		}
	}
	else {//if operations were found
		a.erase(0, 1);//erasing '=' as a first digit of formula
		string firstArg = a.substr(0, operation-1);
		string secondArg = a.substr(operation, a.length()-operation);
		if (secondArg.find_first_of("+*/-", 0) != string::npos) {
			cerr << table[0][column-1] << table[line][0] << ": Found more than one operation in a cell" << endl;
			exit(-22);
		}
		try {
			double firstArgDouble=stod(firstArg);
		}
		catch (const invalid_argument& ia) {
			if (MyHistory.insert(pair<int, int>(line, column)).second) {
				if (!findInTable(firstArg, line, column, table, MyHistory)) {
					cerr << table[0][column-1] << table[line][0] << ": Couldn't find cell!!" << endl;
					exit(-18);
				}
			}
			else {
				cerr << table[0][column-1] << table[line][0] << ": A loop in links found!" << endl;
				exit(-17);
			}
		}
		try {
			double secondArgDouble = stod(secondArg);
		}
		catch (const invalid_argument& ia) {
				if (!findInTable(secondArg, line, column, table, MyHistory)) {
					cerr << table[0][column-1] << table[line][0] << ": Couldn't find cell!" << endl;
					exit(-18);
				}
		}
		//evaluating an operation
		if ((!firstArg.empty()) && (!secondArg.empty())) {
			double rez;
			switch (a[operation-1]) {
			case '*': {
				try {
					rez = stod(firstArg)*stod(secondArg);
				}
				catch (const invalid_argument& ia) {
					cerr << table[0][column-1] << table[line][0] << ": Couldn't evaluate expression!" << endl;
					exit(-19);
				}
				break;
			}
			case '+': {
				try {
					rez = stod(firstArg) + stod(secondArg);
				}
				catch (const invalid_argument& ia) {
					cerr << table[0][column-1] << table[line][0] << ": Couldn't evaluate expression!" << endl;
					exit(-19);
				}

				break;
			}
			case '-': {
				try {
					rez = stod(firstArg) - stod(secondArg);
				}
				catch (const invalid_argument& ia) {
					cerr << table[0][column-1] << table[line][0] << ": Couldn't evaluate expression!" << endl;
					exit(-19);
				}

				break;
			}
			case '/': {
				try {
					if (stod(secondArg) != 0) {
						rez = stod(firstArg) / stod(secondArg);
					}
					else {
						cerr << table[0][column-1] << table[line][0] << ": Division by zero!" << endl;
						exit(-20);
					}
				}
				catch (const invalid_argument& ia) {
					cerr << table[0][column-1] << table[line][0] << ": Couldn't evaluate expression!" << endl;
					exit(-19);
				}


				break;
			}
			default: {
				cerr << table[0][column-1] << table[line][0] << ": Unknown error!" << endl;
				exit(-21);
			}
			}
			ostringstream streamObj;
			// Set Fixed -Point Notation
			streamObj << std::fixed;
			// Set precision to 2 digits
			if (fmod(rez, 1) > 0) {
				streamObj << std::setprecision(2);
			}
			else {
				streamObj << std::setprecision(0);
			}
			//Add double to stream
			streamObj << rez;
			// Get string from output string stream
			a = streamObj.str();
		}
		else {
			cerr << table[0][column-1] << table[line][0] << ": One of the arguments is empty!" << endl;
			exit(-9);
		}
	}
}

bool findInTable(string& str, int line, int column, vector<vector<string>> table, set<pair<int, int>>history) {
	//searches cell in formulas. If another formula is found evalFormula is calling
	string::size_type linenumberPosition=str.find_first_of("1234567890");
	if (linenumberPosition == string::npos) {
		cerr << table[0][column-1] << table[line][0] << ": Invalid expression found!" << endl;
		exit(-14);
	}
	string lineNumber = str.substr(linenumberPosition, str.length());
	string columnName = str.substr(0, linenumberPosition);
	bool wasFound = false;
	vector<string>::iterator columnIterator;
	for (int i = 1; i < table.size(); i++) {
		if (lineNumber == table[i][0]) {
			for (int j = 0; j < table[0].size(); j++) {
				if (columnName == table[0][j]) {
					wasFound = true;
					j++;
					try {
						stod(table[i][j]);
						str = table[i][j];
					}
					catch (const invalid_argument& ia) {
						if (table[i][j][0] == '=') {
							str = table[i][j];
							evalFormula(str, i, j, table, history);
						}
						else {
							cerr << table[0][j] << table[i][0] << ": Invalid expression found!" << endl;
							exit(-14);
						}
					}
					break;
				}
			}
		}
	}
	return wasFound;
}

void tableViewer(vector<vector<string>> table) {
	//prints table to the console
	cout << ',';
	for (auto i : table) {
		for (int j = 0; j < i.size(); j++) {
			//this commented code was used to view quotes without double quotes and colunmnames with commas in quotes
			/*if (i[j].find_first_of('"') != string::npos) {
					set <string::size_type> doubleQuotesPositions;
					string::size_type lastpos = 0;
					while (i[j].find("\"\"", lastpos) != string::npos) {
						doubleQuotesPositions.insert(i[j].find("\"\"", lastpos));
						lastpos += 2;
					}
					lastpos = 0;
					while (i[j].find('"', lastpos) != string::npos) {
						set <string::size_type> temp(doubleQuotesPositions);
						if (temp.insert(i[j].find('"', lastpos)).second) {
							i[j].erase(i[j].find('"', lastpos), i[j].find('"', lastpos)+1);

						}
						else {
							lastpos++;
						}
					}
					lastpos = 0;
					while (i[j].find("\"\"", lastpos) != string::npos) {
						i[j].erase(i[j].find("\"\"", lastpos), i[j].find("\"\"", lastpos)+2);
						lastpos += 2;
					}
			}*/
			if (j != i.size()-1) {
				cout << i[j] << ',';
			}
			else {
				cout << i[j];
			}
		}
		cout << endl;
	}
}