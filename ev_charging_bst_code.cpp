#include <iostream>
#include <queue>
#include <string>
using namespace std;

// Vehicle class to store vehicle details
class ElectricVehicle {
public:
    string make;
    string model;
    ElectricVehicle(string m, string mod) {
        make = m;
        model = mod;
    }
};

// Node structure for each charging slot in the BST
class SlotNode {
public:
    string slotID;
    bool isOccupied;
    ElectricVehicle* currentEV;
    SlotNode* left;
    SlotNode* right;

    SlotNode(string id) {
        slotID = id;
        isOccupied = false;
        currentEV = nullptr;
        left = right = nullptr;
    }
};

// BST for managing charging slots
class EVSlotBST {
private:
    SlotNode* root;

    // Helper function to insert slots into BST
    SlotNode* insert(SlotNode* node, string id) {
        if (node == nullptr) {
            return new SlotNode(id);
        }

        if (id < node->slotID) {
            node->left = insert(node->left, id);
        } else if (id > node->slotID) {
            node->right = insert(node->right, id);
        }

        return node;
    }

    // Helper function to search for a slot by ID
    SlotNode* search(SlotNode* node, string id) {
        if (node == nullptr || node->slotID == id) {
            return node;
        }

        if (id < node->slotID) {
            return search(node->left, id);
        } else {
            return search(node->right, id);
        }
    }

public:
    EVSlotBST() {
        root = nullptr;
    }

    void insertSlot(string id) {
        root = insert(root, id);
    }

    SlotNode* searchSlot(string id) {
        return search(root, id);
    }

    // Function to allocate a slot if available
    bool allocateSlot(string slotID, ElectricVehicle* ev) {
        SlotNode* slot = searchSlot(slotID);
        if (slot != nullptr) {
            if (!slot->isOccupied) {
                slot->isOccupied = true;
                slot->currentEV = ev;
                cout << "Slot " << slot->slotID << " allocated to " << ev->make << " " << ev->model << ".\n";
                return true;
            } else {
                cout << "Slot " << slot->slotID << " is already occupied.\n";
                return false;
            }
        } else {
            cout << "Slot " << slotID << " not found.\n";
            return false;
        }
    }

    // Function to deallocate a slot when done
    void deallocateSlot(string slotID) {
        SlotNode* slot = searchSlot(slotID);
        if (slot != nullptr && slot->isOccupied) {
            slot->isOccupied = false;
            slot->currentEV = nullptr;
            cout << "Slot " << slotID << " is now available.\n";
        } else {
            cout << "Slot " << slotID << " is already available or not found.\n";
        }
    }
};

int main() {
    // Create the BST for charging slots and insert some slots
    EVSlotBST slotNetwork;
    slotNetwork.insertSlot("A1");
    slotNetwork.insertSlot("B1");
    slotNetwork.insertSlot("C1");

    // Create a queue for vehicles
    queue<ElectricVehicle*> vehicleQueue;

    // Vehicle arrivals (vehicles queuing up)
    vehicleQueue.push(new ElectricVehicle("Tesla", "Model 3"));
    vehicleQueue.push(new ElectricVehicle("Nissan", "Leaf"));
    vehicleQueue.push(new ElectricVehicle("BMW", "i3"));

    // Allocate charging slots as they become available
    cout << "\nAllocating slots to vehicles:\n";
    // Allocate first available slot to first vehicle in queue
    slotNetwork.allocateSlot("A1", vehicleQueue.front());
    vehicleQueue.pop();

    // Allocate second available slot to second vehicle in queue
    slotNetwork.allocateSlot("B1", vehicleQueue.front());
    vehicleQueue.pop();

    // Display remaining vehicles in the queue
    cout << "\nRemaining vehicles in queue:\n";
    while (!vehicleQueue.empty()) {
        ElectricVehicle* ev = vehicleQueue.front();
        cout << ev->make << " " << ev->model << " is waiting for a slot.\n";
        vehicleQueue.pop();
    }

    // Deallocate slot A1 when Tesla finishes charging
    slotNetwork.deallocateSlot("A1");

    // Allocate next vehicle in queue to available slot A1
    vehicleQueue.push(new ElectricVehicle("Ford", "Mustang"));
    slotNetwork.allocateSlot("A1", vehicleQueue.front());
    vehicleQueue.pop();

    return 0;
}
