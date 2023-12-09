#pragma once

/* **********************************************************
 * Class to represent a bi-directional iterator for BSTs     *
 * Bi-directional iterators can be moved in both directions, *
 * increasing and decreasing order of items keys             *
 * ***********************************************************/

template <typename Comparable>
class BinarySearchTree<Comparable>::Iterator {
public:
    // Some properties for Iterator  -- so that Iterator can be used with STL-algorithms
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = Comparable;
    using pointer           = Comparable*;  // or also value_type*
    using reference         = Comparable&;  // or also value_type&

    /* ****************************************************************** */

   // Exercise 2: ADD CODE   


	friend class BinarySearchTree;

	Iterator() : current{ nullptr } {}; //default constructor

	~Iterator() = default;

	Comparable& operator*() const { //reference operator
		return current->element;
	}

	Comparable* operator->() const { //pointer operator
		return &current->element;
	}

	bool operator==(const Iterator & it) {
		return (current == it.current);
	}

	bool operator!=(const Iterator & it) {
		return !(current == it.current);
	}

	Iterator& operator++() { //Pre-increment
		current = ptr->find_successor(current);
		return *this; //return iterator by reference
	}

	Iterator operator++(int) { //Pos-increment
		Iterator result = *this; //make a copy of iterator
		this->operator++(); //advance iterator to next element
		return result; //return copy by value
	}


	Iterator& operator--() { //Pre-decrement
		current = ptr->find_predecessor(current);
		return *this; //return iterator by reference
	}

	Iterator operator--(int) { //Pos-decrement
		Iterator result = *this; //make copy of iterator
		this->operator--(); //advance iterator
		return result; //return copy by value
	}

private:
	BinarySearchTree* ptr = nullptr;
	Node* current;
	Iterator(BinarySearchTree * p1, Node * p2) : ptr{ p1 }, current{ p2 } { };
};