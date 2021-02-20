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

    void threshold(int **ary1, int **ary2, int frameSize)
    {
        newMin = 0;
        newMax = 1;

        int r = frameSize;
        while (r < numRows + frameSize)
        {
            int c = frameSize;
            while (c < numCols + frameSize)
            {
                if (ary1[r][c] >= thrVal)
                {
                    ary2[r][c] = 1;
                    cout << ary2[r][c];
                }
                else
                {
                    ary2[r][c] = 0;
                    cout << ary2[r][c];
                }
                c++;
            }
            cout << endl;
            r++;
        }
    }

    void imgReformat(int **inAry, ofstream &outImg, int frameSize)
    {

        outImg << numRows << " " << numCols << " " << newMin << " " << newMax << endl;
        string str = to_string(newMax);
        int width = str.length();
        int r = frameSize;
        while (r < (numRows + frameSize))
        {
            int c = frameSize;
            while (c < (numCols + frameSize))
            {
                outImg << inAry[r][c];
                str = to_string(inAry[r][c]);
                int ww = str.length();
                while (ww < width)
                {
                    outImg << " ";
                    ww++;
                }
                c++;
            }
            r++;
            outImg << endl;
        }
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

        for (int i = 0; i < numRows; ++i)
        {
            for (int j = 0; j < numCols; ++j)
            {
                int pixel;
                input >> pixel;
                mirror3by3Ary[i + 1][j + 1] = pixel;
                mirror5by5Ary[i + 2][j + 2] = pixel;
            }
        }
    }

    void mirrorFraming(int **ary, int frameSize)
    {
        int totalRows = numRows + 2 * frameSize;
        int totalCols = numCols + 2 * frameSize;

        int yDiff = 1;
        for (int i = frameSize - 1; i >= 0; i--)
        {
            if (frameSize == 1)
            {
                mirror3by3Ary[i] = ary[i + yDiff];
            }
            if (frameSize == 2)
            {
                mirror5by5Ary[i] = ary[i + yDiff];
            }
            yDiff = yDiff + 2;
        }
        yDiff = 1;
        for (int i = totalRows - frameSize; i < totalRows; ++i)
        {

            for (int j = 0; j < totalCols; j++)
            {
                if (frameSize == 1)
                {
                    mirror3by3Ary[i] = ary[i - yDiff];
                }
                if (frameSize == 2)
                {
                    mirror5by5Ary[i] = ary[i - yDiff];
                }
            }
            yDiff = yDiff + 2;
        }

        int xDiff = 1;
        for (int i = frameSize - 1; i >= 0; i--)
        {

            for (int j = 0; j < totalRows; j++)
            {
                if (frameSize == 1)
                {
                    mirror3by3Ary[j][i] = ary[j][i + xDiff];
                }
                if (frameSize == 2)
                {
                    mirror5by5Ary[j][i] = ary[j][i + xDiff];
                }
            }
            xDiff = xDiff + 2;
        }
        xDiff = 1;
        for (int i = totalCols - frameSize; i < totalCols; ++i)
        {

            for (int j = 0; j < totalRows; j++)
            {
                if (frameSize == 1)
                {
                    mirror3by3Ary[j][i] = ary[j][i - xDiff];
                }
                if (frameSize == 2)
                {
                    mirror5by5Ary[j][i] = ary[j][i - xDiff];
                }
            }
            xDiff = xDiff + 2;
        }

        for (int i = 0; i < totalCols; ++i)
        {

            for (int j = 0; j < totalRows; ++j)
            {
                if (frameSize == 1)
                {
                    cout << mirror3by3Ary[i][j] << " ";
                }
                else
                {
                    cout << mirror5by5Ary[i][j] << " ";
                }
            }
            cout << endl;
        }
    }
    void computeAvg()
    {
        newMin = 9999;
        newMax = 1;
        avgAry = new int *[numRows + 2];
        for (int i = 0; i < numRows + 2; ++i)
        {
            avgAry[i] = new int[numCols + 2]();
        }

        int r = 1;
        while (r < numRows + 1)
        {
            int c = 1;
            while (c < numCols + 1)
            {
                avgAry[r][c] = avg3x3(r, c);
                if (newMin > avgAry[r][c])
                {
                    newMin = avgAry[r][c];
                }
                if (newMax < avgAry[r][c])
                {
                    newMax = avgAry[r][c];
                }
                c++;
            }
            r++;
        }
        mirrorFraming(avgAry, 1);
    }

    void computeMedian()
    {
        newMin = 9999;
        newMax = 0;
        medianAry = new int *[numRows + 2];
        for (int i = 0; i < numRows + 2; ++i)
        {
            medianAry[i] = new int[numCols + 2]();
        }

        int r = 1;
        while (r < numRows + 1)
        {
            int c = 1;
            while (c < numCols + 1)
            {
                medianAry[r][c] = median3x3(r, c);
                if (newMin > medianAry[r][c])
                {
                    newMin = medianAry[r][c];
                }
                if (newMax < medianAry[r][c])
                {
                    newMax = medianAry[r][c];
                }
                c++;
            }
            r++;
        }
    }
    void computeCPfilter()
    {
        newMin = 9999;
        newMax = 0;
        CPAry = new int *[numRows + 4];
        for (int i = 0; i < numRows + 4; ++i)
        {
            CPAry[i] = new int[numCols + 4]();
        }
        int r = 2;
        while (r < numRows + 2)
        {
            int c = 2;
            while (c < numCols + 2)
            {
                CPAry[r][c] = CP5x5(r, c);
                if (newMin > CPAry[r][c])
                {
                    newMin = CPAry[r][c];
                }
                if (newMax < CPAry[r][c])
                {
                    newMax = CPAry[r][c];
                }
                c++;
            }
            r++;
        }
    }
    void sort(int *neighborAry)
    {
        int temp;
        for (int i = 0; i < 9; i++)
        {
            for (int j = i + 1; j < 9; j++)
            {
                if (neighborAry[i] > neighborAry[j])
                {
                    temp = neighborAry[i];
                    neighborAry[i] = neighborAry[j];
                    neighborAry[j] = temp;
                }
            }
        }
        // for (int i = 0; i < 9; i++)
        // {
        //     cout << neighborAry[i] << " ";
        // }
        // cout << endl;
    }
    int avg3x3(int i, int j)
    {
        const int frameSize = 1;
        const int totalCols = 2 * frameSize + 1;
        const int totalRows = 2 * frameSize + 1;
        const int totalCells = totalCols * totalRows;
        int sum = 0;
        int r = i - frameSize;
        while (r <= (i + frameSize))
        {
            if (r >= 0 && r < numRows + frameSize)
            {
                int c = j - frameSize;
                while (c <= (j + frameSize))
                {
                    if (c >= 0 && c < numCols + frameSize)
                    {
                        cout << mirror3by3Ary[r][c] << endl;
                        sum += mirror3by3Ary[r][c];
                    }
                    c++;
                }
            }
            r++;
        }
        int avg = sum / totalCells;
        return avg;
    }

    int median3x3(int i, int j)
    {
        const int frameSize = 1;
        const int totalCols = 2 * frameSize + 1;
        const int totalRows = 2 * frameSize + 1;
        const int totalCells = totalCols * totalRows;

        int r = i - frameSize;

        int index = 0;
        while (r <= (i + frameSize))
        {
            if (r >= 0 && r < numRows + frameSize)
            {
                int c = j - frameSize;
                while (c <= (j + frameSize))
                {
                    if (c >= 0 && c < numCols + frameSize)
                    {
                        neighborAry[index] = mirror3by3Ary[r][c];
                        index++;
                    }
                    c++;
                }
            }
            r++;
        }
        sort(neighborAry);
        int median = neighborAry[5];
        return median;
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
        imgReformat(ary, outFile, frameSize);
    }

    void prettyPrint(int **inAry, ofstream &outFile, int frameSize)
    {
        outFile << numRows << " " << numCols << " " << newMin << " " << newMax << endl;
        newMin = 0;
        newMax = 1;

        int r = frameSize;
        while (r < numRows + frameSize)
        {
            int c = frameSize;
            while (c < numCols + frameSize)
            {
                if (inAry[r][c] > 0)
                {
                    outFile << 1 << " ";
                }
                else
                {
                    outFile << ". ";
                }
                c++;
            }
            outFile << endl;
            r++;
        }
    }

    void copy2DArray(int **ary1, int **ary2)
    {
        ary2 = new int *[numRows + 2];
        for (int i = 0; i < numRows + 2; ++i)
        {
            ary2[i] = new int[numCols + 2]();
        }
        for (int i = 0; i < numRows + 2; ++i)
        {
            for (int j = 0; j < numCols; j++)
            {
                ary2[i][j] = ary1[i][j];
            }
        }
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
            imgProcessing.mirrorFraming(imgProcessing.mirror3by3Ary, 1);
            imgProcessing.imgReformat(imgProcessing.mirror3by3Ary, rfImg, 1);
            imgProcessing.computeAvg();
            imgProcessing.imgReformat(imgProcessing.avgAry, AvgOutImg, 1);
            int **thrAry;
            thrAry = new int *[imgProcessing.numRows + 2];
            for (int i = 0; i < imgProcessing.numRows + 2; ++i)
            {
                thrAry[i] = new int[imgProcessing.numCols + 2]();
            }
            imgProcessing.threshold(imgProcessing.avgAry, thrAry, 1);

            imgProcessing.aryToFile(thrAry, AvgThrImg, 1);

            imgProcessing.prettyPrint(thrAry, AvgPrettyPrint, 1);

            imgProcessing.computeMedian();

            imgProcessing.imgReformat(imgProcessing.medianAry, MedianOutImg, 1);

            imgProcessing.threshold(imgProcessing.medianAry, thrAry, 1);

            imgProcessing.aryToFile(thrAry, MedianThrImg, 1);

            imgProcessing.prettyPrint(thrAry, MedianPrettyPrint, 1);

            imgProcessing.mirrorFraming(imgProcessing.mirror5by5Ary, 2);

            imgProcessing.computeCPfilter();

            imgProcessing.imgReformat(imgProcessing.CPAry, CPOutImg, 2);

            imgProcessing.threshold(imgProcessing.CPAry, thrAry, 1);

            imgProcessing.aryToFile(thrAry, CPThrImg, 2);

            imgProcessing.prettyPrint(thrAry, CPPrettyPrint, 2);
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
