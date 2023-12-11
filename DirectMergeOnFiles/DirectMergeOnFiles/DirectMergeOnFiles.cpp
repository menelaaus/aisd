#include "DirectMergeOnFiles.h"

int main()
{
    string fileName = "file.txt";
    const int numbersCount = 1000000;
    const int maxNumberValue = 100000;

    for (int i = 0; i < 10; i++) {
        switch (createAndSortFile(fileName, numbersCount, maxNumberValue)) {
        case 1:
            cout << "Test passed." << endl;
            break;

        case -1:
            cout << "Test failed: can't create file." << endl;
            break;

        case -2:
            cout << "Test failed: file isn't sorted." << endl;
            break;
        }
    }

    return 0;
}
