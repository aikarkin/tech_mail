#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

template <typename T>
void shiftDown(T *arr, int arr_size, int i, int (*compare)(T, T)) {
    bool done = false;
    int largest;
    T tmp;

    int j = i;
    while((j * 2 + 1 < arr_size) && (!done)) {
        if (j * 2 + 1 == arr_size - 1)
            largest = j * 2 + 1;
        else if(compare(arr[j * 2 + 1], arr[j * 2 + 2]))
            largest = j * 2 + 1;
        else
            largest = j * 2 + 2;

        if(compare(arr[largest], arr[j])) {
            // swap arr[j] <-> arr[largest]
            tmp = arr[j];
            arr[j] = arr[largest];
            arr[largest] = tmp;
            j = largest;
        }
        else {
            done = true;
        }
    }
}

template <typename T>
void buildHeap(T *arr, int arr_size, int (*compare)(T, T)) {
    for (int i = arr_size/2 - 1; i >=0 ; --i)
        shiftDown(arr, arr_size, i, compare);
}

template <typename T>
void heapSort(T *arr, int arr_size, int (*compare)(T, T)) {
    buildHeap(arr, arr_size, compare);
    T tmp;

    for (int i = arr_size - 1; i > 0 ; --i) {
        tmp  = arr[0];/
        arr[0] = arr[i];
        arr[i] = tmp;
        shiftDown(arr, i, 0, compare);
    }
}

int compare(int a, int b) {
    return a > b;
}

int main() {
    int n;
    cin >> n;
    int *arr = new int[n];

    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    heapSort<int>(arr, n, compare);

    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }

    delete []arr;
    return 0;
}