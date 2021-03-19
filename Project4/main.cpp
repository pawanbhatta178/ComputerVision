#include <iostream>
#include <fstream>
#include <string>
using namespace std;

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
            labelFile << "HEY";
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