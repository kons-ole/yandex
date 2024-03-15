#include <iostream>
#include <vector>
using namespace std;

//  int findAttackRange(char fig, int x, int y, vector<vector<char>>& table) {
//     int count = 1;
//     bool flag1 = true;
//     bool flag2 = true;
//     bool flag3 = true;
//     bool flag4 = true;

//     if (fig == 'B') {
//         for (int i = 1; i != 8; ++i) {
//             if (x + i < 8 && y + i < 8 && flag1) {
//                 if (table[x+i][y+i] == '*'){
//                     count++;
//                     table[x+i][y+i] = '#';
//                 } else if (table[x+i][y+i] != '#') flag1 = false;
//             }
//             if (x - i >= 0 && y - i >= 0 && flag2) {
//                 if (table[x-i][y-i] == '*'){
//                     count++;
//                     table[x-i][y-i] = '#';
//                 } else if (table[x-i][y-i] != '#') flag2 = false;
//             }
//             if (x - i >= 0 && y + i < 8 && flag3) {
//                 if (table[x-i][y+i] == '*'){
//                     count++;
//                     table[x-i][y+i] = '#';
//                 } else if (table[x-i][y+i] != '#') flag3 = false;
//             }
//             if (x + i < 8 && y - i >= 0 && flag4) {
//                 if (table[x+i][y-i] == '*'){
//                     count++;
//                     table[x+i][y-i] = '#';
//                 } else if (table[x+i][y-i] != '#') flag4 = false;
//             }
//         }
//     } else if (fig == 'R') {
//         for (int i = 1; i != 8; ++i) {
//             if (x + i < 8 && flag1) {
//                 if (table[x+i][y] == '*') {
//                     count++;
//                     table[x+i][y] = '#';
//                 } else if (table[x+i][y] != '#') flag1 = false;
//             }
//             if (y + i < 8 && flag2) {
//                 if (table[x][y+i] == '*') {
//                     count++;
//                     table[x][y+i] = '#';
//                 } else if (table[x][y+i] != '#') flag2 = false;
//             }
//             if (x - i >= 0 && flag3) {
//                 if (table[x-i][y] == '*') {
//                     count++;
//                     table[x-i][y] = '#';
//                 } else if (table[x-i][y] != '#') flag3 = false;
//             }
//             if (y - i >= 0 && flag4) {
//                 if (table[x][y-i] == '*') {
//                     count++;
//                     table[x][y-i] = '#';
//                 } else if (table[x][y-i] != '#') flag4 = false;
//             }
//         }
//     }

//     return count;
// }

constexpr int BOARD_SIZE = 8;

int findAttackRange(char fig, int x, int y, vector<vector<char>>& table) {
    int count = 1;
    bool flags[4] = {true, true, true, true}; // Флаги для каждого направления

    for (int i = 1; i < BOARD_SIZE; ++i) {
        int dx[4] = {i, -i, -i, i};
        int dy[4] = {i, i, -i, -i};

        for (int d = 0; d < 4; ++d) {
            int newX = x + dx[d];
            int newY = y + dy[d];

            if (newX >= 0 && newX < BOARD_SIZE && newY >= 0 && newY < BOARD_SIZE && flags[d]) {
                if (table[newX][newY] == '*') {
                    count++;
                    table[newX][newY] = '#';
                } else if (table[newX][newY] != '#') {
                    flags[d] = false;
                }
            }
        }
    }

    return count;
}
int main() {
    int n, a;
    long long sum = 64;
    vector<vector<char>> chess(8, vector<char>(8,'*')); 
    for (int i = 0; i != 8; ++i) {
        for (int j = 0; j != 8; ++j) {
            cin >> chess[i][j];
        }
    }

    for (int i = 0; i != 8; ++i) {
        for (int j = 0; j != 8; ++j) {
            if (chess[i][j] == 'B' || chess[i][j] == 'R')
                sum-= findAttackRange(chess[i][j], i, j, chess);
        }
    }

    cout << sum;

    return 0;
}
