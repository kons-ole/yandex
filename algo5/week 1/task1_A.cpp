#include <iostream>

using namespace std;
int main() {
    int p, v, q, m;
    int p_l, q_l; // крайнее левое значения координат
    cin >> p >> v;
    cin >> q >> m;

    if (p < q) {  // меняем местами чтобы p всегда находилось справа

        p = p + q;
        q = p - q;
        p = p - q;
        v = v + m;
        m = v - m;
        v = v - m;
    } else if (p == q && v > m) {
        v = v + m;
        m = v - m;
        v = v - m;
    } 

    int sum = 0;
    p_l = p - v;
    q_l = q - m;

    int sum_q = q_l+2*m - p_l; // можно назвать разностью векторов

    if (sum_q > 2 * v) { 
        sum = m*2 + 1;
    } else if (sum_q >= 0) {
        sum = v*2+1 + m*2+1 - sum_q - 1;
    } else {
        sum = v*2+1 + m*2+1;
    }

    cout << sum;

    return 0;
}