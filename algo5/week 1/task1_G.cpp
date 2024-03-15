#include <iostream>
using namespace std;

int try_out(int x, int y, int p, int steps) {
    p -= (x - y);
    x -= p;
    steps += 1;
    // cout << x << ' ' << y << ' ' << p << '\n';

    while (x > 0 && p > 0) {
        p-=x;
        x-=p;
        steps++;
    }
    // cout << x << ' ' << y << ' ' << p << '\n';
    // cout << steps << '\n';

    if (x <= 0) return 5001;
    else return steps; 
}

int tacktic_2(int x, int y, int p, int steps) {
    int min = 5001;
    while (y > 0) {
        if (x >= y) {
            // cout << x << '-' << y << '-' << p << '\n';
            int temp = try_out(x, y, p, steps);
            if (temp < min) min = temp;
        }
        if (p >= x) {
            y=0;
        } else {
            y-=(x-p);
        }
        steps++;
    }
    if (min > 5000) min = -1;
    return min;
}

int main() {
    int x,y,p;
    int steps = 0;
    cin >> x >> y >> p;
    if (x >= y) {
        steps = 1;
        y = 0;
    } else {
        y -= x;
        steps = 1;
        steps = tacktic_2(x,y,p,steps);
    }
    // cout << x << '-' << y << '-' << p << '\n';

    cout << steps << '\n';

    return 0;
}
