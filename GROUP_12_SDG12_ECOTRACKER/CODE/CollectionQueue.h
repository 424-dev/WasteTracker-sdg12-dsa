#pragma once
#include <string>

using std::string;

struct PickupRequest {
    int requestID;
    int wasteID;
    string address;
    PickupRequest() : requestID(0), wasteID(0), address("") {}
    PickupRequest(int r, int w, const string& a) : requestID(r), wasteID(w), address(a) {}
};

class CollectionQueue {
private:
    static const int CAP = 100;
    PickupRequest arr[CAP];
    int front;
    int count;
public:
    CollectionQueue();
    bool isEmpty() const;
    bool isFull() const;
    bool enqueue(const PickupRequest& req);
    bool dequeue();
    void display() const;
};
