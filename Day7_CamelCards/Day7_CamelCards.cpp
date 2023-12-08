#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

map<char, char> cardValues = {
	{'A', 'M'},
	{'K', 'L'},
	{'Q', 'K'},
	{'J', 'J'},
	{'T', 'I'},
	{'9', 'H'},
	{'8', 'G'},
	{'7', 'F'},
	{'6', 'E'},
	{'5', 'D'},
	{'4', 'C'},
	{'3', 'B'},
	{'2', 'A'}
};

map<char, char> cardValuesP2 = {
	{'A', 'N'},
	{'K', 'M'},
	{'Q', 'L'},
	{'T', 'K'},
	{'9', 'I'},
	{'8', 'H'},
	{'7', 'G'},
	{'6', 'F'},
	{'5', 'E'},
	{'4', 'D'},
	{'3', 'C'},
	{'2', 'B'},
	{'J', 'A'}
};

int countChar(string input, char zoek) {
	int count = 0;

	for (char kar : input) {
		if (kar == zoek) {
			count++;
		}
	}
	return count;
}

int uniqueChar(string input) {
	map<char, int> count;

	for (char kar : input) {
		count[kar]++;
	}

	return count.size();
}

int checkType(string hand) {
	//Five of a kind = 7 points
	if (countChar(hand, hand[0]) == 5) {
		return 7;
	}

	//Four of a kind = 6 points
	for (char kar : hand) {
		if (countChar(hand, kar) == 4) {
			return 6;
		}
	}

	//Full house = 5 points
	for (char kar : hand) {
		if (countChar(hand, kar) == 3 and uniqueChar(hand) == 2) {
			return 5;
		}
	}

	//Three of a kind = 4 points
	for (char kar : hand) {
		if (countChar(hand, kar) == 3) {
			return 4;
		}
	}

	//Two pair = 3 points

	bool paarGevonden = false;
	char eerstePaar;
	for (char kar : hand) {
		if (countChar(hand, kar) == 2) {
			if (paarGevonden and kar != eerstePaar) {
				return 3;
			}
			paarGevonden = true;
			eerstePaar = kar;
		}
	}

	//One pair = 2 points
	for (char kar : hand) {
		if (countChar(hand, kar) == 2) {
			return 2;
		}
	}

	//Highest card = 1 point
	return 1;
}

int checkTypeJoker(string hand) {
	//Five of a kind = 7 points
	if (countChar(hand, hand[0]) == 5) {
		return 7;
	}

	//Four of a kind = 6 points
	for (char kar : hand) {
		if (countChar(hand, kar) == 4 and kar != 'J') {
			if (countChar(hand, 'J') == 1) {
				return 7;
			}
			else {
				return 6;
			}
		}
	}

	//Full house = 5 points
	for (char kar : hand) {
		if (countChar(hand, kar) == 3 and uniqueChar(hand) == 2 and kar != 'J' and countChar(hand, 'J') != 2) {
			return 5;
		}
	}

	//Three of a kind = 4 points
	for (char kar : hand) {
		if (countChar(hand, kar) == 3 and kar != 'J') {
			if (countChar(hand, 'J') == 1) {
				return 6;
			}
			else if (countChar(hand, 'J') == 2) {
				return 7;
			}
			else {
				return 4;
			}
		}
	}

	//Two pair = 3 points

	bool paarGevonden = false;
	char eerstePaar;
	for (char kar : hand) {
		if (countChar(hand, kar) == 2 and kar != 'J') {
			if (paarGevonden and kar != eerstePaar) {
				if (countChar(hand, 'J') == 1) {
					return 5;
				}
				else {
					return 3;
				}
			}
			paarGevonden = true;
			eerstePaar = kar;
		}
	}

	//One pair = 2 points
	for (char kar : hand) {
		if (countChar(hand, kar) == 2 and kar != 'J') {
			if (countChar(hand, 'J') == 1) {
				return 4;
			}
			else if (countChar(hand, 'J') == 2) {
				return 6;
			}
			else if (countChar(hand, 'J') == 3) {
				return 7;
			}
			else {
				return 2;
			}
		}
	}

	//Highest card = 1 point
	if (countChar(hand, 'J') ==1) {
		return 2;
	}
	else if (countChar(hand, 'J') == 2) {
		return 4;
	} 
	else if (countChar(hand, 'J') == 3) {
		return 6;
	}
	else if (countChar(hand, 'J') >= 4) {
		return 7;
	}
	else {
		return 1;
	}
}

string newFormat(string input) {
	string replace;

	for (char kar : input) {
		replace += cardValuesP2[kar];
	}


	int type = checkTypeJoker(input);

	return to_string(type) + replace;
} //part 2

map<string, int> cardScore(pair<vector<string>, vector<int>> games) {
	map<string, int> sorted;

	for (int i = 0; i < games.first.size(); i++) {
		string cardF = newFormat(games.first[i]);

		sorted.insert({ cardF, games.second[i] });

	}

	return sorted;
}


pair<vector<string>, vector<int>> getData(string fileName) {
	string line;
	ifstream inputReadFile;
	vector<string> hands;
	vector<int> inzet;

	inputReadFile.open(fileName);

	while (!inputReadFile.eof()) {
		getline(inputReadFile, line);

		if (line != "") {
			hands.push_back(line.substr(0, 5));
			inzet.push_back(stoi(line.substr(6, line.size())));
		}

	}

	return { hands, inzet };
}

pair<vector<string>, vector<string>> edgeCases(string fileName) {
	string line;
	ifstream inputReadFile;
	vector<string> hands;
	vector<string> hands2;

	inputReadFile.open(fileName);

	while (!inputReadFile.eof()) {
		getline(inputReadFile, line);

		if (line != "") {
			hands.push_back(line.substr(0, 5));
			hands2.push_back(line.substr(8, line.size()));
		}

	}

	return { hands, hands2 };
}

void checkEdges(pair<vector<string>, vector<string>> input) {
	for (int i = 0; i < input.first.size(); i++) {
		if (checkTypeJoker(input.first[i]) < checkTypeJoker(input.second[i])) {

			cout << input.first[i] << " : " << checkTypeJoker(input.first[i]) << endl;
			cout << input.second[i] << " : " << checkTypeJoker(input.second[i]) << endl;
			cout << endl;
		}
	}
}

int main()
{
	pair<vector<string>, vector<int>> game = getData("input.txt");

	map<string, int> cardScores = cardScore(game);

	/*pair<vector<string>, vector<int>> testData = {
		{"66666", "666JJ", "666J7", "66677", "66J77"},
		{1, 1, 1, 1, 1}
	};

	map<string, int> scoresTest = cardScore(testData);*/

	/*pair<vector<string>, vector<string>> test = edgeCases("edges.txt");
	checkEdges(test);*/

	long long int sum = 0;
	int i = 1;
	
	for (pair<string, int> paar : cardScores) {
		std::cout << paar.first << endl;
		sum += i * paar.second;
		i++;
	}

	std::cout << sum;
}



