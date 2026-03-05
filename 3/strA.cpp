#include <iostream>
#include <fstream>
#include <random>
#include <chrono>

using namespace std;

int move_1(int arr[], int N, int key) {
    for (int idx = 0; idx < N; ++idx) {
        if (arr[idx] == key) {
            if (idx != 0) {
                int temp = arr[idx];
                arr[idx] = arr[0];
                arr[0] = temp;
            }
        return idx;
        }
    }
    return -1;
}

long long measure_time(int N) {
    int* arr = new int[N];

    unsigned seed = 9;
    default_random_engine rng(seed);
    uniform_int_distribution<int> dstr(0, N * 2);
    for (int idx = 0; idx < N; ++idx) {
        arr[idx] = dstr(rng);
    }

    auto begin = chrono::steady_clock::now();

    //равномерное распределение

    // for (unsigned cnt = 100000; cnt != 0; --cnt) {
    //     int key = dstr(rng);
    //     move_1(arr, N, key);
    // }

     //неравномерное распределение 

    for (unsigned cnt = 100000; cnt != 0; --cnt) {
        int key;
        if (dstr(rng) % 10 < 7) {
            key = arr[0];
        } else {
            key = dstr(rng);
        }

        move_1(arr, N, key);
    }

    auto end = chrono::steady_clock ::now();
    delete[] arr;
    return chrono::duration_cast<chrono::milliseconds>(end - begin).count();
}

int main() {
    ofstream file("strategy_A2.csv");
    file << ",X,Y" << endl;
    int elements[] = {100, 500, 1'000, 5'000, 10'000, 50'000, 100'000, 250'000, 500'000, 750'000, 1'000'000};
    for (int idx = 0; idx < 11; ++idx) {
        file << idx << ',' << elements[idx] << ',' << measure_time(elements[idx]) << endl;
    }
    file.close();
    return 0;
}