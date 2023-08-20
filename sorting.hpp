#include <iostream>
#include <vector>
using namespace std;
 
int partition(vector<pair<int,float>>& arr, int start, int end)
{
 
    int pivot = arr[start].first;
 
    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (arr[i].first <= pivot)
            count++;
    }
 
    // Giving pivot element its correct position
    int pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start]);
 
    // Sorting left and right parts of the pivot element
    int i = start, j = end;
 
    while (i < pivotIndex && j > pivotIndex) {
 
        while (arr[i].first <= pivot) {
            i++;
        }
 
        while (arr[j].first > pivot) {
            j--;
        }
 
        if (i < pivotIndex && j > pivotIndex) {
            swap(arr[i++], arr[j--]);
        }
    }
 
    return pivotIndex;
}
 
void quickSort(vector<pair<int,float>>& arr, int start, int end)
{
 
    // base case
    if (start >= end)
        return;
 
    // partitioning the array
    int p = partition(arr, start, end);
 
    // Sorting the left part
    quickSort(arr, start, p - 1);
 
    // Sorting the right part
    quickSort(arr, p + 1, end);
}