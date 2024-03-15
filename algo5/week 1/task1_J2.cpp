#include <iostream>
#include <sstream>
#include <fstream>
#include <set>
#include <string>
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
bool extractFloatXY(const std::string& str, int& dx, int& dy) {
    size_t dxPos = str.find("dx=");
    size_t dyPos = str.find("dy=");

    if (dxPos == std::string::npos || dyPos == std::string::npos) {
        return false;
    }

    stringstream ssdx(str.substr(dxPos + 3));
    stringstream ssdy(str.substr(dyPos + 3));

    ssdx >> dx;
    ssdy >> dy;

    return true;
}

bool isInSurrounded(pair<int, int>& pos, int& w, int& maxW, int& maxH, int& curH,
     set<pair<pair<int, int>, pair<int, int>>>& coorSurr) {
    pair<int, int> checkMove = pos;

    // cout << "input: " << pos.first << ' ' << pos.second << endl;
    for (auto el = coorSurr.begin(); el != coorSurr.end();) {
    // cout << "input after: " << pos.first << ' ' << pos.second << endl;
    // cout << "sur: " << el->first.first << ' ' << el->first.second << ' ' << "sur: " << el->second.first << ' ' << el->second.second << endl;

        if (pos.first >= el->first.first && pos.first <= el->second.first &&
            pos.second >= el->first.second && pos.second <= el->second.second) {
                pos.first = el->second.first + 1;
            } else if (
                (pos.first+w-1 >= el->first.first && pos.first <= el->second.first) &&
            ((pos.second >= el->first.second && pos.second <= el->second.second)
            //  || (pos.second >= el->first.second && pos.second >= el->second.second) || 
            // (pos.second <= el->first.second && pos.second <= el->second.second)
            )
            ) {
                // cout << "cdvig" << pos.first << ' ' << pos.second << endl;
                pos.first = el->second.first + 1;
            }
        if (pos.first+w > maxW) {
            pos.first = 0;
            pos.second += curH;
            curH = maxH;
            el = coorSurr.begin();
    // cout << "input after: " << maxW << ' ' << pos.first << ' ' << pos.second << endl;
        } else {
            el++;
        }
    }

    if (checkMove != pos) {
        return true;
    } else
        return false;
}

void insertWord(pair<int, int>& pos, int& w, int& h, int& maxW, int&maxH, int& curH,
    set<pair<pair<int, int>, pair<int, int>>>& cS) {
        if (isInSurrounded(pos, w, maxW, maxH, curH, cS)) {
            pos.first+=w;
        } else if (pos.first == 0) {
            pos.first+=w;
        } else if (pos.first + 1 < maxW) {
            pos.first+=w;
        } else {
            isInSurrounded(pos, w, maxW, maxH, curH, cS);
            pos.first = w;
            pos.second += curH;
            curH = maxH;
        }
}
void processWord(pair<int, int>& pos, int& len, int& h, int& maxW, int& maxH, int& c, int& curH,
    bool& isFloat,
set<pair<pair<int, int>, pair<int, int>>>& cS) {
    // cout << "word :" << pos.first << ' ' << pos.second << endl;
        pair<int,int> temp ={pos.first-1,pos.second};
        int hh = curH;
    if (pos.first == 0) {
        insertWord(pos, len, h, maxW, maxH, curH, cS);
    } else if (pos.first + c + len <= maxW) {
        if(!isInSurrounded(temp, len, maxW, maxH, hh, cS)) {
            pos.first+=c;
        }
        // pos.first+=c;
        insertWord(pos, len, h, maxW, maxH, curH, cS);
    } else if (pos.first + len <= maxW && isInSurrounded(temp, len, maxW, maxH, hh, cS)) {
        insertWord(pos, len, h, maxW, maxH, curH, cS);
    } else {
        pos.first = 0;
        pos.second+=curH;
        curH = maxH;
        insertWord(pos, len, h, maxW, maxH, curH, cS);
    }
    isFloat = false;
}

