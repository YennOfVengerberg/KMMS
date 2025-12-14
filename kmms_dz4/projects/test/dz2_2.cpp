#include <iostream>
#include <random>
#include <vector>
using namespace std;

int count_in_range(const vector<int> &frequencies, int l, int r) {
    if ( l == 0) {
        return frequencies[r];
    }
    return frequencies[r] - frequencies[l-1];
}

int main() {
    int n, q, k;
    cout << " введите длину, макс число и кол-во запросов ";
    cin >> n >> k >> q; // n Длина k лимит чисел q количество запросов
    vector<int> vec(n);
    mt19937 mt(time(nullptr));
    for (int i = 0; i < n; i++) vec[i] = mt() % (k-1);

    vector<int> frequencies(k+1, 0);
    for(auto &iter : vec) {
        frequencies[iter]++;
    }

    vector<int> prefix_sum(k+1, 0);
    for(int i = 1; i <= k; i++) { 
        prefix_sum[i] = prefix_sum[i-1] + frequencies[i];
    }

    for(; q > 0; q--) {
        int l, r;
        cout << " set range l to r " << endl; // отрезок
        cin >> l >> r;
        int prefix_size = prefix_sum.size();
        cout << endl << count_in_range(prefix_sum, min(prefix_size-1, max(l, 0)), min(prefix_size-1, max(r, 0)));
    }
}