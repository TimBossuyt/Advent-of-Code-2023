#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <deque>

using namespace std;

vector<string> galaxyInput(string fileName) {
	string line;
	ifstream inputReadFile;
	vector<string> pipes;

	inputReadFile.open(fileName);

	while (!inputReadFile.eof()) {
		getline(inputReadFile, line);

		if (line != "") {
			pipes.push_back(line);
		}
	}

	return pipes;
}

bool onlyDots(string lijn) {
	bool dots = true;

	for (char k : lijn) {
		if (k != '.') {
			dots = false;
		}
	}

	return dots;
}

pair<vector<int>, vector<int>> getEmptyRowCol(vector<string> input) {
	vector<int> emptyRow;
	vector<int> emptyCol;

	for (int r = 0; r < input.size(); r++) {
		if (onlyDots(input[r])) {
			emptyRow.push_back(r);
		}
	}
	int col = 0;
	for (char k : input[0]) {
		if (k == '.') {
			string check;
			for (int i = 0; i < input.size(); i++) {
				check += input[i][col];
			}

			if (onlyDots(check)) {
				emptyCol.push_back(col);
			}
		}
		col++;
	}

	return { emptyRow, emptyCol };
}

bool vectorContainsIndex(vector<int> lijst, int index) {
	bool contains = false;
	for (int control : lijst) {
		if (control == index) {
			contains = true;
		}
	}

	return contains;
}

string prodPoint(int get) {
	string out;
	for (int i = 0; i < get; i++) {
		out += ".";
	}
	return out;
}

int calculateManhattanDist(pair<int, int> x, pair<int, int> y) {
	return	abs(x.first - y.first) + abs(x.second - y.second);
}

vector<pair<int, int>> findGalaxies(vector<string> input) {
	vector<pair<int, int>> coord;
	for (int r = 0; r < input.size(); r++) {
		for (int c = 0; c < input[r].size(); c++) {
			if (input[r][c] == '#') {
				coord.push_back({ r, c });
			}
		}
	}

	return coord;
}

vector<string> expandGalaxy(vector<string> galaxy) {
	vector<string> galaxyExp;
	auto emptyRowsCols = getEmptyRowCol(galaxy);

	for (int r = 0; r < galaxy.size(); r++) {
		string lijn;

		int expanded = 0;
		for (int c = 0; c < galaxy[r].size(); c++) {
			lijn += galaxy[r][c];
			if (vectorContainsIndex(emptyRowsCols.second, c)) {
				lijn += galaxy[r][c];
				expanded++;
			}
		}

		if (vectorContainsIndex(emptyRowsCols.first, r)) {
			galaxyExp.push_back(galaxy[r] + prodPoint(expanded));
		}

		galaxyExp.push_back(lijn);
	}

	return galaxyExp;
}

int aantalTussen(int x, int y, vector<int> empty) {
	int aantal = 0;
	bool tussen = false;
	for (int i = min(x, y); i < max(x, y); i++) {
		if (vectorContainsIndex(empty, i)) {
			aantal++;
			tussen = true;
		}
	}

	if (tussen) {
		return 10 * aantal - aantal;
	}

	return 0;
}

bool vectorContainsPair(pair<int, int> paar, vector<pair<int, int>> lijst) {
	bool contain = false;

	for (pair<int, int> p : lijst) {
		if (p == paar) {
			contain = true;
		}
	}

	return contain;
}


void part1() {
	vector<string> galaxy0 = galaxyInput("test.txt");

	auto empties = getEmptyRowCol(galaxy0);

	auto galaxies = findGalaxies(galaxy0);

	int distSum = 0;

	for (pair<int, int> galaxy : galaxies) {
		for (pair<int, int> galaxyNext : galaxies) {
			distSum += calculateManhattanDist(galaxy, galaxyNext);
			distSum += abs(galaxy.first - galaxyNext.first)
				+ 10 * aantalTussen(galaxy.first, galaxyNext.first, empties.first)
				+ abs(galaxy.second - galaxy.second) + 10 * aantalTussen(galaxy.second, galaxyNext.second, empties.second);
		}
	}

	cout << distSum / 2;
}

void part2() {
	vector<string> galaxy0 = galaxyInput("input.txt");

	auto empties = getEmptyRowCol(galaxy0);
	auto galaxies = findGalaxies(galaxy0);

	long long int distSum = 0;

	vector<pair<int, int>> seen;
	for (pair<int, int> galaxy : galaxies) {
		for (pair<int, int> galaxyNext : galaxies) {
			if (!vectorContainsPair(galaxy, seen)) {
				//distSum += abs(galaxy.first - galaxyNext.first) + abs(galaxy.second - galaxy.second);

				//check voor lege rijen
				for (int r = min(galaxy.first, galaxyNext.first); r < max(galaxy.first, galaxyNext.first); r++) {
					if (vectorContainsIndex(empties.first, r)) {
						distSum += 1000000;
					}
					else {
						distSum += 1;
					}
				}

				//check voor lege kolommen tussen
				for (int c = min(galaxy.second, galaxyNext.second); c < max(galaxy.second, galaxyNext.second); c++) {
					if (vectorContainsIndex(empties.second, c)) {
						distSum += 1000000;
					}
					else {
						distSum += 1;
					}
				}

			}
			
		}
		seen.push_back(galaxy);
	}

	cout << distSum / 2;

}

int main()
{
	part2();
}

