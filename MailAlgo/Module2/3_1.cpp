#include <iostream>
#include <vector>

using namespace std;

struct ClientTime {
    int begin;
    int end;
    ClientTime(int _begin, int _end) : begin(_begin), end(_end) { }
    ClientTime() : begin(0), end(0) { }
    bool isPoint() {
        return begin == end;
    }
    bool isEmpty() {
        return begin == 0 && end == 0;
    }
};

int compareCTime(ClientTime ct1, ClientTime ct2) {
    return ct1.end > ct2.end || (ct1.end == ct2.end && ct1.begin < ct2.begin);
}

template<typename T>
void swap(T &a, T &b) {
    T tmp = a;
    a = b;
    b = tmp;
}

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
        tmp  = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;
        shiftDown(arr, i, 0, compare);
    }
}

ClientTime intersection(ClientTime ctime1, ClientTime ctime2) {
    ClientTime res;
    if(ctime1.end < ctime2.begin || ctime2.end < ctime1.begin)
        return res;
    res.begin = max(ctime1.begin, ctime2.begin);
    res.end = min(ctime1.end, ctime2.end);
    return res;
}

int calcTime(ClientTime *arr, int arr_size) {
    if(arr_size == 0)
        return 0;
    vector<ClientTime> inter_lst;
    ClientTime cur_inter;
    inter_lst.push_back(arr[0]);
    for (int i = 1; i < arr_size; ++i) {
        cur_inter = intersection(inter_lst.back(), arr[i]);
        if(cur_inter.isPoint() || cur_inter.isEmpty())
            inter_lst.push_back(arr[i]);
        else
            inter_lst.back() = cur_inter;
    }

    int sumTime = 2;
    //cout << endl << inter_lst[0].begin << " " << inter_lst[0].end << endl;
    for(int i=1; i<inter_lst.size(); ++i){
        //cout << inter_lst[i].begin << " " << inter_lst[i].end << endl;
        if(inter_lst[i - 1].end == inter_lst[i].begin)
            sumTime++;
        else sumTime+=2;
    }

    return sumTime;
}

int main() {
    int n, a, b;
    cin >> n;
    ClientTime *clients = new ClientTime[n];

    for (int i = 0; i < n; ++i) {
        cin >> a >> b;
        clients[i].begin = min(a, b);
        clients[i].end = max(a, b);
    }

    //sorting by right end

    heapSort<ClientTime>(clients, n, compareCTime);

    /*cout << endl;
	for (int i = 0; i < n; ++i) {
		cout << clients[i].begin << " " << clients[i].end << endl;
    }*/

	cout << calcTime(clients, n) << endl;

    delete []clients;
	return 0;
}
    