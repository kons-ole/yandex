#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main() {
    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "Ошибка при открытии файла!" << endl;
        return 1;
    }
    int m, n;
    int countDraw = 0;
    file >> m >> n;
    vector<string> grid(m+2, string(n+2, '.'));
    string line;
    for (int i = 1; i <= m; ++i) {
            file >> line;
            line = '.' + line + '.';
            grid[i] = line;
        for (int j = 1; j <= n; ++j) {
            if (grid[i][j] == '#') countDraw++;
        }
    }

    // Координаты прямоугольников (x1, y1, x2, y2)
    int xl = n + 2, xr = n + 2, yu, yd = m+1;
    int startXa = -1, startYa = -1; 
    int finXa = -1, finYa = -1; 
    bool second = false;
    char color = 'a';
    int countB = 0;
    int countA = 0;
    for (int i = 1; i <= m+1; ++i) {
        for (int j = 1; j <= n+1; ++j) {
            if (grid[i][j] == '#' && startXa == -1) {
                startXa = j;
                startYa = i;
            } else if (grid[i][j] == '.' && startXa > -1 && finXa == -1) {
                // cout << "hello";
                // cout << xr << ' ' << yd-1 << endl;
                if (color == 'b') {
                    cout << startXa << ' ' << j-1 << ' ' << startYa << '|';
                    if (startYa >= yu && startYa <= yd-1 && startXa >=xr && j-1 <= xl) {
                        if (j-1 > xr && grid[yd-1][j-1] != '.') {
                            cout << startXa << ' ' << finXa << ' ' << finYa << '|';
                            finXa = j-1;
                            finYa = i;
                            j = startXa;
                        } else {
                            finXa = xl-1;
                            finYa = i;
                            j = startXa;
                            cout << startXa << ' ' << finXa << ' ' << finYa << '|';
                        }
                } else {
                    finXa = j-1;
                    finYa = i;
                    j = startXa;
                }
                } else {
                finXa = j-1;
                finYa = i;
                j = startXa;
            cout << startXa << ' ' << finXa << ' ' << finYa << '|';
                }
            }
            // cout << startXa << ' ' << finXa << '|';
            if (startXa != -1 && finXa != -1) {
                if (grid[i][j] != '.' && j >= startXa && j <= finXa) {
                    if (grid[i][j] != 'a') countDraw--;
                    grid[i][j] = color;
                    if (color=='b') countB++;
                    else countA++;
                } else if (grid[i][j] == '.' && j >= startXa && j <= finXa) {
                    // color = 'b';
                    // if (color == 'a') {
                        for (int jj = startXa; jj <=finXa; ++jj) {
                            if (grid[i][jj] == 'a' || grid[i][jj] == 'b') {
                            // if (grid[i][jj] == color) {
                                grid[i][jj] = '#';
                                countDraw++;
                            }
                        }

                    // } 
                    // else if (j != startXa){


                    // }
                    if (color == 'b') {
                        i = m+2;
                        j = n+2;
                    } else {
                        xl = startXa;
                        xr = finXa;
                        yu = startYa;
                        yd = i;
                        color = 'b';
                        startXa =-1;
                        startYa =-1;
                        finXa =-1;
                        i = 1;
                        j = 1;
                    }
                }
            }
        }
    }

    // cout << yu << ' ' << yd << endl;
    // cout << countDraw << endl;
    if (countDraw != 0) {
        cout << "NO" << endl;
        // return 0;
    }
    if (countB == 0) {
        if (countA <= 1) {
            cout << "NO" << endl;
            // return 0;
        } else if (yu+1 == yd) {
            grid[yu][xr] = 'b';
        } else {
            for (int i = xl; i <=xr; i++) {
                grid[yu][i] = 'b';
            }
        }
    }
    cout << "YES" << endl;
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            cout << grid[i][j];
        }
        cout << endl;
    }
    // cout << countDraw;

    return 0;
}
