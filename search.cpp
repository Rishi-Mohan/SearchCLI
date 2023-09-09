#include <iostream>
#include <string>
#include <fstream>

#include "trie.cpp"

using namespace std;

int main(int argc, char const *argv[])
{
	string data;
	fstream dictionary;
	Trie query;

	dictionary.open("dictionary.txt", fstream::in); //read dictionary file into trie tree structure
	if (dictionary.is_open())
	{
		while (dictionary)
		{
			dictionary >> data;
			query.insert(data); // inserting into the query
		}
	}
	else
	{
		cout << "error:  file not open." << endl;
		return -1;
	}

	dictionary.close();

	data.clear(); //clear string variable used for file input; string variable will read in user input

	// --------------------------------------- User Interaction ----------------------------------------

	cout << "\t\t\t\t\t Welcome to Search CLI \n";
	cout << "\t\t\t\t======================================\n";

	int choice;
	do {
		cout << "\t\t\t\t1. Search Query \n";
		cout << "\t\t\t\t0. Exit\n";
		cout << "\n\n\t\t\t\tEnter your Choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "\n\t\t\t\tEnter Search Text (leave empty to list all): ";
			cin.ignore();
			getline(cin, data); // getline used over std::cin to catch spaces
			query.is_space(data); // checks whether there's a space in user query

			cout << "\n\n\t\t\t\tYour search options are" << endl;
			cout << "\t\t\t\t======================================\n";

			if (query.getSpace() == true) // if a space exists, remove prefix and pass prefix only to search method
			{
				query.remove_prefix(data);
				query.search(query.break_string(data));
			}
			else { // if no method exists, pass user's query to search method to auto-complete the query
				query.search(data);
			}

			break;
		default:
			break;

		}
		if (choice != 1) {
			cout << "\t\t\t\t======================================\n";
			cout << "\t\t\t\t\t **** Thanku You **** \n";
			cout << "\t\t\t\t======================================\n";

		}
		else {
			cout << "\n\n\t\t\t\t======================================\n";
		}

	} while (choice);


	return 0;
}
