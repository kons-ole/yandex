#include <iostream>
using namespace std;

int main() {
    int n;
    long long a = 0;
    long long first = 0;
    bool zero = false;
    bool even = false;
    bool odd = false;
    cin >> n;
    cin >> first;
    if (first == 0) zero = true;
    if (first%2 == 0) even = true;
    else odd = true;

    for (int i = 1; i != n; ++i) {
        cin >> a;
        if (a%2 == 0) {
            if (even) {
                cout << '+';
            } else {
                cout << '+';
            }
        } else {
            if (even) {
                cout << '+';
            } else {
                cout << 'x';
            }
            even = false;
        }
    }

    return 0;
}