#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Property
{
    int label;
    int numPixels;
    int minR;
    int minC;
    int maxR;
    int maxC;

    Property()
    {
        label = -1;
        numPixels = 0;
        minC = 999;
        minR = 999;
        maxC = 0;
        maxR = 0;
    }
};

class CC
{
public:
    int numRows, numCols, minVal, maxVal, newMin, newMax, newLabel, trueNumCC;
    int **zeroFramedAry;
    int nonZeroNeighborAry[5];
    int *EQary;
    Property *CCproperty;

    CC(ifstream &imgFile)
    {
        loadHeader(imgFile);

        zeroFramedAry = new int *[numRows + 2];
        for (int i = 0; i < numCols + 2; i++)
        {
            zeroFramedAry[i] = new int[numCols + 2];
        }
        zero2DArray(zeroFramedAry, numRows + 2, numCols + 2);
        loadImage(imgFile);
    }

    void loadHeader(ifstream &imgFile)
    {
        imgFile >> numRows >> numCols >> minVal >> maxVal;
    }

    void loadImage(ifstream &imgFile)
    {
        for (int i = 0; i < numRows; i++)
        {
            for (int j = 0; j < numCols; j++)
            {
                imgFile >> zeroFramedAry[i + 1][j + 1];
            }
        }
    }

    bool hasSameLabel(int *ary, int firstXCheck)
    {
        int returnVal = true;
        int label = 0;
        for (int i = 0; i < firstXCheck; i++)
        {
            if (ary[i] != 0)
            {
                if (label == 0)
                {
                    label = ary[i];
                }
                else
                {
                    if (label != ary[i])
                    {
                        returnVal = false;
                    }
                }
            }
        }
        return returnVal;
    }

    int minLabel(int *ary, int firstXCheck)
    {
        int min = 999;
        for (int i = 0; i < firstXCheck; i++)
        {
            if (ary[i] != 0)
            {
                if (ary[i] < min)
                {
                    min = ary[i];
                }
            }
        }
        return min;
    }

    void manageEQAry()
    {
        int readLabel = 0;
        for (int i = 1; i <= newLabel; i++)
        {
            if (i != EQary[i])
            {
                EQary[i] = EQary[EQary[i]];
            }
            else
            {
                readLabel++;
                EQary[i] = readLabel;
            }
        }
        trueNumCC = readLabel;
    }

    void connect4Pass1()
    {
        newMax = 0;
        newMin = 9999;
        newLabel = 0;
        int EQsize = (numRows * numCols) / 4;
        EQary = new int[EQsize];
        for (int i = 0; i < EQsize; i++)
        {
            EQary[i] = i;
        }

        for (int i = 1; i < numRows + 1; i++)
        {
            for (int j = 1; j < numCols + 1; j++)
            {
                if (zeroFramedAry[i][j] > 0)
                {
                    nonZeroNeighborAry[0] = zeroFramedAry[i - 1][j];
                    nonZeroNeighborAry[1] = zeroFramedAry[i][j - 1];

                    //case 1
                    if (nonZeroNeighborAry[0] == 0 && nonZeroNeighborAry[1] == 0)
                    {
                        newLabel++;
                        zeroFramedAry[i][j] = newLabel;

                        EQary[newLabel] = newLabel;
                    }

                    //case 2
                    else if (hasSameLabel(nonZeroNeighborAry, 2))
                    {
                        zeroFramedAry[i][j] = minLabel(nonZeroNeighborAry, 2);
                    }

                    //case 3
                    else
                    {
                        int minVal = minLabel(nonZeroNeighborAry, 2);
                        zeroFramedAry[i][j] = minVal;

                        EQary[zeroFramedAry[i - 1][j]] = minVal;
                        EQary[zeroFramedAry[i][j - 1]] = minVal;
                    }
                    if (zeroFramedAry[i][j] < newMin)
                    {
                        newMin = zeroFramedAry[i][j];
                    }
                    if (zeroFramedAry[i][j] > newMax)
                    {
                        newMax = zeroFramedAry[i][j];
                    }
                }
            }
        }
    }

