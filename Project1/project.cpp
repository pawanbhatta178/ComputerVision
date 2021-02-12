#include <iostream>
#include <fstream>
#include <sstream>
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
    int numRows, numCols, minVal, maxVal;
    int *histAry;
    int thresholdValue;

public:
    Image()
    {
        numRows = 0;
        numCols = 0;
        minVal = 0;
        maxVal = 0;
        thresholdValue = 0;
    }

    Image(int numRows, int numCols, int minVal, int maxVal, int thresholdValue = 0)
    {
        this->numRows = numRows;
        this->numCols = numCols;
        this->minVal = minVal;
        this->maxVal = maxVal;
        this->thresholdValue = thresholdValue;
        this->histAry = new int[maxVal + 1](); //dynamically alloacted and initialized to zero
    }

    void setThreshold(int threshold)
    {
        this->thresholdValue = threshold;
    }

    int getNumRows()
    {
        return numRows;
    }
    int getNumCols()
    {
        return numCols;
    }
    int getMinVal()
    {
        return minVal;
    }
    int getMaxVal()
    {
        return maxVal;
    }

    int getThreshold()
    {
        return thresholdValue;
    }

    int *getHistogram()
    {
        return histAry;
    }

    void computeHist(string inFile)
    {
        string header;
        ifstream input_file;
        input_file.open(inFile);
        if (input_file.good())
        {
            getline(input_file, header);
            stringstream ssin(header);
            if (ssin.good())
            {
                ssin >> numRows;
                ssin >> numCols;
                ssin >> minVal;
                ssin >> maxVal;
            };
            histAry = new int[maxVal + 1](); //dynamically alloacted and initialized to zero
            string row_data;
            while (getline(input_file, row_data))
            {
                istringstream ss(row_data);
                int num;
                while (ss >> num)
                {
                    histAry[num]++;
                }
            };
        }
        input_file.close();
    }

    void printHist(string outFile)
    {
        ofstream out_file;
        out_file.open(outFile);
        out_file << numRows << " " << numCols << " " << minVal << " " << maxVal << " " << endl;
        for (int i = 0; i < maxVal + 1; ++i)
        {
            out_file << i << " " << histAry[i] << endl;
        }
        out_file.close();
    }

    void dispHist(string outFile)
    {
        ofstream out_file;
        out_file.open(outFile);
        out_file << numRows << " " << numCols << " " << minVal << " " << maxVal << " " << endl;
        for (int i = 0; i < maxVal + 1; ++i)
        {
            out_file << i << " "
                     << "(" << histAry[i] << ") "
                     << ": " << getPlus(histAry[i]) << endl;
        }
        out_file.close();
    }

    void threshold(string inFile, string outFile3, string outFile4, int thrVal)
    {
        Image binaryImg(numRows, numCols, 0, 1, thresholdValue);
        ofstream out_file3, out_file4;
        out_file3.open(outFile3);
        out_file4.open(outFile4);
        out_file3 << binaryImg.getNumRows() << " " << binaryImg.getNumCols() << " " << binaryImg.getMinVal() << " " << binaryImg.getMaxVal() << " " << endl;
        out_file4 << binaryImg.getNumRows() << " " << binaryImg.getNumCols() << " " << binaryImg.getMinVal() << " " << binaryImg.getMaxVal() << " " << endl;
        ifstream input_file;
        input_file.open(inFile);
        string header;
        getline(input_file, header);
        string img_row;
        while (getline(input_file, img_row))
        {
            istringstream ss(img_row);
            int num;
            while (ss >> num)
            {
                if (num >= thrVal)
                {
                    out_file3 << "1 ";
                    out_file4 << "1 ";
                }
                else
                {
                    out_file3 << "0 ";
                    out_file4 << ". ";
                }
            }
            out_file3 << endl;
            out_file4 << endl;
        };
        input_file.close();
        out_file3.close();
        out_file4.close();
    }
};

int main(int argc, char **argv)
{
    int threshold = 5;
    Image img;
    img.computeHist(argv[1]);
    img.setThreshold(toInt(argv[2]));
    img.printHist(argv[3]);
    img.dispHist(argv[4]);
    img.threshold(argv[1], argv[5], argv[6], toInt(argv[2]));
}