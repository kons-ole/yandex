#include <iostream>
#include <limits>
#include <vector>
using namespace std;

int main () {
    int N, x, y;
    cin >> N;
    int perimetr = 0;
    vector<vector<int>> field(8,vector<int>(8, 0));

    for (auto i = 0; i != N; ++i) {
        cin >> x >> y;
        field[x-1][y-1]++;
    }
    for (int i = 0; i != 8; ++i) {
        for (int j = 0; j != 8; ++j) {
            if (field[i][j] == 1) {
                if (i - 1 < 0) perimetr++;
                else if (field[i-1][j] != 1) perimetr++;
                if (j - 1 < 0) perimetr++;
                else if (field[i][j-1] != 1) perimetr++;
                if (i + 1 >=8) perimetr++;
                else if (field[i+1][j] != 1) perimetr++;
                if (j + 1 >=8) perimetr++;
                else if (field[i][j+1] != 1) perimetr++;
            }
        }
    }

    cout << perimetr; 

    return 0;
}