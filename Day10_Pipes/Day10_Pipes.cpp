#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <deque>

using namespace std;

vector<string> pipeMap(string fileName) {
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

pair<int, int> findStart(vector<string> input) {
	int hor, ver;

	for (int i = 0; i < input.size(); i++) {
		for (int j = 0; j < input[i].size(); j++) {
			if (input[i][j] == 'S') {
				hor = j;
				ver = i;
				break;
			}
		}
	}

	return { ver, hor };
}

bool checkCharString(char kar, string input) {
	bool contain = false;
	for (char k : input) {
		if (k == kar) {
			contain = true;
		}
	}

	return contain;
}

bool vectorContains(pair<int, int> paar, vector<pair<int, int>> lijst) {
	bool contain = false;

	for (pair<int, int> p : lijst) {
		if (p == paar) {
			contain = true;
		}
	}

	return contain;
}

void part1() {
	vector<string> pipemap = pipeMap("input.txt");

	pair<int, int> start = findStart(pipemap);

	deque<pair<int, int>> conn;
	vector<pair<int, int>> seen;
	conn.push_back(start);
	seen.push_back(start);

	while (!conn.empty()) {
		int r = conn.front().first;
		int c = conn.front().second;

		char ch = pipemap[r][c];

		conn.pop_front();

		//check of boven mogelijk
		if (r > 0 and checkCharString(ch, "SJ|L") and checkCharString(pipemap[r - 1][c], "|7F") and not vectorContains({ r - 1, c }, seen)) {
			seen.push_back({ r - 1, c });
			conn.push_back({ r - 1, c });
		}

		//check of beneden mogelijk
		if (r < pipemap.size() - 1 and checkCharString(ch, "S|F7")
			and checkCharString(pipemap[r + 1][c], "J|L") and not vectorContains({ r + 1, c }, seen)) {

			seen.push_back({ r + 1, c });
			conn.push_back({ r + 1, c });

		}

		//check of links mogelijk
		if (c > 0 and checkCharString(ch, "S-J7")
			and checkCharString(pipemap[r][c - 1], "-LF") and not vectorContains({ r, c - 1 }, seen)) {

			seen.push_back({ r, c - 1 });
			conn.push_back({ r , c - 1 });

		}

		//check of rechts mogelijk
		if (c < pipemap[r].size() - 1 and checkCharString(ch, "S-LF")
			and checkCharString(pipemap[r][c + 1], "-J7") and not vectorContains({ r, c + 1 }, seen)) {

			seen.push_back({ r, c + 1 });
			conn.push_back({ r , c + 1 });

		}
	}


	int verste = (int)seen.size() / 2;

	for (int r = 0; r < pipemap.size(); r++) {
		for (int c = 0; c < pipemap[r].size(); c++) {
			if (vectorContains({ r, c }, seen)) {
				cout << "x";
			}
			else {
				cout << ".";
			}
		}
		cout << endl;
	}

	cout << endl << verste;
}

void part2() {
	vector<string> pipemap = pipeMap("input.txt");

	pair<int, int> start = findStart(pipemap);

	deque<pair<int, int>> conn;
	vector<pair<int, int>> seen;
	conn.push_back(start);
	seen.push_back(start);

	while (!conn.empty()) {
		int r = conn.front().first;
		int c = conn.front().second;

		char ch = pipemap[r][c];

		conn.pop_front();

		//check of boven mogelijk
		if (r > 0 and checkCharString(ch, "SJ|L") and checkCharString(pipemap[r - 1][c], "|7F") and not vectorContains({ r - 1, c }, seen)) {
			seen.push_back({ r - 1, c });
			conn.push_back({ r - 1, c });
		}

		//check of beneden mogelijk
		if (r < pipemap.size() - 1 and checkCharString(ch, "S|F7")
			and checkCharString(pipemap[r + 1][c], "J|L") and not vectorContains({ r + 1, c }, seen)) {

			seen.push_back({ r + 1, c });
			conn.push_back({ r + 1, c });

		}

		//check of links mogelijk
		if (c > 0 and checkCharString(ch, "S-J7")
			and checkCharString(pipemap[r][c - 1], "-LF") and not vectorContains({ r, c - 1 }, seen)) {

			seen.push_back({ r, c - 1 });
			conn.push_back({ r , c - 1 });

		}

		//check of rechts mogelijk
		if (c < pipemap[r].size() - 1 and checkCharString(ch, "S-LF")
			and checkCharString(pipemap[r][c + 1], "-J7") and not vectorContains({ r, c + 1 }, seen)) {

			seen.push_back({ r, c + 1 });
			conn.push_back({ r , c + 1 });

		}
	}

	//alle chars die geen onderdeel zijn van pipe vervangen door .
	vector<string> removedExtra;
	int totaalElementen = 0;
	for (int i = 0; i < pipemap.size(); i++) {
		string row = "";
		for (int j = 0; j < pipemap[i].size(); j++) {
			if (vectorContains({ i, j }, seen)) {
				row += pipemap[i][j];
			}

			else {
				row += ".";
			}
			totaalElementen++;
		}
		removedExtra.push_back(row);
	}

	//rijen overlopen links -> rechts en kijken hoeveel crossings er zijn
	vector<pair<int, int>> outside;
	for (int r = 0; r < removedExtra.size(); r++) {
		bool within = false;
		bool up = NULL;

		for (int c = 0; c < removedExtra[r].size(); c++) {
			char k = removedExtra[r][c];
			if (k == '|') {
				//crossing -> oneven = within
				within = !within;
			}
			else if (k == 'F' or k == 'L') {
				up = (k == 'L'); //omhoog wanneer L en beneden wanneer F
			}
			else if (k == '7' or k == 'J') {
				//J = omhoog, 7 = beneden
				if (up and k == '7') {
					within = !within;
				}
				else if (!up and k == 'J') {
					within = !within;
				}
				up = NULL;
			}

			if (!within) {
				outside.push_back({ r, c });
			}
		}
	}
	int teller = 0;
	
	for (int r = 0; r < removedExtra.size(); r++) {
		for (int c = 0; c < removedExtra[r].size(); c++) {
			//binnen wanneer niet onderdeel van seen/buiten
			if (!vectorContains({ r, c }, seen) and !vectorContains({ r, c }, outside)) {
				teller++;
			}
		}
	}
	cout << teller;

}

int main()
{
	part2();

	//part 2
	//1. alle chars die niet van pijp zijn vervangen door .
	//2. overlopen, hoeken checken, tellen hoeveel links/hoeveel rechts



}


