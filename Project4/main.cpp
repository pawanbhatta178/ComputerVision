#include <iostream>
#include <fstream>
#include <string>
#include <cstdarg>
using namespace std;

template <class T>
T getNonZero(T n)
{
    if (n != 0)
    {
        return n;
    }
    else
    {
        return 0;
    }
}

template <class T, class... Args>
T getNonZero(T n, Args... args)
{
    if (n != 0)
    {
        return n;
    }
    return getNonZero(args...);
}

template <class T>
T getMinVal(T a)
{
    return a;
}

template <class T>
T getMinVal(T a, T b)
{
    if (a == 0 && b == 0)
    {
        return 0;
    }
    if (a == 0)
    {
        return b;
    }
    if (b == 0)
    {
        return a;
    }
    if (a < b)
    {
        return a;
    }
    return b;
}

template <class T, class... Args>
T getMinVal(T a, T b, Args... args)
{
    if (a == 0 && b == 0)
    {
        return getMinVal(args...);
    }
    if (a == 0)
    {
        return getMinVal(b, args...);
    }
    if (b == 0)
    {
        return getMinVal(a, args...);
    }
    if (a < b)
    {
        return getMinVal(a, args...);
    }
    return getMinVal(b, args...);
}

template <class T>
bool isSameValExZero(T a)
{
    return true;
}

template <class T>
bool isSameValExZero(T a, T b)
{

    if (b == 0 || a == 0)
    {
        return true;
    }
    if (a == b)
    {
        return true;
    }
    if (a != b)
    {
        return false;
    }
}

template <class T, class... Args>
bool isSameValExZero(T a, T b, Args... args)
{
    if (a == 0 && b == 0)
    {
        return isSameValExZero(args...);
    }
    else if (a == 0)
    {
        return isSameValExZero(b, args...);
    }
    else if (b == 0)
    {
        return isSameValExZero(a, args...);
    }
    else if (a == b)
    {
        return isSameValExZero(b, args...);
    }
    else
    {
        return false;
    }
}

struct Property
{
    int label;     // The component label
    int numPixels; // total number of pixels in the cc.
    int minR;
    int minC;
    int maxR;
    int maxC;

    Property()
    {
        label = -1;
        numPixels = 0;
        minC = 9999;
        minR = 9999;
        maxC = 0;
        maxR = 0;
    }
};

