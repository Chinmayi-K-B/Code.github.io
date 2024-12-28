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

int main() {
    ParkingTrie trie;
    trie.insert("City1_LotA_Slot3");
    trie.insert("City1_LotB_Slot1");
    
    cout << "Is Slot City1_LotA_Slot3 available? " << (trie.search("City1_LotA_Slot3") ? "Yes" : "No") << endl;
    cout << "Is Slot City1_LotA_Slot4 available? " << (trie.search("City1_LotA_Slot4") ? "Yes" : "No") << endl;
    
    return 0;
}
