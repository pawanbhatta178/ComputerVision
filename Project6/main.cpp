#include <iostream>
#include <fstream>
#include <string>
#include <cstdarg>
using namespace std;

class Thinning
{
public:
    int numRows;
    int numCols;
    int minVal;
    int maxVal;
    int newMin;
    int newMax;
    int rowFrameSize;
    int colFrameSize;
    int extraRows;
    int extraCols;
    int changeFlag;
    int cycleCount;
    int **aryOne;
    int **aryTwo;

    Thinning(ifstream &input)
    {
        loadHeader(input);
        rowFrameSize = 1;
        colFrameSize = 1;
        extraRows = 2 * rowFrameSize;
        extraCols = 2 * colFrameSize;
        //dynamic allocation of zeroframeArray
        aryOne = new int *[numRows + extraRows];
        for (int i = 0; i < numRows + extraRows; i++)
        {
            aryOne[i] = new int[numCols + extraCols];
        }
        zero2D(aryOne, numRows + extraRows, numCols + extraCols);
    }

    void loadHeader(ifstream &input)
    {
        input >> numRows >> numCols >> minVal >> maxVal;
    }

    void loadImage(ifstream &input)
    {
        for (int i = rowFrameSize; i < numRows + rowFrameSize; i++)
        {
            for (int j = colFrameSize; j < numCols + colFrameSize; j++)
            {
                input >> aryOne[i][j];
            }
        }
    }

    void zero2D(int **ary, int numOfRows, int numOfCols)
    {
        for (int i = 0; i < numOfRows; i++)
        {
            for (int j = 0; j < numOfCols; j++)
            {
                ary[i][j] = 0;
            }
        }
    }

    void print2DArray(int **ary, int numOfRows, int numOfCols)
    {
        cout << numRows << " " << numCols << " " << minVal << " " << maxVal << endl;
        for (int i = 0; i < numOfRows; i++)
        {
            for (int j = 0; j < numOfCols; j++)
            {
                cout << ary[i][j] << " ";
            }
            cout << endl;
        }
    }

    // void imgReformat(ofstream &outFile)
    // {
    //     outFile << numRows << " " << numCols << " " << newMin << " " << newMax << endl;
    //     string str = to_string(newMax);
    //     int width = str.length();
    //     for (int i = rowFrameSize; i < numRows + rowFrameSize; i++)
    //     {
    //         for (int j = colFrameSize; j < numCols + colFrameSize; j++)
    //         {
    //             if (zeroFramedAry[i][j] == 0)
    //             {
    //                 outFile << "."
    //                         << " ";
    //             }
    //             else
    //             {
    //                 outFile << zeroFramedAry[i][j] << " ";
    //             }
    //             str = to_string(zeroFramedAry[i][j]);
    //             int ww = str.length();
    //             while (ww < width)
    //             {
    //                 outFile << " ";
    //                 ww++;
    //             }
    //         }
    //         outFile << endl;
    //     }
    // }

    // void printImg(ofstream &outFile)
    // {
    //     outFile << numRows << " " << numCols << " " << newMin << " " << newMax << endl;
    //     string str = to_string(newMax);
    //     int width = str.length();
    //     for (int i = rowFrameSize; i < numRows + rowFrameSize; i++)
    //     {
    //         for (int j = colFrameSize; j < numCols + colFrameSize; j++)
    //         {

    //             outFile << zeroFramedAry[i][j] << " ";
    //             str = to_string(zeroFramedAry[i][j]);
    //             int ww = str.length();
    //             while (ww < width)
    //             {
    //                 outFile << " ";
    //                 ww++;
    //             }
    //         }
    //         outFile << endl;
    //     }
    // }

    ~Thinning()
    {
        for (int i = 0; i < numRows + extraRows; i++)
        {
            delete[] aryOne[i];
        }
    }
};

int main(int argc, const char *argv[])
{
    //READ
    string inputName = argv[1];
    ifstream input;
    input.open(inputName);

    //WRITES
    string thiningOutputName = argv[2], prettyPrintName = argv[3];
    ofstream thinningOutput, rfPrettyPrint;
    rfPrettyPrint.open(prettyPrintName);
    thinningOutput.open(thiningOutputName);

    //Checking if IO operations succeeds
    if (input.is_open())
    {
        if (rfPrettyPrint.is_open() && thinningOutput.is_open())
        {
            Thinning t(input);
            t.loadImage(input);
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

    input.close();
    rfPrettyPrint.close();
    thinningOutput.close();
    return 0;
}