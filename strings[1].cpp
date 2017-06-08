#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <cstring>
#include <regex>
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
const int MAX_PER_LINE = 9;
int largest = 0;

void findall(vector<string>& v, string& s) {
	regex r("[a-zA-Z'-]+");
	for_each(sregex_iterator(begin(s), end(s), r), sregex_iterator(), [&v](smatch p) {
		if (p.str().length() > largest) {
			largest = p.str().length();
		}
		v.push_back(p.str()); });
}
struct comp {
	bool operator()(const string& a, const string& b) const{
		if (strcasecmp(a.c_str(), b.c_str()) < 0)
			return true;
		else if (strcasecmp(a.c_str(), b.c_str()) > 0)
			return false;
		else
			return a < b;
	}
};
struct length {
	bool operator() (const string& a, const string& b)
	{
		return a.size() < b.size();
	}
};
void addToMap(map<string, map<int, int>, comp>& wordMap, vector<string>& v, int lineCount) {
	for (int i = 0; i < v.size(); ++i) {
		++wordMap[v.at(i)][lineCount];
	}
}


int main(int argc, const char* argv[]) {

	std::ofstream ofs;
	ofs.open("output.txt", std::ofstream::out);//| std::ofstream::app

	
	ifstream myFile;
	string fileName;
	int spaceFiller = 0;
	string longest, temp;
	map<string, map<int, int>, comp> wordsLineCount;

	if (argc == 2) {
		fileName = argv[1];
		myFile.open(fileName);

		while (myFile.fail())
		{
			cout << "The file at location " << fileName << " failed to open." << endl;
			cout << "Please enter the location of the file: ";
			getline(cin, fileName);
			myFile.open(fileName);
		}
		cout << "You opened " << fileName << endl;
	}
	else {
		cout << "You must specify a file location: (myFile.txt)" << endl;

		//gets file location from the user if not in command line argv
		getline(cin, fileName);

		//opens the file
		myFile.open(fileName);

		//makes sure that the file opened properly
		while (myFile.fail())
		{
			cout << "The file at location " << fileName << " failed to open." << endl;
			cout << "Please enter the location of the file: ";
			getline(cin, fileName);
			myFile.open(fileName);
		}
		cout << "You opened " << fileName << endl;
	}

	//start processing the file.
	string read1, read2;
	int lineCount = 1;
	vector <string> words;
	while (getline(myFile, read1)) {
		//vector <string> words;
		findall(words, read1);

		//add to the map
		addToMap(wordsLineCount, words, lineCount);
		++lineCount;
		words.clear();

	}

	//print out data
	int countPos1 = 0;
	int countPos = 0;

	spaceFiller = largest + 1;
	int newLineSpaceFiller = spaceFiller + 1;
	++newLineSpaceFiller;

	for (auto pos = wordsLineCount.begin(); pos != wordsLineCount.end(); ++pos) {
		ofs << std::left << setw(spaceFiller) << std::setfill(' ') << pos->first << ": "; // align output to left, fill goes to right			
		countPos1 = 1;
		for (auto pos1 = pos->second.begin(); pos1 != pos->second.end(); ++pos1) {
			if (countPos == 0) {
				ofs << pos1->first << ":" << pos1->second;
				--countPos1;
				countPos = 1;
			}
			else {
				if (countPos1%MAX_PER_LINE == 0) {
					ofs << endl;
					ofs << std::right << setw(newLineSpaceFiller) << std::setfill(' ');
					ofs << " : ";
				}
				ofs << pos1->first << ":" << pos1->second;
			}
			if ((++pos1) != pos->second.end()) {
				ofs << ", ";
			}
			--pos1;
			++countPos1;
		}
		countPos = 0;
		ofs << endl;

	}
	ofs.close();
}
//This was good to have right before/during spring break. Still makes you think but once you get it then you get it :) 
//It was a little struggle to get the display just right. I still wonder if the way I did it was the best or if there are better ways. 
//I did have this running but it was taking like 30 second to run. I changed the way i did things so the it now uns faster... Under couple seconds. 
//I feel this was a valuable program to do. 