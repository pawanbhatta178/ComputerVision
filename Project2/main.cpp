#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int toInt(string input)
{
    return stoi(input);
}

class ImageProcessing
{
public:
    int numRows, numCols, minVal, maxVal, newMin, newMax, thrVal;
    int neighborAry[9];
    int CPmasks[8][5][5];
    int neighbor5x5[5][5];
    int **mirror3by3Ary;
    int **mirror5by5Ary;
    int **avgAry;
    int **medianAry;
    int **CPAry;

    void threshold(int *arr1, int *arr2, int frameSize) {}

    void imgReformat(int *inAry, ofstream &outImg, int frameSize)
    {
        outImg << numRows << " " << numCols << " " << newMin << " " << newMax << endl;
    }

    void loadCPmasks()
    {
    }

    void loadNeighbors()
    {
    }
    void loadImage(ifstream &input)
    {
        mirror3by3Ary = new int *[numRows + 2];
        for (int i = 0; i < numRows + 2; ++i)
        {
            mirror3by3Ary[i] = new int[numCols + 2]();
        }

        mirror5by5Ary = new int *[numRows + 4]();
        for (int i = 0; i < numRows + 4; ++i)
        {
            mirror5by5Ary[i] = new int[numCols + 4];
        }

        for (int i = 1; i < numRows + 1; ++i)
        {
            for (int j = 1; j < numCols + 1; ++j)
            {
                input >> mirror3by3Ary[i][j];
            }
        }

        for (int i = 0; i < numRows; ++i)
        {
            for (int j = 0; j < numCols; ++j)
            {
                int pixel;
                input >> pixel;
                mirror3by3Ary[i][j] = pixel;
                mirror5by5Ary[i][j] = pixel;
            }
        }

        for (int i = 1; i < numRows + 1; ++i)
        {
            cout << endl;
            for (int j = 1; j < numCols + 1; ++j)
            {
                cout << mirror3by3Ary[i][j];
            }
        }

        cout << endl
             << "5x5" << endl;
        for (int i = 1; i < numRows + 1; ++i)
        {

            for (int j = 2; j < numCols + 2; ++j)
            {
                cout << mirror5by5Ary[i][j];
            }
        }
    }

    void mirrorFraming(int **ary, int frameSize)
    {
    }
    void computeAvg()
    {
    }
    void computeMedian()
    {
    }
    void computeCPfilter()
    {
    }
    void sort(int *neighborAry)
    {
    }
    int avg3x3(int i, int j)
    {
        return 0;
    }
    int median3x3(int i, int j)
    {
        return 0;
    }
    int CP5x5(int i, int j)
    {
        return 0;
    }
    int convolution()
    {
        return 0;
    }
    void aryToFile(int **ary, ofstream &outFile, int frameSize)
    {
    }
    void prettyPrint(int **inAry, ofstream &outFile)
    {
    }

    void cleanUp()
    {
        for (int i = 0; i < numRows + 2; ++i)
        {
            delete[] mirror3by3Ary[i];
        }
        delete[] mirror3by3Ary;
    }
};

int main(int argc, const char *argv[])
{
    //READ
    string inputName = argv[1];
    ifstream input;
    input.open(inputName);

    int thrVal = toInt(argv[2]);

    //WRITES
    string rfImgName = argv[3], avgOutImgName = argv[4], avgThrImgName = argv[5], avgPrettyPrintName = argv[6], medianOutImgName = argv[7], medianThrImgName = argv[8], medianPrettyPrintName = argv[9], CPOutImgName = argv[10], CPThrImgName = argv[11], CPPrettyPrintName = argv[12];
    ofstream rfImg, AvgOutImg, AvgThrImg, AvgPrettyPrint, MedianOutImg, MedianThrImg, MedianPrettyPrint, CPOutImg, CPThrImg, CPPrettyPrint;
    rfImg.open(rfImgName);
    AvgOutImg.open(avgOutImgName);
    AvgThrImg.open(avgThrImgName);
    AvgPrettyPrint.open(avgPrettyPrintName);
    MedianOutImg.open(medianOutImgName);
    MedianThrImg.open(medianThrImgName);
    MedianPrettyPrint.open(medianPrettyPrintName);
    CPOutImg.open(CPOutImgName);
    CPThrImg.open(CPThrImgName);
    CPPrettyPrint.open(CPPrettyPrintName);

    if (input.is_open())
    {

        if (rfImg.is_open() && AvgOutImg.is_open() && AvgThrImg.is_open() && AvgPrettyPrint.is_open() && MedianOutImg.is_open() && MedianThrImg.is_open() && MedianPrettyPrint.is_open() && CPOutImg.is_open() && CPThrImg.is_open() && CPPrettyPrint.is_open())
        {
            ImageProcessing imgProcessing;
            imgProcessing.thrVal = thrVal;
            input >> imgProcessing.numRows >> imgProcessing.numCols >> imgProcessing.minVal >> imgProcessing.maxVal;
            imgProcessing.newMin = imgProcessing.minVal;
            imgProcessing.newMax = imgProcessing.maxVal;

            imgProcessing.loadImage(input);
        }
        else
        {
            cout << "Error: Some output files is missing or couldnt be opened" << endl;
        }
    }
    else
    {
        cout << "Error: Reading the input file: " << inputName << endl;
    };

    rfImg.close();
    AvgOutImg.close();
    AvgThrImg.close();
    AvgPrettyPrint.close();
    MedianOutImg.close();
    MedianThrImg.close();
    MedianPrettyPrint.close();
    CPOutImg.close();
    CPThrImg.close();
    CPPrettyPrint.close();
    return 0;
}
