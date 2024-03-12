//
//  sbtree.cpp
//  sbtree
//
//  Created by Morgan Dickerson on 3/4/24.
//

#include <iostream>
#include <cstdlib>

using namespace std;

enum Color { RED, BLACK };

struct Node {
    int key;
    Color color;
    Node* left;
    Node* right;
    Node* parent;
    
    Node(int k) : key(k), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node* root;
    
    void leftRotate(Node* pivot) {
        Node* newParent = pivot->right; //newParent is set equal to first right child
        pivot->right = newParent->left; //newParent->left becomes pivot->right
        if (newParent->left != nullptr) //checks to see if newParent has left child
            newParent->left->parent = pivot; //updates newParent left child's parent to be pivot
        newParent->parent = pivot->parent; //moves newParent into pivot->parent spot
        if (pivot->parent == nullptr)
            root = newParent               //if no parent to pivot, newParent becomes root
        else if (pivot == pivot->parent->left)
            pivot->parent->left = newParent;  //if pivot is L child of it's parent, the L child pointer of pivot's parent point's to newParent
        else
            pivot->parent->right = newParent; //if pivot is R child of it's parent, the R child pointer of pivot's parent point's to newParent
        
        newParent->left = pivot;      //newParent point's left to pivot
        pivot->parent = newParent;    //pivot points to newParent as parent
            
    }
    
    void rightRotate(Node* pivot) {
        Node* newParent = pivot->left;
        pivot->left = newParent->right;
    }
}

