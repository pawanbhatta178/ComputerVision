#include <iostream>
#include <fstream>
#include <string>
#include <cstdarg>
using namespace std;

class Encoding
{
public:
    int numRows;
    int numCols;
    int minVal;
    int maxVal;
    int startRow;
    int startCol;
    int greyScale;
    int length;
    int **img;

    Encoding(ifstream &inputFile)
    {
        loadHeader(inputFile);

        img = new int *[numRows];

        for (int i = 0; i < numRows; i++)
        {
            img[i] = new int[numCols];
        }

        loadImage(inputFile);
    }

    void loadHeader(ifstream &inputImg)
    {
        inputImg >> numRows >> numCols >> minVal >> maxVal;
    }

    void loadImage(ifstream &inputImg)
    {
        for (int i = 0; i < numRows; i++)
        {
            for (int j = 0; j < numCols; j++)
            {
                inputImg >> img[i][j];
            }
        }
    }

    void print2DArray()
    {
        for (int i = 0; i < numRows; i++)
        {
            for (int j = 0; j < numCols; j++)
            {
                cout << img[i][j];
            }
            cout << "\n";
        }
    }

    void encodeOneRow(int row, ofstream &encodeFile, ofstream &debugFile)
    {
        startRow = row;
        startCol = 0;
        greyScale = img[row][0];
        length = 1;
        for (int i = 1; i < numCols; i++)
        {
            if (img[row][i] == greyScale)
            {
                length++;
            }
            else
            {
                encodeFile << row << " " << i << " " << greyScale << " " << length << " ";
                encodeFile << "\n";
                length = 1;
                greyScale = img[row][i];
            }

            if (i == numCols - 1)
            {
                encodeFile << row << " " << i << " " << greyScale << " " << length << " ";
                encodeFile << "\n";
                length = 1;
                greyScale = img[row][i];
            }
        }
    }
};

int main(int argc, const char *argv[])
{
    string inputFileName = argv[1];
    ifstream inputFile;
    inputFile.open(inputFileName);

    string encodeFileName = argv[2];
    ofstream encodeFile;
    encodeFile.open(encodeFileName);

    string debugFileName = argv[3];
    ofstream debugFile;
    debugFile.open(debugFileName);

    if (inputFile.is_open() && debugFile.is_open() && encodeFile.is_open())
    {
        Encoding t(inputFile);
        encodeFile << t.numRows << " " << t.numCols << " " << t.minVal << " " << t.maxVal << endl;
        for (int r = 0; r < t.numRows; r++)
        {
            t.encodeOneRow(r, encodeFile, debugFile);
        }
    }
    else
    {
        cout << "Error reading file." << endl;
    }

    inputFile.close();
    debugFile.close();
    encodeFile.close();
    return 0;
}