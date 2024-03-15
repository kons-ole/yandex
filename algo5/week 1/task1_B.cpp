#include <iostream>

using namespace std;
int main() {
    int a1, b1, a2, b2, home;
    char c;
    cin >> a1 >> c >> b1;
    cin >> a2 >> c >> b2;
    cin >> home;

    if (a1 + a2 > b1 + b2) {
        cout << 0;
    } else if (a1 + a2 == b1 + b2) {
        if (home == 1) {
            if (b1 >= a2) {
                cout << 1;
            } else {
                cout << 0;
            }
        } else {
            if (b2 >= a1) {
                cout << 1;
            } else {
                cout << 0;
            }
        }
    } else {
        int goals_need = b1 + b2 - a1 - a2;
        if (home == 1) {
            if (a2 + goals_need > b1)
                cout << goals_need;
            else {                                
                cout << goals_need + 1;
            }
        } else {
            if (a1 > b2)
                cout << goals_need;
            else
                cout << goals_need + 1;
        }
    }

    return 0;
}