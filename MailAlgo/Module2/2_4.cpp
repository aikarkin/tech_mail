#include <iostream>
#include <queue>

using namespace std;

class Heap {

private:
    int *heap, *order;
    int focus;
    int count;
    int size;

    void swap(int i, int j) {
        int tmp = heap[i];
        heap[i] = heap[j];
        heap[j] = tmp;

        tmp = order[i];
        order[i] = order[j];
        order[j] = tmp;
    }

    void shiftDown(int i) {
        int left, right, largest;

        while(2 * i + 1 < size) {
            left = 2 * i + 1;
            right = left + 1;
            largest = left;

            if(right < size && heap[right] > heap[left])
                largest = right;
            if(heap[i] >= heap[largest])
                break;

            swap(i, largest);
            i = largest;
        }
    }

    void shiftUp(int i) {
        while (heap[i] > heap[(i - 1) / 2]) {
            swap(i, (i - 1) / 2);
            i = (i - 1) / 2;
        }
    }

public:
    Heap(int _size) : size(_size), count(0), focus(0) {
        heap = new int[_size];
        order = new int[_size];
    }

    ~Heap() {
        delete []heap;
    }

    void insertElem(int val) {
        if(count == size) {
            cout << "Can't add element to heap. Buffer is overflow." << endl;
        }
        heap[count] = val;
        order[count] = count;
        shiftUp(count++);
    }

    void changeElemByIndex(int i, int val) {
        int oldVal = heap[i];
        heap[i] = val;
        if(val > oldVal)
            shiftUp(i);
        else if(val < oldVal)
            shiftDown(i);
    }

    int maxVal() {
        return heap[0];
    }

    void replaceOldest(int val) {
        int curHeapInd = order[focus];
        changeElemByIndex(curHeapInd, val);
        focus = (focus + 1) % size;
    }

    void printHeap() {
        cout << "elements in heap: ";
        for (int i = 0; i < count; ++i) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }

    void printHeapIndexes() {
        cout << "indexes of elements in heap in order of insertion: " << endl;
        for (int i = 0; i < size; ++i)
            cout << i << " ";
        cout << endl;
        for (int i = 0; i < size; ++i)
            cout << order[i] << " ";
        cout << endl;
    }
    int getFocus() { return focus; }
};

int main() {
    int n, k;
    cin >> n;
    int *arr = new int[n];

    for (int i = 0; i < n; i++)
        cin >> arr[i];
    cin >> k;
    Heap win_heap(k);

    for (int i = 0; i < k; ++i)
        win_heap.insertElem(arr[i]);

    for (int i = k; i < n; ++i) {
        cout << "max val:" << win_heap.maxVal() << " " << endl << "focus: " << win_heap.getFocus() << endl;
        win_heap.printHeap();
        win_heap.printHeapIndexes();
        win_heap.replaceOldest(arr[i]);
        cout << "---------------" << endl << endl;
    }
    cout << "max val:" << win_heap.maxVal() << " " << endl << "focus: " << win_heap.getFocus() << endl;
    win_heap.printHeap();
    win_heap.printHeapIndexes();
    cout << win_heap.maxVal() << endl;

    return 0;
}