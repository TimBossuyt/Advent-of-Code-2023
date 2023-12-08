#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>

using namespace std;


vector<vector<string>> engineModel;

vector<vector<string>> readFile(string fileName) {
	string line;
	vector< vector<string> > engine;

	ifstream inputReadFile;


	inputReadFile.open(fileName);

	while (!inputReadFile.eof()) {
		getline(inputReadFile, line);
		vector<string> vecLine = {};

		if (line != "") {
			vecLine.push_back(".");
			for (int k = 0; k < line.size(); k++) {
				vecLine.push_back(line.substr(k, 1));
			}
			vecLine.push_back(".");
		}

		engine.push_back(vecLine);
	}

	return engine;
}

bool isSymbol(string kar) {
	bool symbol = false;

	if (kar != "." and !isdigit(kar[0])) {
		symbol = true;
	}

	return symbol;
}

vector<int> partNumbers(vector<vector<string>> engineModel) {
	//gekende positie van nr gekend -> alle omliggende ints zoeken en samenstellen

	vector<int> nummers;

	string nummer;
	bool nummerGevonden = false;
	bool symbol = false;

	for (int i = 0; i < engineModel.size(); i++) {

		for (int j = 0; j < engineModel[i].size(); j++) {
			string kar = engineModel[i][j];
			if (isdigit(kar[0])) {
				nummer += kar;
				nummerGevonden = true;

				//check of symbool boven, onder, naast
				//BOVEN EN ONDER
				if (i > 0) {
					for (int horPos = j - 1; horPos <= j + 1; horPos++) {
						if (isSymbol(engineModel[i - 1][horPos])) {
							symbol = true;
						}
					}
				}

				//ONDER
				if (i < engineModel.size() - 1) {
					for (int horPos = j - 1; horPos <= j + 1; horPos++) {
						if (isSymbol(engineModel[i + 1][horPos])) {
							symbol = true;
						}
					}
				}

				//NAAST (grenzenprobleem opgelost door .x. toe te voegen)
				if (isSymbol(engineModel[i][j + 1]) || isSymbol(engineModel[i][j - 1])) {
					symbol = true;
				}


			}

			if (((isSymbol(kar) or kar == ".") and nummerGevonden)) {
				if (symbol) {
					nummers.push_back(stoi(nummer));
					symbol = false;
				}
				nummer = "";
				nummerGevonden = false;
			}
		}
	}

	return nummers;
}

//{i, j}, aantal keer gebruikt
map<pair<int, int>, int> gearLocations(vector<vector<string>> engineModel) {
	map<pair<int, int>, int> locations;

	pair<int, int> location;

	for (int i = 0; i < engineModel.size(); i++) {

		for (int j = 0; j < engineModel[i].size(); j++) {
			if (engineModel[i][j] == "*") {
				location = { i, j };
				locations.insert({ location, 0 });
			}

		}
	}

	return locations;
}

multimap<int, pair<int, int>> gearRatios(vector<vector<string>> engineModel) {
	//map van getallen, met locatie van gear + map van gear aantal gebruikt updaten
	//map van upgedate gear met value 2 overlopen en juiste ratios optellen

	multimap<int, pair<int, int>> nummerGearLoc;

	pair<int, int> gearLoc;

	string nummer;
	bool nummerGevonden = false;
	bool gearNearby = false;

	for (int i = 0; i < engineModel.size(); i++) {

		for (int j = 0; j < engineModel[i].size(); j++) {
			string kar = engineModel[i][j];
			if (isdigit(kar[0])) {
				nummer += kar;
				nummerGevonden = true;

				//check of symbool boven, onder, naast
				//BOVEN EN ONDER
				if (i > 0) {
					for (int horPos = j - 1; horPos <= j + 1; horPos++) {
						if (engineModel[i - 1][horPos] == "*") {
							gearNearby = true;
							gearLoc = { i - 1, horPos };
						}
					}
				}

				//ONDER
				if (i < engineModel.size() - 1) {
					for (int horPos = j - 1; horPos <= j + 1; horPos++) {
						if (engineModel[i + 1][horPos] == "*") {
							gearNearby = true;
							gearLoc = { i + 1, horPos };
						}
					}
				}

				//NAAST (grenzenprobleem opgelost door .x. toe te voegen)
				if (engineModel[i][j + 1] == "*" ) {
					gearNearby = true;
					gearLoc = { i, j + 1 };
				}

				if (engineModel[i][j - 1] == "*") {
					gearNearby = true;
					gearLoc = { i, j - 1 };
				}


			}

			if (((isSymbol(kar) or kar == ".") and nummerGevonden)) {
				if (gearNearby) {
					int num = stoi(nummer);
					nummerGearLoc.insert({num, gearLoc});

					gearNearby = false;
				}
				nummer = "";
				nummerGevonden = false;
			}
		}
	}



	return nummerGearLoc;
}



int main()
{
	engineModel = readFile("input.txt");

	/*vector<int> nummers = partNumbers(engineModel);

	int sum = 0;

	for (int partNumber : nummers) {
		sum += partNumber;
	}

	cout << sum;*/

	map<pair<int, int>, int> locations = gearLocations(engineModel);
	multimap<int, pair<int, int>> gears = gearRatios(engineModel);

	int sumRatio = 0;

	//itereren over gearRatios en gearLocations updaten:
	for (const auto& myPair : gears) {
		locations[myPair.second]++;
	}

	for (const auto& myPair : locations) {
		int ratio = 1;

		cout << "Tandwiel op locatie: ";
		cout << myPair.first.first << " " << myPair.first.second << "  met tandwielen: ";

		if (myPair.second == 2) {
			for (const auto& gearLoc : gears) {
				if (gearLoc.second == myPair.first) {
					cout << gearLoc.first << " ratio: ";
					ratio *= gearLoc.first;
				}
			}
			sumRatio += ratio;
			cout << ratio;

		}

		cout << endl;
	}


	cout << sumRatio;
}

