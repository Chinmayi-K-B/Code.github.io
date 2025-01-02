#include <iostream>
#include <unordered_map>
#include <cctype>
#include <vector>
#include <queue>
using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEndOfSlot;
    string parkingType; // Type of parking (compact, regular, handicapped)
    bool isOccupied;    // Whether the slot is occupied
    TrieNode() : isEndOfSlot(false), isOccupied(false), parkingType("regular") {}
};

class ParkingTrie {
    TrieNode* root;

public:
    ParkingTrie() {
        root = new TrieNode();
    }

    // Insert slot into the trie
    void insert(const string& location, const string& slot, const string& type) {
        TrieNode* node = root;
        for (char ch : location + slot) {
            if (node->children.find(ch) == node->children.end()) {
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
        }
        node->isEndOfSlot = true;
        node->parkingType = type;
    }

    // Search for slot in the trie
    bool search(const string& location, const string& slot) {
        TrieNode* node = root;
        for (char ch : location + slot) {
            if (node->children.find(ch) == node->children.end()) {
                return false;
            }
            node = node->children[ch];
        }
        return node->isEndOfSlot;
    }

    // Check if a slot is available
    bool isSlotAvailable(const string& location, const string& slot) {
        TrieNode* node = root;
        for (char ch : location + slot) {
            if (node->children.find(ch) == node->children.end()) {
                return false;
            }
            node = node->children[ch];
        }
        return node->isEndOfSlot && !node->isOccupied;
    }

    // Mark a slot as occupied
    void occupySlot(const string& location, const string& slot) {
        TrieNode* node = root;
        for (char ch : location + slot) {
            if (node->children.find(ch) == node->children.end()) {
                cout << "Error: Slot not found.\n";
                return;
            }
            node = node->children[ch];
        }
        if (node->isEndOfSlot) {
            node->isOccupied = true;
            cout << "Parking slot " << location << " " << slot << " is now occupied.\n";
        }
    }

    // Mark a slot as available
    void freeSlot(const string& location, const string& slot) {
        TrieNode* node = root;
        for (char ch : location + slot) {
            if (node->children.find(ch) == node->children.end()) {
                cout << "Error: Slot not found.\n";
                return;
            }
            node = node->children[ch];
        }
        if (node->isEndOfSlot) {
            node->isOccupied = false;
            cout << "Parking slot " << location << " " << slot << " is now available.\n";
        }
    }

    // Display all available slots
    void displayAllSlots() {
        vector<string> slots;
        collectAllSlots(root, "", slots);

        if (slots.empty()) {
            cout << "No available parking slots.\n";
        } else {
            cout << "Available Parking Slots in Vayujiva:\n";
            for (const string& slot : slots) {
                cout << slot << "\n";
            }
        }
    }

    // Function to perform DFS and collect all available slots
    void collectAllSlots(TrieNode* node, string currentSlot, vector<string>& slots) {
        if (node->isEndOfSlot && !node->isOccupied) {
            slots.push_back(currentSlot);
        }

        for (const auto& pair : node->children) {
            collectAllSlots(pair.second, currentSlot + pair.first, slots);
        }
    }

    // Validate the slot ID
    bool validateSlotID(const string& slot) {
        if (slot.empty()) {
            cout << "Error: Slot ID cannot be empty.\n";
            return false;
        }
        for (char ch : slot) {
            if (!isalnum(ch) && ch != '_') {
                cout << "Error: Slot ID can only contain alphanumeric characters and underscores.\n";
                return false;
            }
        }
        return true;
    }
};

void displayMenu() {
    cout << "\n--- Smart Parking System ---\n";
    cout << "1. Insert Parking Slot\n";
    cout << "2. Search Parking Slot\n";
    cout << "3. Occupy Parking Slot\n";
    cout << "4. Free Parking Slot\n";
    cout << "5. Display All Available Parking Slots\n";
    cout << "6. Exit\n";
    cout << "----------------------------\n";
    cout << "Enter your choice: ";
}

int main() {
    ParkingTrie trie;
    int choice;
    string location, slot, type;

    do {
        displayMenu();
        cin >> choice;
        cin.ignore();  // Clear the input buffer

        switch(choice) {
            case 1:
                cout << "Enter parking location (e.g., Vayujiva > Parking Lot A): ";
                getline(cin, location);
                cout << "Enter parking slot ID: ";
                getline(cin, slot);
                cout << "Enter parking type (compact, regular, handicapped): ";
                getline(cin, type);
                if (trie.validateSlotID(slot)) {
                    trie.insert(location, slot, type);
                    cout << "Parking slot \"" << location << " " << slot << "\" inserted successfully.\n";
                }
                break;
            case 2:
                cout << "Enter parking location (e.g., Vayujiva > Parking Lot A): ";
                getline(cin, location);
                cout << "Enter parking slot ID: ";
                getline(cin, slot);
                if (trie.search(location, slot)) {
                    cout << "Slot \"" << location << " " << slot << "\" is available.\n";
                } else {
                    cout << "Slot \"" << location << " " << slot << "\" is not available.\n";
                }
                break;
            case 3:
                cout << "Enter parking location (e.g., Vayujiva > Parking Lot A): ";
                getline(cin, location);
                cout << "Enter parking slot ID to occupy: ";
                getline(cin, slot);
                trie.occupySlot(location, slot);
                break;
            case 4:
                cout << "Enter parking location (e.g., Vayujiva > Parking Lot A): ";
                getline(cin, location);
                cout << "Enter parking slot ID to free: ";
                getline(cin, slot);
                trie.freeSlot(location, slot);
                break;
            case 5:
                trie.displayAllSlots();
                break;
            case 6:
                cout << "Exiting program... Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 6);  // Repeat until the user chooses to exit

    return 0;
}
