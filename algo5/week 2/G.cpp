#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
// #include <fstream>
using namespace std;

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
        sort(a.begin(), a.end());
        int count = 0;
        int len = n;
        vector<int> l;

        for (int j = 0; j < n;) {
            if (a[j] < len) {
                // cout <<a[j] << ' ';
                count++;
                len -= a[j];
                l.push_back(a[j]);
                j += a[j];  
            } else {
                // cout << len << " количество стр" << ++count << endl;
                count++;
                l.push_back (len);
                j = n;
            }
        }
        cout << count << endl;
        // sort(l.begin(), l.end()); 
        for (auto& el : l) 
            cout << el << ' ';
        cout << endl;
    }


    return 0;
}