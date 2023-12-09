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
	// i en row �r det t->element men eftersom en row har tv� v�rden
	// skapar man egna operatorer f�r att J�MF�RA key
	// insert() i binarysearch vet inte vad den ska j�mf�ra och den kallar p� dessa operator-funktioner
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
		BinarySearchTree<Row> Tree; //Bin�rt tr�d med rader.
		std::vector<Row>Vector;

		//O(n) g� igenom alla
		while (file >> word)
		{
			// den tredje argumentet word.begin --> s�ger att man vill l�gga in/override transfomrationen o b�jran av ordet
			// allts� att man �ndrar fr�n b�rjan till slut i order, Elin --> elin, HEJ --> hej

			//den tredje haft word.end() d�r s� hade det blivit ex Elinelin f�r vi b�rjar inserta i slutet av ordet

			std::transform(word.begin(), word.end(), word.begin(), [](char c) {return static_cast<char>(std::tolower(c)); });

			// remove skapar en iteror som letar upp alla tecken
			// std::remove(word.begin(), word.end(), ',' �r en iterator med villkor som letar upp det d�r tecknet
			// anropar next funktion, returnera n�sta som �r enligt krav
			// erase anv�nder iteratorn f�r att ta bort 'tecken'
			// word.erase, det �r funktionen erase som tar bort tecknen fr�n objektet word

			/* Borde funka men funkar endast f�r den l�nga vet ej varf�r.(Detta ist�llet f�r att skriva erase f�r varje tecken)
			word.erase(std::remove_if(word.begin(), word.end(), [](char const& c) {
				return std::ispunct(c);
			}), word.end());
			*/
			//erase �r enligt cppreference O(n)
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

			// man g�r en iterator och kollar om ordet word =r.key finns
			// om den inte finns f�r man tilbaka table.end()
			// eftersom man har g�tt igenom det man har av tr�det just nu
			BinarySearchTree<Row>::Iterator compareWord = Tree.find(r);

			if (compareWord == Tree.end()) {
				Tree.insert(r); //s�tter in ett objekt fr�n row r i tree t eftersom det inte finns �n
			}
			else {
				compareWord->counter++; // om ordet redan finns �kar counter p� det ordet
			}

		}//while-loop ends

		//Kommer i bokstavsordning f�r att tr�det �r i ordning (struktur)
		// O(n)
		for (auto i = Tree.begin(), end = Tree.end(); i != end; ++i) {
			auto counterV = *i; //transform an interator into a counter
			Vector.push_back(counterV);
		}

		file.close(); // st�nger filen EFTER vi har insetat alla word till binary search

		// Display the binary search tree
		std::cout << "---------Tree: -----------\n";
		// O(n)
		Tree.printTree();
		std::cout << '\n';
		std::cout << "\nEND TREE\n\n";

		// Display the freq.table
		std::cout << "\n------ Table: ----------\n";

		// skapar en iterator som kan g� igenom vector V och ta fram key och counter
		// O(n)
		for (std::vector<Row>::iterator j = Vector.begin(); j != Vector.end(); ++j) {

			// variabler som ger mellanslag mellan ord och counter
			const char separator = ' ';
			const int wordWidth = 25; //utrymme finns f�r 25 bokst�ver i ett ord
			const int counterWidth = 3; //utrymme f�r counter

			// left g�r att j->key och j->counte rb�rja rtill v�nster i sitt lilla utrymme
			std::cout << std::left << std::setw(wordWidth) << std::setfill(separator) << j->key;
			std::cout << std::left << std::setw(counterWidth) << std::setfill(separator) << j->counter << "\n";

		}
	}
	assert(BinarySearchTree<Row>::get_count_nodes() == 0);

	std::cout << "Success!!\n";

#endif		
}