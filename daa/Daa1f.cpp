#include <iostream>
#include <cstdlib>
#include <chrono>

using namespace std;
using namespace std::chrono;

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; --i) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void generateRandomArray(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = rand();
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    int sizes[] = {100, 500, 1000, 1500};

    cout << "\n\nFor Heap Sort:" << endl;

    for (int i = 0; i < 4; ++i) {
        int size = sizes[i];
        int* arr = new int[size];
        //sri
        generateRandomArray(arr, size);

        auto start = high_resolution_clock::now();
        heapSort(arr, size);
        auto end = high_resolution_clock::now();

        auto time_spent = duration_cast<nanoseconds>(end - start).count();

        cout << "The elapsed time for " << size << " elements is " << time_spent << " nanoseconds" << endl;

        delete[] arr;
    }

    cout<<endl<<endl;
    return 0;
}
