#include <iostream>
#include <string>
#include <limits>

#include "WasteList.h"
#include "WasteSearch.h"
#include "CollectionQueue.h"
#include "WasteSort.h"
#include "WasteCategoryTree.h"
#include <algorithm>

using namespace std;

void pause() {
    cout << "Press Enter to continue...";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void showMenu() {
    cout << "\n===== ECO-TRACK (SDG 12) =====\n";
    cout << "1. Load waste records from data.csv\n";
    cout << "2. Display all waste items\n";
    cout << "3. Search waste item by ID\n";
    cout << "4. Sort waste items by priority\n";
    cout << "5. Submit pickup request\n";
    cout << "6. View pickup request queue\n";
    cout << "7. Insert waste category\n";
    cout << "8. Add a waste record\n";
    cout << "9. Save waste records to saved_data.csv\n";
    cout << "0. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    WasteList list;
    WasteSearch searcher;
    CollectionQueue queue;
    WasteSorter sorter;
    WasteCategoryTree tree;

    int choice = 0;
    int nextRequestId = 1;

    while (true) {
        showMenu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.\n";
            continue;
        }
        cin.ignore();

        if (choice == 1) {
            if (list.loadFromFile("../INPUT_DATA/data.csv")) cout << "Loaded data.csv successfully.\n";
            else cout << "Failed to load data.csv (make sure file exists in project folder).\n";
            pause();
        }
        else if (choice == 2) {
            list.displayAll();
            pause();
        }
        else if (choice == 3) {
            int id;
            cout << "Enter waste ID to search: ";
            cin >> id; cin.ignore();
            
            int maxN = 500;
            WasteItem* arr = new WasteItem[maxN];
            int n = list.toArray(arr, maxN);
            
            std::sort(arr, arr + n, [](const WasteItem& a, const WasteItem& b){ return a.id < b.id; });
            int idx = searcher.binarySearchById(arr, n, id);
            if (idx != -1) {
                cout << "Found: ID " << arr[idx].id << " Type: " << arr[idx].type
                     << " Weight: " << arr[idx].weight << " Date: " << arr[idx].date
                     << " Priority: " << arr[idx].priority << '\n';
            } else cout << "ID not found.\n";
            delete[] arr;
            pause();
        }
        else if (choice == 4) {
            int maxN = 500;
            WasteItem* arr = new WasteItem[maxN];
            int n = list.toArray(arr, maxN);
            if (n == 0) { cout << "No items to sort.\n"; delete[] arr; pause(); continue; }
            sorter.mergeSort(arr, 0, n - 1);
            cout << "Sorted list (by priority, then weight):\n";
            cout << "ID\tType\tWeight\tDate\tPriority\n";
            for (int i = 0; i < n; ++i) {
                cout << arr[i].id << '\t' << arr[i].type << '\t' << arr[i].weight << '\t'
                     << arr[i].date << '\t' << arr[i].priority << '\n';
            }
            delete[] arr;
            pause();
        }
        else if (choice == 5) {
            int wasteId;
            string address;
            cout << "Enter waste ID to pick up: ";
            cin >> wasteId; cin.ignore();
            cout << "Enter pickup address: ";
            std::getline(cin, address);
            PickupRequest req(nextRequestId++, wasteId, address);
            if (queue.enqueue(req)) cout << "Pickup request added (ReqID " << req.requestID << ").\n";
            else cout << "Queue is full. Try later.\n";
            pause();
        }
        else if (choice == 6) {
            queue.display();
            pause();
        }
        else if (choice == 7) {
            string cat;
            cout << "Enter category name: ";
            std::getline(cin, cat);
            tree.insert(cat);
            cout << "Category inserted.\n";
            cout << "Categories (alphabetical):\n";
            tree.display();
            pause();
        }
        else if (choice == 8) {
            cout << "Adding new waste item...\n";
            list.addNewItem();

        if (list.saveToFile("saved_data.csv")) {
            cout << "Data added!\n";
    } 
        else {
            cout << "ERROR: Unable to save file.\n";
    }

    pause();
}

        else if (choice == 9) {
            if (list.saveToFile("saved_data.csv")) cout << "Saved to saved_data.csv\n";
            else cout << "Failed to save file.\n";
            pause();
        }
        else if (choice == 0) {
            cout << "Exiting EcoTrack. Goodbye!\n";
            break;
        }
        else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}
