#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<pair<int, int>> ships(N);
    vector<int> rows(N+1,0);
    for (int i = 0; i < N; ++i) {
        cin >> ships[i].first >> ships[i].second;
        if(rows[ships[i].first] == 0) {
            rows[ships[i].first] = 1;
            ships[i].first = 0;
        }
    }
    int min_moves = INT_MAX;
    int current_row_moves = 0;
    for (int col = 1; col <= N; ++col) {
        int current_moves = 0;
        int min_row_moves = N + 1;
        int min_row_moves_right = N + 1;
        int row_right = -1;
        int min_row = col;
        int i_reminder = -1;
        int i_reminder_r = -1;
        for (int i = 0; i < N; ++i) {
            current_moves += abs(ships[i].second - col);
            if (rows[col] == 0 && ships[i].first > 0) {
                if (ships[i].first <= min_row) {
                    min_row_moves = abs(ships[i].first - col);
                    min_row = ships[i].first;
                    i_reminder = i;
                } else if (abs(ships[i].first - col) <= min_row_moves_right) {
                    min_row_moves_right = abs(ships[i].first - col);
                    i_reminder_r = i;
                }
            }
        }
        // cout << ships[i_reminder].first << ' ' << min_row_moves <<" act row " << col << endl;
        if (i_reminder > -1) {
            ships[i_reminder].first = -1;
            current_row_moves += min_row_moves;
        } else if (i_reminder_r > -1) {
            ships[i_reminder_r].first = -1;
            current_row_moves += min_row_moves_right;
        }
        min_moves = min(min_moves, current_moves);
    }



    cout << min_moves + current_row_moves << endl;
    // cout << current_row_moves << endl;
    // cout << min_moves << endl;
    return 0;
}
