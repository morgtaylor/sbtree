//
//  avlTree.cpp
//  sbtree
//
//  Created by Morgan Dickerson on 3/5/24.
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;
// node struct for node in AVL tree
struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};

// create new node
Node* newNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1; // initial height 1
    return node;
}

// get height
int height(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

// get balance factor
int balanceFactor(Node* node) {
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}

// update height
void updateHeight(Node* node) {
    node->height = 1 + max(height(node->left), height(node->right));
}

// right rotation
Node* rightRotate(Node* parent) {
    Node* pivot = parent->left;
    Node* subtree = pivot->right;

    // roation
    pivot->right = parent;
    parent->left = subtree;

    // call update height fucntion
    updateHeight(parent);
    updateHeight(pivot);

    return pivot; // new root
}

// left rotation
Node* leftRotate(Node* parent) {
    Node* pivot = parent->right;
    Node* subtree = pivot->left;

    // rotation
    pivot->left = parent;
    parent->right = subtree;

    // call update height function
    updateHeight(parent);
    updateHeight(pivot);

    return pivot; // new root
}

// insert a new key into AVL tree
Node* insert(Node* root, int key) {
    if (root == nullptr)
        return newNode(key);
    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else // duplicate keys not allowed
        return root;

    // update height of current node
    updateHeight(root);

    // get balance factor
    int balance = balanceFactor(root);

    // perform rotations if needed
    if (balance > 1 && key < root->left->key) // left left case
        return rightRotate(root);
    if (balance < -1 && key > root->right->key) // right right case
        return leftRotate(root);
    if (balance > 1 && key > root->left->key) { // left right case
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && key < root->right->key) { // right left case
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root; // return unchanged root pointer
}

int main() {
    Node* root = nullptr;

    int n = 100000000;//num elements to insert
    int minVal = 1;
    int maxVal = 10000000;
    
    // open CSV file for writing
        ofstream outputFile("insertion_times.csv");
        outputFile << "n,time" << endl;
    
    //insert keys into AVL tree
    for (int i = 0; i < n; ++i) {
        int num = rand() % (maxVal - minVal + 1) + minVal; //gen random int
        //measure time of insertion
        auto start = high_resolution_clock::now();
                root = insert(root, num);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<nanoseconds>(stop - start);
        //print to csv
        if (i % 100000 == 0 && i != 0) {
                    cout << "Index: " << i << ", Time: " << duration.count() << " nanoseconds" << endl;
                    outputFile << i << "," << duration.count() << endl;
                }
            }
    //close CSV
    outputFile.close();

    return 0;
}
