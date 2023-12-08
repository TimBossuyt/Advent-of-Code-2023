#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>

using namespace std;


map<pair<long long int, long long int>, long long int> transform(string input) {
	map<pair<long long int, long long int>, long long int> transform;

	string xS;
	string yS;
	string rangeS;

	long long int x;
	long long int y;
	long long int range;

	yS = input.substr(0, input.find(" "));
	xS = input.substr(input.find(" ") + 1, input.size() - input.find_last_of(" ") + 1);
	rangeS = input.substr(input.find_last_of(" ") + 1, input.size());

	x = stoll(xS);
	y = stoll(yS);
	range = stoll(rangeS);

	transform.insert({ {x, y}, range });

	return transform;
}

long long int mapResultFast(map<pair<long long int, long long int>, long long int> map, long long int input) {
	long long int result = 25;

	for (const pair<pair<long long int, long long int>, long long int>& paar : map) {
		if (paar.first.first <= input and input < (paar.first.first + paar.second)) {
			result = (input - paar.first.first) + paar.first.second;
			break;
		}
		else {
			result = input;
		}
	}

	return result;
}

long long int mapResultFastReverse(map<pair<long long int, long long int>, long long int> map, long long int input) {
	long long int result = 25;

	for (const pair<pair<long long int, long long int>, long long int>& paar : map) {
		if (paar.first.second <= input and input < (paar.first.second + paar.second)) {
			result = (input - paar.first.second) + paar.first.first;
			break;
		}
		else {
			result = input;
		}
	}

	return result;
}

vector<long long int> getNummers(string input) {
	bool nummerGevonden = false;
	string nummer = "";
	vector<long long int> numbers;
	input += " ";

	for (int i = 0; i < input.size(); i++) {
		if (isdigit(input[i])) {
			nummerGevonden = true;
			nummer += input[i];
		}
		else if (nummerGevonden) {
			nummerGevonden = false;
			numbers.push_back(stoll(nummer));
			nummer = "";
		}
	}

	return numbers;
}

vector<pair<long long int, long long int>> getRanges(string input) {
	vector<pair<long long int, long long int>> ranges;
	vector<pair<long long int, long long int>> rangesSplit;
	pair<long long int, long long int> range;

	vector<long long int> nummers = getNummers(input);

	for (int i = 0; i < nummers.size(); i++) {
		range.first = nummers[i];
		i++;
		range.second = nummers[i];

		ranges.push_back(range);
	}

	return ranges;
}

long long int readFile(string fileName) {
	string line;
	ifstream inputReadFile;

	inputReadFile.open(fileName);

	bool seedSoilFound = false;
	bool soilFertilizerFound = false;
	bool fertilizerWaterFound = false;
	bool waterLightFound = false;
	bool lightTempFound = false;
	bool tempHumFound = false;
	bool humLocFound = false;


	map<pair<long long int, long long int>, long long int> seedSoil;
	map<pair<long long int, long long int>, long long int> soilFertilizer;
	map<pair<long long int, long long int>, long long int> fertilizerWater;
	map<pair<long long int, long long int>, long long int> waterLight;
	map<pair<long long int, long long int>, long long int> lightTemp;
	map<pair<long long int, long long int>, long long int> tempHum;
	map<pair<long long int, long long int>, long long int> humLoc;

	map<pair<long long int, long long int>, long long int> temp;

	vector<map<pair<long long int, long long int>, long long int>> mappings;
	vector<pair<long long int, long long int>> seeds;

	while (!inputReadFile.eof()) {
		getline(inputReadFile, line);

		if (line != "") {

			if (humLocFound) {
				temp = transform(line);
				humLoc.insert(temp.begin(), temp.end());
			}

			if (line == "humidity-to-location map:") {
				tempHumFound = false;
				humLocFound = true;
			}

			if (tempHumFound) {
				temp = transform(line);
				tempHum.insert(temp.begin(), temp.end());
			}

			if (line == "temperature-to-humidity map:") {
				lightTempFound = false;
				tempHumFound = true;

			}

			if (lightTempFound) {
				temp = transform(line);
				lightTemp.insert(temp.begin(), temp.end());
			}

			if (line == "light-to-temperature map:") {
				waterLightFound = false;
				lightTempFound = true;
			}

			if (waterLightFound) {
				temp = transform(line);
				waterLight.insert(temp.begin(), temp.end());
			}

			if (line == "water-to-light map:") {
				fertilizerWaterFound = false;
				waterLightFound = true;
			}

			if (fertilizerWaterFound) {
				temp = transform(line);
				fertilizerWater.insert(temp.begin(), temp.end());
			}

			if (line == "fertilizer-to-water map:") {
				soilFertilizerFound = false;
				fertilizerWaterFound = true;
			}

			if (soilFertilizerFound) {
				temp = transform(line);
				soilFertilizer.insert(temp.begin(), temp.end());
			}

			if (line == "soil-to-fertilizer map:") {
				seedSoilFound = false;
				soilFertilizerFound = true;
			}

			if (seedSoilFound) {
				temp = transform(line);
				seedSoil.insert(temp.begin(), temp.end());
			}

			if (line == "seed-to-soil map:") {
				seedSoilFound = true;
			}


		}

		if (line.find("seeds:") != -1) {
			seeds = getRanges(line);
		}

	}


	mappings = { humLoc, tempHum, lightTemp, waterLight, fertilizerWater, 
		soilFertilizer, seedSoil };


	/*for (pair<long long int, long long int> seedRange : seeds) {
		for (int i = seedRange.first; i < seedRange.first + seedRange.second; i++) {
			long long int temp = i;
			for (map<pair<long long int, long long int>, long long int> map : mappings) {
				temp = mapResultFast(map, temp);
			}
			locations.push_back(temp);

			
		}
	}*/

	//reverse mapping: beginnen zoeken met laagste locaties -> als seed bestaat -> laagste locatie

	int result = mapResultFastReverse(seedSoil, 51);

	bool laagsteGevonden = false;
	long long int laagsteLocatie = 0;
	long long int tempSeed = 0;

	while (!laagsteGevonden) {
		laagsteLocatie++;
		tempSeed = laagsteLocatie;
		for (map<pair<long long int, long long int>, long long int> map : mappings) {
			tempSeed = mapResultFastReverse(map, tempSeed);
		}

		for (pair<long long int, long long int> seedRange : seeds) {
			if (tempSeed > seedRange.first and tempSeed < (seedRange.first + seedRange.second)) {
				//laagste locatie in seedrange
				laagsteGevonden = true;
			}
		}
		
	}

	return laagsteLocatie;
}





int main()
{
	//vector<pair<long long int, long long int>> test = getRanges("seeds: 1187290020 247767461 40283135 64738286 2044483296 66221787 1777809491 103070898 108732160 261552692 3810626561 257826205 3045614911 65672948 744199732 300163578 3438684365 82800966 2808575117 229295075");


	cout << readFile("input.txt");
}

