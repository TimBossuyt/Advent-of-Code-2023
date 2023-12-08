#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

vector<int> getNummers(string input) {
    bool nummerGevonden = false;
    string nummer = "";
    vector<int> numbers;

    input += " ";

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

long long int getNummerP2(string input) {
    bool nummerGevonden = false;
    string nummer = "";
    long long int nummerConv{};

    input += ";";

    for (int i = 0; i < input.size(); i++) {
        if (isdigit(input[i])) {
            nummerGevonden = true;
            nummer += input[i];
        }
        else if (nummerGevonden and input[i] == ';') {
            nummerGevonden = false;
            nummerConv = stoll(nummer);
        }
    }

    return nummerConv;
}

pair<vector<int>, vector<int>> getData(string fileName) {
    vector<int> times, distances;

    string line;
    ifstream inputReadFile;
    int sum = 0;

    inputReadFile.open(fileName);

    while (!inputReadFile.eof()) {
        getline(inputReadFile, line);

        if (line.find("Time:") != -1 ) {
            times = getNummers(line);
        }
        else if (line.find("Distance:") != -1) {
            distances = getNummers(line);
        }

    }

    return { times, distances };
}

pair<double, double> roots(long long int a, long long int b, long long int c) {
    double d = pow(b, 2) - 4 * a * c;

    return { (-b + sqrt(d)) / (2 * a) , (-b - sqrt(d)) / (2 * a) };
}

long long int numberOptions(long long int time, long long int distance) {
    pair<double, double> root = roots(-1, time, - distance);

    long long int min = ceil(root.first + 0.001);
    long long int max = floor(root.second - 0.01);

    return max - min + 1;
}

int numberOptionsTotal(pair<vector<int>, vector<int>> data) {
    vector<int> times = data.first;
    vector<int> distances = data.second;
    int product = 1;

    for (int i = 0; i < times.size(); i++) {
        product *= numberOptions(times[i], distances[i]);
    }

    return product;
}

pair<long long int,long long int> getDataP2(string fileName) {
    long long int time, distance;
    string line;
    ifstream inputReadFile;

    inputReadFile.open(fileName);

    while (!inputReadFile.eof()) {
        getline(inputReadFile, line);

        if (line.find("Time:") != -1) {
            time = getNummerP2(line);
        }
        else if (line.find("Distance:") != -1) {
            distance = getNummerP2(line);
        }

    }

    return { time, distance };
}

int main()
{
    //pair<vector<int>, vector<int>> data = getData("input.txt");

    //cout << numberOptionsTotal(data);

    pair<long long int, long long int> data = getDataP2("input.txt");

    cout << numberOptions(data.first, data.second);
}

