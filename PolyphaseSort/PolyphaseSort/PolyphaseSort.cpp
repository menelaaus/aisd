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

enum ErrorCode
{
	errorOpenFile 
};

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

int splittingFile(int* D, int n, fstream** files, ifstream* initialFile)
{
	int N = 0;
	int* A = new int[n];
	for (int i = 0; i < n; i++) A[i] = D[i] = 1;
	A[n - 1] = D[n - 1] = 0;
	int nextNumber;
	*initialFile >> nextNumber;
	while (*initialFile)
	{
		for (int i = 0; (i < n) && *initialFile && (D[i] != 0); i++)
		{
			while ((D[i] > 0) && (*initialFile))
			{
				int lastNumber;
				do
				{
					*files[i] << " " << nextNumber;
					lastNumber = nextNumber;
					*initialFile >> nextNumber;
				} while ((lastNumber <= nextNumber) && (*initialFile));

				D[i]--;
				*files[i] << " " << -1;
			}
		}
		N++;
		if (*initialFile)
		{
			int oldA0 = A[0];
			for (int i = 0; i < (n - 1); i++)
			{
				D[i] = A[i + 1] - A[i] + oldA0;
				A[i] = A[i + 1] + oldA0;
			}
		}
	}
	cout << "A: ";
	for (int i = 0; i < n; i++)
		cout << A[i] << " ";
	delete[]A;
	return N;
}
