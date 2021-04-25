import java.io.*;
import java.util.Scanner;

class Image {
int numRows, numCols, minVal,maxVal;
int [][]imageAry;
int [][]boundaryAry;
int [][]CCAry;

}

class CCproperty{
int numCC,label,numPixels,minRow,minCol,maxRow, maxCol;

CCproperty(){

}

void clearCCAry(){}

void loadCCAry(){

}

}

class Point{
    int row, col;
}

class ChainCode {
   Point [] neighborCoord;
   int [] zeroTable;
   Point startP;
   Point currentP;// current none zero border pixel
   Point nextP;// next none-zero border pixel
   int lastQ; // Range from 0 to 7; it is the direction of the last zero scanned from currentP
   int nextDir;// the next scanning direction of currentP's neighbors
   int pChainDir; // chain code direction from currentP to nextP

    ChainCode(){

    }

    void getChainCode(){

    }

    // Given currentP's row and col, the method determines and stores the row and col of each of currentP's
    // 8 neighbors (0 to 7 w.r.t the chain-code direction) in neighborCoord[] array.
    void loadNeigborsCoord(Point currentP){

    }

    int findNextP(Point currentP, Point nextQ, Point nextP){

        return 0;
    }

    // Give the chainCode file, create an image contains only the boundary of objects in the labelled file
    void constructBoundary(){

    }

    public static void main(String[] args) throws IOException {
        String labelFileName = args[0]+".txt";
        FileReader labelFileReader = null;
        BufferedReader labelFileBuffReader= null;
        Scanner labelFile = null;

        String propFileName = args[0]+".txt";
        FileReader propFileReader = null;
        BufferedReader propFileBuffReader = null;
        Scanner propFile = null;

        String chainCodeFileName = args[0]+"_chainCode.txt";
        FileWriter chainCodeFileWriter = null;
        BufferedWriter chainCodeFile = null;

        String boundaryFileName = args[0]+"_Boundary.txt";
        FileWriter boundaryFileWriter = null;
        BufferedWriter boundaryFile = null;


        try {
            labelFileReader = new FileReader(labelFileName);
            labelFileBuffReader = new BufferedReader(labelFileReader);
            labelFile  = new Scanner(labelFileBuffReader);

            propFileReader = new FileReader( propFileName);
            propFileBuffReader = new BufferedReader(propFileReader);
            propFile = new Scanner(propFileBuffReader);

            chainCodeFileWriter = new FileWriter(chainCodeFileName);
            chainCodeFile = new BufferedWriter(chainCodeFileWriter);

            boundaryFileWriter = new FileWriter(boundaryFileName);
            boundaryFile = new BufferedWriter(boundaryFileWriter);



        } finally {
            if (labelFile != null)
                labelFile.close();
            if (propFile != null)
                propFile.close();
            if (chainCodeFile != null)
                chainCodeFile.close();
            if (boundaryFile != null)
                boundaryFile.close();

        }
    }

}
