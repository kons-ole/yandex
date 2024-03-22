#include <iostream>
#include <limits>
#include <vector>
#include <map>
using namespace std;

int main () {
    int n, a, b, k;
    cin >> n;
    vector<int> bonus(n, 0);
    // map<int, int> maxdict;

    int max = numeric_limits<int>::min();
    int maxX = numeric_limits<int>::min();
    for (auto i = 0; i != n; ++i) {
        cin >> bonus[i];
        // maxdict.insert(bonus[i], i);
    }
    cin >> a >> b >> k;
    // for (auto i = 0; i < n; ++i) {
    //     // bonus[i]
    //     // (i+1)*k
    //     int start = ((a - 1) / k) % n;
    // }
    int i, j;
    for (i = (a - 1) / k, j = 0; i <= (b-1) / k && j < n; i++, j++) {
        // int sector = ((i-1) / k) % n;
        int sector = i % n;
        // cout << sector << ' ' << n - sector << endl;
        if (sector != 0) {
            if (bonus[sector] > max) max = bonus[sector];
            if (bonus[n - sector] > max) max = bonus[n - sector];
        } else if (bonus[sector] > max) max = bonus[sector];
        // if (max == maxX) break;
    }


    cout << max;

    return 0;
}  