#include <iostream>
#include <chrono>
#include <random>
#include <fstream>

using namespace std;

bool sum_of_two(int const arr[], int N, int sum) {
    for (int idx_1 = 0; idx_1 < N; ++idx_1) {
        for (int idx_2 = idx_1 + 1; idx_2 < N; ++idx_2) {
            if (arr[idx_1] + arr[idx_2] == sum) {
                return true;
            }
        }
    }
    return false;
}

long long measure_time(int N) {
    int* arr = new int[N];

    unsigned seed = 9;
    default_random_engine rng(seed);
    uniform_int_distribution<int> dstr(0, N -1);
    for (int idx = 0; idx < N; ++idx) {
        arr[idx] = dstr(rng);
    }

    int key = -1;

    auto begin = chrono::steady_clock::now();
    for (unsigned cnt = 1000; cnt != 0; --cnt)
        sum_of_two(arr, N, key);
    auto end = chrono::steady_clock ::now();
    delete[] arr;
    return chrono::duration_cast<chrono::milliseconds>(end - begin).count();
}

int main() {
    ofstream file("sum.csv");
    file << ",X,Y" << endl;
    int elements[] = {100, 250, 500, 750, 1'000, 2'000, 3'000, 4'000, 5'000};
    for (int idx = 0; idx < 9; ++idx) {
        file << idx << ',' << elements[idx] << ',' << measure_time(elements[idx]) << endl;
    }
    file.close();
    return 0;
}