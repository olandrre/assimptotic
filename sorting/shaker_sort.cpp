#include <iostream>

using namespace std;

void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void forward_step(unsigned arr[], unsigned const begin_idx, unsigned const end_idx) {
    for (unsigned int idx = begin_idx; idx < end_idx; ++idx) {
        if (arr[idx] > arr[idx + 1]) swap(arr[idx], arr[idx + 1]);
    }
}

void backward_step(unsigned arr[], unsigned const begin_idx, unsigned const end_idx) {
    for (unsigned int idx = end_idx; idx > begin_idx; --idx) {
        if (arr[idx] < arr[idx - 1]) swap(arr[idx], arr[idx - 1]);
    }
}

void shaker_sort(unsigned arr[], unsigned const begin_idx, unsigned const end_idx) {
    int begin = begin_idx, end = end_idx;
    while (begin < end) {
        forward_step(arr, begin, end);
        --end;
        backward_step(arr, begin, end);
        ++begin;
    }
}

void printArray(unsigned arr[], int size) {
    for (unsigned idx = 0; idx < size; ++idx) {
        cout << arr[idx] << ' ';
    }
    cout << endl;
}

void test_forward() {
    unsigned arr[] = {1, 4, 5, 10, 2, 8, 3, 7};
    forward_step(arr, 0, 7);
    printArray(arr, 8);
}

void test_backward() {
    unsigned arr[] = {1, 4, 5, 10, 2, 8, 3, 7};
    backward_step(arr, 0, 7);
    printArray(arr, 8);
}

void test_shaker() {
    unsigned arr[] = {1, 4, 5, 10, 2, 8, 3, 7};
    shaker_sort(arr, 0, 7);
    printArray(arr, 8);
}

int main() {
    test_forward();
    test_backward();
    test_shaker();
    return 0;
}