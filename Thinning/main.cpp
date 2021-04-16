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

    int changeFlag;
    int cycleCount;
    int **aryOne;
    int **aryTwo;

    Thinning(ifstream &inputFile)
    {
        loadHeader(inputFile);

        aryOne = new int *[numRows + 2];
        aryTwo = new int *[numRows + 2];

        for (int i = 0; i < numRows + 2; i++)
        {
            aryOne[i] = new int[numCols + 2];
            aryTwo[i] = new int[numCols + 2];
        }
        zero2D(aryOne, numRows + 2, numCols + 2);
        zero2D(aryTwo, numRows + 2, numCols + 2);

        changeFlag = 1;
    }

    void loadHeader(ifstream &inputImg)
    {
        inputImg >> numRows >> numCols >> minVal >> maxVal;
    }

    void loadImage(ifstream &inputImg)
    {
        for (int i = 1; i < numRows + 1; i++)
        {
            for (int j = 1; j < numCols + 1; j++)
            {
                inputImg >> aryOne[i][j];
            }
        }
    }

    void zero2D(int **array, int r, int c)
    {
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                array[i][j] = 0;
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

    void imgReformat(ofstream &outFile, int **ary)
    {
        outFile << numRows << " " << numCols << " " << minVal << " " << maxVal << endl;
        int width = to_string(newMax).length();
        for (int i = 1; i < numRows + 1; i++)
        {
            for (int j = 1; j < numCols + 1; j++)
            {
                if (ary[i][j] == 0)
                {
                    outFile << "."
                            << " ";
                }
                else
                {
                    outFile << ary[i][j] << " ";
                }
                int currentLength = to_string(ary[i][j]).length();
                while (currentLength < width)
                {
                    outFile << " ";
                    currentLength++;
                }
            }
            outFile << endl;
        }
    }

    void printImg(ofstream &outFile)
    {
        outFile << numRows << " " << numCols << " " << minVal << " " << maxVal << endl;
        string str = to_string(newMax);
        int width = str.length();
        for (int i = 1; i < numRows + 1; i++)
        {
            for (int j = 1; j < numCols + 1; j++)
            {
                outFile << aryOne[i][j] << " ";
                str = to_string(aryOne[i][j]);
                int currentLength = str.length();
                while (currentLength < width)
                {
                    outFile << " ";
                    currentLength++;
                }
            }
            outFile << endl;
        }
    }

    void copyArys(int **array1, int **array2)
    {
        for (int i = 0; i < numRows + 2; i++)
        {
            for (int j = 0; j < numCols + 2; j++)
            {
                array1[i][j] = array2[i][j];
            }
        }
    }

    bool hasXNeighbors(int i, int j, int numOfObjectNeighbors)
    {
        int a = aryOne[i - 1][j - 1];
        int b = aryOne[i - 1][j];
        int c = aryOne[i - 1][j + 1];
        int d = aryOne[i][j - 1];
        int e = aryOne[i][j + 1];
        int f = aryOne[i + 1][j - 1];
        int g = aryOne[i + 1][j];
        int h = aryOne[i + 1][j + 1];
        int sum = a + b + c + d + e + f + g + h;

        if (sum >= numOfObjectNeighbors)
        {
            return true;
        }
        return false;
    }

    bool isConnector(int i, int j)
    {
        int a = aryOne[i - 1][j - 1];
        int b = aryOne[i - 1][j];
        int c = aryOne[i - 1][j + 1];
        int d = aryOne[i][j - 1];
        int e = aryOne[i][j + 1];
        int f = aryOne[i + 1][j - 1];
        int g = aryOne[i + 1][j];
        int h = aryOne[i + 1][j + 1];

        //case 1
        if (d == 0 && e == 0 && (a == 1 || b == 1 || c == 1) && (f == 1 || g == 1 || h == 1))
        {
            return true;
        }
        //case 2
        if (b == 0 && g == 0 && (a == 1 || d == 1 || f == 1) && (c == 1 || e == 1 || h == 1))
        {
            return true;
        }
        //case Alpha
        if (b == 0 && d == 0 && a == 1)
        {
            return true;
        }
        //case Beta
        if (d == 0 && g == 0 && f == 1)
        {
            return true;
        }
        //case Gamma
        if (b == 0 && e == 0 && c == 1)
        {
            return true;
        }

        //case delta
        if (g == 0 && e == 0 && h == 1)
        {
            return true;
        }
        return false;
    }

    void NorthThinning(int **array1, int **array2)
    {
        for (int i = 1; i < numRows + 1; i++)
        {
            for (int j = 1; j < numCols + 1; j++)
            {
                if (array1[i][j] > 0)
                {
                    array2[i][j] = 1;

                    if (array1[i - 1][j] == 0 && hasXNeighbors(i, j, 4) && !isConnector(i, j))
                    {
                        array2[i][j] = 0;
                        changeFlag++;
                    }
                }
            }
        }
    }

    void SouthThinning(int **array1, int **array2)
    {
        for (int i = 1; i < numRows + 1; i++)
        {
            for (int j = 1; j < numCols + 1; j++)
            {
                if (array1[i][j] > 0)
                {
                    array2[i][j] = 1;

                    if (array1[i + 1][j] == 0 && hasXNeighbors(i, j, 4) && !isConnector(i, j))
                    {
                        array2[i][j] = 0;
                        changeFlag++;
                    }
                }
            }
        }
    }

    void EastThinning(int **array1, int **array2)
    {
        for (int i = 1; i < numRows + 1; i++)
        {
            for (int j = 1; j < numCols + 1; j++)
            {
                if (array1[i][j] > 0)
                {
                    array2[i][j] = 1;

                    if (array1[i][j + 1] == 0 && hasXNeighbors(i, j, 3) && !isConnector(i, j))
                    {

                        array2[i][j] = 0;
                        //change occurs only if all 3 conditions are met
                        changeFlag++;
                    }
                }
            }
        }
    }

    void WestThinning(int **array1, int **array2)
    {
        for (int i = 1; i < numRows + 1; i++)
        {
            for (int j = 1; j < numCols + 1; j++)
            {
                if (array1[i][j] > 0)
                {
                    array2[i][j] = 1;

                    if (array1[i][j - 1] == 0 && hasXNeighbors(i, j, 3) && !isConnector(i, j))
                    {
                        array2[i][j] = 0;
                        //change occurs only if all 3 conditions are met
                        changeFlag++;
                    }
                }
            }
        }
    }
};

