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

void partitioningPhase(fstream& file, fstream* FilesToWrite, int p)
{
	int readableElement;
	file >> readableElement;

	int fileNumber = 0;
	while (file)
	{
		for (int i = 0; file && (i < p); i++)
		{
			FilesToWrite[fileNumber] << readableElement << " ";
			file >> readableElement;
		}
		fileNumber = 1 - fileNumber;
	}
}

int mergePhase(fstream* FilesToRead, fstream* FilesToWrite, int p)
{
	int ReadableElement[2];
	FilesToRead[0] >> ReadableElement[0];
	FilesToRead[1] >> ReadableElement[1];
	int fileNumber = 0;
	while (FilesToRead[0] && FilesToRead[1])
	{
		int i = 0, j = 0;
		while ((FilesToRead[0] && FilesToRead[1]) && i < p && j < p)
		{
			if (ReadableElement[0] < ReadableElement[1])
			{
				FilesToWrite[fileNumber] << ReadableElement[0] << " ";
				FilesToRead[0] >> ReadableElement[0];
				i++;
			}
			else
			{
				FilesToWrite[fileNumber] << ReadableElement[1] << " ";
				FilesToRead[1] >> ReadableElement[1];
				j++;
			}
		}

		while (FilesToRead[0] && (i < p))
		{
			FilesToWrite[fileNumber] << ReadableElement[0] << " ";
			FilesToRead[0] >> ReadableElement[0];
			i++;
		}

		while (FilesToRead[1] && (j < p))
		{
			FilesToWrite[fileNumber] << ReadableElement[1] << " ";
			FilesToRead[1] >> ReadableElement[1];
			j++;
		}
		fileNumber = 1 - fileNumber;
	}

	while (FilesToRead[0])
	{
		FilesToWrite[fileNumber] << ReadableElement[0] << " ";
		FilesToRead[0] >> ReadableElement[0];
	}
	while (FilesToRead[1])
	{
		FilesToWrite[fileNumber] << ReadableElement[1] << " ";
		FilesToRead[1] >> ReadableElement[1];
	}
	return 0;
}

bool notEmptyFile(fstream& file)
{
	if (file.peek() == ifstream::traits_type::eof())
	{
		return false;
	}
	return true;
}

int sort(const std::string& fileName)
{
	int p = 1;
	fstream file(fileName, fstream::in);
	fstream FilesToWrite[2] = {
		fstream("a.txt", fstream::out),
		fstream("b.txt", fstream::out),
	};

	for (int i = 0; i < 2; i++)
	{
		if (!file.is_open() || !FilesToWrite[i].is_open())
		{
			return -1;
		}
	}

	partitioningPhase(file, FilesToWrite, p);

	bool isSecondFileNotEmpty = notEmptyFile(FilesToWrite[1]);

	for (int i = 0; i < 2; i++)
	{
		FilesToWrite[i].close();
	}
	file.close();

	while (isSecondFileNotEmpty)
	{
		FilesToWrite[0].open("a.txt", fstream::in);
		FilesToWrite[1].open("b.txt", fstream::in);

		fstream FilesToRead[2] = {
			fstream("c.txt", fstream::out),
			fstream("d.txt", fstream::out),
		};

		mergePhase(FilesToWrite, FilesToRead, p);

		for (int i = 0; i < 2; i++)
		{
			FilesToWrite[i].close();
			FilesToRead[i].close();
		}

		p = 2 * p;

		FilesToRead[0].open("c.txt", fstream::in);
		FilesToRead[1].open("d.txt", fstream::in);

		FilesToWrite[0].open("a.txt", fstream::out);
		FilesToWrite[1].open("b.txt", fstream::out);

		mergePhase(FilesToRead, FilesToWrite, p);
		isSecondFileNotEmpty = notEmptyFile(FilesToWrite[1]);

		for (int i = 0; i < 2; i++)
		{
			FilesToWrite[i].close();
			FilesToRead[i].close();
		}
		p = 2 * p;
	}
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

