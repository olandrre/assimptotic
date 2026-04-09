#include <iostream>
#include <chrono>
#include <random>
#include <fstream>

using namespace std;

int linear(int arr[], int size, int key) {
    for (int idx = 0; idx < size; ++idx) {
        if (arr[idx] == key) {
            return idx;
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

    int key, res;

    // худший случай

    key = -1;

    auto begin = chrono::steady_clock::now();
    for (unsigned cnt = 10'000'000; cnt != 0; --cnt) {
        // key = arr[dstr(rng)];
        res = linear(arr, N, key);
    }
    auto end = chrono::steady_clock ::now();
    delete[] arr;
    return chrono::duration_cast<chrono::nanoseconds>(end - begin).count() / 10'000'000;
}

long long measure_time0(int N) {
    int* arr = new int[N];

    unsigned seed = 9;
    default_random_engine rng(seed);
    uniform_int_distribution<int> dstr(0, N -1);
    for (int idx = 0; idx < N; ++idx) {
        arr[idx] = dstr(rng);
    }

    int key, res;
    long long sum = 0;

    // худший случай

    key = -1;

    for (unsigned cnt = 10'000'000; cnt != 0; --cnt) {
        // key = arr[dstr(rng)];
        auto begin = chrono::steady_clock::now();
        res = linear(arr, N, key);
        auto end = chrono::steady_clock ::now();
        sum += chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
    }
    delete[] arr;
    return sum / 10'000'000;
}

int main() {
    int x = measure_time(100);
    int y = measure_time0(100);
    cout << x << endl;
    cout << y << endl;
    cout << x - y << endl;
    return 0;
}