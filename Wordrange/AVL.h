#ifndef AVL_h
#define AVL_h

#include<iostream>
#include <string>

using namespace std;

// node struct to hold data
class Node
{
	public:
      string key;
      int tree_size = 0;
	    Node *left, *right, *parent;

        Node() // default constructor
        {
            left = right = parent = NULL; // setting everything to NULL
        }

        Node(string val) // constructor that sets key to val
        {
            key = val;
            left = right = parent = NULL; // setting everything to NULL
        }
};

class AVL
{
private:
		Node *root; // Stores root of tree
	public:
        AVL(); // Default constructor sets root to null
        void insert(string); // insert string into list 
        void insert(Node*, Node*); // recursive version that inserts a node
        Node* find(string); // find string in tree, and return pointer to node with that string 
        Node* find(Node*, string); // recursive version that finds in a rooted subtree
        Node* minNode(Node*); // gets minimum node in rooted subtree
        Node* maxNode(Node*); // gets maximum node in rooted subtree
        Node* deleteKey(string); // remove a node with string (if it exists), and return pointer to deleted node. This does not delete all nodes with the value.
        Node* deleteNode(Node*); // try to delete node pointed by argument. This also returns the node, isolated from the tree.
        void deleteAVL(); // deletes every node to prevent memory leaks, and frees memory
        void deleteAVL(Node* start); // deletes every Node in subtree rooted at start to prevent memory leaks.
        Node* lca(string, string); // calls reccursive lca method
        Node* lca(Node*, string, string); // recursive method that finds the least common ancestor 
        int range(string, string); // calls recursive range method
        int range(Node*, string, string); // finds the amount of nodes with keys between the given range
};

#endif