void processExpression(const string& expression, pair<int,int>& pos, int& w, int& h, int& c, int& curH,
    pair<int, int>& floatPos, bool& isFloat,
    set<pair<pair<int, int>, pair<int, int>>>& surr
) {
    int width, height, dx, dy;
    int layout;
    extractDimensions(expression, width, height);


    if (expression.find("embedded") != string::npos) {

        // isInSurrounded(pos, width, w, h, curH, surr);
            // cout << "zxc: " << pos.first << ' ' << pos.second << endl;
        pair<int,int> temp ={pos.first-1,pos.second};
        int hh = curH;
        pair<int,int> tempcoor = pos;
        isInSurrounded(pos, width, w, h, curH, surr);
        if (pos == tempcoor) {
            if (pos.first == 0) {
                isInSurrounded(pos, width, w, h, curH, surr);
                cout << pos.first << ' ' << pos.second << endl;
            } else if (pos.first+width+c <= w) {
            // cout << "hellllllo\n";
                int tempC = 0;
                int tempI = 0;
                // if(!isInSurrounded(temp, tempC, w, h, hh, surr)) {
                //     pos.first+=c;
                // }
                while (!isInSurrounded(temp, tempC, w, h, hh, surr) && tempI <c) {
                    hh = curH;
                    // tempC++;
                    tempI++;
                    temp ={pos.first-1 + tempI ,pos.second};
                }
                    // cout << "cdvig " << tempI << endl;
                    pos.first+=tempI;
                isInSurrounded(pos, width, w, h, curH, surr);
                cout << pos.first << ' ' << pos.second << endl;
            } else if (pos.first+width <= w && isInSurrounded(temp, width, w, h, hh, surr)) {
                isInSurrounded(pos, width, w, h, curH, surr);
                cout << pos.first << ' ' << pos.second << endl;
            } else {
                pos.first=0;
                // cout<<"height: "<<curH<<endl;
                pos.second+=curH;
                curH = h;
                isInSurrounded(pos, width, w, h, curH, surr);
                cout << pos.first << ' ' << pos.second << endl;
            }
        } else {
                cout << pos.first << ' ' << pos.second << endl;
        }
        if (height > curH)  curH = height;
        pos.first+=width;
        isFloat = false;

    } else if (expression.find("surrounded") != string::npos) {
        isInSurrounded(pos, width, w, h, curH, surr);
        if (pos.first + width > w) {
            pos.first = 0;
            pos.second+=curH;
            curH = h;
            isInSurrounded(pos, width, w, h, curH, surr);
            cout << pos.first << ' ' << pos.second << endl;
        } else {
            cout << pos.first << ' ' << pos.second << endl;
        }
        // cout << "surrounded" << pos.first << ' ' << pos.second << '-' << pos.first+width - 1 << ' ' << pos.second + height - 1 << '\n';
        surr.insert({pos, {pos.first+width - 1, pos.second + height - 1}});
        pos.first+=width;
        isFloat = false;
    } else if (expression.find("floating") != string::npos) {
        if (!isFloat) {
            floatPos = pos;
        }

            // cout<< "hello\n";
        extractFloatXY(expression, dx, dy);
        if (floatPos.first + dx + width > w) {
            int x = w - width;
            cout << x << ' ' << floatPos.second + dy << endl;
            floatPos.first = x + width;
            floatPos.second = floatPos.second + dy;
        } else if (floatPos.first + dx < 0) {
            int x = 0;
            cout << x << ' ' << floatPos.second + dy << endl;
            floatPos.first = x + width;
            floatPos.second = floatPos.second + dy;
        } else {
            cout << floatPos.first + dx << ' ' << floatPos.second + dy << endl;
            floatPos.first = floatPos.first + dx + width;
            floatPos.second = floatPos.second + dy;
        }
        // cout << "cdvig " << floatPos.first << ' ' << floatPos.second << endl;
        isFloat = true;
    }
}

void paragraphSurrounded(pair<int, int>& pos, int& curH, int& h, 
    set<pair<pair<int, int>, pair<int, int>>>& cS) {
        // cout << pos.second<< endl;
    for (auto& el : cS) {
        if (pos.second < el.second.second) {
            while (pos.second < el.second.second) {
                pos.second += curH;
                curH = h;
            }
        }
    }
        // cout << pos.second<< endl;
} 

void processParagraph(pair<int, int>& pos, int& h, int& curH, 
    pair<int, int>& floatPos, bool& isFloat,
    set<pair<pair<int, int>, pair<int, int>>>& cS ) {
    // cout << "paragraph pos: "<< pos.first << ' ' << pos.second << endl;

    if (pos.first == 0 && floatPos.first == 0) {
        paragraphSurrounded(pos, curH, h, cS);
    } else { 
        pos.second+=curH;
        pos.first = 0;
        curH = h;
        paragraphSurrounded(pos, curH, h, cS);
    }

    // pos.second+=h;
    isFloat = false;
}

int main() {

    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "Ошибка при открытии файла!" << endl;
        return 1;
    }

    int w,h,c;
    file >> w >> h >> c;
    string dummy, temp;
    while(getline(file, temp)) {
        if (temp.empty()) {
            dummy +="\n\n";
        } else {
            dummy+=temp + ' ';
        }
    }
// cout << dummy;
    stringstream buffer;
    buffer << dummy;
    string line;

    pair<int, int> currentPosition = {0, 0};
    pair<int, int> floatPos = {0, 0};
    set<pair<pair<int, int>, pair<int, int>>> surr;
    int currentHeight = h;
    bool isFloat = false;
    while (getline(buffer, line)) {
        if (line.empty()) {
    // cout << "Новый абзац" << endl;
            processParagraph(currentPosition, h, currentHeight, floatPos, isFloat, surr);
            currentHeight = h;
            continue;
        }

        stringstream linestream(line);
        string token;
        char nextChar;

        while (linestream >> nextChar) {
            // cout << "cur pos: "<< currentPosition.first << ' ' << currentPosition.second << endl;
            // cout << nextChar << endl;
            if (nextChar == '(') {
                getline(linestream, token, ')');
                processExpression(token, currentPosition, w, h, c, currentHeight, floatPos, isFloat, surr);
            } else {
                linestream.putback(nextChar);
                linestream >> token;
                int len = token.length() * c;
                processWord(currentPosition, len, h, w, h, c, currentHeight, isFloat, surr);
            // cout << "word pos: "<< currentPosition.first << ' ' << currentPosition.second << endl;
            }
        }
    }

    return 0;
}  
