#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class CClabel
{

public:
};

int main(int argc, const char *argv[])
{
    //READ
    string inputName = argv[1];
    ifstream input;
    input.open(inputName);
    int connectedness = stoi(argv[2]);

    //WRITES
    string rfPrettyPrintFileName = argv[3], labelFileName = argv[4], propertyFileName = argv[5];
    ofstream rfPrettyPrint, labelFile, propertyFile;
    rfPrettyPrint.open(rfPrettyPrintFileName);
    labelFile.open(labelFileName);
    propertyFile.open(propertyFileName);

    //Checking if IO operations succeeds
    if (input.is_open())
    {
        if (rfPrettyPrint.is_open() && labelFile.is_open() && propertyFile.is_open())
        {
        }
        else
        {
            cout << "ERROR: Some output files is missing or couldnt be opened." << endl;
        }
    }
    else
    {
        cout << "ERROR: The input file with following name does not exists or there was problem reading it: " << inputName << endl;
    }
}