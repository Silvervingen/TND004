#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cassert>  //assert

#include "BinarySearchTree.h"

#define TEST_EXERCISE3

/* *********************************************
 * Exercise 3: frequency table
 ********************************************* */

#ifdef TEST_EXERCISE3

struct Row {
	// ADD CODE: exercise 3
	std::string key = "";
	int counter = 1;

	// i insert() i binarysearchtree kollar man t->element
	// i en row är det t->element men eftersom en row har två värden
	// skapar man egna operatorer för att JÄMFÖRA key
	// insert() i binarysearch vet inte vad den ska jämföra och den kallar på dessa operator-funktioner
	//O(1)
	bool operator<(const Row& rhs) const
	{
		if (key < rhs.key)
		{
			return true;
		}
		else {
			return false;
		}
	}

	//O(1)
	bool operator>(const Row& rhs) const
	{
		if (key > rhs.key)
		{
			return true;
		}
		else {
			return false;
		}
	}

	//O(1)
	bool operator==(const Row& rhs) const
	{
		if (key == rhs.key)
		{
			return true;
		}
		else {
			return false;
		}
	}
};

// Add other stuff, if needed
// O(1)
std::ostream& operator<<(std::ostream& os, const Row& dt)
{
	int indent = 5;
	os << dt.key << std::string(indent, ' ') << dt.counter;
	return os;
}

#endif

void exercise3() {
#ifdef TEST_EXERCISE3
	{
		std::ifstream file("../code/text.txt");  // contains 56 unique words
		 //std::ifstream file("../code/text_long.txt"); // contains 497 unique words

		if (!file) {
			std::cout << "Couldn't open file text.txt\n";
			// std::cout << "Couldn't open file text_long.txt\n";
			return;
		}

		// ADD CODE: exercise 3
		std::string word = "";
		BinarySearchTree<Row> Tree; //Binärt träd med rader.
		std::vector<Row>Vector;

		//O(n) gå igenom alla
		while (file >> word)
		{
			// den tredje argumentet word.begin --> säger att man vill lägga in/override transfomrationen o böjran av ordet
			// alltså att man ändrar från början till slut i order, Elin --> elin, HEJ --> hej

			//den tredje haft word.end() där så hade det blivit ex Elinelin för vi börjar inserta i slutet av ordet

			std::transform(word.begin(), word.end(), word.begin(), [](char c) {return static_cast<char>(std::tolower(c)); });

			// remove skapar en iteror som letar upp alla tecken
			// std::remove(word.begin(), word.end(), ',' är en iterator med villkor som letar upp det där tecknet
			// anropar next funktion, returnera nästa som är enligt krav
			// erase använder iteratorn för att ta bort 'tecken'
			// word.erase, det är funktionen erase som tar bort tecknen från objektet word

			/* Borde funka men funkar endast för den långa vet ej varför.(Detta istället för att skriva erase för varje tecken)
			word.erase(std::remove_if(word.begin(), word.end(), [](char const& c) {
				return std::ispunct(c);
			}), word.end());
			*/
			//erase är enligt cppreference O(n)
			word.erase(std::remove(word.begin(), word.end(), ','), word.end());
			word.erase(std::remove(word.begin(), word.end(), '.'), word.end());
			word.erase(std::remove(word.begin(), word.end(), '"'), word.end());
			word.erase(std::remove(word.begin(), word.end(), '?'), word.end());
			word.erase(std::remove(word.begin(), word.end(), '!'), word.end());
			word.erase(std::remove(word.begin(), word.end(), ')'), word.end());
			word.erase(std::remove(word.begin(), word.end(), '('), word.end());
			word.erase(std::remove(word.begin(), word.end(), '/'), word.end());
			word.erase(std::remove(word.begin(), word.end(), ';'), word.end());
			word.erase(std::remove(word.begin(), word.end(), ':'), word.end());

			Row r;
			r.key = word;

			// man gör en iterator och kollar om ordet word =r.key finns
			// om den inte finns får man tilbaka table.end()
			// eftersom man har gått igenom det man har av trädet just nu
			BinarySearchTree<Row>::Iterator compareWord = Tree.find(r);

			if (compareWord == Tree.end()) {
				Tree.insert(r); //sätter in ett objekt från row r i tree t eftersom det inte finns än
			}
			else {
				compareWord->counter++; // om ordet redan finns ökar counter på det ordet
			}

		}//while-loop ends

		//Kommer i bokstavsordning för att trädet är i ordning (struktur)
		// O(n)
		for (auto i = Tree.begin(), end = Tree.end(); i != end; ++i) {
			auto counterV = *i; //transform an interator into a counter
			Vector.push_back(counterV);
		}

		file.close(); // stänger filen EFTER vi har insetat alla word till binary search

		// Display the binary search tree
		std::cout << "---------Tree: -----------\n";
		// O(n)
		Tree.printTree();
		std::cout << '\n';
		std::cout << "\nEND TREE\n\n";

		// Display the freq.table
		std::cout << "\n------ Table: ----------\n";

		// skapar en iterator som kan gå igenom vector V och ta fram key och counter
		// O(n)
		for (std::vector<Row>::iterator j = Vector.begin(); j != Vector.end(); ++j) {

			// variabler som ger mellanslag mellan ord och counter
			const char separator = ' ';
			const int wordWidth = 25; //utrymme finns för 25 bokstäver i ett ord
			const int counterWidth = 3; //utrymme för counter

			// left gör att j->key och j->counte rbörja rtill vänster i sitt lilla utrymme
			std::cout << std::left << std::setw(wordWidth) << std::setfill(separator) << j->key;
			std::cout << std::left << std::setw(counterWidth) << std::setfill(separator) << j->counter << "\n";

		}
	}
	assert(BinarySearchTree<Row>::get_count_nodes() == 0);

	std::cout << "Success!!\n";

#endif		
}