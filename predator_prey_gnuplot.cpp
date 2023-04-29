#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

#include <math.h>

#define GNUPLOT_LSA "C:\\gnuplot\\bin\\gnuplot -perist"

using namespace std;

int main() {
    FILE* pipe = _popen(GNUPLOT_LSA, "w");
    double v0, k0, alpha1, betta1, alpha2, betta2, T, N;
    cin >> v0 >> k0 >> alpha1 >> betta1 >> alpha2 >> betta2 >> T >> N;
    fprintf(pipe, "%s\n", "set multiplot");
    double delta = T / N;
    fprintf(pipe, "%s %d %s\n", "set xrange [0:", (int) T+5, "]");
    fprintf(pipe, "%s %d %s\n", "set yrange [0:", (int) (v0 + k0), "]");
    double i_fill = 0;
    vector<double> t;
    while (i_fill <= T) {
        t.push_back(i_fill);
        i_fill += delta;
    }
    double v_stab = alpha2 / betta2;
    double k_stab = alpha1 / betta1;
    vector<double> v = *new vector<double>(t.size());
    vector<double> k = *new vector<double>(t.size());
    for (int i = 0; i < t.size(); ++i) {
        v[i] = (v0 - v_stab) * cos(sqrt(alpha1 * alpha2) * t[i])
               - (k0 - k_stab) * (sqrt(alpha2 / alpha1) * betta1 / betta2) * sin(sqrt(alpha1 * alpha2) * t[i])
               + v_stab;
        k[i] = (v0 - v_stab) * (sqrt(alpha1 / alpha2) * betta2 / betta1) * sin(sqrt(alpha1 * alpha2) * t[i])
               + (k0 - k_stab) * cos(sqrt(alpha1 * alpha2) * t[i])
               + k_stab;
    }
    cout << "t:" << endl;
    for (double i : t) {
        cout << fixed << setprecision(2) << i << " ";
    }
    cout << endl << "v:" << endl;
    for (double i : v) {
        cout << fixed << setprecision(2) << i << " ";
    }
    cout << endl << "k:" << endl;
    for (double i : k) {
        cout << fixed << setprecision(2) << i << " ";
    }
    fprintf(pipe, "%s\n", "plot '-' using 1:2 title 'victims' with points pointtype 6 linecolor 'blue', \
                        '-' using 1:2 title 'killers' with points pointtype 6 linecolor 'red'");
    for (int i = 0; i < N+1; ++i) {
        fprintf(pipe, "%lf %lf\n", t[i], v[i]);
    }
    fprintf(pipe, "%s\n", "e");
    for (int i = 0; i < N+1; ++i) {
        fprintf(pipe, "%lf %lf\n", t[i], k[i]);
    }
    fprintf(pipe, "%s\n", "e");

    //
    fprintf(pipe, "%s\n", "e");
    fprintf(pipe, "%s\n", "unset multiplot");
    fflush(pipe);
    _pclose(pipe);
    return 0;
}
