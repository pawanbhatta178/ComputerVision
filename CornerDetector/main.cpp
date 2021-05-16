#include <iostream>
#include <fstream>
#include <string>
#include <cstdarg>
using namespace std;

struct BoundaryPt
{
    int x;
    int y;
    double curvature;
    int localMax;
    int corner; //1 means not a corner, 9 means corner
};

class Image
{
public:
    int numRows, numCols, minVal, maxVal, newMax, newMin;
    int **imgAry;

    Image(ifstream &inFile)
    {
        inFile >> numRows >> numCols >> minVal >> maxVal;
        imgAry = new int *[numRows];
        for (int i = 0; i < numRows; i++)
        {
            imgAry[i] = new int[numCols]();
        }
    }

    void reformatPrettyPrint(ofstream &outFile)
    {
        outFile << numRows << " " << numCols << " " << minVal << " " << maxVal << endl;
        for (int i = 0; i < numRows; i++)
        {
            for (int j = 0; j < numCols; j++)
            {
                if (imgAry[i][j] > 0)
                {
                    outFile << imgAry[i][j] << " ";
                }
                else
                {
                    outFile << ". ";
                }
            }
            outFile << endl;
        }
    }

    ~Image()
    {
        for (int i = 0; i < numRows; i++)
        {
            delete[] imgAry[i];
        }
    }
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

    void init(ifstream &boundaryFile, string inputFileName)
    {
        countPts(boundaryFile);
        PtAry = new BoundaryPt[numPts];
        boundaryFile.close();

        boundaryFile.open(inputFileName);
        int a;
        boundaryFile >> a >> a >> a >> a >> a;

        for (int i = 0; i < numPts; i++)
        {
            int x, y;
            boundaryFile >> x >> y;
            storePt(x, y, i);
        }
    }

    void cornerDetection(ofstream &outFile)
    {
        Q = 0;
        P = K;
        R = 2 * K;
        cout << "K" << K << endl;
        cout << "Number of Pts: " << numPts << endl;

        for (int i = 0; i < numPts; i++)
        {
            PtAry[i].curvature = computeCurvature(P, Q, R);
            P = (P + 1) % numPts;
            Q = (Q + 1) % numPts;
            R = (R + 1) % numPts;
        }
    }

    double computeCurvature(int p, int q, int r)
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

        double curvature;

        //Math error cases
        if (r1 == r2 && r2 == r3)
        {
            curvature = abs((c1 - c2) / 0.1 - (c2 - c3) / 0.01);
        }
        else if (r1 == r2)
        {
            curvature = abs((c1 - c2) / 0.1 - (c2 - c3) / (r2 - r3));
        }
        else if (r2 == r3)
        {
            curvature = abs((c1 - c2) / (r1 - r2) - (c2 - c3) / 0.1);
        }
        else
        {
            curvature = abs((c1 - c2) / (r1 - r2) - (c2 - c3) / (r2 - r3));
        }

        cout << " Curvature: " << curvature << endl;
        return curvature;
    }

    void storePt(int x, int y, int index)
    {
        PtAry[index].x = x;
        PtAry[index].y = y;
    }

    void computeLocalMaxima()
    {
        double n1, n2, n3, n4; //all neighbours' curvature
        double n;
        for (int i = 2; i < numPts + 2; i++)
        {
            n1 = PtAry[(i - 2) % numPts].curvature;
            n2 = PtAry[(i - 1) % numPts].curvature;
            n3 = PtAry[(i + 1) % numPts].curvature;
            n4 = PtAry[(i + 2) % numPts].curvature;
            n = PtAry[i % numPts].curvature;
            if (n >= n1 && n >= n2 && n >= n3 && n >= n4)
            {
                PtAry[i % numPts].localMax = 1;
            }
            else
            {
                PtAry[i % numPts].localMax = 0;
            }
        }
    }

    void markCorner()
    {
        double n1, n2, n3, n4; //all neighbours' local maxima
        double n;
        for (int i = 2; i < numPts + 2; i++)
        {
            if (PtAry[i % numPts].localMax == 1)
            {
                n1 = PtAry[(i - 2) % numPts].localMax;
                n2 = PtAry[(i - 1) % numPts].localMax;
                n3 = PtAry[(i + 1) % numPts].localMax;
                n4 = PtAry[(i + 2) % numPts].localMax;
                if ((n2 == 1 || n3 == 1))
                {
                    PtAry[i % numPts].corner = 9;
                }
                else
                {
                    PtAry[i % numPts].corner = 1;
                }
            }
            else
            {
                PtAry[i % numPts].corner = 1;
            }
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

    void printPtAry(ofstream &outFile) // For debugging, print the content of the entire PtAry to outFile3
    {
        for (int i = 0; i < numPts; i++)
        {
            outFile << "r: " << PtAry[i].x << " c: " << PtAry[i].y << " "
                    << " Curvature: " << PtAry[i].curvature << " Local Max: " << PtAry[i].localMax << " Corner: " << PtAry[i].corner << endl;
        }
    }

    void printBoundary(ofstream &outFile)
    {
        outFile << numPts << endl;
        for (int i = 0; i < numPts; i++)
        {
            outFile << PtAry[i].x << " " << PtAry[i].y
                    << " " << PtAry[i].corner << endl;
        }
    }
    void display(Image &img)
    {
        img.newMax = 0;
        for (int i = 0; i < numPts; i++)
        {
            int x = PtAry[i].x;
            int y = PtAry[i].y;
            img.imgAry[x][y] = PtAry[i].corner;

            //Updating newMax
            if (PtAry[i].corner > img.newMax)
            {
                img.newMax = PtAry[i].corner;
            }
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

            outFile3 << endl
                     << "Before applying k curvature corner detection algorithm:" << endl;
            k.printPtAry(outFile3);
            k.cornerDetection(outFile3);
            k.computeLocalMaxima();
            k.markCorner();
            k.printPtAry(outFile3);
            k.printBoundary(outFile1);
            k.display(img);
            img.reformatPrettyPrint(outFile2);
        }
    }
}