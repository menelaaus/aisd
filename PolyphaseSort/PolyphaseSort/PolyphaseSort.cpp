#include <iostream>
#include <fstream>
#include <random>

using std::cin;
using std::cout;
using std::string;
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::endl;
using std::ios;

bool createFileWithRandomNumbers(const string& fileName, const int numbersCount, const int maxNumberValue = 100) {
	ofstream file(fileName);
	if (!file) throw errorOpenFile;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dist(0, maxNumberValue);
	int* x;
	for (int i = 0; i < numbersCount; i++)
	{
		x[i] = dist(gen);
		file << " " << x[i];
	}
}

bool isFileContainsSortedArray(const string& fileName) {
	ifstream file(fileName);
	if (!file) throw errorOpenFile;
	int lastNumber;
	file >> lastNumber;
	bool fileSorted = 1;
	int newNumber;
	while ((file >> newNumber) && fileSorted)
	{
		if (newNumber < lastNumber) fileSorted = 0;
		lastNumber = newNumber;
	}
	if (fileSorted) cout << "File " << fileName << " was sorted" << endl;
	else cout << "File " << fileName << " was not sorted" << endl;
	return fileSorted;
}
