#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>
#include <vector>

using namespace std;

// TrieNode definition with arrays
class TrieNode {
public:
    TrieNode* children[26];  // 26 letters for a-z
    bool isEndOfWord;
    string location;

    TrieNode() : isEndOfWord(false), location("") {
        fill(begin(children), end(children), nullptr);
    }
};

// Trie class to manage EV charging stations by name
class EVChargingStationTrie {
private:
    TrieNode* root;

public:
    EVChargingStationTrie() {
        root = new TrieNode();
    }

    // Insert a charging station name into the Trie
    void insert(const string& stationName, const string& stationLocation) {
        TrieNode* node = root;
        for (char c : stationName) {
            int index = c - 'a';
            if (node->children[index] == nullptr) {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }
        node->isEndOfWord = true;
        node->location = stationLocation;
        cout << "Charging station '" << stationName << "' added at location: " << stationLocation << endl;
    }

    // Search for a charging station by name and get its location
    bool searchAndGetLocation(const string& stationName, string& location) {
        TrieNode* node = root;
        for (char c : stationName) {
            int index = c - 'a';
            if (node->children[index] == nullptr) {
                return false;
            }
            node = node->children[index];
        }
        if (node->isEndOfWord) {
            location = node->location;  // Retrieve the location
            return true;
        }
        return false;
    }

    // Update the location of a charging station in the Trie
    bool updateLocation(const string& stationName, const string& newLocation) {
        TrieNode* node = root;
        for (char c : stationName) {
            int index = c - 'a';
            if (node->children[index] == nullptr) {
                cout << "Station '" << stationName << "' not found!" << endl;
                return false;
            }
            node = node->children[index];
        }
        if (node->isEndOfWord) {
            node->location = newLocation;  // Update the location
            cout << "Charging station '" << stationName << "' updated to location: " << newLocation << endl;
            return true;
        } else {
            cout << "Station '" << stationName << "' not found!" << endl;
            return false;
        }
    }

    // Delete a charging station from the Trie
    bool deleteStationHelper(TrieNode* node, const string& stationName, int index) {
        if (node == nullptr) {
            return false;
        }

        if (index == stationName.size()) {
            if (!node->isEndOfWord) {
                return false; // Station name doesn't exist
            }

            node->isEndOfWord = false;
            return true;
        }

        int currentCharIndex = stationName[index] - 'a';
        TrieNode* nextNode = node->children[currentCharIndex];
        if (nextNode == nullptr) {
            return false; // If the character doesn't exist, return false
        }

        bool shouldDeleteCurrentNode = deleteStationHelper(nextNode, stationName, index + 1);

        if (shouldDeleteCurrentNode) {
            node->children[currentCharIndex] = nullptr;
            return true;
        }

        return false;
    }

    bool deleteStation(const string& stationName) {
        if (stationName.empty()) {
            cout << "Station name cannot be empty!" << endl;
            return false;
        }

        bool result = deleteStationHelper(root, stationName, 0);
        if (result) {
            cout << "Station '" << stationName << "' deleted successfully." << endl;
        } else {
            cout << "Station '" << stationName << "' not found." << endl;
        }
        return result;
    }

    // Display all charging stations and their locations
    void displayStations(TrieNode* node, string& prefix) {
        if (node->isEndOfWord) {
            cout << "Station: " << prefix << " | Location: " << node->location << endl;
        }
        for (int i = 0; i < 26; ++i) {
            if (node->children[i] != nullptr) {
                prefix.push_back('a' + i);
                displayStations(node->children[i], prefix);
                prefix.pop_back();
            }
        }
    }

    void displayAllStations() {
        string prefix = "";
        displayStations(root, prefix);
    }

    // Search for all stations starting with a given prefix
    void searchByPrefix(const string& prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            int index = c - 'a';
            if (node->children[index] == nullptr) {
                cout << "No stations found with the prefix '" << prefix << "'\n";
                return;
            }
            node = node->children[index];
        }
        string stationPrefix = prefix;
        displayStations(node, stationPrefix);
    }
};

// BSTNode for charging station data
struct BSTNode {
    string stationName;
    string location;
    BSTNode* left;
    BSTNode* right;

    BSTNode(string name, string loc) : stationName(name), location(loc), left(nullptr), right(nullptr) {}
};

