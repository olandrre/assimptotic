#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

double rect_integration(double const psi[], double const pdf[], double const dv, unsigned size, bool FMA) {
    double sum = 0.0;
    for (unsigned idx = 0; idx < size; ++idx) {
        if (FMA) {
            sum = fma(psi[idx] * pdf[idx], dv, sum);
        } else {
            sum += psi[idx] * pdf[idx] * dv;
        }
    }
    return sum;
}

double recursive(double const psi[], double const pdf[], unsigned size) {
    if (size == 1) return psi[0] * pdf[0];

    unsigned mid = size / 2;
    return recursive(psi, pdf, mid) + recursive(psi + mid, pdf + mid, size - mid);
}

double recursive_integration(double const psi[], double const pdf[], double const dv, unsigned size) {
    return recursive(psi, pdf, size) * dv;
}

double circle_recurs(double const psi[], double const pdf[], double const dv, unsigned size) {
    double *tmp = new double[size];
    for (unsigned idx = 0; idx < size; ++idx) {
        tmp[idx] = psi[idx] * pdf[idx];
    }

    for (unsigned step = 1; step < size; step *= 2) {
        for (unsigned idx = 0; idx + step < size; idx += step * 2) {
            tmp[idx] += tmp[idx + step];
        }
    }
    
    double sum = tmp[0] * dv;
    delete[] tmp;

    return sum;
}

double Kahan_intefr(double const psi[], double const pdf[], double const dv, unsigned size) {
    double sum = 0.0;
    double c = 0.0;

    for (unsigned idx = 0; idx < size; ++idx) {
        double x = psi[idx] * pdf[idx];
        double y = x - c;
        double t = sum + y;
        c = (t - sum) - y;
        sum = t;
    }

    return sum * dv;
}

int main() {
    ofstream file("results_double.txt");
    double values_T[] = {0.1, 1.0, 100.0, 10000.0};
    unsigned int values_N[] = {10, 1000, 100000};
    
    file << scientific << setprecision(15);

    for (double T : values_T) {
        file << endl << "T = " << T << endl;

        double L = 6.0 * sqrt(T);
        double theory_v = sqrt(T / M_PI);
        double theory_v2 = T / 2.0;

        for (unsigned N : values_N) {
            double dv = 2.0 * L / N;

            double *pdf = new double[N];
            double *psi_v = new double[N];
            double *psi_v2 = new double[N];

            for (unsigned idx = 0; idx < N; ++idx) {
                double v_idx = -L + idx * dv;

                psi_v[idx] = fabs(v_idx);
                pdf[idx] = exp(-(v_idx * v_idx) / T) / sqrt(M_PI * T);
                psi_v2[idx] = v_idx * v_idx;
            }

            double rect_v = rect_integration(psi_v, pdf, dv, N, false);
            double rect_v_fma = rect_integration(psi_v, pdf, dv, N, true);
            double recurs_v = recursive_integration(psi_v, pdf, dv, N);
            double c_recurs_v = circle_recurs(psi_v, pdf, dv, N);
            double kahan_v = Kahan_intefr(psi_v, pdf, dv, N);

            double rect_v2 = rect_integration(psi_v2, pdf, dv, N, false);
            double rect_v2_fma = rect_integration(psi_v2, pdf, dv, N, true);
            double recurs_v2 = recursive_integration(psi_v2, pdf, dv, N);
            double c_recurs_v2 = circle_recurs(psi_v2, pdf, dv, N);
            double kahan_v2 = Kahan_intefr(psi_v2, pdf, dv, N);

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

            delete[] pdf;
            delete[] psi_v;
            delete[] psi_v2;
        }
    }
    file.close();
    return 0;
}