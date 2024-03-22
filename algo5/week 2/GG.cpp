#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;
        // if (xf == xt) {
        //     x = xs;
        //     y = yf;
        // } else if (xs == xt) {
        //     x = xf;
        //     y = ys;
        // } else if (yf == yt) {
        //     x = xf;
        //     y = ys;
        // } else if (ys == yt) {
        //     x = xs;
        //     y = yf;

        // }

int main () {
    //     ifstream file("input.txt");
    // if (!file.is_open()) {
    //     cerr << "Ошибка при открытии файла!" << endl;
    //     return 1;
    // }
    int t;

    cin >> t;
    for (int i=0; i<t;++i) {
        int n;
        cin >> n;
        vector<int> a(n,0);
        for (int j = 0; j<n;++j){
            cin >> a[j];
        }
        // sort(a.begin(), a.end());
        int count = 0;
        int len = 0;
        vector<int> l;
        int min = numeric_limits<int>::max();
        for (int j = 0; j < n; j++) {
            len++;
            if (a[j] < min) min = a[j];
            if (min == len) {
                l.push_back(len);
                min = numeric_limits<int>::max();
                count++;
                len = 0;
            } else if (min < len) {
                l.push_back(len-1);
                len = 0;
                count++;
                j--;
            }
            if (j + 1 == n && len > 0) {
                l.push_back(len);
                count++;
            }
            // if (a[j] < len) {
            //     // cout <<a[j] << ' ';
            //     count++;
            //     len -= a[j];
            //     l.push_back(a[j]);
            //     j += a[j];  
            // } else {
            //     // cout << len << " количество стр" << ++count << endl;
            //     count++;
            //     l.push_back (len);
            //     j = n;
            // }
        }
        cout << count << endl;
        // sort(l.begin(), l.end()); 
        for (auto& el : l) 
            cout << el << ' ';
        cout << endl;
    }


    return 0;
}