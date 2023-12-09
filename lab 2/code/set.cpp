#include "set.h"
#include "node.h"


int Set::Node::count_nodes = 0;  // initialize total number of existing nodes to zero

/*****************************************************
 * Implementation of the member functions             *
 ******************************************************/

 // Used for debug purposes -- static member function
 // Return number of existing nodes
int Set::get_count_nodes() {
	return Set::Node::count_nodes;
}

// Default constructor
Set::Set() : counter{ 0 } {
	head = new Node;
	tail = new Node;

	head->next = tail;
	tail->prev = head;

}

// Conversion constructor
Set::Set(int n) : Set{} {  // create an empty list
	insert_node(tail, n);
}

// Constructor to create a Set from a sorted vector v
// create an empty list
Set::Set(const std::vector<int>& v) : Set{} {

	Node* p = head;

	for (int item : v) {
		p = p->next = new Node(item, nullptr, p);
		++counter;
	}
	p->next = tail;
	tail->prev = p;
}

// Make the set empty
void Set::make_empty() {
	if (head->next == tail) return;

	Node* p = head->next;

	while (p != tail) {
		p = p->next;
		delete p->prev;
	}

	head->next = tail;
	tail->prev = head;
	counter = 0;
}

// Destructor
Set::~Set() {
	make_empty();
	delete head; delete tail;
}

// Copy constructor
Set::Set(const Set& source) : Set{} {  // create an empty list
	Node* ps = source.head->next;
	Node* pt = head;

	while (ps != source.tail) {
		pt->next = new Node(ps->value, nullptr, pt);
		ps = ps->next;
		pt = pt->next;
	}

	pt->next = tail;
	tail->prev = pt;
	counter = source.counter;
}


// Copy-and-swap assignment operator
Set& Set::operator=(Set source) {
	std::swap(head, source.head);
	std::swap(tail, source.tail);
	//std::swap(counter, source.counter);

	counter = source.counter;

	return *this;
}

// Test set membership
bool Set::is_member(int val) const {
	if (head->next == tail) return false;
	if (head->next->value > val || tail->prev->value < val) return false;

	Node* p = head->next;

	while (p != tail) {
		if (p->value == val) return true;
		p = p->next;
	}

	return false;
}

// Test whether a set is empty
bool Set::is_empty() const {
	return (counter == 0);
}

// Return number of elements in the set
size_t Set::cardinality() const {
	return counter;
}

// Return true, if the set is a subset of b, otherwise false
// a <= b iff every member of a is a member of b
bool Set::less_than(const Set& b) const {
	Node* p1 = head->next;
	Node* p2 = b.head->next;

	while (p1 != tail && p2 != b.tail) {
		if (p1->value > p2->value) {
			p2 = p2->next;
		}
		else if (p1->value < p2->value) return false;
		p2 = p2->next;
		p1 = p1->next;
	}
	return p1 == tail;  // delete if needed
}

// Modify *this such that it becomes the union of *this with Set S
// Add to *this all elements in Set S (repeated elements are not allowed)
Set& Set::operator+=(const Set& S) {

	Node* p1 = head->next;
	Node* p2 = S.head->next;

	while (p1 != tail && p2 != S.tail) {
		if (p1->value < p2->value) {
			p1 = p1->next;
		}
		else if (p1->value > p2->value) {
			insert_node(p1, p2->value);
			p2 = p2->next;
		}
		else {
			p1 = p1->next;
			p2 = p2->next;
		}
	}

	while (p2 != S.tail) {
		insert_node(p1, p2->value);
		p2 = p2->next;
		p1 = p1->next;
	}

	return *this;
}

// Modify *this such that it becomes the intersection of *this with Set S
Set& Set::operator*=(const Set& S) {

	if (is_empty() || S.is_empty()) {
		*this = Set{};
		return *this;
	}

	Node* p1 = head->next;
	Node* p2 = S.head->next;

	while (p1 != tail && p2 != S.tail) {
		if (p1->value < p2->value) {
			Node* temp = p1;
			p1 = p1->next;
			remove_node(temp);
		}
		else if (p1->value > p2->value) {
			p2 = p2->next;
		}
		else {
			p1 = p1->next;
			p2 = p2->next;
		}
	}

	while (p1 != tail) {
		Node* temp = p1;
		p1 = p1->next;
		remove_node(temp);
	}

	return *this;
}

// Modify *this such that it becomes the Set difference between Set *this and Set S
Set& Set::operator-=(const Set& S) {

	if (is_empty()) {
		return *this;
	}

	Node* p1 = head->next;
	Node* p2 = S.head->next;

	while (p1 != tail && p2 != S.tail) {
		if (p1->value < p2->value) {
			p1 = p1->next;
		}
		else if (p1->value > p2->value) {
			p2 = p2->next;
		}
		else {
			Node* temp = p1;
			p1 = p1->next;
			p2 = p2->next;
			remove_node(temp);
		}
	}

	return *this;
}

/* ******************************************** *
 * Private Member Functions -- Implementation   *
 * ******************************************** */

 // If you add any private member functions to class Set then write the implementation here


void Set::write_to_stream(std::ostream& os) const {
	if (is_empty()) {
		os << "Set is empty!";
	}
	else {
		Set::Node* temp{ head->next };

		os << "{ ";
		while (temp != tail) {
			os << temp->value << " ";
			temp = temp->next;
		}
		os << "}";
	}
}


// Insert a new Node storing val after the Node pointed by p
void Set::insert_node(Node* p, int val) {
	p->prev = p->prev->next = new Node(val, p, p->prev);
	counter++;
}

// Remove the Node pointed by p
void Set::remove_node(Node* p) {
	p->prev->next = p->next;
	p->next->prev = p->prev;
	counter--;
	delete p;
}