#include <iostream>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <string>

using namespace std;

vector<int> getNummers(string input) {
    bool nummerGevonden = false;
    string nummer = "";
    vector<int> numbers;

    for (int i = 0; i < input.size(); i++) {
        if (isdigit(input[i])) {
            nummerGevonden = true;
            nummer += input[i];
        }
        else if (nummerGevonden) {
            nummerGevonden = false;
            numbers.push_back(stoi(nummer));
            nummer = "";
        }
    }

    return numbers;
}



int parseLineMatches(string input) {
    vector<int> winningNumbers;
    vector<int> numbers;

    string left = input.substr(input.find(':') + 2, input.find('|') - input.find(':') - 2) + " ";
    string right = input.substr(input.find('|'), input.size() - input.find('|')) + " ";

    numbers = getNummers(right);
    winningNumbers = getNummers(left);

    int match = 0;

    for (int winner : winningNumbers) {
        for (int nummer : numbers) {
            if (nummer == winner) {
                match++;
            }
        }
    }

    return match;
}

int parseLine(string input) {

    vector<int> winningNumbers;
    vector<int> numbers;

    string left = input.substr(input.find(':') + 2, input.find('|') - input.find(':') - 2) + " ";
    string right = input.substr(input.find('|'), input.size() - input.find('|')) + " ";

    numbers = getNummers(right);
    winningNumbers = getNummers(left);

    int match = 0;
    int points = 0;

    for (int winner : winningNumbers) {
        for (int nummer : numbers) {
            if (nummer == winner) {
                match++;
            }
        }
    }

    if (match != 0) {
        points = pow(2, match - 1);
    }

    return points;
}

int readFile(string fileName) {
    string line;
    ifstream inputReadFile;
    int sum = 0;

    inputReadFile.open(fileName);

    while (!inputReadFile.eof()) {
        getline(inputReadFile, line);

        if (line != "") {
            int points = parseLine(line);
            cout << points << endl;
            sum += points;
        }

    }

    return sum;
}

map<int, int> getMatches(string fileName) {
    map<int, int> matches;
    int lijn = 1;

    string line;
    ifstream inputReadFile;

    inputReadFile.open(fileName);

    while (!inputReadFile.eof()) {
        getline(inputReadFile, line);

        if (line != "") {
            int points = parseLineMatches(line);
            matches.insert({ lijn, points });
            lijn++;
        }

    }

    return matches;
}


map<int, int> aantalKaarten(int aantalGames) {
    map<int, int> kaarten;
    for (int i = 1; i < aantalGames + 1; i++) {
        kaarten.insert({ i, 1 });
    }

    return kaarten;
}
int main()
{
    map<int, int> matches = getMatches("input.txt");
    map<int, int> kaarten = aantalKaarten(matches.size());
    int overeenkomst;
    


    int aantalKaarten = 0;

    for (int i = 1; i < matches.size()  + 1; i++) {
        overeenkomst = matches[i];
        cout << "Game " << i << ": " << overeenkomst << endl;
        if (overeenkomst > 0) {
            for (int k = 0; k < kaarten[i]; k++) {
                for (int j = 1; j < overeenkomst + 1; j++) {
                    kaarten[i + j]++;
                }
            }
        }
    }

    for (int i = 0; i < kaarten.size(); i++) {
        aantalKaarten += kaarten[i + 1];
    }

    cout << aantalKaarten;
}

