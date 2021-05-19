import java.io.*;
import java.util.Scanner;

class Image {
    int numRows, numCols, minVal, maxVal;
    int[][] imageAry;

    Image(Scanner imgFile) {
        loadHeader(imgFile);
    }

    void loadHeader(Scanner imgFile) {
        numRows = imgFile.nextInt();
        numCols = imgFile.nextInt();
        minVal = imgFile.nextInt();
        maxVal = imgFile.nextInt();
    }

    void loadImage(Scanner imgFile) {
        imageAry = new int[numRows][numCols];
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                imageAry[i][j] = imgFile.nextInt();
            }
        }
    }

    void writeHeader(BufferedWriter outFile) throws IOException {
        outFile.write(numRows + " " + numCols + " " + minVal + " " + maxVal + "\n");
    }

    void prettyPrint(BufferedWriter outFile) throws IOException {
        writeHeader(outFile);
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
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

class rcCoord {
    int r;
    int c;
}

class HoughTransform {
    rcCoord point;
    int angleInDegree;
    double angleInRadians;
    int HoughAngle; // set to 180
    int HoughDist; // 2 times of the diagnol of image
    int[][] HoughAry;// a 2D int array size of HoughDist by HoughAngle; dynamically allocate
    int offset;
    int maxLabel;

    void buildHoughSpace(Image img) {
        offset = HoughDist / 2;
        maxLabel = 0;

        for (int r = 0; r < img.numRows; r++) {
            for (int c = 0; c < img.numCols; c++) {
                if (img.imageAry[r][c] > 0) {
                    angleInDegree = 0;
                    while (angleInDegree <= 179) {
                        angleInRadians = angleInDegree / 180.00 * Math.PI;
                        int distInt = (int) (c * Math.cos(angleInRadians) + r * Math.sin(angleInRadians));
                        System.out.println("(r,c):(" + r + "," + c + " " + ") " + " angleInRadian: " + angleInRadians
                                + " Distance (without offset):" + distInt);
                        HoughAry[distInt + offset][angleInDegree]++;
                        angleInDegree++;

                        if (distInt > maxLabel) {
                            maxLabel = distInt;
                        }
                    }
                }
            }
        }
    }

    void reformatPrettyPrint(int[][] ary, BufferedWriter outFile) throws IOException {
        outFile.write(HoughDist + " " + HoughAngle + " " + 0 + " " + maxLabel + "\n");

        for (int i = 0; i < HoughDist; i++) {
            for (int j = 0; j < HoughAngle; j++) {
                if(HoughAry[i][j]==0){
                    outFile.write(  ". ");
                }
                else{
                    outFile.write(HoughAry[i][j] + " ");
                }
            }
            outFile.write("\n");
        }
    }

    public static void main(String[] args) throws IOException {
        String inputName = args[0];
        FileReader inputReader = null;
        BufferedReader inputBuffReader = null;
        Scanner input = null;

        String outputName = args[1];
        FileWriter outputFileWriter = null;
        BufferedWriter output = null;

        try {
            inputReader = new FileReader(inputName);
            inputBuffReader = new BufferedReader(inputReader);
            input = new Scanner(inputBuffReader);

            outputFileWriter = new FileWriter(outputName);
            output = new BufferedWriter(outputFileWriter);

            Image img = new Image(input);
            img.loadImage(input);
            HoughTransform h = new HoughTransform();
            h.HoughAngle = 180;
            h.HoughDist = 2 * ((int) Math.sqrt((img.numRows * img.numRows) + (img.numCols * img.numCols)));
            h.HoughAry = new int[h.HoughDist][h.HoughAngle];
            h.buildHoughSpace(img);
            h.reformatPrettyPrint(h.HoughAry, output);

        } finally {
            if (input != null)
                input.close();
            if (output != null)
                output.close();

        }
    }

}
