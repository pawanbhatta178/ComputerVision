#include <iostream>
#include <fstream>
#include <string>
#include <cstdarg>
using namespace std;

class Image
{
    int numRows;
    int numCols;
    int minVal;
    int maxVal;
    int **imgAry; // a 2D array for display, initially set to 0

    Image()
    {
    }

    void plotPt2Img()
    {
    }

    void reformatPrettyPrint()
    {
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

    void init()
    {
    }

    void cornerDetection()
    {
    }

    void countPts()
    {
    }

    void storePt(int x, int y, int index)
    {
        PtAry[index].x = x;
        PtAry[index].y = y;
    }

    void computeCurvature()
    {
    }

    void computeLocalMaxima()
    {
        // P(i) is a local maxima if in its 1 X 5 neighborhood if the curvature
        // of p(i) is >= the curvatures of
        // its linear neighbors: p(i-2), p(i-1), p(i+1), p(i+2)
        // returns 1 if yes, returns 0 if not.
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

    void printPtAry() // For debugging, print the content of the entire PtAry to outFile3
    {
    }
};
