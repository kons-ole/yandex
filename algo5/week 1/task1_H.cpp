#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>
using namespace std;

bool greaterThanZero(double value) {
    const double EPSILON = 1e-10;
    return value > EPSILON;
}

void findMatchTime(int l, int x1, int v1, int x2, int v2) {
    double minT = std::numeric_limits<double>::max();

    for (int i = -2; i <= 2; ++i) {
        double t1 = static_cast<double>(x1 - x2 + l * i) / (v2 - v1);
        double t2 = static_cast<double>(x1 + x2 + l * i) / (-v1 - v2);
        if (greaterThanZero(t1)) {
            minT = min(minT, t1);
        }
        if (greaterThanZero(t2)) {
            minT = min(minT, t2);
        }
        // std::cout << std::fixed << std::setprecision(9) << t1 << endl << t2 << endl;
    }
    cout << "YES" << endl;
    cout << std::fixed << std::setprecision(9) << minT << endl;
}
//2.407592338
//615143346 79387687 -80123649 306422480 -80123649

//0.2859497397634569 2
//948744004 861724643 848773505 584154450 730556189
int main() {
    int l,x1,v1,x2,v2;

    cin >> l >> x1 >> v1 >> x2 >> v2;
    if (x1 == x2 || l - x1 == x2 || l - x2 == x1){
        cout << "YES" << endl;
        cout << std::fixed << std::setprecision(9) << 0.0 << endl;
    } else if (abs(v1)+abs(v2) == 0) cout << "NO" << endl;
    else {
        findMatchTime(l, x1, v1, x2, v2);
    }

    return 0;
}