#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <numeric>

using namespace std;

pair<string, pair<string, string>> parseLine(string input) {
	string node, left, right;

	node = input.substr(0, 3);
	left = input.substr(input.find('(') + 1, 3);
	right = input.substr(input.find(')') - 3, 3);


	return { node, {left, right} };
}

pair<map<string, pair<string, string>>, string> getData(string fileName) {
	string line;
	ifstream inputReadFile;
	map<string, pair<string, string>> map;
	string instructions;

	inputReadFile.open(fileName);

	while (!inputReadFile.eof()) {
		getline(inputReadFile, line);

		if (line != "" and line.find(' ') != -1) {
			auto node = parseLine(line);
			map.insert({ node.first, node.second });
		}
		else if (line != "") {
			instructions = line;
		}

	}

	return { map, instructions };
}

string getInstructions(string fileName) {
	return "";
}

void getStepsPart2() {
	auto inputData = getData("input.txt");

	auto nodes = inputData.first;
	string instructions = inputData.second;

	bool endFound = false;
	string location = "AAA";
	string nextLocation;
	int aantalStappen = 0;

	while (!endFound) {
		for (char kar : instructions) {
			if (kar == 'L') {
				nextLocation = nodes[location].first;
			}
			else if (kar == 'R') {
				nextLocation = nodes[location].second;
			}
			location = nextLocation;
			aantalStappen++;
		}

		if (nextLocation == "ZZZ") {
			endFound = true;
		}
	}
	cout << "Loop done" << endl;


	cout << aantalStappen;
}

int aantalStappen(string startLocation,
	map<string, pair<string, string>> nodes, string instructions) {

	bool endFound = false;
	string location = startLocation;
	string nextLocation;
	int aantalStappen = 0;

	while (!endFound) {
		for (char kar : instructions) {
			if (kar == 'L') {
				nextLocation = nodes[location].first;
			}
			else if (kar == 'R') {
				nextLocation = nodes[location].second;
			}
			location = nextLocation;
			aantalStappen++;
		}

		if (nextLocation.find_last_of('Z') == 2) {
			endFound = true;
		}
	}

	return aantalStappen;

}

vector<string> startNodes(map <string, pair<string, string>> map) {
	string node;
	vector<string> startingNodes;
	for (pair<string, pair<string, string>> paar : map) {
		node = paar.first;
		if (node.find_last_of('A') == 2) {
			startingNodes.push_back(node);
		}
	}

	return startingNodes;
}

// Function to calculate the GCD using Euclidean algorithm
long long int gcd(long long int a,long long int b) {
	while (b != 0) {
		long long int temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}

// Function to calculate the LCM of two numbers
long long int lcm(long long int a, long long int b) {
	return (a * b) / gcd(a, b);
}

// Function to calculate the LCM of a vector of integers
long long int lcmOfVector(vector<int> numbers) {
	long long int result = numbers[0];
	for (int i = 1; i < numbers.size(); ++i) {
		result = lcm(result, numbers[i]);
	}

	return result;
}

int main()
{
	auto inputData = getData("input.txt");

	auto nodes = inputData.first;
	string instructions = inputData.second;

	vector<int> steps;


	vector<string> startingNodes = startNodes(nodes);
	//voor elke startnode uitrekenen steps -> LCM zoeken
	for (string startNode : startingNodes) {
		steps.push_back(aantalStappen(startNode, nodes, instructions));
	}

	cout << lcmOfVector(steps) << endl;


}

