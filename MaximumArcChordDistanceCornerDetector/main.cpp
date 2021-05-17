#include <iostream>
#include <fstream>
#include <string>
#include <cstdarg>
#include <cmath>

using namespace std;

class BoundaryPt
{
public:
    int x, y;
    int vote;
    int corner; // 1 means it is not a corner or 9 means it is a corner
};

class Image
{
public:
    int numRows;
    int numCols;
    int minVal;
    int maxVal;
    int newMin;
    int newMax;
    int **imgAry; // a 2D array for display, initially set to 0

    Image(ifstream &inFile)
    {
        inFile >> numRows >> numCols >> minVal >> maxVal;
        imgAry = new int *[numRows];
        for (int i = 0; i < numRows; i++)
        {
            imgAry[i] = new int[numCols]();
        }
    }

    // void plotPt2Img(kCurvature &kC)
    // {
    //     newMin = 0;
    //     newMax = 0;
    //     for (int i = 0; i < kC.numPts; i++)
    //     {
    //         int x = kC.PtAry[i].x;
    //         int y = kC.PtAry[i].y;
    //         imgAry[x][y] = kC.PtAry[i].corner;

    //         //Updating newMax
    //         if (kC.PtAry[i].corner > newMax)
    //         {
    //             newMax = kC.PtAry[i].corner;
    //         }
    //     }
    // }

    void reformatPrettyPrint(ofstream &outFile)
    {
        outFile << numRows << " " << numCols << " " << newMin << " " << newMax << endl;
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

class maxArcChord
{
public:
    int K;             //length of neighborhood
    int numPts;        //number of boundary Points
    BoundaryPt *PtAry; // an 1D array of boundaryPt class size is numPts,
    // need to dynamically allocate.
    // use mod function to compute the curvature for the beginning of
    // the K points without extending the tail of the array,
    double *distanceAry;

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
        int P = 0;
        int Q = K;

        //Find a range say k in which to calculate perpendicular distance
        //For each points in the range, calculate the perpendicular distance from line formed by P and Q to the point
        //At the end, find the maximum arc chord and add 1 to the vote for that point i

        for (int i = 0; i < numPts; i++)
        {
            debugFile << "Neighborhood with: startingPoint: (" << PtAry[P].x << "," << PtAry[P].y << ") endingPoint: (" << PtAry[Q].x << "," << PtAry[Q].y << ")" << endl;
            //find the equation of the line PQ or get coordinates of PQ
            int x1 = PtAry[P].x;
            int y1 = PtAry[P].y;
            int x2 = PtAry[Q].x;
            int y2 = PtAry[Q].y;

            int A = y2 - y1;
            int B = x1 - x2;
            int C = (x2 * y1) - (x1 * y2);

            double deno = sqrt((A * A) + (B * B));

            int max = P;
            double maxDistance = 0;
            for (int j = 0; j < K; j++)
            {
                int x = PtAry[(j + P) % numPts].x;
                int y = PtAry[(j + P) % numPts].y;
                //find the perpendicular distance between j and line PQ
                debugFile << "Perpendicular distance from PQ to (" << PtAry[(j + P) % numPts].x << "," << PtAry[(j + P) % numPts].y << "): ";
                double numerator = ((double)abs(A * x + B * y + C));
                double distance = numerator / deno;
                debugFile << distance << " A:" << A << "B: " << B << "C: " << C << " AX+BY+C=" << numerator << " root(A*A+B*B)=" << deno << endl;
                //Finding maximum Distance point
                if (distance > maxDistance)
                {
                    maxDistance = distance;
                    max = (j + P) % numPts;
                }
            }

            //Incrementing vote for max Point
            PtAry[max].vote++;
            debugFile << "Voting: (" << PtAry[max].x << "," << PtAry[max].y << ")" << endl;

            P = (P + 1) % numPts;
            Q = (Q + 1) % numPts;
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
    }

    void computeLocalMaxima()
    {
    }

    void markCorner()
    {
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

    void printBoundary(ofstream &outFile)
    {
        outFile << numPts << endl;
        for (int i = 0; i < numPts; i++)
        {
            outFile << PtAry[i].x << " " << PtAry[i].y
                    << " " << PtAry[i].corner << endl;
        }
    }

    void printPtAry(ofstream &outFile) // For debugging, print the content of the entire PtAry to outFile3
    {
        for (int i = 0; i < numPts; i++)
        {
            outFile << "r: " << PtAry[i].x << " c: " << PtAry[i].y << " "
                    << " Votes: " << PtAry[i].vote << " Corner: " << PtAry[i].corner << endl;
        }
    }

    ~maxArcChord()
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
    cout << "Enter the value of Neighborhood: ";
    cin >> K;

    //Checking if IO operations succeeds
    if (input.is_open())
    {
        if (outFile1.is_open() && outFile2.is_open() && outFile3.is_open())
        {
            Image img(input);
            int label;
            input >> label;
            maxArcChord m;
            m.K = K;
            m.init(input, inputName);
            outFile3 << endl
                     << "Before applying max arc chord algorithm:" << endl;
            m.printPtAry(outFile3);
            m.cornerDetection(outFile3);
            outFile3 << endl
                     << "After applying k curvature corner detection algorithm:" << endl;
            m.printPtAry(outFile3);
            m.computeLocalMaxima();
            m.markCorner();
            outFile3 << endl
                     << "After marking corners:" << endl;
            m.printPtAry(outFile3);
            m.printBoundary(outFile1);
            m.display(img);
            img.reformatPrettyPrint(outFile2);
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
