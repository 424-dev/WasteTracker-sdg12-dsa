#include "WasteList.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>


using std::cout;
using std::cin;
using std::getline;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::stringstream;

WasteList::WasteList() : head(nullptr) {}

WasteList::~WasteList() {
    clear();
}

void WasteList::clear() {
    Node* cur = head;
    while (cur) {
        Node* tmp = cur;
        cur = cur->next;
        delete tmp;
    }
    head = nullptr;
}

void WasteList::insert(const WasteItem& item) {
    Node* n = new Node(item);
    n->next = head;
    head = n;
}

void WasteList::displayAll() const {
    Node* cur = head;
    if (!cur) {
        cout << "No waste items.\n";
        return;
    }

    cout << std::left
         << std::setw(8) << "ID"
         << std::setw(12) << "Type"
         << std::setw(10) << "Weight"
         << std::setw(15) << "Date"
         << std::setw(10) << "Priority"
         << "\n";

    while (cur) {
        cout << std::left
             << std::setw(8)  << cur->data.id
             << std::setw(12) << cur->data.type
             << std::setw(10) << cur->data.weight
             << std::setw(15) << cur->data.date
             << std::setw(10) << cur->data.priority
             << "\n";
        cur = cur->next;
    }
}


bool WasteList::loadFromFile(const string& filename) {
    ifstream in(filename);
    if (!in.is_open()) return false;
    clear();
    string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string token;
        int id; string type; double weight; string date; int pr;
        
        if (!std::getline(ss, token, ',')) continue;
        if (!isdigit(token[0])) continue; 
        id = std::stoi(token);
        if (!std::getline(ss, type, ',')) continue;
        if (!std::getline(ss, token, ',')) continue;
        weight = std::stod(token);
        if (!std::getline(ss, date, ',')) continue;
        if (!std::getline(ss, token, ',')) continue;
        pr = std::stoi(token);
        insert(WasteItem(id, type, weight, date, pr));
    }
    in.close();
    return true;
}

bool WasteList::saveToFile(const string& filename) const {
    ofstream out(filename);
    if (!out.is_open()) return false;
    Node* cur = head;
    while (cur) {
        out << cur->data.id << ','
            << cur->data.type << ','
            << cur->data.weight << ','
            << cur->data.date << ','
            << cur->data.priority << '\n';
        cur = cur->next;
    }
    out.close();
    return true;
}

int WasteList::toArray(WasteItem arr[], int maxSize) const {
    int count = 0;
    Node* cur = head;
    while (cur && count < maxSize) {
        arr[count++] = cur->data;
        cur = cur->next;
    }
    return count;
}

int WasteList::size() const {
    int c = 0;
    Node* cur = head;
    while (cur) { c++; cur = cur->next; }
    return c;
}

void WasteList::addNewItem() {
    int id, pr;
    string type, date;
    double weight;

    cout << "Enter ID: ";
    cin >> id;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    cout << "Enter type: ";
    getline(cin, type);

    cout << "Enter weight: ";
    cin >> weight;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    cout << "Enter date (YYYY-MM-DD): ";
    getline(cin, date);

    cout << "Enter priority: ";
    cin >> pr;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    insert(WasteItem(id, type, weight, date, pr));
    cout << "✔ New waste item added successfully.\n";
}