    void connect4Pass2()
    {
        newMin = 999;
        newMax = 0;
        for (int i = numRows; i >= 1; i--)
        {
            for (int j = numCols; j >= 1; j--)
            {
                if (zeroFramedAry[i][j] > 0)
                {
                    nonZeroNeighborAry[0] = zeroFramedAry[i][j + 1];
                    nonZeroNeighborAry[1] = zeroFramedAry[i + 1][j];
                    nonZeroNeighborAry[2] = zeroFramedAry[i][j];
                    //Case 1
                    if (nonZeroNeighborAry[0] == 0 && nonZeroNeighborAry[1] == 0)
                    {
                        //do nothing
                    }

                    //Case 2
                    else if (hasSameLabel(nonZeroNeighborAry, 3))
                    {
                        //do nothing
                    }

                    //Case 3
                    else
                    {
                        int minValue = minLabel(nonZeroNeighborAry, 3);
                        zeroFramedAry[i][j] = minValue;

                        //Updating EQ Table
                        if (zeroFramedAry[i][j] > minValue)
                        {
                            EQary[zeroFramedAry[i][j]] = minValue;
                        }

                        EQary[nonZeroNeighborAry[0]] = minValue;
                        EQary[nonZeroNeighborAry[1]] = minValue;
                    }

                    if (zeroFramedAry[i][j] < newMin)
                    {
                        newMin = zeroFramedAry[i][j];
                    }
                    if (zeroFramedAry[i][j] > newMax)
                    {
                        newMax = zeroFramedAry[i][j];
                    }
                }
            }
        }
    }

    void connect8Pass1()
    {
        newMax = 0;
        newMin = 9999;
        newLabel = 0;
        int EQsize = (numRows * numCols) / 4;
        EQary = new int[EQsize];
        for (int i = 0; i < EQsize; i++)
        {
            EQary[i] = i;
        }

        for (int i = 1; i < numRows + 1; i++)
        {
            for (int j = 1; j < numCols + 1; j++)
            {
                if (zeroFramedAry[i][j] > 0)
                {
                    nonZeroNeighborAry[0] = zeroFramedAry[i - 1][j - 1];
                    nonZeroNeighborAry[1] = zeroFramedAry[i - 1][j];
                    nonZeroNeighborAry[2] = zeroFramedAry[i - 1][j + 1];
                    nonZeroNeighborAry[3] = zeroFramedAry[i][j - 1];
                    //case 1
                    if (nonZeroNeighborAry[0] == 0 && nonZeroNeighborAry[1] == 0 && nonZeroNeighborAry[2] == 0 && nonZeroNeighborAry[3] == 0)
                    {
                        newLabel++;
                        zeroFramedAry[i][j] = newLabel;
                        EQary[newLabel] = newLabel;
                    }

                    //case 2
                    else if (hasSameLabel(nonZeroNeighborAry, 4))
                    {
                        zeroFramedAry[i][j] = minLabel(nonZeroNeighborAry, 4);
                    }

                    //case 3
                    else
                    {
                        int minVal = minLabel(nonZeroNeighborAry, 4);
                        zeroFramedAry[i][j] = minVal;

                        EQary[nonZeroNeighborAry[0]] = minVal;
                        EQary[nonZeroNeighborAry[1]] = minVal;
                        EQary[nonZeroNeighborAry[2]] = minVal;
                        EQary[nonZeroNeighborAry[3]] = minVal;
                    }
                    if (zeroFramedAry[i][j] < newMin)
                    {
                        newMin = zeroFramedAry[i][j];
                    }
                    if (zeroFramedAry[i][j] > newMax)
                    {
                        newMax = zeroFramedAry[i][j];
                    }
                }
            }
        }
    }

