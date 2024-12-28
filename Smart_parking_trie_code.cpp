#include <iostream>
#include <unordered_map>
using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEndOfSlot;
    TrieNode() : isEndOfSlot(false) {}
};

class ParkingTrie {
    TrieNode* root;
    
public:
    ParkingTrie() {
        root = new TrieNode();
    }
    
    void insert(string slot) {
        TrieNode* node = root;
        for (char ch : slot) {
            if (node->children.find(ch) == node->children.end()) {
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
        }
        node->isEndOfSlot = true;
    }
    
    bool search(string slot) {
        TrieNode* node = root;
        for (char ch : slot) {
            if (node->children.find(ch) == node->children.end()) {
                return false;
            }
            node = node->children[ch];
        }
        return node->isEndOfSlot;
    }
};
