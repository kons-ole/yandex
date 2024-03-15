#include <iostream>
using namespace std;

int main() {
    long long n,k,d;
    cin >> n >> k >> d;

    if (n%k == 0) {
        cout << n;
        for (int i = 0; i != d; ++i) cout << 0;
    } else {
        n*=10;
        for (int i = 0; i != 9; i++) {
            if (n%k == 0) break;
            n++;
        }

        if (n%k == 0) {
            cout << n;
            for (int i = 0; i != d - 1; ++i) cout << 0;
        } else {
            cout << -1;
        }
    }

    return 0;
}