    void connect8Pass2()
    {
        newMin = 999;
        newMax = 0;
        for (int i = numRows; i >= 1; i--)
        {
            for (int j = numCols; j >= 1; j--)
            {
                if (zeroFramedAry[i][j] > 0)
                {
                    nonZeroNeighborAry[0] = zeroFramedAry[i][j + 1];
                    nonZeroNeighborAry[1] = zeroFramedAry[i + 1][j - 1];
                    nonZeroNeighborAry[2] = zeroFramedAry[i + 1][j];
                    nonZeroNeighborAry[3] = zeroFramedAry[i + 1][j + 1];
                    nonZeroNeighborAry[4] = zeroFramedAry[i][j];

                    //Case 1
                    if (nonZeroNeighborAry[0] == 0 && nonZeroNeighborAry[1] == 0 && nonZeroNeighborAry[2] == 0 && nonZeroNeighborAry[3] == 0)
                    {
                        //do nothing
                    }

                    //Case 2
                    else if (hasSameLabel(nonZeroNeighborAry, 5))
                    {
                        //do nothing
                    }

                    //Case 3
                    else
                    {
                        int minValue = minLabel(nonZeroNeighborAry, 5);
                        zeroFramedAry[i][j] = minValue;

                        //Updating EQ Table
                        if (zeroFramedAry[i][j] > minValue)
                        {
                            EQary[zeroFramedAry[i][j]] = minValue;
                        }

                        EQary[nonZeroNeighborAry[0]] = minValue;
                        EQary[nonZeroNeighborAry[1]] = minValue;
                        EQary[nonZeroNeighborAry[2]] = minValue;
                        EQary[nonZeroNeighborAry[3]] = minValue;
                        EQary[nonZeroNeighborAry[4]] = minValue;
                    }

                    if (zeroFramedAry[i][j] < newMin)
                    {
                        newMin = zeroFramedAry[i][j];
                    }
                    if (zeroFramedAry[i][j] > newMax)
                    {
                        newMax = zeroFramedAry[i][j];
                    }
                }
            }
        }
    }

    void connectPass3()
    {
        CCproperty = new Property[trueNumCC + 1]();
        newMax = 0;
        newMin = 999;
        for (int i = 1; i < numRows + 1; i++)
        {
            for (int j = 1; j < numCols + 1; j++)
            {
                if (zeroFramedAry[i][j] > 0)
                {
                    zeroFramedAry[i][j] = EQary[zeroFramedAry[i][j]];
                    Property *property = &CCproperty[zeroFramedAry[i][j]];
                    property->label = zeroFramedAry[i][j];
                    property->numPixels = property->numPixels + 1;

                    if (property->minR > i - 1)
                    {
                        property->minR = i - 1;
                    }
                    if (property->maxR < i - 1)
                    {
                        property->maxR = i - 1;
                    }
                    if (property->minC > j - 1)
                    {
                        property->minC = j - 1;
                    }
                    if (property->maxC < j - 1)
                    {
                        property->maxC = j - 1;
                    }
                }

                if (zeroFramedAry[i][j] < newMin)
                {
                    newMin = zeroFramedAry[i][j];
                }
                if (zeroFramedAry[i][j] > newMax)
                {
                    newMax = zeroFramedAry[i][j];
                }
            }
        }
    }

    void zero2DArray(int **ary, int rowSize, int colSize)
    {
        for (int i = 0; i < rowSize; i++)
        {
            for (int j = 0; j < colSize; j++)
            {
                ary[i][j] = 0;
            }
        }
    }

    void imgReformat(ofstream &outFile)
    {
        outFile << numRows << " " << numCols << " " << newMin << " " << newMax << endl;
        string max = to_string(newMax);
        int maxWidth = max.length();
        for (int i = 1; i < numRows + 1; i++)
        {
            for (int j = 1; j < numCols + 1; j++)
            {
                if (zeroFramedAry[i][j] == 0)
                {
                    outFile << "."
                            << " ";
                }
                else
                {
                    outFile << zeroFramedAry[i][j] << " ";
                }
                string s = to_string(zeroFramedAry[i][j]);
                int currentLength = s.length();
                while (currentLength < maxWidth)
                {
                    outFile << " ";
                    currentLength++;
                }
            }
            outFile << endl;
        }
        outFile << endl
                << endl;
    }

    void printEQAry(ofstream &outFile)
    {
        for (int i = 1; i <= newLabel; i++)
        {
            outFile << i << " " << EQary[i] << endl;
        }
        outFile << endl;
    }

