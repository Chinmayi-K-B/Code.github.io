#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

// Parking Slot structure
struct ParkingSlot {
    string lot;    // Lot name
    string slotID; // Unique Slot ID
    string type;   // compact, regular, handicapped
    bool isOccupied;

    ParkingSlot(string l, string id, string t)
        : lot(l), slotID(id), type(t), isOccupied(false) {}
};

// Trie Node for managing parking slots
class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEndOfSlot;
    string parkingType;
    bool isOccupied;

    TrieNode() : isEndOfSlot(false), parkingType("regular"), isOccupied(false) {}
};

class ParkingTrie {
private:
    TrieNode* root;

public:
    ParkingTrie() { root = new TrieNode(); }

    // Insert a parking slot
    void insertSlot(const string& lot, const string& slotID, const string& type) {
        TrieNode* node = root;
        for (char ch : lot + slotID) {
            if (node->children.find(ch) == node->children.end()) {
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
        }
        node->isEndOfSlot = true;
        node->parkingType = type;
    }

    // Mark a slot as occupied
    void markOccupied(const string& lot, const string& slotID) {
        TrieNode* node = root;
        for (char ch : lot + slotID) {
            if (node->children.find(ch) == node->children.end()) {
                cout << "Error: Slot not found.\n";
                return;
            }
            node = node->children[ch];
        }
        if (node->isEndOfSlot) {
            node->isOccupied = true;
        }
    }

    // Check if a slot is available
    bool isSlotAvailable(const string& lot, const string& slotID) {
        TrieNode* node = root;
        for (char ch : lot + slotID) {
            if (node->children.find(ch) == node->children.end()) {
                return false;
            }
            node = node->children[ch];
        }
        return node->isEndOfSlot && !node->isOccupied;
    }

    // Display all available slots
    void displayAvailableSlots(const string& lotPrefix = "") {
        vector<string> availableSlots;
        collectAvailableSlots(root, lotPrefix, "", availableSlots);

        cout << "\n--- Available Parking Slots in Vayujiva ---\n";
        if (availableSlots.empty()) {
            cout << "No available parking slots.\n";
        } else {
            for (const string& slot : availableSlots) {
                cout << slot << "\n";
            }
        }
    }

    // Collect available slots using DFS
    void collectAvailableSlots(TrieNode* node, const string& lotPrefix, string currentSlot, vector<string>& availableSlots) {
        if (node->isEndOfSlot && !node->isOccupied) {
            availableSlots.push_back(lotPrefix + currentSlot);
        }

        for (const auto& pair : node->children) {
            collectAvailableSlots(pair.second, lotPrefix, currentSlot + pair.first, availableSlots);
        }
    }
};

// Parking Queue class
class ParkingQueue {
private:
    queue<string> vehicleQueue; // Queue for vehicles
    unordered_map<string, queue<ParkingSlot>> lotToSlotQueue; // Map from lot to slots available in that lot
    ParkingTrie trie; // Parking slot trie

public:
    // Add a vehicle to the queue
    void enqueueVehicle(const string& vehicle) {
        vehicleQueue.push(vehicle);
        cout << "Vehicle \"" << vehicle << "\" added to the queue in Vayujiva.\n";
    }

    // Add a parking slot
    void addSlot(const string& lot, const string& slotID, const string& type) {
        ParkingSlot newSlot(lot, slotID, type);
        lotToSlotQueue[lot].push(newSlot);
        trie.insertSlot(lot, slotID, type);
        cout << "Parking slot \"" << slotID << "\" in lot \"" << lot
             << "\" (type: " << type << ") added in Vayujiva.\n";
    }

    // Allocate the next available slot to the next vehicle in queue
    void allocateSlot() {
        if (vehicleQueue.empty()) {
            cout << "No vehicles in the queue in Vayujiva.\n";
            return;
        }

        string vehicle = vehicleQueue.front();
        vehicleQueue.pop(); // Remove the vehicle from the queue

        bool slotAllocated = false;

        // Iterate through all parking lots to find an available slot
        for (auto& lot : lotToSlotQueue) {
            while (!lot.second.empty()) {
                ParkingSlot slot = lot.second.front();
                lot.second.pop(); // Remove the slot from the lot queue

                // Check if the slot is available
                if (!slot.isOccupied) {
                    // Mark the slot as occupied
                    slot.isOccupied = true;
                    trie.markOccupied(slot.lot, slot.slotID);
                    cout << "Allocated Slot \"" << slot.slotID << "\" (" << slot.type
                         << ") in Lot \"" << slot.lot << "\" to Vehicle \"" << vehicle
                         << "\" in Vayujiva.\n";
                    slotAllocated = true;
                    break;
                }
            }

            if (slotAllocated) break; // Exit once a slot is allocated
        }

        if (!slotAllocated) {
            cout << "No available slots for vehicle \"" << vehicle << "\" in Vayujiva.\n";
        }
    }

    // Display all available slots
    void displayAvailableSlots() {
        trie.displayAvailableSlots();
    }

    // Display vehicles in the queue
    void displayVehicleQueue() const {
        cout << "\n--- Vehicles Waiting in the Queue in Vayujiva ---\n";
        if (vehicleQueue.empty()) {
            cout << "No vehicles are waiting in the queue.\n";
        } else {
            queue<string> tempQueue = vehicleQueue;
            while (!tempQueue.empty()) {
                cout << "\"" << tempQueue.front() << "\" ";
                tempQueue.pop();
            }
            cout << endl;
        }
    }
};

// Display menu
void displayMenu() {
    cout << "\n--- Smart Parking Management System for Vayujiva ---\n";
    cout << "1. Add Vehicle to Queue\n";
    cout << "2. Add Parking Slot\n";
    cout << "3. Allocate Slot to Vehicle\n";
    cout << "4. Display Vehicle Queue\n";
    cout << "5. Display Available Parking Slots\n";
    cout << "6. Exit\n";
    cout << "---------------------------------------\n";
    cout << "Enter your choice: ";
}

int main() {
    ParkingQueue parkingQueue;
    int choice;
    string vehicle, lot, slotID, type;

    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore(); // Clear input buffer

        switch (choice) {
            case 1:
                cout << "Enter vehicle name: ";
                cin >> vehicle;
                parkingQueue.enqueueVehicle(vehicle);
                break;

            case 2:
                cout << "Enter parking lot name: ";
                cin >> lot;
                cout << "Enter parking slot ID: ";
                cin >> slotID;
                cout << "Enter slot type (compact/regular/handicapped): ";
                cin >> type;
                parkingQueue.addSlot(lot, slotID, type);
                break;

            case 3:
                parkingQueue.allocateSlot();
                break;

            case 4:
                parkingQueue.displayVehicleQueue();
                break;

            case 5:
                parkingQueue.displayAvailableSlots();
                break;

            case 6:
                cout << "Exiting the system. Goodbye!\n";
                return 0;

            default:
                cout << "Invalid choice, please try again.\n";
        }
    }
}
