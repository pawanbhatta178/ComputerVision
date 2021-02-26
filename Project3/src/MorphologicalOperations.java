import java.io.*;
import java.util.Scanner;

public class MorphologicalOperations {
    int numImgRows;
    int numImgCols;
    int imgMin;
    int imgMax;

    int numStructRows;
    int numStructCols;
    int structMin;
    int structMax;
    int rowOrigin;
    int colOrigin;

    int rowFrameSize;
    int colFrameSize;
    int extraRows;
    int extraCols;

    int [] [] zeroFramedAry;
    int [] [] morphAry;
    int [] [] tempAry;
    int [] [] structAry;

    void setFrameSize(){
        rowFrameSize=numStructRows/2;
        colFrameSize=numStructCols/2;
    }


    void setExtraFrame(){
        extraRows  =rowFrameSize*2;
        extraCols  =colFrameSize*2;
    }

    void allocateArrays(){
        zeroFramedAry=new int [numImgRows+extraRows][numImgCols+extraCols];
        morphAry=new int [numImgRows+extraRows][numImgCols+extraCols];
        tempAry=new int [numImgRows+extraRows][numImgCols+extraCols];
        structAry=new int [numStructRows][numStructCols];
    }

    public static void main(String[] args) throws IOException {
        String inputName1 = args[0];
        FileReader inputReader1 = null;
        BufferedReader buffInReader1 = null;
        Scanner imgFile = null;

        String inputName2 = args[1];
        FileReader inputReader2 = null;
        BufferedReader buffInReader2 = null;
        Scanner structFile = null;

        String outputName1 = args[2];
        FileWriter outputWriter1 = null;
        BufferedWriter dilateOutFile = null;

        String outputName2 = args[3];
        FileWriter outputWriter2 = null;
        BufferedWriter erodeOutFile = null;

        String outputName3 = args[4];
        FileWriter outputWriter3 = null;
        BufferedWriter closingOutFile = null;

        String outputName4 = args[5];
        FileWriter outputWriter4 = null;
        BufferedWriter openingOutFile = null;

        String outputName5 = args[6];
        FileWriter outputWriter5 = null;
        BufferedWriter prettyPrintFile = null;


        try {
            inputReader1 = new FileReader(inputName1);
            buffInReader1 = new BufferedReader(inputReader1);
            imgFile = new Scanner(buffInReader1);

            inputReader2 = new FileReader(inputName2);
            buffInReader2 = new BufferedReader(inputReader2);
            structFile = new Scanner(buffInReader2);

            outputWriter1 = new FileWriter(outputName1);
            dilateOutFile = new BufferedWriter(outputWriter1);

            outputWriter2 = new FileWriter(outputName2);
            erodeOutFile = new BufferedWriter(outputWriter2);

            outputWriter3 = new FileWriter(outputName3);
            openingOutFile = new BufferedWriter(outputWriter3);

            outputWriter4 = new FileWriter(outputName4);
            closingOutFile = new BufferedWriter(outputWriter4);

            outputWriter5 = new FileWriter(outputName5);
            prettyPrintFile = new BufferedWriter(outputWriter5);


            MorphologicalOperations morpOperations = new MorphologicalOperations();
            if (imgFile.hasNextInt()) morpOperations.numImgRows = imgFile.nextInt();
            if (imgFile.hasNext()) morpOperations.numImgCols = imgFile.nextInt();
            if (imgFile.hasNext()) morpOperations.imgMin = imgFile.nextInt();
            if (imgFile.hasNext()) morpOperations.imgMax = imgFile.nextInt();

            if (structFile.hasNext()) morpOperations.numStructRows = structFile.nextInt();
            if (structFile.hasNext()) morpOperations.numStructCols = structFile.nextInt();
            if (structFile.hasNext()) morpOperations.structMin = structFile.nextInt();
            if (structFile.hasNext()) morpOperations.structMax = structFile.nextInt();
            if (structFile.hasNext()) morpOperations.rowOrigin = structFile.nextInt();
            if (structFile.hasNext()) morpOperations.colOrigin = structFile.nextInt();

            morpOperations.setFrameSize();
            morpOperations.setExtraFrame();

            morpOperations.allocateArrays();



        } finally {
            if (imgFile != null) imgFile.close();
            if(structFile!=null) structFile.close();
            if (dilateOutFile != null) dilateOutFile.close();
            if (erodeOutFile != null) erodeOutFile.close();
            if (closingOutFile != null) closingOutFile.close();
            if (openingOutFile != null) openingOutFile.close();
            if (prettyPrintFile != null) prettyPrintFile.close();
        }
    }


}
