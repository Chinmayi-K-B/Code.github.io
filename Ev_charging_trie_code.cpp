#include <iostream>
#include <unordered_map>
using namespace std;

class EVChargingTrieNode {
public:
    unordered_map<char, EVChargingTrieNode*> children;
    bool isEndOfSlot;
    EVChargingTrieNode() : isEndOfSlot(false) {}
};

class EVChargingTrie {
    EVChargingTrieNode* root;
    
public:
    EVChargingTrie() {
        root = new EVChargingTrieNode();
    }
    
    void insert(string slot) {
        EVChargingTrieNode* node = root;
        for (char ch : slot) {
            if (node->children.find(ch) == node->children.end()) {
                node->children[ch] = new EVChargingTrieNode();
            }
            node = node->children[ch];
        }
        node->isEndOfSlot = true;
    }
    
    bool search(string slot) {
        EVChargingTrieNode* node = root;
        for (char ch : slot) {
            if (node->children.find(ch) == node->children.end()) {
                return false;
            }
            node = node->children[ch];
        }
        return node->isEndOfSlot;
    }
};

int main() {
    EVChargingTrie trie;
    trie.insert("City1_StationA_Slot3");
