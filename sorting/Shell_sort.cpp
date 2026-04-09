#include <iostream>
#include <cmath>
#include <random>
#include <fstream>

using namespace std;

int ShellSort_1(int* arr, int size) {
    int swaps = 0;
    
    for (int idx = size / 2; idx > 0; idx /= 2) {
        for (int i = idx; i < size; ++i) {
            int tmp = arr[i];
            int j = i;

            while (j >= idx and arr[j - idx] > tmp) {
                arr[j] = arr[j - idx];
                j -= idx;
                ++swaps;
            }

            arr[j] = tmp;
        }

    }

    return swaps;
}

int ShellSort_2(int* arr, int size) {
    int swaps = 0;
    int idx = 1;
    while ((1 << idx) - 1 <= size) ++idx;
    --idx;

    while (idx > 0) {
        int i = (1 << idx) - 1;

        for (int j = i; j < size; ++j) {
            int tmp = arr[j];
            int k = j;

            while (k >= i and arr[k - i] > tmp) {
                arr[k] = arr[k - i];
                k -= i;
                ++swaps;
            }

            arr[k] = tmp;
        }

        --idx;
    }

    return swaps;
}

int ShellSort_3(int* arr, int size) {
    int swaps = 0;

    int F1 = 1, F2 = 2;

    while (F2 <= size) {
        int next = F1 + F2;
        F1 = F2;
        F2 = next;
    }

    while (F1 > 0) {
        int idx = F1;

        for (int i = idx; i < size; ++i) {
            int tmp = arr[i];
            int j = i;

            while (j >= idx and arr[j - idx] > tmp) {
                arr[j] = arr[j - idx];
                j -= idx;
                ++swaps;
            }

            arr[j] = tmp;
        }

        int prev = F2 - F1;
        F2 = F1;
        F1 = prev;
    }

    return swaps;
}

long long measure_time(int N) {
    unsigned int n;

    auto begin = chrono::steady_clock::now();

    for (unsigned cnt = 5; cnt != 0; --cnt) {
        int* arr = new int[N];

        for (int idx = 0; idx < N; ++idx) {
        arr[idx] = N - idx;
        }


        n = ShellSort_3(arr, N);
        delete[] arr;
    }
    
    auto end = chrono::steady_clock::now();
    return chrono::duration_cast<chrono::microseconds>(end - begin).count();
}

unsigned int iterations(int N) {
    unsigned int n = 0;

    for (unsigned cnt = 5; cnt != 0; --cnt) {
        int* arr = new int[N];

        for (int idx = 0; idx < N; ++idx) {
        arr[idx] = N - idx;
        }


        n += ShellSort_3(arr, N);
        delete[] arr;
    }

    return n;
}

int main() {
    int N;

    ofstream file("Shell_sort_3.csv");
    file << "index,elements,time,swaps" << endl;
    int elements[] = {100, 1'000, 10'000, 50'000, 100'000, 200'000, 300'000, 400'000, 500'000, 600'000, 700'000, 800'000, 900'000, 1'000'000, 2'000'000};
    for (int idx = 0; idx < 15; ++idx) {
        file << idx << ',' << elements[idx] << ',' << measure_time(elements[idx]) << ',' << iterations(elements[idx]) << endl;
    }
    file.close();
    return 0;
}