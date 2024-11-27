#include <iostream>
#include <chrono>
#include <cstdlib>

using namespace std; 
using namespace std::chrono;

void bubbleSort(int arr[], int n) {
    int flag=0;
    for (int i = 0; i < n - 1; ++i) {
        flag=0;
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                // Swap if the element found is greater than the next element
                swap(arr[j], arr[j + 1]);
                flag=1;
            }
        }
        // If no two elements were swapped by inner loop, then the array is sorted
        if (flag!=1) break;
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

    cout<<"\n\nFor Bubble Sort:"<<endl;

    for (int i = 0; i < 4; ++i) {
        int size = sizes[i];
        int* arr = new int[size];
        //sri
        generateRandomArray(arr, size);

        auto start = high_resolution_clock::now();
        bubbleSort(arr, size);
        auto end = high_resolution_clock::now();

        auto time_spent = duration_cast<nanoseconds>(end - start).count();

        cout << "The elapsed time for " << size << " elements is " << time_spent << " nanoseconds" << endl;

        delete[] arr; // Deallocate the array
    }

    cout<<endl<<endl;
    return 0;
}
