#include "AVL.h"
#include <cstdlib>
#include <iostream>
#include <vector> 
#include <algorithm>
#include <string>
#include <stack>
#include <queue>

using namespace std;

// Default constructor sets head and tail to null
AVL :: AVL()
{
	root = NULL;
}

// Insert(string val): Inserts the string val into tree, at the head of the list.
void AVL :: insert(string val)
{
    Node *to_insert = new Node(val); // create a new Node with the value val
    if (root == NULL) // tree is currently empty
        root = to_insert; // make new node the root
    else
      if (find(root, val) == NULL){
        insert(root,to_insert); // make call to recursive insert, starting from root
      } else {
        return;
      }
}

// insert(Node* start, Node* to_insert): Inserts the Node to_insert into tree rooted at start. We will always call with start being non-null. Note that there may be multiple copies of val in the list. 
// Input: string to insert into the subtree
// Output: Void, just inserts new Node
void AVL :: insert(Node* start, Node* to_insert)
{
    if (start == NULL) // in general, this should not happen. We never call insert from a null tree
        return;
    if (to_insert->key <= start->key) // inserted node has smaller (or equal) key, so go left
    {
        if(start->left == NULL)
        {
            start->left = to_insert; // make this node the left child
            to_insert->parent = start; // set the parent pointer
            return;
        }
        else // need to make recursive call
        {
            insert(start->left, to_insert);
            return;
        }
    }
    else // inserted node has larger key, so go right
    {
        if(start->right == NULL)
        {
            start->right = to_insert; // make this node the right child
            to_insert->parent = start; // set the parent pointer
            return;
        }
        else // need to make recursive call
        {
            insert(start->right, to_insert);
            return;
        }
    }
}

// find(int val): Finds a Node with key "val"
// Input: int to be found
// Output: a pointer to a Node containing val, if it exists. Otherwise, it returns NULL
// Technically, it finds the first Node with val, at it traverses down the tree
Node* AVL :: find(string val)
{
    return find(root, val); // call the recursive function starting at root
}

// find(Node* start, int val): Recursively tries to find a Node with key "val", in subtree rooted at val
// Input: int to be found
// Output: a pointer to a Node containing val, if it exists. Otherwise, it returns NULL
// Technically, it finds the first Node with val, at it traverses down the tree
Node* AVL :: find(Node* start, string val)
{
    if (start == NULL || start->key == val) // tree is empty or we found val
        return start;
    if(val < start->key) // val is smaller, so go left
        return find(start->left, val);
    else // val is larger, so go right
        return find(start->right, val);
}

// minNode(Node* start): gets the minimum Node in subtree rooted at start
// Input: Pointer to subtree root
// Output: pointer to the minimum node in the subtree
Node* AVL :: minNode(Node* start)
{
    if(start == NULL) // typically, this should not happen. But let's return the safe thing
        return NULL;
    if(start->left == NULL) // Base case: we have found the minimum
        return start;
    else
        return minNode(start->left); // recursive call in left subtree
}

// maxNode(Node* start): gets the maximum Node in subtree rooted at start
// Input: Pointer to subtree root
// Output: pointer to the maximum node in the subtree
Node* AVL :: maxNode(Node* start)
{
    if(start == NULL) // typically, this should not happen. But let's return the safe thing
        return NULL;
    if(start->right == NULL) // Base case: we have found the maximum
        return start;
    else
        return minNode(start->right); // recursive call in left subtree
}

// deleteNode(int val): Delete a Node with key val, if it exists. Otherwise, do nothing.
// Input: int to be removed
// Output: pointer to Node that was deleted. If no Node is deleted, return NULL. If there are multiple Nodes with val, only the first Node in the list is deleted.
Node* AVL :: deleteKey(string val)
{
    return deleteNode(find(val)); // get a node with the value and delete that node
}

