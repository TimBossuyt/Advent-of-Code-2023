#include <iostream>
#include <string>
#include <ctype.h>
#include <fstream>

using namespace std;

const string letters[] = {
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine"
};

static int calibrationValue(string input) {
    string nummers = "";
    string firstLastNumbers = "";
    for (int i = 0; i < input.size(); i++) {
        char ch = input[i];
        if (isdigit(ch)) {
            nummers += ch;
        }
    }

    firstLastNumbers += nummers[0];
    firstLastNumbers += nummers[nummers.size() - 1];

    cout << firstLastNumbers << endl;

    return stoi(firstLastNumbers);
}

//Part 2 replace spelled out numbers <- inefficient
int replaceSpelled(string input) {
    for (int i = 0; i < 9; i++) {
        int begin = input.find(letters[i]);
        int size = letters[i].size();
        string toReplace = letters[i][0] + to_string(i + 1) + letters[i][size - 1];
        if (begin != -1) {
            input.replace(begin, size, toReplace);
            i--;
        }
    }

    return calibrationValue(input);
}

//More efficient solution for PART 2: left search and right search:
int getCalibration(string input) {
    string firstNum = "";
    string lastNum = "";
    string search;

    //left search -> first number
    for (int i = 0; i < input.size(); i++)
    {
        search = input.substr(0, i);
        //check if number
        if (isdigit(input[i])) {
            firstNum = input[i];
        }

        //check if spelled number
        for (int j = 0; j < 9; j++) {
            int find = search.find(letters[j]);
            if (find != -1) {
                firstNum = to_string(j + 1);
            }
        }

        if (firstNum != "") {
            break;
        }
    }

    //right search -> last number
    for (int i = input.size() - 1; i >= 0; i--) {
        search = input.substr(i, input.size() - i);

        if (isdigit(input[i])) {
            cout << input[i] << endl;
            lastNum = input[i];
        }

        //check if spelled number
        for (int j = 0; j < 9; j++) {
            int find = search.find(letters[j]);
            if (find != -1) {
                lastNum = to_string(j + 1);
            }
        }

        if (lastNum != "") {
            break;
        }
    }
    cout << stoi(firstNum + lastNum) << endl;
    return stoi(firstNum + lastNum);
}

int readFile(string fileName) {
    string line;
    int sum = 0;

    ifstream inputReadFile;

    inputReadFile.open(fileName);
    while (!inputReadFile.eof()) {
        getline(inputReadFile, line);
        

        cout << line << endl;

        if (line != "") {
            sum += getCalibration(line);
        }
        
    }

    return sum;
}




int main()
{
    int sum = readFile("input.txt");
    cout << sum;

    //cout << getCalibration("five2two7hstbbqzrninegbtwo2");
    //CORRECT ANSWER P1: 53386
    //P2: 53312
}




