#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int toInt(string input)
{
    return stoi(input);
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
    void printHist()
    {
    }
    void dispHist()
    {
    }
    void threshold()
    {
    }
};

int main()
{
    int threshold = 5;
    Image img;
    img.computeHist("input.txt");
    img.setThreshold(threshold);
    int *histogramData = img.getHistogram();
    for (int i = 0; i < img.getMaxVal(); i++)
    {
        cout << histogramData[i] << endl;
    }
}