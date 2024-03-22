#include <iostream>
#include <limits>
using namespace std;

int main () {
    int K;
    int maxX = std::numeric_limits<int>::min();
    int maxY = std::numeric_limits<int>::min();
    int minX = std::numeric_limits<int>::max();
    int minY = std::numeric_limits<int>::max();
    cin >> K;
    for (auto i = 0; i != K; ++i) {
        int x, y;
        cin >> x >> y;
        if (x > maxX) maxX = x;
        if (y > maxY) maxY = y;
        if (x < minX) minX = x;
        if (y < minY) minY = y;
    }

    cout << minX << ' ' << minY << ' ' << maxX << ' ' << maxY;

    return 0;
}