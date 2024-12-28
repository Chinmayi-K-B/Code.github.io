#include <iostream>
#include <queue>
using namespace std;

struct Vehicle {
    string licensePlate;
    int arrivalTime;
    
    bool operator>(const Vehicle& v) const {
        return arrivalTime > v.arrivalTime;
    }
};

class ParkingQueue {
    priority_queue<Vehicle, vector<Vehicle>, greater<Vehicle>> queue;
    
public:
    void addVehicle(string licensePlate, int arrivalTime) {
        queue.push({licensePlate, arrivalTime});
    }
    
    void allocateSlot() {
        if (!queue.empty()) {
            Vehicle v = queue.top();
            queue.pop();
            cout << "Allocating slot to vehicle: " << v.licensePlate << endl;
        } else {
            cout << "No vehicles in queue!" << endl;
        }
    }
};

int main() {
    ParkingQueue pq;
    pq.addVehicle("AB123CD", 2);
    pq.addVehicle("XY987ZT", 1);
    
    pq.allocateSlot(); // Should allocate to XY987ZT
    pq.allocateSlot(); // Should allocate to AB123CD
    
    return 0;
}
