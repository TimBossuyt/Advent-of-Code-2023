#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <fstream>

using namespace std;


map<string, int> maxCubes = {
            {"blue", 14},
            {"red", 12},
            {"green", 13}
};

vector<string> splitBy(char split, string input) {
    vector<string> seglist;

    stringstream inputStream(input);
    string segment;

    while (getline(inputStream, segment, split)) {
        seglist.push_back(segment);
    }


    return seglist;
}


bool isGamePossible(string input) {
    string setsOnly = input.substr(input.find(":") + 1, input.size() - input.find(":"));

    vector<string> setsVec = splitBy(';', setsOnly);

    bool gamePossible = true;

    for (string set : setsVec) {
        vector<string> cubes = splitBy(',', set);

        for (string cube : cubes) {

            int locSplit = cube.find_last_of(' ');

            string kleur = cube.substr(locSplit + 1, cube.size());

            int aantal = stoi(cube.substr(1, locSplit - 1));

            if (aantal > maxCubes[kleur]) {
                gamePossible = false;
                break;
            }


        }
        if (not gamePossible) {
            break;
        }
    }

    return gamePossible;
}


int getPowerGame(string input) {
    string setsOnly = input.substr(input.find(":") + 1, input.size() - input.find(":"));

    vector<string> setsVec = splitBy(';', setsOnly);

    map<string, int> minCubes = {
            {"blue", 0},
            {"red", 0},
            {"green", 0}
    };

    for (string set : setsVec) {
        vector<string> cubes = splitBy(',', set);

        for (string cube : cubes) {

            int locSplit = cube.find_last_of(' ');

            string kleur = cube.substr(locSplit + 1, cube.size());

            int aantal = stoi(cube.substr(1, locSplit - 1));

            if (aantal > minCubes[kleur]) {
                minCubes[kleur] = aantal;
            }
        }
    }

    return minCubes["blue"] * minCubes["red"] * minCubes["green"];
}

int getGameId(string input) {
    int id = stoi(input.substr(5, input.find(":") - 5));
    return id;
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
            sum += getPowerGame(line);
        }

    }

    return sum;
}


int main()
{
    //int sumId = readFile("input.txt");

    //cout << sumId;

    int powerSum = readFile("input.txt");

    cout << powerSum;
    
}

