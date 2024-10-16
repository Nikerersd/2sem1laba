#pragma once
#include <iostream>
using namespace std;

struct NodeT {
    int key;
    int height;
    NodeT* left;
    NodeT* right;

    NodeT(int k);
};

int heightTree(NodeT* n);
int getBalance(NodeT* n);
void updateHeight(NodeT* n);
NodeT* rotateRight(NodeT* y);
NodeT* rotateLeft(NodeT* x);
NodeT* insertTree(NodeT* node, int key);
NodeT* searchTree(NodeT* root, int key);
NodeT* minValueNode(NodeT* node);
NodeT* deleteNodeT(NodeT* root, int key);
void printTree(NodeT* root, int space = 0, int level = 0);
void freeTree(NodeT* root);
void writeTreeToFile(NodeT* root, const string& filename, int space = 0, int level = 0);
void writeAVLTreeToFile(NodeT* root, const string& filename);