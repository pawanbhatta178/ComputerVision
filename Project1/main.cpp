#include <iostream>
#include <fstream>
using namespace std;

const int MAX_PLUS = 70;

int toInt(string input)
{
    return stoi(input);
}

string getPlus(int numberOfPlus)
{
    string returnVal = "";
    if (numberOfPlus > MAX_PLUS)
    {
        numberOfPlus = MAX_PLUS;
    }
    for (int k = 0; k < numberOfPlus; k++)
    {
        returnVal = returnVal + "+";
    }
    return returnVal;
}

class Image
{
public:
    int numRows, numCols, minVal, maxVal;
    int *histAry;
    int thresholdValue;

    void computeHist(ifstream &input)
    {
        for (int i{0}; i < this->numRows; ++i)
        {
            for (int j{0}; j < this->numCols; ++j)
            {
                int pixelValue;
                input >> pixelValue;
                histAry[pixelValue]++;
            }
        }
    }

    void printHist(ofstream &output)
    {
        output << this->numRows << " " << this->numCols << " " << this->minVal << " " << this->maxVal << endl;

        for (int i = 0; i < maxVal + 1; ++i)
        {
            output << i << " " << histAry[i] << endl;
        }
    }

    void dispHist(ofstream &output)
    {

        output << numRows << " " << numCols << " " << minVal << " " << maxVal << " " << endl;
        for (int i = 0; i < maxVal + 1; ++i)
        {
            output << i << " "
                   << "(" << histAry[i] << ") "
                   << ": " << getPlus(histAry[i]) << endl;
        }
    }

    void threshold(ifstream &input, ofstream &output3, ofstream &output4, int thrVal)
    {
        Image binaryImg;
        binaryImg.minVal = 0;
        binaryImg.maxVal = 1;
        int anon;
        input >> binaryImg.numRows >> binaryImg.numCols >> anon >> anon;

        output3 << binaryImg.numRows << " " << binaryImg.numCols << " " << binaryImg.minVal << " " << binaryImg.maxVal << " " << endl;
        output4 << binaryImg.numRows << " " << binaryImg.numCols << " " << binaryImg.minVal << " " << binaryImg.maxVal << " " << endl;

        for (int i{0}; i < this->numRows; ++i)
        {

            for (int j{0}; j < this->numCols; ++j)
            {
                int pixelValue;
                input >> pixelValue;
                if (pixelValue >= thrVal)
                {
                    output3 << "1 ";
                    output4 << "1 ";
                }
                else
                {
                    output3 << "0 ";
                    output4 << ". ";
                }
            }
            output3 << endl;
            output4 << endl;
        }
    };
};

int main(int argc, const char *argv[])
{
    //READ
    string inputName = argv[1]; //(1) get the input file
    ifstream input;             //(2) instantiate the input
    input.open(inputName);      //(3) tell the input object

    //WRITES
    string outputName1{argv[3]}, outputName2{argv[4]}, outputName3{argv[5]}, outputName4{argv[6]};
    ofstream output1, output2, output3, output4;
    output1.open(outputName1);
    output2.open(outputName2);
    output3.open(outputName3);
    output4.open(outputName4);

    if (input.is_open())
    {

        if (output1.is_open() && output2.is_open() && output3.is_open() && output4.is_open())
        {
            Image img;
            input >> img.numRows >> img.numCols >> img.minVal >> img.maxVal;
            img.histAry = new int[img.maxVal + 1](); //dynamically alloacted and initialized to zero
            img.computeHist(input);
            img.printHist(output1);
            img.dispHist(output2);
            input.close();
            input.open(inputName);
            int thrVal = toInt(argv[2]);
            output3 << "The threshold value uses is " << thrVal << endl;
            output4 << "The threshold value uses is " << thrVal << endl;
            img.threshold(input, output3, output4, thrVal);
        }
        else
        {
            cout << "Error: Some output files couldnt be opened" << endl;
        }
    }
    else
    {
        cout << "Error: " << inputName << endl;
    };

    output1.close();
    output2.close();
    output3.close();
    output4.close();
    return 0;
}
