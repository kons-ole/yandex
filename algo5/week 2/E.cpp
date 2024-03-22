#include <iostream>
#include <limits>
#include <vector>
#include <set>
using namespace std;

int main () {
    int n;
    cin >> n;
    long long maxHeight = 0;
    int max = numeric_limits<int>::min();
    int minDif = numeric_limits<int>::min();
    int minMax = numeric_limits<int>::min();
    int maxIndex = -1;
    int minIndex = -1;
    set<int> plusIndex;
    set<int> minusIndex;
    pair<int, int> maxPair;
    vector<pair<int, int>> b(n, pair<int, int>{0, 0});
    
    for (auto i = 0; i != n; ++i) {
        cin >> b[i].first >> b[i].second;
        if (b[i].first - b[i].second > 0) {
            if (b[i].first > max) {
                if (maxIndex >= 0) {
                    maxHeight+=minDif;
                    plusIndex.insert(maxIndex);
                }
                max = b[i].first;
                maxIndex = i;
                minDif = b[i].first - b[i].second;
            } else if (b[i].first == max && b[i].first - b[i].second < minDif) {
                if (maxHeight >= 0) {
                    maxHeight+=minDif;
                    plusIndex.insert(maxIndex);
                }
                // plusIndex.insert(maxIndex);
                minDif = b[i].first - b[i].second;
                maxIndex = i;
            } else { 
                plusIndex.insert(i);
                maxHeight+= b[i].first - b[i].second;
            }
        } else {
            if (b[i].first > minMax) {
                if (minIndex >=0){
                    minusIndex.insert(minIndex);
                }
                minMax = b[i].first;
                minIndex = i;
            } else if (minIndex >=0) {
                minusIndex.insert(i);
            }
        }
    }
    if (max > 0) {
        maxHeight+=max;
    }
    if (minMax > 0 && minMax > b[maxIndex].second) {
        maxHeight+=minMax - b[maxIndex].second;
        plusIndex.insert(maxIndex);
        maxIndex = minIndex;
    } else {
        minusIndex.insert(minIndex);
    }

    cout << maxHeight << endl;
    for(auto& el : plusIndex){
        cout<< el+1 <<' ';
    }
    cout << maxIndex+1 << ' ';
    cout << endl;
    for(auto& el : minusIndex){
        cout << el+1 <<' ';
    }

    return 0;
}