// deleteNode(Node* to_delete): Delete the input node, and return pointer to the deleted node. The node will be isolated from the tree, to prevent memory leaks
// Input: Node to be removed
// Output: pointer to Node that was deleted. If no Node is deleted, return NULL. 
Node* AVL :: deleteNode(Node* to_delete)
{
    if(to_delete == NULL) // val not present in tree, so return NULL
        return NULL;

    bool isRoot = (to_delete == root) ? true : false; // determine if node to delete is root
    bool isLeftChild = false;
    if (!isRoot) // if this is not the root
        isLeftChild = (to_delete->parent->left == to_delete) ? true : false; // determine if node is left child of parent. Note that line throws error iff to_delete is root

    bool isDeleted = false; // convenient flag for writing code
    
    // if to_delete's left child is NULL, then we can splice this node off. We set the appropriate
    // pointer of the parent to the right child of to_delete
    if(to_delete->left == NULL)
    {
//         cout << "left is null, isLeftChild is "+to_string(isLeftChild) << endl;
//         cout << "parent is "+to_string(to_delete->parent->key) << endl;
        if(isRoot) // if deleting root, then we reset root
        {
            root = to_delete->right;
            if(root != NULL)
                root->parent = NULL; // set parent to be NULL
        }
        else
        {
            if(isLeftChild) // node is left child of parent
                to_delete->parent->left = to_delete->right; // setting left child of parent to be right child of node
            else // node is right child of parent
                to_delete->parent->right = to_delete->right; // setting right child of parent to be right child of node
            if(to_delete->right != NULL) // to_delete is not a leaf
                to_delete->right->parent = to_delete->parent; // update parent of the child of the deleted node, to be parent of deleted node
        }
        isDeleted = true; // delete is done
    }
    // suppose node is not deleted yet, and it's right child is NULL. We splice off as before, by setting parent's child pointer to to_delete->left
    if(!isDeleted && to_delete->right == NULL) 
    {
        if(isRoot) // if deleting root, then we reset root
        {
            root = to_delete->left;
            if(root != NULL)
                root->parent = NULL; // set parent to be NULL
        }
        else
        {
            if(isLeftChild) // node is left child of parent
                to_delete->parent->left = to_delete->left; // setting left child of parent to be left child of node
            else // node is right child of parent
                to_delete->parent->right = to_delete->left; // setting right child of parent to be left child of node
            if(to_delete->left != NULL) // to delete is not a leaf
                to_delete->left->parent = to_delete->parent; // update parent of the child of deleted node, to be parent of deleted node
        }
        isDeleted = true; // delete is done
    }
    if(isDeleted) // so node has been deleted
    {
        to_delete->left = to_delete->right = NULL;
        return to_delete;
    }
    
    // phew. The splicing case is done, so now for the recursive case. Both children of to_delete are not null, so we replace the data in to_delete by the successor. Then we delete the successor node
    // first, get the minimum node of right subtree
    Node* succ = minNode(to_delete->right);
    to_delete->key = succ->key;
//     cout << "Replacing with "+to_string(succ->key) << endl;
    return deleteNode(succ); // make recursive call on succ. Note that succ has one null child, so this recursive call will terminate without any other recursive calls
}


// Deletes every Node to prevent memory leaks.
// Input: None
// Output: Void, just deletes every Node of the list
void AVL :: deleteAVL()
{
    deleteAVL(root);
}

// Deletes every Node in subtree rooted at startto prevent memory leaks.
// Input: Node* start
// Output: Void, just deletes every Node of the list
void AVL :: deleteAVL(Node* start)
{
    if(start == NULL) // tree is already empty
        return; 
    deleteAVL(start->left); // delete left subtree
    deleteAVL(start->right); // delete right subtree
    delete(start); // delete node itself
}

Node* AVL :: lca(string val1, string val2){
    Node* temp = root;
    if (find(root, val1)!= NULL && find(root, val2) != NULL){ // if min and max found in the tree
        temp = lca(root, val1, val2); // set temp equal to the least common ancestor
    } 
    return temp;
}

Node* AVL :: lca(Node* parent, string val1, string val2){
       if (find(parent->left, val1) != NULL && find(parent->left, val2) != NULL){
           return lca(parent->left, val1, val2);
       }
       else if ((find(parent->right, val1) != NULL && find(parent->right, val2) != NULL)){
           return lca(parent->right, val1, val2);
       }
       return parent; // return the least common ancestor 
}

int AVL :: range(string min, string max){
//   int counter = 0;
  Node* start = lca(min, max); // use lca to lower run time if min and max found within the tree
  return range(start, min, max); // return the recursive method
}

int AVL :: range(Node* parent, string min, string max){
    if (!parent) // Base Case 
      return 0;
  
//     if (parent->key <= max && parent->key >= min){
//       counter++;
//       return range(parent->left, min, max, counter);
//     }
//     else if (parent->key < min) {
//       return range(parent->right, min, max, counter);
//     } else {
//       return range(parent->left, min, max, counter);
//     }
//     return counter;
// }
  
  
    if (parent -> key <= max && parent->key >= min){ // if the node contains a key that is between the min and max
       return 1 + range(parent->left, min, max) + range(parent->right, min, max); // add 1 and traverse down the entire tree by first going left and then right
    } else if (parent->key < min) { // by defininion of a BST if the key is smaller than the min, then traverse to the right side
       return range(parent->right, min, max);
    } else if (parent->key > max){ // by definition of a BST if the key is greater than the max, then traverse to the left side
       return range(parent->left, min, max);
    }
  return 0;
}

