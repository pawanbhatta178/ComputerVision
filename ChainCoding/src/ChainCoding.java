
import java.io.*;
import java.util.Scanner;

class Image{
int numRows, numCols, minVal, maxVal;
int [][] imageAry;
int [][] boundaryAry;
int [][] ccAry;


Image(Scanner imgFile){
    loadHeader(imgFile);
    imageAry = new int[numRows + 2][numCols + 2];
    loadImage(imgFile);
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

    void printBoundaryAry(BufferedWriter outFile) throws IOException {
        writeHeader(outFile);
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                outFile.write(Integer.toString(boundaryAry[i][j]) + " ");
            }
            outFile.write("\n");
        }
    }

    void prettyPrintBoundaryAry(BufferedWriter outFile) throws IOException {
        writeHeader(outFile);
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                if (boundaryAry[i][j] == 0) {
                    outFile.write(". ");
                } else {
                    outFile.write(Integer.toString(boundaryAry[i][j]) + " ");
                }
            }
            outFile.write("\n");
        }
    }

    void constructBoundary(Scanner chainCodeFile) {
        numRows = chainCodeFile.nextInt();
        numCols = chainCodeFile.nextInt();
        minVal = chainCodeFile.nextInt();
        maxVal = chainCodeFile.nextInt();

        boundaryAry=new int [numRows][numCols];
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                boundaryAry[i][j] = 0;
            }
        }

        while(chainCodeFile.hasNextInt()){
            int pixelVal=chainCodeFile.nextInt();
            Point startP=new Point(chainCodeFile.nextInt(), chainCodeFile.nextInt());
            boundaryAry[startP.row][startP.col]=pixelVal;
            Point currentP=getNextP(startP, chainCodeFile.nextInt());
            while(!currentP.equals(startP)){
                boundaryAry[currentP.row][currentP.col]=pixelVal;
                currentP=getNextP(currentP, chainCodeFile.nextInt());
            }
        }



    }
    Point getNextP(Point currentP, int direction) {
        Point returnVal = new Point(0, 0);
        switch (direction) {
            case 0:
                returnVal.update(currentP.row, currentP.col + 1);
                break;
            case 1:
                returnVal.update(currentP.row - 1, currentP.col + 1);
                break;
            case 2:
                returnVal.update(currentP.row - 1, currentP.col);
                break;
            case 3:
                returnVal.update(currentP.row - 1, currentP.col - 1);
                break;
            case 4:
                returnVal.update(currentP.row, currentP.col - 1);
                break;
            case 5:
                returnVal.update(currentP.row + 1, currentP.col - 1);
                break;
            case 6:
                returnVal.update(currentP.row + 1, currentP.col);
                break;
            case 7:
                returnVal.update(currentP.row + 1, currentP.col + 1);
                break;
            default:
                break;
        }

        return returnVal;
    }


}

class CCproperty{
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
        CCAry = new int[maxRow - minRow + 1 + 2][maxCol - minCol + 1 + 2];
        clearCCAry();

        // Copying all the pixel values of a given CC by using bounding box's values
        for (int i = 1; i < maxRow - minRow + 1 + 1; i++) {
            for (int j = 1; j < maxCol - minCol + 1 + 1; j++) {
                CCAry[i][j] = imgAry[i + minRow][j + minCol];
            }
        }
    }
}

class Point {
    int row, col;

    Point(int i, int j) {
        row = i;
        col = j;
    }

    void update(int i, int j) {
        row = i;
        col = j;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;
        if ((obj == null) || (obj.getClass() != this.getClass()))
            return false;
        // object must be Point at this point
        Point p = (Point) obj;
        return (row == p.row) && (col == p.col);
    }

    @Override
    public String toString() {
        return "(" + row + "," + col + ")";
    }
}


public class ChainCoding {
    Point[] neighborCoord;
    int[] zeroTable;
    Point startP;
    Point currentP;// current none zero border pixel
    Point nextP;// next none-zero border pixel
    int lastQ; // Range from 0 to 7; it is the direction of the last zero scanned from currentP
    int nextDir;// the next scanning direction of currentP's neighbors
    int pChainDir; // chain code direction from currentP to nextP
    CCproperty ccProp;

    ChainCoding() {
        zeroTable = new int[] { 6, 0, 0, 2, 2, 4, 4, 6 };
    }

    void getChainCode(CCproperty cc, BufferedWriter chainCodeFile) throws IOException{
        ccProp=cc;
        startP = new Point(1, 1);
        currentP = new Point(1, 1);
        lastQ=4;

    outerloop: for(int i=1;i<cc.maxRow-cc.minRow+1;i++){
         for(int j=1;j<cc.maxCol-cc.minCol+1;j++){
            System.out.println(cc.minRow+" "+cc.minCol);
             if(cc.CCAry[i][j]==cc.label){
                 startP.row = i;
                 startP.col = j;
                 currentP.row = startP.row;
                 currentP.col = startP.col;
                 lastQ = 4;
                 chainCodeFile.write(cc.label+" "+(i+cc.minRow-1)+" "+(j+cc.minCol-1)+" ");
                 break outerloop;
             }
         }
     }
     int count=0;
     while(count==0 || !currentP.equals(startP)){
         count++;
         loadNeighborsCoord(currentP);
         nextDir=++lastQ%8;
         pChainDir=findNextP(nextDir, currentP);
         nextP = new Point(neighborCoord[pChainDir].row, neighborCoord[pChainDir].col);
         ccProp.CCAry[nextP.row][nextP.col] = (-1) * ccProp.CCAry[nextP.row][nextP.col];
         chainCodeFile.write(pChainDir + " ");
         if(pChainDir==0){
             lastQ=zeroTable[7];
         }
         else{
             lastQ = zeroTable[pChainDir - 1];
         }
         currentP.row = nextP.row;
         currentP.col = nextP.col;
     }

    }

