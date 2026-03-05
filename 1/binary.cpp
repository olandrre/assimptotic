#include <iostream>
#include <chrono>
#include <random>
#include <fstream>

using namespace std;


int binary(int arr[], int size, int key) {
    int mid;
    int l_idx = 0, r_idx = size - 1;
    while (l_idx <= r_idx) {
        mid = (l_idx + r_idx) / 2;
        if (arr[mid] == key) {
            return mid;
        } else if (arr[mid] < key) {
            l_idx = mid + 1;
        } else {
            r_idx = mid - 1;
        }
    }
    return -1;
}

long long measure_time(int N) {
    int* arr = new int[N];

    unsigned seed = 9;
    default_random_engine rng(seed);
    uniform_int_distribution<int> dstr(0, N -1);
    for (int idx = 0; idx < N; ++idx) {
        arr[idx] = dstr(rng);
    }

    sort(arr, arr + N);

    int key;
    // key = -1;
    // int total = 0;

    auto begin = chrono::steady_clock::now();
    for (unsigned cnt = 10'000'000; cnt != 0; --cnt) {
        key = arr[dstr(rng)];
        // total += binary(arr, N, key);
        binary(arr, N, key);
    }
    auto end = chrono::steady_clock::now();
    delete[] arr;
    // cout << total << endl;
    return chrono::duration_cast<chrono::microseconds>(end - begin).count();
}

int main() {
    ofstream file("binary_mid.csv");
    file << ",X,Y" << endl;
    int elements[] = {100, 500, 1'000, 5'000, 10'000, 50'000, 100'000, 250'000, 500'000, 750'000, 1'000'000};
    for (int idx = 0; idx < 11; ++idx) {
        file << idx << ',' << elements[idx] << ',' << measure_time(elements[idx]) << endl;
    }
    file.close();
    return 0;
}