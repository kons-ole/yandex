#include <iostream>
using namespace std;

int main() {
    int n, a;
    long long sum = 0;

    cin >> n;

    for (int i = 0; i != n; ++i) {
        cin >> a;
        sum += a / 4;
        a%=4;
        if (a == 3) {
            sum += 2;
        } else sum+=a;
    }

    cout << sum;

    return 0;
}