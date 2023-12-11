#pragma once
#include <iostream>
#include <fstream>
#include <random>
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::string;
using std::cout;
using std::endl;

bool createFileWithRandomNumbers(const string& fileName, const int numbersCount, const int maxNumberValue)
{
	fstream file;
	file.open(fileName, fstream::out);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dist(0, maxNumberValue);
	for (int i = 0; i < numbersCount; i++)
	{
		file << int(dist(gen)) << " ";
	}

	if (!file.is_open())
	{
		return false;
	}
	else
	{
		file.close();
		return true;
	}
}


bool isFileContainsSortedArray(const string& fileName)
{
	fstream file(fileName, fstream::in);
	if (!file.is_open())
	{
		return -1;
	}
	int a, b;
	file >> a;
	while (file >> b)
	{
		if (a > b)
		{
			return false;
		}
		a = b;
	}
	return true;
}


int createAndSortFile(const string& fileName, const int numbersCount, const int maxNumberValue)
{
	if (!createFileWithRandomNumbers(fileName, numbersCount, maxNumberValue)) {
		return -1;
	}

	//sortFile(fileName);

	if (!isFileContainsSortedArray(fileName)) {
		return -2;
	}
	return 1;
}

