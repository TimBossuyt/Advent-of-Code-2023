#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

vector<long long int> getNummers(string input) {
	bool nummerGevonden = false;
	string nummer = "";
	vector<long long int> numbers;
	bool isNegative = false;
	input += " ";

	for (int i = 0; i < input.size(); i++) {
		if (isdigit(input[i])) {
			nummerGevonden = true;
			nummer += input[i];
		}
		else if (input[i] == '-') {
			isNegative = true; 

		}
		else if (nummerGevonden) {
			nummerGevonden = false;
			if (isNegative) {
				numbers.push_back(- stoll(nummer));
			}
			else {
				numbers.push_back(stoll(nummer));
			}
			isNegative = false;
			nummer = "";
		}
	}

	return numbers;
}

long long int sumVector(vector<long long int> input) {
	long long int sum = 0;

	for (int i : input) {
		sum += i;
	}

	return sum;
}

bool allZeros(vector<long long int> input) {
	bool allZeros = true;

	for (long long int i : input) {
		if (i != 0) {
			allZeros = false;
			break;
		}
	}

	return allZeros;
}

vector<vector<long long int>> getAllDiffs(vector<long long int> history) {
	vector<vector<long long int>> calculations;
	calculations.push_back(history);
	int i = 0;

	while (!allZeros(calculations[i])) {
		vector<long long int> diff;
		for (int j = 0; j < calculations[i].size() - 1; j++) {

			diff.push_back(calculations[i][j + 1] - calculations[i][j]);
		}
		calculations.push_back(diff);
		i++;
	}

	return calculations;
}

long long int predictNext(vector<vector<long long int>> calculations) {
	long long int sum = 0;

	for (int i = calculations.size() - 1; i > 0; i--) {
		sum = sum + calculations[i - 1][calculations[i - 1].size() - 1];
	}

	return sum;
}

long long int predictBefore(vector<vector<long long int>> calculations) {
	long long int sum = 0;

	for (int i = calculations.size() - 1; i > 0; i--) {
		sum =  - sum + calculations[i - 1][0];
	}

	return sum;
}

vector<vector<long long int>> readFile(string fileName) {
	string line;
	ifstream inputReadFile;
	vector<vector<long long int>> numbers;

	inputReadFile.open(fileName);

	while (!inputReadFile.eof()) {
		getline(inputReadFile, line);

		if (line != "") {
			numbers.push_back(getNummers(line));
		}

	}

	return numbers;
}

int main()
{
	auto data = readFile("input.txt");

	long long int total = 0;

	for (auto reeks : data) {
		auto diff = getAllDiffs(reeks);
		auto predict = predictBefore(diff);
		total += predict;
	}

	cout << total;

}

