#include <iostream>
#include <limits>
#include <vector>
using namespace std;

int main () {
    int N, l;
    cin >> N;
    int sum = 0;
    int max = numeric_limits<int>::min();
    int line;
    for (auto i = 0; i != N; ++i) {
        cin >> l;
        if (l > max) max = l;
        sum += l;
    }
    sum-=max;
    if (sum == max) line = max*2;
    else if (sum < max) line = max - sum;
    else line = sum + max;

    cout << line;

    return 0;
}