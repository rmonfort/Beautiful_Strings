#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <algorithm>
#include <set>
#include <map>
#include <utility>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::sort;
using std::set;
using std::multimap;

class Beauty_Judge
{
public:
	Beauty_Judge(const string& s); // Constructor
	int quanitify_beauty();
private:
	string entry;
};

// Constructor
Beauty_Judge::Beauty_Judge(const string &s)
{
	entry = s;
}

// Determines beauty of string entry
int Beauty_Judge::quanitify_beauty()
{
	string sorted_entry;

	// Cycle through each character in entry 
	for (auto &l : entry)
	{
		// Ignore punctuation and whitespace
		if (ispunct(l) || isspace(l) || isdigit(l))
		{
			continue; 
		}
		// Convert to lowercase if uppercase and load into sorted_entry
		else if (isupper(l))
		{
			
			sorted_entry.push_back(tolower(l)); 
		}
		// Load into sorted_entry otherwise
		else
		{
			sorted_entry.push_back(l); 
		}
	}

	// Sort string and obtain unique elements by copying into a set
	sort(sorted_entry.begin(), sorted_entry.end());
	set<char> uniques(sorted_entry.begin(), sorted_entry.end());

	// Pair number of occurrences in sorted_entry with each character in uniques
	std::multimap<int, char> occurrences;
	for (const auto &l : uniques)
	{
		int temp = std::count(sorted_entry.begin(), sorted_entry.end(), l);
		occurrences.insert(std::make_pair(temp, l));
	}

	// Cycle through occurrences while calculating beauty
	int count = 26;
	int sum = 0;
	for (auto it = occurrences.crbegin(); it != occurrences.crend(); it++, count--)
	{
		sum += (it->first * count);
	}
	return sum;
}

int main(int argc, char *argv[])
{
	string input_file;

	// Check first argument if it exists for input file, otherwise ask user
	if (argc > 1)
	{
		input_file = argv[1];
	}
	else
	{
		cout << "Please enter the path to your input file: " << endl;
		cin >> input_file;
	}

	// Open input file and check if successfully opened
	ifstream ifs(input_file);
	if (!ifs)
	{
		cout << "Failed to open input file." << endl;
		return 1;
	}

	// Cycle through each line in file
	string line;
	while (getline(ifs, line))
	{
		// Ignore empty lines
		if (line.empty())
		{
			continue;
		}

		// Create beauty object using constructor and output beauty
		Beauty_Judge bj(line);
		int beauty = bj.quanitify_beauty();
		cout << beauty << endl;
	}

	return 0;
}