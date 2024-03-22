#include <iostream>
#include <limits>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

int main () {
    // clock_t start_time = clock();
    //     ifstream file("input.txt");
    // if (!file.is_open()) {
    //     cerr << "Ошибка при открытии файла!" << endl;
    //     return 1;
    // }
    int n, m;
    // int max = std::numeric_limits<int>::min();
    int xf,yf, xs, ys, xt, yt, x, y;
    int firstMax = std::numeric_limits<int>::min();
    int secondMax = std::numeric_limits<int>::min();
    int thirdMax = std::numeric_limits<int>::min();
    cin >> n >> m;
    vector<vector<int>> v(n, vector<int>(m,0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> v[i][j];
            if (v[i][j] >= firstMax) {
                secondMax = firstMax;
                xs = xf;
                ys = yf;
                firstMax = v[i][j];
                xf=j;
                yf=i;
            } else if(v[i][j] > secondMax) {
                secondMax =v[i][j];
                xs = j;
                ys = i;
            }
        }
    }

    // cout << yf << ' ' << xf << ' ' << ys << ' ' << xs << endl;
    v[yf][xf] = -1;
    v[ys][xs] = -1;
    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j < m; ++j) {
    //         if (v[i][j] > secondMax) {
    //             secondMax = v[i][j];
    //             ys = i;
    //             xs = j;
    //         }
    //     }
    // }
    // v[ys][xs] = -1;

    if (xf == xs) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (j != xs) {
                    if (v[i][j] > thirdMax) {
                        thirdMax = v[i][j];
                        xt = j;
                        yt = i;
                    }
                }
            }
        }
        x=xs;
        y=yt;
    } else if (yf == ys) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (i != ys) {
                    if (v[i][j] > thirdMax) {
                        thirdMax = v[i][j];
                        xt = j;
                        yt = i;
                    }
                }
            }
        }
        x = xt;
        y = ys;
    } else {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (i == ys || i == yf || j == xs || j == xf) {
                    if (v[i][j] >= thirdMax) {
                        thirdMax = v[i][j];
                        yt = i;
                        xt = j;
                    }
                }
            }
        }
    // cout << yt << ' ' << xt << endl;
        if (xf == xt) {
            x = xt;
            y = ys;
        } else if (xs == xt) {
            x = xt;
            y = yf;
        } else if (yf == yt) {
            x = xs;
            y = yt;
        } else if (ys == yt) {
            x = xf;
            y = yt;

        }
    }

    // cout << y << ' ' << x << endl;
    cout << y+1 << ' ' << x+1 << endl;
    // cout << xf << ' ' <<yf << endl;
    // cout << xs << ' ' <<ys << endl;
    // clock_t end_time = clock();
    // cout << xt << ' ' <<yt << endl;
    // clock_t elapsed_time = end_time - start_time;
    // cout << "Время выполнения: " << static_cast<float>(elapsed_time) / CLOCKS_PER_SEC << " секунд" << endl;

    // for (int i = 0; i < m; i++) {
    //     if (v[y][i] > max) {
    //         max = v[y][i];
    //         secDim = y;
    //     }
    // }




    // if (secDim == x) cout << y << ' ' << secDim;
    // else cout << secDim << ' ' << x;

    // cout << max;

    return 0;
}