#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

int daysInYear(int year) {
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        return 366;
    } else {
        return 365;
    }
}

int dayOfYear(int day, const string& month, int year) {
    vector<pair<string, int>> months = {
        {"January", 31}, {"February", 28}, {"March", 31},
        {"April", 30}, {"May", 31}, {"June", 30},
        {"July", 31}, {"August", 31}, {"September", 30},
        {"October", 31}, {"November", 30}, {"December", 31}
    };

    if (daysInYear(year) == 366) {
        months[1].second = 29;
    }

    int dayNum = 0;
    for (const auto& m : months) {
        if (m.first == month) {
            dayNum += day;
            break;
        }
        dayNum += m.second;
    }

    return dayNum;
}



int main() {

    map<string, int> weekToInt = {
        {"Monday", 0},
        {"Tuesday", 1}, 
        {"Wednesday", 2}, 
        {"Thursday", 3}, 
        {"Friday", 4}, 
        {"Saturday", 5}, 
        {"Sunday", 6}
    };
    map<int, int> weekdays = {
        {0, 52},
        {1, 52},
        {2, 52},
        {3, 52},
        {4, 52},
        {5, 52},
        {6, 52}
        };

    map<int, string> weekdaysStr = {
        {0, "Monday"},
        {1, "Tuesday"},
        {2, "Wednesday"},
        {3, "Thursday"},
        {4, "Friday"},
        {5, "Saturday"},
        {6, "Sunday"}
    };

    int n, year, day;
    string month;
    string day_of_week;
    cin >> n;
    cin >> year;
    vector<int> holidays;

    for (int i = 0; i != n; ++i) {
        cin >> day >> month;
        holidays.push_back(dayOfYear(day, month, year));
    }
    cin >> day_of_week;

    weekdays[(weekToInt[day_of_week]+7)%7]++;
    if (daysInYear(year) == 366){
        weekdays[(weekToInt[day_of_week]+8)%7]++;
    }

    for (auto& d : holidays) {
        int weekDay = (d + weekToInt[day_of_week] - 1) % 7;
        weekdays[weekDay]--;
    }

    auto minElement = min_element(weekdays.begin(), weekdays.end(),
     [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.second < b.second;
        });

    auto maxElement = max_element(weekdays.begin(), weekdays.end(),
        [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.second < b.second;
        });

    string maxday = weekdaysStr[maxElement->first];
    string minday = weekdaysStr[minElement->first];

    for (const auto& pair : weekdays) {
        std::cout << "день недели: " << pair.first << ", Значение: " << pair.second << std::endl;
    }
    std::cout << maxday << ' ' << minday << endl;

    return 0;
}
