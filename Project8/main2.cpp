#include <iostream>
#include <fstream>
#include <string>
#include <cstdarg>
using namespace std;

class Image
{
public:
    int numRows;
    int numCols;
    int minVal;
    int maxVal;
    int **imgAry; // a 2D array for display, initially set to 0

    Image(ifstream &inFile)
    {
        inFile >> numRows >> numCols >> minVal >> maxVal;
        imgAry = new int *[numRows];
        for (int i = 0; i < numRows; i++)
        {
            imgAry[i] = new int[numCols];
        }
    }

    void plotPt2Img()
    {
    }

    void reformatPrettyPrint()
    {
    }

    ~Image()
    {
        for (int i = 0; i < numRows; i++)
        {
            delete[] imgAry[i];
        }
    }
};

class BoundaryPt
{
public:
    int x, y;
    double curvature;
    int localMax;
    int corner; // 1 means it is not a corner or 9 means it is a corner
};

class kCurvature
{
public:
    int K;
    int numPts;        //number of boundary Points
    int Q;             //an index of the array, initially set to 0
    int P;             //an index of the array, initially set to K
    int R;             //an index of the array, initially set to 2*K
    BoundaryPt *PtAry; // an 1D array of boundaryPt class size is numPts,
    // need to dynamically allocate.
    // use mod function to compute the curvature for the beginning of
    // the K points without extending the tail of the array,

    kCurvature()
    {
    }

    void init(ifstream &inFile, string inputFileName)
    {
        countPts(inFile);
        //initializing boundaryPts array
        PtAry = new BoundaryPt[numPts];

        inFile.close();
        inFile.open(inputFileName);
        int a;
        //skipping image header and label
        inFile >> a >> a >> a >> a >> a;

        //Storing each points in the array
        for (int i = 0; i < numPts; i++)
        {
            int x, y;
            inFile >> x >> y;
            storePt(x, y, i);
        }
    }

    void cornerDetection(ofstream &debugFile)
    {
        Q = 0;
        P = K;
        R = 2 * K;
        cout << "K" << K << endl;
        cout << "Number of Pts: " << numPts << endl;
        for (int i = 0; i < numPts; i++)
        {

            double curvature = computeCurvature(Q, P, R);
            PtAry[P].curvature = curvature;
            P = (P + 1) % numPts;
            Q = (Q + 1) % numPts;
            R = (R + 1) % numPts;
        }
    }

    void countPts(ifstream &inFile)
    {
        int x, y;
        int count = 0;
        while (inFile >> x && inFile >> y)
        {
            count++;
        }
        numPts = count;
    }

    void storePt(int x, int y, int index)
    {
        PtAry[index].x = x;
        PtAry[index].y = y;
    }

    double computeCurvature(int q, int p, int r)
    {
        cout << "Q: " << Q << " P: " << P << " R: " << R << " ";
        cout << "P has " << PtAry[p].x << " " << PtAry[p].y << " ";
        double r1 = (double)PtAry[q].x;
        double c1 = (double)PtAry[q].y;
        double r2 = (double)PtAry[p].x;
        double c2 = (double)PtAry[p].y;
        double r3 = (double)PtAry[r].x;
        double c3 = (double)PtAry[r].y;
        cout << "r1 c1 r2 c2 r3 c3: " << r1 << " " << c1 << " " << r2 << " " << c2 << " " << r3 << " " << c3 << " ";

        //Math error cases
        if (r1 == r2)
        {
            r2 = r2 - 0.1;
            cout << " Math Error";
        }
        if (r2 == r3)
        {
            r2 = r2 - 0.2;
            cout << " Maths error";
        }

        double curvature = (c1 - c2) / (r1 - r2) - (c2 - c3) / (r2 - r3);

        cout << " Curvature: " << curvature << endl;
        return curvature;
    }

    void computeLocalMaxima()
    {
        // P(i) is a local maxima if in its 1 X 5 neighborhood if the curvature
        // of p(i) is >= the curvatures of
        // its linear neighbors: p(i-2), p(i-1), p(i+1), p(i+2)
        // returns 1 if yes, returns 0 if not.
        for (int i = 2; i < numPts + 2; i++)
        {
            double neighbour1 = PtAry[(i - 2) % numPts].curvature;
            double neigbour2 = PtAry[(i - 1) % numPts].curvature;
            double neigbour3 = PtAry[(i + 1) % numPts].curvature;
            double neigbour4 = PtAry[(i + 2) % numPts].curvature;

            int index = i % numPts;
            double p = PtAry[index].curvature;
            if (p >= neighbour1 && p >= neigbour2 && p >= neigbour3 && p >= neigbour4)
            {
                PtAry[index].localMax = 1;
            }
            else
            {
                PtAry[index].localMax = 0;
            }
        }
    }

    void markCorner()
    {
        // go thru the entire PtAry, i = 0 to numPts -1
        // set PtAry[i]-> corner to 9
        //if a) PtAry [i] is a local maxima &&
        //   b) in its 1X5 neighborhood, only PtAry [i-1] or PtAry [i+1] can be a local maxima
        // otherwise, set PtAry[i]-> corner to 1
    }

    void printBoundary()
    {
        // output only (x, y, corner) of the entire PtAry to outFile1 in format given in the above.
    }

    void display() // plot PtAry to imgAry
    {
    }

    void printPtAry(ofstream &outFile) // For debugging, print the content of the entire PtAry to outFile3
    {
        for (int i = 0; i < numPts; i++)
        {
            outFile << PtAry[i].x << " " << PtAry[i].y << " " << PtAry[i].localMax << " Curvature: " << PtAry[i].curvature << endl;
        }
    }

    ~kCurvature()
    {
        delete[] PtAry;
    }
};

int main(int argc, const char *argv[])
{

    // READ
    string inputName = argv[1];
    ifstream input;
    input.open(inputName);

    //WRITES
    string outFile1Name = argv[2],
           outFile2Name = argv[3], outFile3Name = argv[4];
    ofstream outFile1, outFile2, outFile3;
    outFile1.open(outFile1Name);
    outFile2.open(outFile2Name);
    outFile3.open(outFile3Name);

    //Input for K
    int K;
    cout << "Enter the value of K: ";
    cin >> K;

    //Checking if IO operations succeeds
    if (input.is_open())
    {
        if (outFile1.is_open() && outFile2.is_open() && outFile3.is_open())
        {
            Image img(input);
            int label;
            input >> label;
            kCurvature k;
            k.K = K;
            k.init(input, inputName);
            k.printPtAry(outFile3);
            k.cornerDetection(outFile3);
            k.computeLocalMaxima();
            k.printPtAry(outFile3);
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
    outFile1.close();
    outFile2.close();
    outFile3.close();
    return 0;
};