class CClabel
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
    int newLabel;
    int trueNumCC; // the true number of connected components in the image
    int **zeroFramedAry;
    int NonZeroNeighborAry[5];
    int *EQAry; // an 1-D array, of size (numRows * numCols) / 4
    Property *CCproperty;

    CClabel(ifstream &input)
    {
        loadHeader(input);
        rowFrameSize = 1;
        colFrameSize = 1;
        extraRows = 2 * rowFrameSize;
        extraCols = 2 * colFrameSize;
        //dynamic allocation of zeroframeArray
        zeroFramedAry = new int *[numRows + extraRows];
        for (int i = 0; i < numRows + extraRows; i++)
        {
            zeroFramedAry[i] = new int[numCols + extraCols];
        }
        zero2D(zeroFramedAry, numRows + extraRows, numCols + extraCols);
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
                input >> zeroFramedAry[i][j];
            }
        }
    }

    void connect8Pass1()
    {
        newLabel = 0;
        //allocating EQTable
        int EQSize = (numRows * numCols) / 4;
        EQAry = new int[EQSize];
        for (int i = 0; i < EQSize; i++)
        {
            EQAry[i] = i;
        }

        newMax = 0;
        newMin = 9999;

        for (int i = rowFrameSize; i < numRows + rowFrameSize; i++)
        {
            for (int j = colFrameSize; j < numCols + colFrameSize; j++)
            {
                if (zeroFramedAry[i][j] > 0)
                {
                    int a = zeroFramedAry[i - 1][j - 1];
                    int b = zeroFramedAry[i - 1][j];
                    int c = zeroFramedAry[i - 1][j + 1];
                    int d = zeroFramedAry[i][j - 1];

                    //Case 1
                    if (a == 0 && b == 0 && c == 0 && d == 0)
                    {
                        newLabel++;
                        zeroFramedAry[i][j] = newLabel;

                        //updating EQ table
                        EQAry[newLabel] = newLabel;
                    }

                    //Case 2
                    else if (isSameValExZero(a, b, c, d))
                    {
                        zeroFramedAry[i][j] = getNonZero(a, b, c, d);
                    }

                    //Case 3
                    else
                    {
                        int minVal = getMinVal(a, b, c, d);
                        zeroFramedAry[i][j] = minVal;

                        //updating EQ Table
                        EQAry[a] = minVal;
                        EQAry[b] = minVal;
                        EQAry[c] = minVal;
                        EQAry[d] = minVal;
                    }

                    //Updating newMax and newMin
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

    void connect4Pass1()
    {
        newLabel = 0;
        //allocating EQTable
        int EQSize = (numRows * numCols) / 4;
        EQAry = new int[EQSize];
        for (int i = 0; i < EQSize; i++)
        {
            EQAry[i] = i;
        }

        newMax = 0;
        newMin = 9999;

        for (int i = rowFrameSize; i < numRows + rowFrameSize; i++)
        {
            for (int j = colFrameSize; j < numCols + colFrameSize; j++)
            {
                if (zeroFramedAry[i][j] > 0)
                {
                    int a = zeroFramedAry[i - 1][j];
                    int b = zeroFramedAry[i][j - 1];

                    //Case 1
                    if (a == 0 && b == 0)
                    {
                        newLabel++;
                        zeroFramedAry[i][j] = newLabel;

                        //updating EQ table
                        EQAry[newLabel] = newLabel;
                    }

                    //Case 2
                    else if (isSameValExZero(a, b))
                    {
                        zeroFramedAry[i][j] = getNonZero(a, b);
                    }

                    //Case 3
                    else
                    {
                        int minVal = getMinVal(a, b);
                        zeroFramedAry[i][j] = minVal;

                        //updating EQ Table
                        EQAry[a] = minVal;
                        EQAry[b] = minVal;
                    }

                    //Updating newMax and newMin
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
        newMax = 0;
        newMin = 9999;
        for (int i = numRows + rowFrameSize - 1; i >= rowFrameSize; i--)
        {
            for (int j = numCols + colFrameSize - 1; j >= colFrameSize; j--)
            {

                if (zeroFramedAry[i][j] > 0)
                {
                    int e = zeroFramedAry[i][j + 1];
                    int f = zeroFramedAry[i + 1][j - 1];
                    int g = zeroFramedAry[i + 1][j];
                    int h = zeroFramedAry[i + 1][j + 1];

                    //Case 1
                    if (e == 0 && f == 0 && g == 0 && h == 0)
                    {
                        //do nothing
                    }

                    //Case 2
                    else if (isSameValExZero(e, f, g, h, zeroFramedAry[i][j]))
                    {
                        //do nothing
                    }

                    //Case 3
                    else
                    {
                        int minLabel = getMinVal(e, f, g, h, zeroFramedAry[i][j]);
                        zeroFramedAry[i][j] = minLabel;

                        //Updating EQ Table
                        if (zeroFramedAry[i][j] > minLabel)
                        {
                            EQAry[zeroFramedAry[i][j]] = minLabel;
                        }
                        EQAry[e] = minLabel;
                        EQAry[f] = minLabel;
                        EQAry[g] = minLabel;
                        EQAry[h] = minLabel;
                    }

                    //Updating newMax and newMin
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
        newMax = 0;
        newMin = 9999;
        for (int i = numRows + rowFrameSize - 1; i >= rowFrameSize; i--)
        {
            for (int j = numCols + colFrameSize - 1; j >= colFrameSize; j--)
            {
                if (zeroFramedAry[i][j] > 0)
                {
                    int c = zeroFramedAry[i][j + 1];
                    int d = zeroFramedAry[i + 1][j];

                    //Case 1
                    if (c == 0 && d == 0)
                    {
                        //do nothing
                    }

                    //Case 2
                    else if (isSameValExZero(c, d, zeroFramedAry[i][j]))
                    {
                        //do nothing
                    }

                    //Case 3
                    else
                    {
                        int minLabel = getMinVal(c, d, zeroFramedAry[i][j]);
                        zeroFramedAry[i][j] = minLabel;

                        //Updating EQ Table
                        if (zeroFramedAry[i][j] > minLabel)
                        {
                            EQAry[zeroFramedAry[i][j]] = minLabel;
                        }

                        EQAry[c] = minLabel;
                        EQAry[d] = minLabel;
                    }

                    //Updating newMax and newMin
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
        newMax = 0;
        newMin = 9999;
        CCproperty = new Property[trueNumCC + 1]();
        for (int i = rowFrameSize; i < numRows + rowFrameSize; i++)
        {
            for (int j = colFrameSize; j < numCols + colFrameSize; j++)
            {
                if (zeroFramedAry[i][j] > 0)
                {
                    zeroFramedAry[i][j] = EQAry[zeroFramedAry[i][j]];
                    Property *p = &CCproperty[zeroFramedAry[i][j]];
                    p->label = zeroFramedAry[i][j];
                    p->numPixels = p->numPixels + 1;

                    if (p->minR > i - 1)
                    {
                        p->minR = i - 1;
                    }
                    if (p->maxR < i - 1)
                    {
                        p->maxR = i - 1;
                    }
                    if (p->minC > j - 1)
                    {
                        p->minC = j - 1;
                    }
                    if (p->maxC < j - 1)
                    {
                        p->maxC = j - 1;
                    }
                }
                //Updating newMax and newMin
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

    void manageEQAry()
    {
        int readLabel = 0;
        for (int i = 1; i <= newLabel; i++)
        {
            if (i != EQAry[i])
            {
                EQAry[i] = EQAry[EQAry[i]];
            }
            else
            {
                readLabel++;
                EQAry[i] = readLabel;
            }
        }
        trueNumCC = readLabel;
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

    void minus1D(int *ary, int arrayLength)
    {
        for (int i = 0; i < arrayLength; i++)
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

    void imgReformat(ofstream &outFile)
    {
        outFile << numRows << " " << numCols << " " << newMin << " " << newMax << endl;
        string str = to_string(newMax);
        int width = str.length();
        for (int i = rowFrameSize; i < numRows + rowFrameSize; i++)
        {
            for (int j = colFrameSize; j < numCols + colFrameSize; j++)
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
                str = to_string(zeroFramedAry[i][j]);
                int ww = str.length();
                while (ww < width)
                {
                    outFile << " ";
                    ww++;
                }
            }
            outFile << endl;
        }
    }

    void printImg(ofstream &outFile)
    {
        outFile << numRows << " " << numCols << " " << newMin << " " << newMax << endl;
        string str = to_string(newMax);
        int width = str.length();
        for (int i = rowFrameSize; i < numRows + rowFrameSize; i++)
        {
            for (int j = colFrameSize; j < numCols + colFrameSize; j++)
            {

                outFile << zeroFramedAry[i][j] << " ";
                str = to_string(zeroFramedAry[i][j]);
                int ww = str.length();
                while (ww < width)
                {
                    outFile << " ";
                    ww++;
                }
            }
            outFile << endl;
        }
    }

    void printEQAry(ofstream &outFile)
    {
        for (int i = 1; i <= newLabel; i++)
        {
            outFile << i << " " << EQAry[i] << endl;
        }
    }

    void printCCproperty(ofstream &outFile)
    {
        outFile << numRows << " " << numCols << " " << newMin << " " << newMax << endl;
        outFile << trueNumCC << endl;
        outFile << "---" << endl;
        for (int i = 1; i < trueNumCC + 1; i++)
        {
            Property *p = &CCproperty[i];
            outFile << p->label << endl;
            outFile << p->numPixels << endl;
            outFile << p->minR << " " << p->minC << endl;
            outFile << p->maxR << " " << p->maxC << endl;
            outFile << "---" << endl;
        }
    }

    void drawBoxes()
    {
        int minRow, minCol, maxRow, maxCol, label;
        for (int i = 1; i < trueNumCC + 1; i++)
        {
            label = CCproperty[i].label;
            minRow = CCproperty[i].minR + 1;
            minCol = CCproperty[i].minC + 1;
            maxRow = CCproperty[i].maxR + 1;
            maxCol = CCproperty[i].maxC + 1;

            //drawing horizontal top line
            for (int j = minCol; j <= maxCol; j++)
            {
                zeroFramedAry[minRow][j] = label;
            }

            //drawing horizontal bottom line
            for (int j = minCol; j <= maxCol; j++)
            {
                zeroFramedAry[maxRow][j] = label;
            }

            //drawing vertical left line
            for (int i = minRow; i <= maxRow; i++)
            {
                zeroFramedAry[i][minCol] = label;
            }

            //drawing vertical right line
            for (int i = minRow; i <= maxRow; i++)
            {
                zeroFramedAry[i][maxCol] = label;
            }
        }
    }

    ~CClabel()
    {
        cout << "Destructor called" << endl;
        delete[] EQAry;
        delete[] CCproperty;
    }
};

int main(int argc, const char *argv[])
{
    //READ
    string inputName = argv[1];
    ifstream input;
    input.open(inputName);
    int connectedness = stoi(argv[2]);

    //WRITES
    string rfPrettyPrintFileName = argv[3], labelFileName = argv[4], propertyFileName = argv[5];
    ofstream rfPrettyPrint, labelFile, propertyFile;
    rfPrettyPrint.open(rfPrettyPrintFileName);
    labelFile.open(labelFileName);
    propertyFile.open(propertyFileName);

    //Checking if IO operations succeeds
    if (input.is_open())
    {
        if (rfPrettyPrint.is_open() && labelFile.is_open() && propertyFile.is_open())
        {
            CClabel cc(input);
            cc.loadImage(input);
            if (connectedness == 4)
            {
                cc.connect4Pass1();
                rfPrettyPrint << "Pass 1" << endl;
                cc.imgReformat(rfPrettyPrint);
                rfPrettyPrint << endl
                              << "Equivalency Array after: Pass 1" << endl;
                cc.printEQAry(rfPrettyPrint);
                cc.connect4Pass2();
                rfPrettyPrint << endl
                              << "Pass 2" << endl;
                cc.imgReformat(rfPrettyPrint);
                rfPrettyPrint << endl
                              << "Equivalency Array after: Pass 2" << endl;
                cc.printEQAry(rfPrettyPrint);
            }
            if (connectedness == 8)
            {
                cc.connect8Pass1();
                rfPrettyPrint << "Pass 1" << endl;
                cc.imgReformat(rfPrettyPrint);
                rfPrettyPrint << endl
                              << "Equivalency Array after: Pass 1" << endl;
                cc.printEQAry(rfPrettyPrint);
                cc.connect8Pass2();
                rfPrettyPrint << endl
                              << "Pass 2" << endl;
                cc.imgReformat(rfPrettyPrint);
                rfPrettyPrint << endl
                              << "Equivalency Array after: Pass 2" << endl;
                cc.printEQAry(rfPrettyPrint);
            }
            //Managing EQ table
            cc.manageEQAry();
            rfPrettyPrint << endl
                          << "Equivalency Array after: EQ Management" << endl;
            cc.printEQAry(rfPrettyPrint);

            //Third Pass
            cc.connectPass3();
            rfPrettyPrint << endl
                          << "Pass 3" << endl;
            cc.imgReformat(rfPrettyPrint);
            rfPrettyPrint << endl
                          << "Equivalency Array after: Pass 3" << endl;
            cc.printEQAry(rfPrettyPrint);

            //Printing final product of pass 3
            cc.printImg(labelFile);

            //Printing into CC Property File
            cc.printCCproperty(propertyFile);

            //drawing bounding box for each components
            cc.drawBoxes();
            rfPrettyPrint << endl
                          << "Drawing Boxes" << endl;
            cc.imgReformat(rfPrettyPrint);
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
    labelFile.close();
    propertyFile.close();
    return 0;
}