    void loadNeighborsCoord(Point p){
      neighborCoord=new Point[8];
      neighborCoord[0]=new Point(p.row, p.col+1);
      neighborCoord[1]=new Point(p.row-1, p.col+1);
        neighborCoord[2]=new Point(p.row-1, p.col);
        neighborCoord[3]=new Point(p.row-1, p.col-1);
        neighborCoord[4]=new Point(p.row, p.col-1);
        neighborCoord[5]=new Point(p.row+1, p.col-1);
        neighborCoord[6]=new Point(p.row+1, p.col);
        neighborCoord[7]=new Point(p.row+1, p.col+1);

    }

    int findNextP(int direction, Point p){
        int row=p.row;
        int col=p.col;

       for(int i=0;i<8;i++){
           switch(direction){
               case 0:
                   if(ccProp.CCAry[row][col+1]>0|| ccProp.CCAry[row][col + 1] == -1){
                       return 0;
                   }
                   break;
               case 1:
                   if(ccProp.CCAry[row-1][col+1]>0|| ccProp.CCAry[row-1][col + 1] == -1){
                       return 1;
                   }
                   break;
               case 2:
                   if(ccProp.CCAry[row-1][col]>0|| ccProp.CCAry[row-1][col ] == -1){
                       return 2;
                   }
                   break;
               case 3:
                   if(ccProp.CCAry[row-1][col-1]>0|| ccProp.CCAry[row-1][col - 1] == -1){
                       return 3;
                   }
                   break;
               case 4:
                   if(ccProp.CCAry[row][col-1]>0|| ccProp.CCAry[row][col - 1] == -1){
                       return 4;
                   }
                   break;
               case 5:
                   if(ccProp.CCAry[row+1][col-1]>0|| ccProp.CCAry[row+1][col - 1] == -1){
                       return 5;
                   }
                   break;
               case 6:
                   if(ccProp.CCAry[row+1][col]>0|| ccProp.CCAry[row+1][col ] == -1){
                       return 6;
                   }
                   break;
               case 7:
                   if(ccProp.CCAry[row+1][col+1]>0|| ccProp.CCAry[row+1][col + 1] == -1){
                       return 7;
                   }
                   break;
               default:
                   break;

           }
           direction=++direction%8;
       }
       return 0;
    }

    public static void main(String [] args ) throws IOException{
     String labelFileName=args[0]+".txt";
     FileReader labelFileReader=null;
     BufferedReader labelFileBuffReader=null;
     Scanner labelFile=null;

     String propertyFileName=args[1]+".txt";
     FileReader propertyFileReader=null;
     BufferedReader propertyFileBuffReader=null;
     Scanner propertyFile=null;

     String chainCodeFileName=args[0]+"_chainCode.txt";
     FileWriter chainCodeFileWriter=null;
     BufferedWriter chainCodeFile=null;

     String boundaryFileName=args[0]+"_boundary.txt";
     FileWriter boundaryFileWriter=null;
     BufferedWriter boundaryFile=null;

     //We need to close the chain code file and read it again to form the original image from the chain code
        String chainCodeInputFileName=args[0]+"_chainCode.txt";
        FileReader chainCodeInputFileReader=null;
        BufferedReader chainCodeInputFileBuffReader=null;
        Scanner chainCodeInputFile=null;

        try{
        labelFileReader=new FileReader(labelFileName);
        labelFileBuffReader=new BufferedReader(labelFileReader);
        labelFile=new Scanner(labelFileBuffReader);

        propertyFileReader=new FileReader(propertyFileName);
        propertyFileBuffReader=new BufferedReader(propertyFileReader);
        propertyFile=new Scanner(propertyFileBuffReader);

        boundaryFileWriter=new FileWriter(boundaryFileName);
        boundaryFile=new BufferedWriter(boundaryFileWriter);

        chainCodeFileWriter=new FileWriter(chainCodeFileName);
        chainCodeFile=new BufferedWriter(chainCodeFileWriter);

        //creating chain Code using Property File and labelled File
         Image img=   new Image(labelFile);

         CCproperty ccProp=new CCproperty(propertyFile);

         img.writeHeader(chainCodeFile);
         for(int i=0;i<ccProp.numCC;i++){
             ccProp.loadCCAry(propertyFile,img.imageAry);
             ChainCoding c=new ChainCoding();
             c.getChainCode(ccProp,chainCodeFile);
         }

        if(chainCodeFile!=null){
            chainCodeFile.close();
        }

        //reading from the newly created Chain Code file and
        chainCodeInputFileReader=new FileReader(chainCodeInputFileName);
        chainCodeInputFileBuffReader=new BufferedReader(chainCodeInputFileReader);
        chainCodeInputFile=new Scanner(chainCodeInputFileBuffReader);

        img.constructBoundary(chainCodeInputFile);
        img.prettyPrintBoundaryAry(boundaryFile);
        img.prettyPrintBoundaryAry(boundaryFile);


        if(chainCodeInputFile!=null){
            chainCodeInputFile.close();
        }

        }
        finally{
            if(labelFile!=null){
                labelFile.close();
            }
            if(propertyFile!=null){
                propertyFile.close();
            }
            if(boundaryFile!=null){
                boundaryFile.close();
            }
        }

    }
}