int main(int argc, const char *argv[])
{
    string inputFileName = argv[1];
    ifstream inputFile;
    inputFile.open(inputFileName);

    string thiningFileName = argv[2];
    ofstream thinningOutput;
    thinningOutput.open(thiningFileName);

    string prettyPrintFileName = argv[3];
    ofstream prettyPrint;
    prettyPrint.open(prettyPrintFileName);

    if (inputFile.is_open() && prettyPrint.is_open() && thinningOutput.is_open())
    {
        Thinning t(inputFile);
        t.loadImage(inputFile);
        prettyPrint << "Original Image" << endl;
        t.imgReformat(prettyPrint, t.aryOne);

        t.cycleCount = 0;
        while (t.changeFlag > 0)
        {
            t.changeFlag = 0;
            t.NorthThinning(t.aryOne, t.aryTwo);
            t.copyArys(t.aryOne, t.aryTwo);
            t.SouthThinning(t.aryOne, t.aryTwo);
            t.copyArys(t.aryOne, t.aryTwo);
            t.WestThinning(t.aryOne, t.aryTwo);
            t.copyArys(t.aryOne, t.aryTwo);
            t.EastThinning(t.aryOne, t.aryTwo);
            t.copyArys(t.aryOne, t.aryTwo);
            t.cycleCount++;
            prettyPrint << "\nResult of Thinning (N,S = 4): Cycle - " << t.cycleCount << endl;
            t.imgReformat(prettyPrint, t.aryOne);
        }
        t.printImg(thinningOutput);
    }
    else
    {
        cout << "Error reading file." << endl;
    }

    inputFile.close();
    prettyPrint.close();
    thinningOutput.close();
    return 0;
}