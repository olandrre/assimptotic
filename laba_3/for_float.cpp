#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

float rect_integration(float const psi[], float const pdf[], float const dv, unsigned size, bool FMA) {
    float sum = 0.f;
    for (unsigned idx = 0; idx < size; ++idx) {
        if (FMA) {
            sum = fma(psi[idx] * pdf[idx], dv, sum);
        } else {
            sum += psi[idx] * pdf[idx] * dv;
        }
    }
    return sum;
}

float recursive(float const psi[], float const pdf[], unsigned size) {
    if (size == 1) return psi[0] * pdf[0];

    unsigned mid = size / 2;
    return recursive(psi, pdf, mid) + recursive(psi + mid, pdf + mid, size - mid);
}

float recursive_integration(float const psi[], float const pdf[], float const dv, unsigned size) {
    return recursive(psi, pdf, size) * dv;
}

float circle_recurs(float const psi[], float const pdf[], float const dv, unsigned size) {
    float *tmp = new float[size];
    for (unsigned idx = 0; idx < size; ++idx) {
        tmp[idx] = psi[idx] * pdf[idx];
    }

    for (unsigned step = 1; step < size; step *= 2) {
        for (unsigned idx = 0; idx + step < size; idx += step * 2) {
            tmp[idx] += tmp[idx + step];
        }
    }
    
    float sum = tmp[0] * dv;
    delete[] tmp;

    return sum;
}

float Kahan_intefr(float const psi[], float const pdf[], float const dv, unsigned size) {
    float sum = 0.f;
    float c = 0.f;

    for (unsigned idx = 0; idx < size; ++idx) {
        float x = psi[idx] * pdf[idx];
        float y = x - c;
        float t = sum + y;
        c = (t - sum) - y;
        sum = t;
    }

    return sum * dv;
}

int main() {
    ofstream file("results_float.txt");
    ofstream result_v("v_float.csv");
    ofstream result_v2("v2_float.csv");

    result_v << "T,N,method,result,theory,error" << endl;
    result_v2 << "T,N,method,result,theory,error" << endl;
    float values_T[] = {0.1f, 1.f, 100.f, 10'000.f};
    unsigned int values_N[] = {10, 1'000, 100'000};
    
    file << scientific << setprecision(7);
    result_v << scientific << setprecision(7);
    result_v2 << scientific << setprecision(7);

    for (float T : values_T) {
        file << endl << "T = " << T << endl;

        float L = 6.f * sqrt(T);
        float theory_v = sqrt(T / M_PI);
        float theory_v2 = T / 2.f;

        for (unsigned N : values_N) {
            float dv = 2.0 * L / N;

            float *pdf = new float[N];
            float *psi_v = new float[N];
            float *psi_v2 = new float[N];

            for (unsigned idx = 0; idx < N; ++idx) {
                float v_idx = -L + idx * dv;

                psi_v[idx] = abs(v_idx);
                pdf[idx] = exp(-(v_idx * v_idx) / T) / sqrt(M_PI * T);

                psi_v2[idx] = v_idx * v_idx;
            }

            float rect_v = rect_integration(psi_v, pdf, dv, N, false);
            float rect_v_fma = rect_integration(psi_v, pdf, dv, N, true);
            float recurs_v = recursive_integration(psi_v, pdf, dv, N);
            float c_recurs_v = circle_recurs(psi_v, pdf, dv, N);
            float kahan_v = Kahan_intefr(psi_v, pdf, dv, N);

            float rect_v2 = rect_integration(psi_v2, pdf, dv, N, false);
            float rect_v2_fma = rect_integration(psi_v2, pdf, dv, N, true);
            float recurs_v2 = recursive_integration(psi_v2, pdf, dv, N);
            float c_recurs_v2 = circle_recurs(psi_v2, pdf, dv, N);
            float kahan_v2 = Kahan_intefr(psi_v2, pdf, dv, N);

            file << endl << "N = " << N << endl;
            file << "<v> наивным методом: " << rect_v << ", ошибка: " << fabs(rect_v - theory_v) << endl;
            file << "<v> наивным методом с FMA: " << rect_v_fma << ", ошибка: " << fabs(rect_v_fma - theory_v) << endl;
            file << "<v> рекурсивным методом: " << recurs_v << ", ошибка: " << fabs(recurs_v - theory_v) << endl;
            file << "<v> рекурсивным методом с циклом: " << c_recurs_v << ", ошибка: " << fabs(c_recurs_v - theory_v) << endl;
            file << "<v> алгоритмом Кахена: " << kahan_v << ", ошибка: " << fabs(kahan_v - theory_v) << endl;
            
            file << endl;

            file << "<v^2> наивным методом: " << rect_v2 << ", ошибка: " << fabs(rect_v2 - theory_v2) << endl;
            file << "<v^2> наивным методом с FMA: " << rect_v2_fma << ", ошибка: " << fabs(rect_v2_fma - theory_v2) << endl;
            file << "<v^2> рекурсивным методом: " << recurs_v2 << ", ошибка: " << fabs(recurs_v2 - theory_v2) << endl;
            file << "<v^2> рекурсивным методом с циклом: " << c_recurs_v2 << ", ошибка: " << fabs(c_recurs_v2 - theory_v2) << endl;
            file << "<v^2> алгоритмом Кахена: " << kahan_v2 << ", ошибка: " << fabs(kahan_v2 - theory_v2) << endl;

            result_v << T << ',' << N << ',' << "naive" << ',' << rect_v << ',' << theory_v << ',' << fabs(rect_v / theory_v - 1) * 100 << endl;
            result_v << T << ',' << N << ',' << "naive_FMA" << ',' << rect_v_fma << ',' << theory_v << ',' << fabs(rect_v_fma / theory_v - 1) * 100 << endl;
            result_v << T << ',' << N << ',' << "recursive" << ',' << recurs_v << ',' << theory_v << ',' << fabs(recurs_v / theory_v - 1) * 100 << endl;
            result_v << T << ',' << N << ',' << "circle_recursive" << ',' << c_recurs_v << ',' << theory_v << ',' << fabs(c_recurs_v / theory_v - 1) * 100 << endl;
            result_v << T << ',' << N << ',' << "kahan" << ',' << kahan_v << ',' << theory_v << ',' << fabs(kahan_v / theory_v - 1) * 100 << endl;
            result_v2 << T << ',' << N << ',' << "naive" << ',' << rect_v2 << ',' << theory_v2 << ',' << fabs(rect_v2 / theory_v2 - 1) * 100 << endl;
            result_v2 << T << ',' << N << ',' << "naive_FMA" << ',' << rect_v2_fma << ',' << theory_v2 << ',' << fabs(rect_v2_fma / theory_v2 - 1) * 100 << endl;
            result_v2 << T << ',' << N << ',' << "recursive" << ',' << recurs_v2 << ',' << theory_v2 << ',' << fabs(recurs_v2 / theory_v2 - 1) * 100 << endl;
            result_v2 << T << ',' << N << ',' << "circle_recursive" << ',' << c_recurs_v2 << ',' << theory_v2 << ',' << fabs(c_recurs_v2 / theory_v2 - 1) * 100 << endl;
            result_v2 << T << ',' << N << ',' << "kahan" << ',' << kahan_v2 << ',' << theory_v2 << ',' << fabs(kahan_v2 / theory_v2 - 1) * 100 << endl;

            delete[] pdf;
            delete[] psi_v;
            delete[] psi_v2;
        }
    }
    file.close();
    result_v.close();
    result_v2.close();
    return 0;
}