#include <iostream>
#include <limits>
#include <vector>
using namespace std;

int main () {
    int N, K;
    cin >> N >> K;
    vector<int> price(N,0);
    for (auto i = 0; i != N; ++i) {
        cin >> price[i];
    }
    int min = numeric_limits<int>::max();
    int max = numeric_limits<int>::min();
    int mini, maxi;
    int profit = 0;

    for (auto i = 0; i < N; i++) {
        for (auto j = i; j < i + K + 1 && j < N; ++j) {
            if (price[j] - price[i] > profit) profit = price[j] - price[i];
        }
    }
    if (profit > 0)
        cout << profit;
    else cout << 0;

    return 0;
}