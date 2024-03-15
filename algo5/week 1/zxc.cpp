#include <iostream>
#include <sstream>
#include <fstream>
#include <set>
using namespace std;

bool extractDimensions(const std::string& str, int& width, int& height) {
    size_t widthPos = str.find("width=");
    size_t heightPos = str.find("height=");

    if (widthPos == std::string::npos || heightPos == std::string::npos) {
        return false;
    }

    stringstream ssWidth(str.substr(widthPos + 6));
    stringstream ssHeight(str.substr(heightPos + 7));

    ssWidth >> width;
    ssHeight >> height;

    return true;
}

bool isInSurrounded(pair<int, int>& pos, int& w, int& maxW, int& maxH,
     set<pair<pair<int, int>, pair<int, int>>>& coorSurr) {
    // set<pair<pair<int, int>, pair<int, int>>> coordinateSurr;
    pair<int, int> checkMove = pos;

    for (auto el = coorSurr.begin(); el != coorSurr.end(); ++el) {
        if (pos.first >= el->first.first && pos.first <= el->second.first &&
            pos.second >= el->first.second && pos.second <= el->second.second) {
                pos.first = el->second.first + 1;
            } else if (
                pos.first+w >= el->first.first && pos.first+w <= el->second.first &&
            pos.second+maxH >= el->first.second && pos.second+maxH <= el->second.second
            ) {
                pos.first = el->second.first + 1;
            }
        if (pos.first+w > maxW) {
            pos.first = 0;
            pos.second += maxH;
            el = coorSurr.begin();
        }
    }

    if (checkMove != pos) {
        return true;
    } else
        return false;
}

void insertWord(pair<int, int>& pos, int& w, int& h, int& maxW, int&maxH,
    set<pair<pair<int, int>, pair<int, int>>>& cS) {
        if (isInSurrounded(pos, w, maxW, maxH, cS)) {
            pos.first+=w;
        } else if (pos.first == 0) {
            pos.first+=w;
        } else if (pos.first + 1 < maxW) {
            pos.first+=w;
        } else {
            isInSurrounded(pos, w, maxH, maxW, cS);
            pos.first = w;
            pos.second = maxH;
        }
}
void processWord(pair<int, int>& pos, int& len, int& h, int& maxW, int& maxH, int& c,
set<pair<pair<int, int>, pair<int, int>>>& cS) {
    if (pos.first == 0) {
        insertWord(pos, len, h, maxW, maxH, cS);
    } else {
        pos.first+=c;
        insertWord(pos, len, h, maxW, maxH, cS);
    }
    // Обработка слова
    cout << "Слово: \n" << endl;
}

void processExpression(const string& expression, pair<int,int>& pos, int& w, int& h, int& c,
    set<pair<pair<int, int>, pair<int, int>>>& surr
) {
    // Обработка выражения в скобках
    int width, height, dx, dy;
    int layout;
    // set<pair<pair<int, int>, pair<int, int>>> z;
    extractDimensions(expression, width, height);

    cout << "Выражение: " << expression << endl;

    if (expression.find("embedded") != string::npos) {
        if (pos.first == 0) {
            isInSurrounded(pos, width, w, h, surr);
            cout << "embedded - " << pos.first << ' ' << pos.second << endl;
            pos.second+=height;
        } else if (pos.first+width+c < w) {
            pos.first+=c;
            isInSurrounded(pos, width, w, h, surr);
            cout << "embedded - " << pos.first << ' ' << pos.second << endl;
            if (pos.first == 0) {
                pos.second+=height;
            }
        }
        pos.first+=width;
        // cout << "embedded - " << pos.first << ' ' << pos.second << endl;
    } else if (expression.find("surrounded") != string::npos) {
        isInSurrounded(pos, width, w, h, surr);
            // cout << "zxczxc";
        cout << "surrounded - " << pos.first << ' ' << pos.second << endl;
        surr.insert({pos, {pos.first+width, pos.second + height}});
    }
}

void processParagraph(pair<int, int>& pos, const int& h) {
    // Обработка нового абзаца
    cout << "Новый абзац" << endl;
    pos.second +=h;
}

int main() {

    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "Ошибка при открытии файла!" << endl;
        return 1;
    }

    int w,h,c;
    file >> w >> h >> c;
    string dummy;
    getline(file, dummy);

    // Чтение оставшегося содержимого файла
    stringstream buffer;
    // buffer << file.rdbuf();
    string line;

    pair<int, int> currentPosition = {0, 0};
    set<pair<pair<int, int>, pair<int, int>>> surr;
    string temp;
    while (getline(file, line)) {
        if(!line.empty()) {
            temp+=line + ' ';
        } else if (line.empty()) {
            stringstream linestream(temp);
            string token;
            char nextChar;

            while (linestream >> nextChar) {
                // cout << currentPosition.first << ' ' << currentPosition.second << endl;
                if (nextChar == '(') {
                    // Чтение и обработка выражения в скобках
                    getline(linestream, token, ')');
                    processExpression(token, currentPosition, w, h, c, surr);
                } else {
                    // Чтение и обработка слова
                    linestream.putback(nextChar);
                    linestream >> token;
                    cout << token << endl;
                    int len = token.length() * c;
                    processWord(currentPosition, len, h, w, h, c, surr);
                }
            }
            processParagraph(currentPosition, h);
            temp.clear();
            line.clear();
            continue;
        }
    }

    return 0;
}  
