/*********************************************
 * file:	~\code4b\graph.h                  *
 * remark:implementation of undirected graphs *
 **********************************************/

#include <iostream>
#include <iomanip>
#include <cassert>  //assert

#include "graph.h"
#include "heap.h"
#include "dsets.h"

#include <algorithm>
#include <queue>
using namespace std;

// Note: graph vertices are numbered from 1 -- i.e. there is no vertex zero

// -- CONSTRUCTORS

// Create a graph with n vertices and no vertices
Graph::Graph(int n) : table(size_t(n) + 1), size{n}, n_edges{0} {
    assert(n >= 1);
}

Graph::Graph(const std::vector<Edge> &V, int n) : Graph{n} {
    for (auto e : V) {
        insertEdge(e);
    }
}

// -- MEMBER FUNCTIONS

// insert undirected edge e
// update weight if edge e is present
void Graph::insertEdge(const Edge &e) {
    assert(e.head >= 1 && e.head <= size);
    assert(e.tail >= 1 && e.tail <= size);

    auto edge_insertion = [&T = this->table, &n = this->n_edges](const Edge &e1) {
        if (auto it = std::find_if(begin(T[e1.head]), end(T[e1.head]),
                                   [e1](const Edge &ed) { return e1.links_same_nodes(ed); });
            it == end(T[e1.head])) {
            T[e1.head].push_back(e1);  // insert new edge e
            ++n;                       // increment the counter of edges
        } else {
            it->weight = e1.weight;  // update the weight
        }
    };

    edge_insertion(e);
    edge_insertion(e.reverse());
}

// remove undirected edge e
void Graph::removeEdge(const Edge &e) {
    assert(e.head >= 1 && e.head <= size);
    assert(e.tail >= 1 && e.tail <= size);

    auto edgeRemoval = [&T = this->table, &n = this->n_edges](const Edge &e1) {
        auto it = std::find_if(begin(T[e1.head]), end(T[e1.head]),
                               [e1](const Edge &ed) { return e1.links_same_nodes(ed); });

        assert(it != end(T[e1.head]));
        T[e1.head].erase(it);  // remove edge e1
        --n;                   // decrement the counter of edges
    };

    edgeRemoval(e);
    edgeRemoval(e.reverse());
}

// Prim's minimum spanning tree algorithm
void Graph::mstPrim() const {
    std::vector<int> dist(size_t(size) + 1);
    std::vector<int> path(size_t(size) + 1);
    std::vector<bool> done(size_t(size) + 1);

    // *** TODO ***
	int start = 1;
	for (int i = 0; i <= size; i++) {
		dist[i] = std::numeric_limits<int>::max();
		path[i] = 0;
		done[i] = false;
	}

	dist[start] = 0;
	done[start] = true;
	int totalWeight = 0;
	int v = start;

	while (true) {
		for (auto e : table[v]) {
			if (done[e.tail] == false && dist[e.tail] > e.weight) {
				path[e.tail] = v;
				dist[e.tail] = e.weight;
			}
		}

		int minV = 0;
		int length = std::numeric_limits<int>::max();
		for (int i = 1; i <= size; i++) {
			if (dist[i] < length && done[i] == false) {
				minV = i;
				length = dist[i];
			}
		}
		v = minV;
		if (v == 0)break;
		done[v] = true;
		std::cout << "(" << path[v] << ", " << v << ", " << dist[v] << ")\n";
		totalWeight += dist[v];
	}
	cout << "Total weight is: " << totalWeight << endl;
}

// Kruskal's minimum spanning tree algorithm
void Graph::mstKruskal() const {

    // *** TODO ***
																					
	int n = size; // n = |V|
	//Heap<Edge> H; // min-heap by edges cost
	DSets D(n); // n trees with one node each

	std::vector<Edge> edges;
	edges.reserve(n_edges);

	for (auto listOfEdges : table) {
		for (auto it = listOfEdges.begin(); it != listOfEdges.end(); ++it) {
			// H.insert(it);
			Edge myEdge(it->head, it->tail, it->weight);
			//H.insert(myEdge);
			edges.push_back(myEdge);
		}
	}

	Heap<Edge> H(edges);

	int counter = 0;
	int totalDist = 0;

	while (counter < n - 1) {
		Edge deleted = H.deleteMin();
		int v = deleted.head;
		int u = deleted.tail;

		if (D.find(v) != D.find(u)) {
			std::cout << deleted << "\n"; // Displaying
			totalDist += deleted.weight;

			D.join(D.find(v), D.find(u));
			counter++;
		}
	}

	std::cout << "Total weight = " << totalDist << "\n";							
}

// print graph
void Graph::printGraph() const {
    std::cout << "------------------------------------------------------------------\n";
    std::cout << "vertex  adjacency list                                            \n";
    std::cout << "------------------------------------------------------------------\n";

    for (int v = 1; v <= size; v++) {
        std::cout << std::setw(4) << v << " : ";
        for (auto it = table[v].begin(); it != table[v].end(); ++it) {
            std::cout << " (" << std::setw(2) << it->tail << ", " << std::setw(2) << it->weight
                      << ") ";
        }
        std::cout << "\n";
    }
    std::cout << "------------------------------------------------------------------\n";
}
