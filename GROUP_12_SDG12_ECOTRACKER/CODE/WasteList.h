#pragma once
#include <string>

using std::string;

static const int MAX_WASTE_ITEMS = 50;

struct WasteItem {
    int id;
    string type;
    double weight;
    string date;
    int priority;

    WasteItem() : id(0), type(""), weight(0.0), date(""), priority(0) {}
    WasteItem(int _id, const string& _type, double _weight, const string& _date, int _priority)
        : id(_id), type(_type), weight(_weight), date(_date), priority(_priority) {}
};

class WasteList {
private:
    struct Node {
        WasteItem data;
        Node* next;
        Node(const WasteItem& d) : data(d), next(nullptr) {}
    };
    Node* head;

public:
    WasteList();
    ~WasteList();

    void insert(const WasteItem& item);       
    void displayAll() const;
    void clear();
    void addNewItem();

    
    bool loadFromFile(const string& filename);
    bool saveToFile(const string& filename) const;

  
    int toArray(WasteItem arr[], int maxSize) const;
    int size() const;
};



