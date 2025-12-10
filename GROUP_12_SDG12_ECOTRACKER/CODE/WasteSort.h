#pragma once
#include "WasteList.h"

class WasteSorter {
public:
    
    void mergeSort(WasteItem arr[], int left, int right);

private:
    void merge(WasteItem arr[], int left, int mid, int right);
    bool compare(const WasteItem& a, const WasteItem& b);
};
