import java.io.*;
import java.util.Scanner;

class Image {
    int numRows, numCols, minVal, maxVal;
    int[][] imageAry;
    int[][] boundaryAry;
    int[][] CCAry;

    Image(Scanner imgFile) {
        loadHeader(imgFile);
        zeroFrameImageAry();
        loadImage(imgFile);
    }

    void zeroFrameImageAry() {
        imageAry = new int[numRows + 2][numCols + 2];
    }

    void loadHeader(Scanner imgFile) {
        numRows = imgFile.nextInt();
        numCols = imgFile.nextInt();
        minVal = imgFile.nextInt();
        maxVal = imgFile.nextInt();
    }

    void loadImage(Scanner imgFile) {
        for (int i = 1; i < numRows + 1; i++) {
            for (int j = 1; j < numCols + 1; j++) {
                imageAry[i][j] = imgFile.nextInt();
            }
        }
    }

    void writeHeader(BufferedWriter outFile) throws IOException {
        outFile.write(numRows + " " + numCols + " " + minVal + " " + maxVal + "\n");
    }

    void prettyPrint(BufferedWriter outFile) throws IOException {
        writeHeader(outFile);
        for (int i = 1; i < numRows + 1; i++) {
            for (int j = 1; j < numCols + 1; j++) {
                if (imageAry[i][j] == 0) {
                    outFile.write(". ");
                } else {
                    outFile.write(Integer.toString(imageAry[i][j]) + " ");
                }
            }
            outFile.write("\n");
        }
    }

}

class CCproperty {
    int numCC, label, numPixels, minRow, minCol, maxRow, maxCol;
    int[][] CCAry;

    CCproperty(Scanner propImgFile) {
        int numRows = propImgFile.nextInt();
        int numCols = propImgFile.nextInt();
        int minVal = propImgFile.nextInt();
        int maxVal = propImgFile.nextInt();
        numCC = propImgFile.nextInt();
    }

    void clearCCAry() {
        for (int i = 0; i < maxRow - minRow; i++) {
            for (int j = 0; j < maxCol - minCol; j++) {
                CCAry[i][j] = 0;
            }
        }
    }

    void loadCCAry(Scanner propImg, int[][] imgAry) {
        label = propImg.nextInt();
        numPixels = propImg.nextInt();
        minRow = propImg.nextInt();
        minCol = propImg.nextInt();
        maxRow = propImg.nextInt();
        maxCol = propImg.nextInt();

        // Initializing CCAry according to the current CC label
        CCAry = new int[maxRow - minRow + 1][maxCol - minCol + 1];
        clearCCAry();

        // Copying all the pixel values of a given CC by using bounding box's values
        for (int i = 0; i < maxRow - minRow + 1; i++) {
            for (int j = 0; j < maxCol - minCol + 1; j++) {
                CCAry[i][j] = imgAry[i + minRow + 1][j + minCol + 1];
            }
        }
    }

    void prettyPrint(BufferedWriter outFile) throws IOException {
        for (int i = 0; i < maxRow - minRow + 1; i++) {
            for (int j = 0; j < maxCol - minCol + 1; j++) {
                if (CCAry[i][j] == 0) {
                    outFile.write(". ");
                } else {
                    outFile.write(Integer.toString(CCAry[i][j]) + " ");
                }
            }
            outFile.write("\n");
        }
    }

}

class Point {
    int row, col;
}

class ChainCode {
    Point[] neighborCoord;
    int[] zeroTable;
    Point startP;
    Point currentP;// current none zero border pixel
    Point nextP;// next none-zero border pixel
    int lastQ; // Range from 0 to 7; it is the direction of the last zero scanned from currentP
    int nextDir;// the next scanning direction of currentP's neighbors
    int pChainDir; // chain code direction from currentP to nextP

    ChainCode() {

    }

    void getChainCode() {

    }

    // Given currentP's row and col, the method determines and stores the row and
    // col of each of currentP's
    // 8 neighbors (0 to 7 w.r.t the chain-code direction) in neighborCoord[] array.
    void loadNeigborsCoord(Point currentP) {

    }

    int findNextP(Point currentP, Point nextQ, Point nextP) {

        return 0;
    }

    // Give the chainCode file, create an image contains only the boundary of
    // objects in the labelled file
    void constructBoundary() {

    }

    public static void main(String[] args) throws IOException {
        String labelFileName = args[0] + ".txt";
        FileReader labelFileReader = null;
        BufferedReader labelFileBuffReader = null;
        Scanner labelFile = null;

        String propFileName = args[1] + ".txt";
        FileReader propFileReader = null;
        BufferedReader propFileBuffReader = null;
        Scanner propFile = null;

        String chainCodeFileName = args[0] + "_chainCode.txt";
        FileWriter chainCodeFileWriter = null;
        BufferedWriter chainCodeFile = null;

        String boundaryFileName = args[0] + "_Boundary.txt";
        FileWriter boundaryFileWriter = null;
        BufferedWriter boundaryFile = null;

        try {
            labelFileReader = new FileReader(labelFileName);
            labelFileBuffReader = new BufferedReader(labelFileReader);
            labelFile = new Scanner(labelFileBuffReader);

            propFileReader = new FileReader(propFileName);
            propFileBuffReader = new BufferedReader(propFileReader);
            propFile = new Scanner(propFileBuffReader);

            chainCodeFileWriter = new FileWriter(chainCodeFileName);
            chainCodeFile = new BufferedWriter(chainCodeFileWriter);

            boundaryFileWriter = new FileWriter(boundaryFileName);
            boundaryFile = new BufferedWriter(boundaryFileWriter);

            Image img = new Image(labelFile);
            img.prettyPrint(chainCodeFile);

            CCproperty ccProp = new CCproperty(propFile);

            for (int i = 0; i < ccProp.numCC; i++) {
                ccProp.loadCCAry(propFile, img.imageAry);
                ccProp.prettyPrint(chainCodeFile);
            }

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
