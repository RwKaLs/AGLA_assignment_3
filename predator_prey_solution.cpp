#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    double v0, k0, alpha1, betta1, alpha2, betta2, T, N;
    cin >> v0 >> k0 >> alpha1 >> betta1 >> alpha2 >> betta2 >> T >> N;
    double delta = T / N;
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
    return 0;
}
