//implement binary search and binary search and analyze its time complexity
#include <iostream>
#include <chrono>
#include <cstdlib>
using namespace std;
using namespace std::chrono;

int binarySearch(int arr[], int n, int key)
{
    int low = 0;
    int high = n - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (arr[mid] == key)
        {
            return mid;
        }
        else if (arr[mid] < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return -1;
}

void generateRandomArray(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = rand();
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    int sizes[] = {100, 500, 1000, 1500};

    cout << "\n\nFor Binary Search:" << endl;

    for (int i = 0; i < 4; ++i) {
        int size = sizes[i];
        int* arr = new int[size];
        //sri
        generateRandomArray(arr, size);

        auto start = high_resolution_clock::now();
        binarySearch(arr, size, rand());
        auto end = high_resolution_clock::now();

        auto time_spent = duration_cast<nanoseconds>(end - start).count();

        cout << "The elapsed time for " << size << " elements is " << time_spent << " nanoseconds" << endl;

        delete[] arr;
    }

    cout<<endl<<endl;
    return 0;
}