#include <iostream>
#include <random>
#include <fstream>

using namespace std;

void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

int swap_N(int* arr, int size, int N) {
    int swapped = 0;
    for (int idx = 0; idx < size - N; ++idx) {
        if (arr[idx] > arr[idx + N]) {
            swap(arr[idx], arr[idx + N]);
            ++swapped;
        }
    }
    return swapped;
}

unsigned int comb_sort(int* arr, int size) {
    unsigned int k = 0;
    int N = size;
    int swapped = 0;
    bool sorted = false;
    while (N > 1 or !sorted) {
        N /= 1.247; //or do I have to use 2???
        if (N == 0) N = 1;
        swapped = swap_N(arr, size, N);
        k += swapped;
        sorted = (swapped == 0);
    }
    return k;
}

long long measure_time(int N, default_random_engine &rng) {
    unsigned int n;

    uniform_int_distribution<int> dstr(0, N - 1);

    unsigned int total = 0;

    for (unsigned cnt = 10'000; cnt != 0; --cnt) {
        int* arr = new int[N];
 
        for (int idx = 0; idx < N; ++idx) {
            arr[idx] = dstr(rng);
        }

            
        auto begin = chrono::steady_clock::now();
        n = comb_sort(arr, N);
        auto end = chrono::steady_clock::now();

        total += chrono::duration_cast<chrono::microseconds>(end - begin).count();
        delete[] arr;
    }

    return total;
}

unsigned int iterations(int N, default_random_engine &rng) {
    unsigned int n;

    int* arr = new int[N];

    uniform_int_distribution<int> dstr(0, N - 1);
    for (int idx = 0; idx < N; ++idx) {
        arr[idx] = dstr(rng);
    }

    n = comb_sort(arr, N);
    delete[] arr;
    return n;
}

int main() {
    int N;
    unsigned seed = 9;
    default_random_engine rng(seed);

    ofstream file("combSorto01.csv");
    file << "index,elements,time,swaps" << endl;
    int elements[] = {100, 500, 1'000, 2'000, 3'000, 4'000, 5'000, 6'000, 7'000, 8'000, 9'000, 10'000};
    for (int idx = 0; idx < 12; ++idx) {
        file << idx << ',' << elements[idx] << ',' << measure_time(elements[idx], rng) << ',' << iterations(elements[idx], rng) << endl;
    }
    file.close();
    return 0;
}