// BST class to manage charging stations
class EVChargingStationBST {
private:
    BSTNode* root;

public:
    EVChargingStationBST() : root(nullptr) {}

    // Insert a charging station into the BST
    void insert(const string& stationName, const string& location) {
        root = insertHelper(root, stationName, location);
    }

    BSTNode* insertHelper(BSTNode* node, const string& stationName, const string& location) {
        if (node == nullptr) {
            return new BSTNode(stationName, location);
        }
        if (stationName < node->stationName) {
            node->left = insertHelper(node->left, stationName, location);
        } else if (stationName > node->stationName) {
            node->right = insertHelper(node->right, stationName, location);
        }
        return node;
    }

    // Search for a charging station by name
    BSTNode* search(const string& stationName) {
        return searchHelper(root, stationName);
    }

    BSTNode* searchHelper(BSTNode* node, const string& stationName) {
        if (node == nullptr || node->stationName == stationName) {
            return node;
        }
        if (stationName < node->stationName) {
            return searchHelper(node->left, stationName);
        } else {
            return searchHelper(node->right, stationName);
        }
    }

    // Delete a charging station from the BST
    BSTNode* deleteStationHelper(BSTNode* root, const string& stationName) {
        if (root == nullptr) return root;

        if (stationName < root->stationName) {
            root->left = deleteStationHelper(root->left, stationName);
        } else if (stationName > root->stationName) {
            root->right = deleteStationHelper(root->right, stationName);
        } else {
            if (root->left == nullptr) {
                BSTNode* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                BSTNode* temp = root->left;
                delete root;
                return temp;
            }

            BSTNode* temp = minValueNode(root->right);
            root->stationName = temp->stationName;
            root->location = temp->location;
            root->right = deleteStationHelper(root->right, temp->stationName);
        }
        return root;
    }

    BSTNode* minValueNode(BSTNode* node) {
        BSTNode* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    void deleteStation(const string& stationName) {
        root = deleteStationHelper(root, stationName);
        cout << "Station '" << stationName << "' deleted successfully." << endl;
    }

    // Display all stations in sorted order
    void displayStations(BSTNode* node) {
        if (node != nullptr) {
            displayStations(node->left);
            cout << "Station: " << node->stationName << " | Location: " << node->location << endl;
            displayStations(node->right);
        }
    }

    void displayAllStations() {
        displayStations(root);
    }
};

// Menu display function
void displayMenu() {
    cout << "\nMenu:\n";
    cout << "1. Add a charging station\n";
    cout << "2. Search for a charging station and get its location\n";
    cout << "3. Update location of a charging station\n";
    cout << "4. Delete a charging station\n";
    cout << "5. Display all charging stations\n";
    cout << "6. Search stations by prefix\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
}

// Main function to test all functionalities
int main() {
    EVChargingStationTrie trie;
    EVChargingStationBST bst;
    string stationName, location, newLocation, prefix;
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter the charging station name to add: ";
            cin.ignore();
            getline(cin, stationName);
            cout << "Enter the location of the station: ";
            getline(cin, location);
            trie.insert(stationName, location);
            bst.insert(stationName, location);
            break;

        case 2:
            cout << "Enter the charging station name to search: ";
            cin.ignore();
            getline(cin, stationName);
            if (trie.searchAndGetLocation(stationName, location)) {
                cout << "Station found! Location: " << location << endl;
            } else {
                cout << "Station not found.\n";
            }
            break;

        case 3:
            cout << "Enter the charging station name to update: ";
            cin.ignore();
            getline(cin, stationName);
            cout << "Enter the new location: ";
            getline(cin, newLocation);
            if (!trie.updateLocation(stationName, newLocation)) {
                cout << "Station not found.\n";
            }
            break;

        case 4:
            cout << "Enter the charging station name to delete: ";
            cin.ignore();
            getline(cin, stationName);
            trie.deleteStation(stationName);
            break;

        case 5:
            cout << "Displaying all charging stations:\n";
            trie.displayAllStations();
            break;

        case 6:
            cout << "Enter the prefix to search stations: ";
            cin.ignore();
            getline(cin, prefix);
            trie.searchByPrefix(prefix);
            break;

        case 7:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
