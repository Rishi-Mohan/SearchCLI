#include <iostream>
#include <string>
using namespace std;

class Node //node used to hold data in trie tree structure
{
	friend class Trie;
private:
	char c;
	bool word; //true = marks end of word
	Node* child[128]; //points to next node; each pointer for each char in ASCII table (0-127)
public:
	Node() {
		this->setChar('\0');
		this->setWord(false);
		for (int i = 0; i < 128; i++)
			this->child[i] = NULL;
	}

	void setWord(int flag) {
		this->word = flag;
	}
	bool isWord() {
		return this->word;
	}
	void setChar(char ch) {
		this->c = ch;
	}
	char getChar() const {
		return this->c;
	}
};


class Trie
{
	friend class Node;
private:
	bool space; //true - string that stores user query contains space
	string no_prefix; //if space in string exists - string that stores user query minus prefix used for query completion
	Node* root;
public:
	Trie() {
		root = new Node(); 
		this->space = false;
	}
	void is_space(string data); //searches user's query string for space and sets bool space appropriately
	bool getSpace() {
		return space;
	}
	void insert(string data); //builds trie tree struction
	void search(string data); //wrapper for main auto-completion method; advances to last char in user's prefix
	void print_tree(Node* root, string data, string str); //prints suggested queries
	void print_tree(Node* root, string str); //overloaded print_tree method used for recursion
	void remove_prefix(string data); //removes the prefix (if space in string)
	string getNo_prefix() {
		return no_prefix;
	}
	string break_string(string); //returns only prefix (if space in string) used in search and print_tree methods
};

void Trie::insert(string data) //constructions trie tree structure
{
	Node* tmp = root;
	for (auto ch : data)
	{
		if (tmp->child[ch] != NULL) 
			tmp = tmp->child[ch];
		else
		{
			tmp->child[ch] = new Node(); //create new node
			tmp = tmp->child[ch];
			tmp->setChar(ch); //insert char in new node
		}
	}
	tmp->setWord(true); //mark word
}

// method that prints query options to completing the incomplete word -> suffix word
void Trie::print_tree(Node* root, string data, string str) 
{
 	for (int i = 0; i < 128; i++) //loops through all 128 pointers in node to check if there's a child
	{
		Node* adv = root;
		if (adv->child[i] != NULL) //child exists
		{
			adv = adv->child[i]; //advance pointer
			str += adv->getChar(); //append char to end of prefix
			
			if (adv->isWord()) //if point at end of word, print word
			{
				cout << "\t\t\t\t";
				if (this->getSpace() == true) //if the user's search query contained a space, print the search query minus prefix then print word
					cout << this->getNo_prefix();
				cout << str << endl;
			}
			// after every addition of new char we are exploring all the path that is available
			print_tree(adv, str); //recursive call to keep moving down tree
		}
		str = data; //reset prefix string
	}
}




void Trie::print_tree(Node* root, string str) //overloaded function for recursive calls
{
	string str_tmp = str; // str_tmp is the incomplete last word that need to be completed everytime

	for (int i = 0; i < 128; i++)
	{
		Node* adv = root;
		if (adv->child[i] != NULL)
		{
			adv = adv->child[i];
			str += adv->getChar();
			if (adv->isWord())
			{
				cout << "\t\t\t\t";
				if (this->getSpace() == true) // we found one word that matched to prefix
					cout << this->no_prefix;  // printed the all string except the last word
				cout << str << endl;          // last word is now str -> completed word
			}

			print_tree(adv, str); // ?
		}
		str = str_tmp; // again reassigning to the original incomplete string
	}
}

// 
void Trie::search(string data) //wrapper for function that completes the prefix, generating search options
{
	Node* tmp = root;

	for (auto ch : data) 
	{
		if (tmp->child[ch] == NULL) // string is not found in the string
		{
			cout << "\n\t\t\t\terror:  string not found" << std::endl;
			return;
		}
		else{
			tmp = tmp->child[ch];
		}

		// cout << "point 1" << endl;
		if (tmp->getChar() != ch) // lets user know if prefix not in dictionary (char does not match corresponding char in prefix)
		{
			cout << "\n\t\t\t\terror:  string not found 222222222" << endl;
			return;
		}
	}
	string str = data;          //copy user's query prefix into generic string used for appending operations to complete query prefix in print_tree method
	if(tmp->isWord()){
		cout << "\t\t\t\t";
		if(this->getSpace() == true)
			cout << this->no_prefix;
		cout << str << endl;
	}
	print_tree(tmp, data, str);	//passes pointer that has advanced to last char in query prefix to printing method
	// tmp : advance pointer of the last char
	// data : original incomplete suffix
	// str : original incomplete suffix
}

// if user string contains space in the query
void Trie::is_space(string data) 
{
	for (auto ch : data)
	{
		if (ch == ' ')
		{
			space = true;
			return;
		}
		
	}
}

// return only suffix word that need to be completed given that space is given
string Trie::break_string(string data) 
{
	string str;
	int ind = -1;
	for(int i = data.length() - 1; i >= 0; i--){
		if(data[i] == ' '){
			ind = i;
			break;
		}
	}
	str = data.substr(ind + 1);
	return str; 
}

// all string except last suffix word
void Trie::remove_prefix(string data) //method removes the user's query prefix and copies to no_prefix attribute; print to screen along with
												//completed words to offer user search options
{
	int ind = -1;
	for(int i = data.length() - 1; i>=0; i--){
		if(data[i] == ' '){
			ind = i;
			break;
		}
	}
	no_prefix = data.substr(0, ind + 1);
}