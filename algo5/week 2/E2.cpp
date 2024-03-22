#include <iostream>
#include <limits>
#include <vector>
#include <set>
#include <fstream>
using namespace std;

int main () {
        ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "Ошибка при открытии файла!" << endl;
        return 1;
    }

    int n;
    file >> n;
    vector<pair<int, int>> b (n, {0 , 0});
    int maxDescent = numeric_limits<int>::min();
    int maxAscent = numeric_limits<int>::min();
    int descentPos = -1;
    int ascentPos = -1;
    long long maxHeight = 0;
    set<int> ascentElems;
    set<int> descentElems;

    for (int i = 0; i != n; ++i) {
        // cout << maxHeight << endl;
        file >> b[i].first >> b[i].second;
        // cout << b[i].first << ' ' << b[i].second << endl;
        if (b[i].first - b[i].second > 0 && b[i].second > maxDescent) {
            // cout << "hello";
            if (descentPos != -1) {
                ascentElems.insert(descentPos);
                maxHeight+= b[descentPos].first - b[descentPos].second;
            }
            maxDescent = b[i].second;
            descentPos = i;
        } else if (b[i].first - b[i].second <= 0 && b[i].first > maxAscent) {
            if (ascentPos != -1) {
                descentElems.insert(ascentPos);
            }
            maxAscent = b[i].first;
            ascentPos = i;
        } else if (b[i].first - b[i].second >= 0) {
            ascentElems.insert(i);
            maxHeight+=b[i].first - b[i].second;
        } else {
            descentElems.insert(i);
        }
    }
        
    // cout << maxHeight << " maxHeight\n";
    int peack;
    if (descentPos != -1) {
        maxHeight += b[descentPos].first;
    }
    if (maxDescent < maxAscent) {
        // cout << b[descentPos].first << ' ' <<  b[descentPos].second <<' '<< maxAscent << endl;
        if (descentPos != -1) {
            maxHeight = maxHeight - b[descentPos].second + maxAscent;
            ascentElems.insert(descentPos);
        } else {
        maxHeight = maxHeight + maxAscent;
        }
        peack = ascentPos;
    } else {
        peack = descentPos;
        if (ascentPos != -1)
            descentElems.insert(ascentPos);
    }

    cout << maxHeight << endl;
    
    for(auto& el : ascentElems) {
        cout<< el+1 <<' ';
    }
    cout << peack + 1 << ' ';
    // // cout << endl;
    for(auto& el : descentElems) {
        cout << el+1 <<' ';
    }
    // cout << maxHeight << endl;
    // cout << peack + 1 << ' ';
    // cout << b[peack].first;

    return 0;
}
