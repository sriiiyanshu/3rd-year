#include <iostream>
#include <vector>
using namespace std;

void compareAndSwap(int &a, int &b) {
    if (a > b) {
        swap(a, b);
    }
}

// Function to implement the sorting network for 4 elements
void sortingNetwork4(int &a, int &b, int &c, int &d) {
    compareAndSwap(a, b);
    compareAndSwap(c, d);
    
    compareAndSwap(a, c);
    compareAndSwap(b, d);
    
    compareAndSwap(b, c);
}

void printArray(const vector<int> &arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    vector<int> arr(4);
    
    cout << "Enter 4 integers to sort: ";
    for (int i = 0; i < 4; i++) {
        cin >> arr[i];
    }

    sortingNetwork4(arr[0], arr[1], arr[2], arr[3]);
    
    cout << "Sorted array: ";
    printArray(arr);
    
    return 0;
}
