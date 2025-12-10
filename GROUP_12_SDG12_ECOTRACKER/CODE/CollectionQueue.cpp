#include "CollectionQueue.h"
#include <iostream>

using std::cout;
using std::endl;

CollectionQueue::CollectionQueue() : front(0), count(0) {}

bool CollectionQueue::isEmpty() const { return count == 0; }
bool CollectionQueue::isFull() const { return count == CAP; }

bool CollectionQueue::enqueue(const PickupRequest& req) {
    if (isFull()) return false;
    int pos = (front + count) % CAP;
    arr[pos] = req;
    ++count;
    return true;
}

bool CollectionQueue::dequeue() {
    if (isEmpty()) return false;
    front = (front + 1) % CAP;
    --count;
    return true;
}

void CollectionQueue::display() const {
    if (isEmpty()) {
        cout << "Pickup queue is empty.\n";
        return;
    }
    cout << "ReqID\tWasteID\tAddress\n";
    int idx = front;
    for (int i = 0; i < count; ++i) {
        cout << arr[idx].requestID << '\t' << arr[idx].wasteID << '\t' << arr[idx].address << '\n';
        idx = (idx + 1) % CAP;
    }
}
