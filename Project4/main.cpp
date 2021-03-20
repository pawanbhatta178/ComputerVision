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
    if (a < b && a != 0)
    {
        return a;
    }
    return b;
}

template <class T, class... Args>
T getMinVal(T a, T b, Args... args)
{
    if (a < b && a != 0)
    {
        return getMinVal(a, args...);
    }
    return getMinVal(b, args...);
}

template <class T>
T isSameValExZero(T a)
{
    return a;
}

template <class T>
T isSameValExZero(T a, T b)
{

    if (a == 0)
    {
        return b;
    }
    if (b == 0)
    {
        return a;
    }
    if (a != b)
    {
        return 0;
    }
    if (a == b)
    {
        return a;
    }
}

template <class T, class... Args>
T isSameValExZero(T a, T b, Args... args)
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
        return 0;
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
    // In the Cartesian coordinate system, any rectangular box can be
    //represented by two points: upper-left corner and the lower -right
    //corner of the box. Here, the two points:(minR minC) and(maxR maxC)
    //represents the smallest rectangular box that the cc can fit inside the box.
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
    int newLabel;  // initialize to 0
    int trueNumCC; // the true number of connected components in the image
    // It will be determined in manageEQAry method.
    int **zeroFramedAry;       // a 2D array, need to dynamically allocate
    int NonZeroNeighborAry[5]; // 5 is the max number of neighbors you have to check.
    // For easy programming, you may consider using this 1-D array
    // to store pixel (i, j)’s non-zero neighbors during pass 1 and pass2.
    int *EQAry; // an 1-D array, of size (numRows * numCols) / 4
    // dynamically allocate at run time
    // and initialize to its index, i.e., EQAry[i] = i.
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
                    }

                    //Case 2
                    else if (isSameValExZero(a, b, c, d) != 0)
                    {
                        zeroFramedAry[i][j] = getNonZero(a, b, c, d);
                    }

                    //Case 3
                    else
                    {
                        zeroFramedAry[i][j] = getMinVal(a, b, c, d);
                    }
                }
            }
        }
        print2DArray(zeroFramedAry, numRows + extraRows, numCols + extraCols);
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
                    }

                    //Case 2
                    else if (a == b || a == 0 || b == 0)
                    {
                        zeroFramedAry[i][j] = getNonZero(a, b);
                    }

                    //Case 3
                    else
                    {
                        if (a == 0)
                        {
                            zeroFramedAry[i][j] = b;
                        }
                        if (b == 0)
                        {
                            zeroFramedAry[i][j] = a;
                        }
                        zeroFramedAry[i][j] = getMinVal(a, b);
                    }
                }
            }
        }
        print2DArray(zeroFramedAry, numRows + extraRows, numCols + extraCols);
    }

    void connect8Pass2()
    {

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
                    else if (isSameValExZero(e, f, g, h, zeroFramedAry[i][j]) != 0)
                    {
                        //do nothing
                    }

                    //Case 3
                    else
                    {
                        zeroFramedAry[i][j] = getMinVal(e, f, g, h, zeroFramedAry[i][j]);
                    }
                }
            }
        }
        print2DArray(zeroFramedAry, numRows + extraRows, numCols + extraCols);
    }

    void connect4Pass2()
    {
    }

    void connectPass3()
    {
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
                // cc.connect4Pass1();
            }
            if (connectedness == 8)
            {
                cc.connect8Pass1();
                cout << endl;
                cc.connect8Pass2();
            }
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