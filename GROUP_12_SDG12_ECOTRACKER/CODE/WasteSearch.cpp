#include "WasteSearch.h"

int WasteSearch::binarySearchById(const WasteItem arr[], int size, int targetId) {
    int l = 0, r = size - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (arr[m].id == targetId) return m;
        if (arr[m].id < targetId) l = m + 1;
        else r = m - 1;
    }
    return -1;
}