    void printImg(ofstream &outFile)
    {
        outFile << numRows << " " << numCols << " " << newMin << " " << newMax << endl;
        string max = to_string(newMax);
        int maxWidth = max.length();
        for (int i = 1; i < numRows + 1; i++)
        {
            for (int j = 1; j < numCols + 1; j++)
            {

                outFile << zeroFramedAry[i][j] << " ";
                string s = to_string(zeroFramedAry[i][j]);
                int currentLength = s.length();
                while (currentLength < maxWidth)
                {
                    outFile << " ";
                    currentLength++;
                }
            }
            outFile << endl;
        }
        outFile << endl
                << endl;
    }

    void minus1DArray(int *ary, int arraySize)
    {
        for (int i = 0; i < arraySize; i++)
        {
            ary[i] = -1;
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

    void printCCproperty(ofstream &outFile)
    {
        outFile << numRows << " " << numCols << " " << newMin << " " << newMax << endl;
        outFile << trueNumCC << endl;
        outFile << endl;
        for (int i = 1; i < trueNumCC + 1; i++)
        {
            Property *p = &CCproperty[i];
            outFile << p->label << endl;
            outFile << p->numPixels << endl;
            outFile << p->minR << " " << p->minC << endl;
            outFile << p->maxR << " " << p->maxC << endl;
            outFile << endl;
        }
    }
    void drawBoxes()
    {
        int minR, minC, maxR, maxC, label;
        for (int i = 1; i < trueNumCC + 1; i++)
        {
            minR = CCproperty[i].minR + 1;
            minC = CCproperty[i].minC + 1;
            maxR = CCproperty[i].maxR + 1;
            maxC = CCproperty[i].maxC + 1;
            label = CCproperty[i].label;

            // top line
            for (int j = minC; j <= maxC; j++)
            {
                zeroFramedAry[minR][j] = label;
            }

            //bottom line
            for (int j = minC; j <= maxC; j++)
            {
                zeroFramedAry[maxR][j] = label;
            }

            //right line
            for (int i = minR; i <= maxR; i++)
            {
                zeroFramedAry[i][maxC] = label;
            }

            // left line
            for (int i = minR; i <= maxR; i++)
            {
                zeroFramedAry[i][minC] = label;
            }
        }
    }
};

int main(int argc, const char *argv[])
{
    string inputName = argv[1];
    int connectedness = stoi(argv[2]);
    string prettyPrintFileName = argv[3];
    string labelFileName = argv[4];
    string propertyFileName = argv[5];

    ifstream input;
    input.open(inputName);
    ofstream prettyPrintFile, labelFile, propertyFile;
    prettyPrintFile.open(prettyPrintFileName);
    labelFile.open(labelFileName);
    propertyFile.open(propertyFileName);

    if (input.is_open() && prettyPrintFile.is_open() && labelFile.is_open() && propertyFile.is_open())
    {
        CC cc(input);
        cc.imgReformat(prettyPrintFile);

        if (connectedness == 4)
        {
            cc.connect4Pass1();
            cc.imgReformat(prettyPrintFile);
            cc.printEQAry(prettyPrintFile);
            cc.connect4Pass2();
            cc.imgReformat(prettyPrintFile);
            cc.printEQAry(prettyPrintFile);
        }
        if (connectedness == 8)
        {
            cc.connect8Pass1();
            cc.imgReformat(prettyPrintFile);
            cc.printEQAry(prettyPrintFile);
            cc.connect8Pass2();
            cc.imgReformat(prettyPrintFile);
            cc.printEQAry(prettyPrintFile);
        }

        cc.manageEQAry();
        prettyPrintFile << "After EQ management:" << endl;
        cc.printEQAry(prettyPrintFile);
        cc.connectPass3();
        cc.imgReformat(prettyPrintFile);
        cc.printImg(labelFile);
        cc.printCCproperty(propertyFile);
        cc.drawBoxes();
        cc.imgReformat(prettyPrintFile);
    }
    else
    {
        cout << "Required Files could not be read/open" << endl;
    }

    input.close();
    prettyPrintFile.close();
    labelFile.close();
    propertyFile.close();
}