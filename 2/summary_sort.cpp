#include <iostream>
#include <chrono>
#include <random>
#include <fstream>

using namespace std;

bool sum_of_two_sort(int const arr[], int N, int sum_0) {
    int l_idx = 0, r_idx = N - 1;
    while (l_idx < r_idx) {
        int sum = arr[l_idx] + arr[r_idx];
        if (sum == sum_0) {
            return true;
        } else if (sum < sum_0) {
            ++l_idx;
        } else {
            --r_idx;
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

    sort(arr, arr + N);

    int key = -1;

    auto begin = chrono::steady_clock::now();
    for (unsigned cnt = 100000; cnt != 0; --cnt)
        sum_of_two_sort(arr, N, key);
    auto end = chrono::steady_clock ::now();
    delete[] arr;
    return chrono::duration_cast<chrono::milliseconds>(end - begin).count();
}

int main() {
    ofstream file("sort_sum.csv");
    file << ",X,Y" << endl;
    int elements[] = {100, 500, 1'000, 5'000, 10'000, 50'000, 100'000, 250'000, 500'000, 750'000, 1'000'000};
    for (int idx = 0; idx < 11; ++idx) {
        file << idx << ',' << elements[idx] << ',' << measure_time(elements[idx]) << endl;
    }
    file.close();
    return 0;
}