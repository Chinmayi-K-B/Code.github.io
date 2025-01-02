#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

// Parking Slot structure to hold information about parking slots
struct ParkingSlot {
    string city;
    string lot;
    string slot;
    bool isAvailable;

    // Constructor with a fixed city "Vayujiva"
    ParkingSlot(string l, string s) : city("Vayujiva"), lot(l), slot(s), isAvailable(true) {}
};

// Queue class for real-time parking slot allocation
class ParkingQueue {
private:
    queue<string> vehicleQueue;  // To hold vehicles waiting for parking
    queue<ParkingSlot> parkingQueue;  // To hold available parking slots

public:
    // Add vehicle to the queue
    void enqueueVehicle(const string& vehicle) {
        vehicleQueue.push(vehicle);
        cout << "Vehicle \"" << vehicle << "\" added to the queue.\n";
    }

    // Add parking slot to the queue
    void enqueueSlot(const ParkingSlot& slot) {
        parkingQueue.push(slot);
        cout << "Parking slot at " << slot.city << " > " << slot.lot << " > " << slot.slot << " added to the available slots.\n";
    }

    // Allocate parking slot to the first vehicle in the queue
    void allocateSlotToVehicle() {
        if (vehicleQueue.empty()) {
            cout << "Error: No vehicles in the queue to allocate a parking slot.\n";
            return;
        }

        if (parkingQueue.empty()) {
            cout << "Error: No available parking slots.\n";
            return;
        }

        string vehicle = vehicleQueue.front();
        vehicleQueue.pop();

        ParkingSlot slot = parkingQueue.front();
        parkingQueue.pop();

        // Mark the slot as occupied
        slot.isAvailable = false;

        cout << "Vehicle \"" << vehicle << "\" has been allocated parking slot: "
             << slot.city << " > " << slot.lot << " > " << slot.slot << endl;
    }

    // Check if there are any vehicles in the queue
    bool isVehicleQueueEmpty() const {
        return vehicleQueue.empty();
    }

    // Check if there are any available parking slots
    bool isSlotQueueEmpty() const {
        return parkingQueue.empty();
    }

    // Display all vehicles in the queue
    void displayVehicleQueue() const {
        if (vehicleQueue.empty()) {
            cout << "No vehicles are waiting in the queue.\n";
            return;
        }
        cout << "Vehicles in the queue: ";
        queue<string> tempQueue = vehicleQueue;
        while (!tempQueue.empty()) {
            cout << "\"" << tempQueue.front() << "\" ";
            tempQueue.pop();
        }
        cout << endl;
    }

    // Display all available parking slots
    void displayParkingQueue() const {
        if (parkingQueue.empty()) {
            cout << "No available parking slots.\n";
            return;
        }
        cout << "Available Parking slots: ";
        queue<ParkingSlot> tempQueue = parkingQueue;
        while (!tempQueue.empty()) {
            ParkingSlot slot = tempQueue.front();
            cout << slot.city << " > " << slot.lot << " > " << slot.slot << " ";
            tempQueue.pop();
        }
        cout << endl;
    }
};

// Main function for testing Queue (Real-Time Allocation) with user-based interaction
int main() {
    ParkingQueue parkingQueue;

    int choice;
    string vehicle;
    string lot, slot;

    while (true) {
        // Display the menu with clear instructions
        cout << "\n--- Parking Management System ---\n";
        cout << "1. Add Vehicle to Queue\n";
        cout << "2. Add Parking Slot\n";
        cout << "3. Allocate Parking Slot to Vehicle\n";
        cout << "4. Display Vehicles in Queue\n";
        cout << "5. Display Available Parking Slots\n";
        cout << "6. Exit\n";
        cout << "---------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                // Add vehicle to the queue
                cout << "Enter vehicle name (e.g., Car1, Bike2): ";
                cin >> vehicle;
                parkingQueue.enqueueVehicle(vehicle);
                break;
            }
            case 2: {
                // Add parking slot to the queue (City is fixed to "Vayujiva")
                cout << "Enter lot and slot (space-separated): ";
                cin >> lot >> slot;
                parkingQueue.enqueueSlot(ParkingSlot(lot, slot));
                break;
            }
            case 3: {
                // Allocate parking slot to the first vehicle in the queue
                parkingQueue.allocateSlotToVehicle();
                break;
            }
            case 4: {
                // Display vehicles in the queue
                parkingQueue.displayVehicleQueue();
                break;
            }
            case 5: {
                // Display available parking slots
                parkingQueue.displayParkingQueue();
                break;
            }
            case 6: {
                // Exit the system
                cout << "Exiting the system. Goodbye!\n";
                return 0;
            }
            default:
                cout << "Invalid choice, please try again.\n";
        }
    }
}
