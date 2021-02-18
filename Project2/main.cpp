#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int toInt(string input)
{
    return stoi(input);
}

class imageProcessing
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

    void imgReformat(int *inAry, imageProcessing *outImg, int frameSize)
    {
    }

    void loadCPmasks()
    {
    }

    void loadNeighbors()
    {
    }
    void loadImage()
    {
    }
    void mirrorFraming(int *ary, int frameSize)
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
    }
    int median3x3(int i, int j)
    {
    }
    int CP5x5(int i, int j)
    {
    }
    int convolution()
    {
    }
    void aryToFile(int **ary, ofstream &outFile, int frameSize)
    {
    }
    void prettyPrint(int **inAry, ofstream &outFile)
    {
    }
};

int main(int argc, const char *argv[])
{
    //READ
    string inputName = argv[1]; //(1) get the input file
    ifstream input;             //(2) instantiate the input
    input.open(inputName);      //(3) tell the input object
    int thrVal = toInt(argv[2]);

    //WRITES
    string rfImgName{argv[3]}, avgOutImgName{argv[4]}, avgThrImgName{argv[5]}, avgPrettyPrintName{argv[6]}, medianOutImgName{argv[7]}, medianThrImgName{argv[8]}, medianPrettyPrintName{argv[9]}, CPOutImgName{argv[10]}, CPThrImgName{argv[11]}, CPPrettyPrintName{argv[12]};
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
