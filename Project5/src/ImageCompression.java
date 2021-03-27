import java.io.*;
import java.util.Scanner;

class DistanceTransformCompression {
    int numImgRows;
    int numImgCols;
    int minVal;
    int maxVal;
    int newMin;
    int newMax;
    int rowFrameSize;
    int colFrameSize;
    int extraRows;
    int extraCols;
    int[][] zeroFramedAry;
    int[][] skeletonAry;

    DistanceTransformCompression(Scanner imgFile){
        setTotalFrameSize();
        setFrameSize();
        loadHeader(imgFile);
        initializeArrays();
        loadImg(imgFile);
    }

    void initializeArrays(){
        zeroFramedAry=new int [numImgRows+extraRows][numImgCols+extraCols];
        skeletonAry=new int [numImgRows+extraRows][numImgCols+extraCols];
    }

    void setTotalFrameSize() {
        extraRows =  2;
        extraCols =  2;
    }

    void setFrameSize() {
        rowFrameSize = extraRows / 2;
        colFrameSize =extraCols / 2;
    }

    void loadHeader(Scanner imgFile){
        numImgRows=imgFile.nextInt();
        numImgCols=imgFile.nextInt();
        minVal=imgFile.nextInt();
        maxVal=imgFile.nextInt();
    }


    void loadImg(Scanner imgFile) {
        for (int i = rowFrameSize; i < numImgRows + rowFrameSize; i++) {
            for (int j = colFrameSize; j < numImgCols + colFrameSize; j++) {
                zeroFramedAry[i][j] = imgFile.nextInt();
            }
        }
    }

    void writeHeader(BufferedWriter outFile) throws IOException {
        outFile.write(numImgRows+" "+numImgCols+" "+newMin+" "+newMax+"\n");
    }

    void prettyPrint(BufferedWriter outFile) throws IOException {
        writeHeader(outFile);
     int maxLength;
     maxLength=Integer.toString(newMax).length();
       System.out.println(newMax);
        for (int i = rowFrameSize; i < numImgRows + rowFrameSize; i++)
        {
            for (int j = colFrameSize; j <numImgCols + colFrameSize; j++)
            {
                if (zeroFramedAry[i][j] == 0)
                {
                    outFile.write(". ");
                }
                else
                {
                    outFile.write(Integer.toString(zeroFramedAry[i][j])+" ");
                }
                int currentLength;
                currentLength = Integer.toString(zeroFramedAry[i][j]).length();

                while (currentLength < maxLength)
                {
                    outFile.write( " ");
                    currentLength++;
                }
            }
            outFile.write("\n");
        }
    }

    void prettyPrint(BufferedWriter outFile, int [][]arrayToPrint) throws IOException {
        writeHeader(outFile);
        int maxLength;
        maxLength=Integer.toString(newMax).length();
        System.out.println(newMax);
        for (int i = rowFrameSize; i < numImgRows + rowFrameSize; i++)
        {
            for (int j = colFrameSize; j <numImgCols + colFrameSize; j++)
            {
                if (arrayToPrint[i][j] == 0)
                {
                    outFile.write(". ");
                }
                else
                {
                    outFile.write(Integer.toString(arrayToPrint[i][j])+" ");
                }
                int currentLength;
                currentLength = Integer.toString(arrayToPrint[i][j]).length();

                while (currentLength < maxLength)
                {
                    outFile.write( " ");
                    currentLength++;
                }
            }
            outFile.write("\n");
        }
    }

    void print2DArray(int [][] array){
        for (int i=0;i<array.length;i++){
            for (int j=0;j<array[0].length;j++){
                System.out.print(array[i][j]);
            }
            System.out.print("\n");
        }
        System.out.print("\n\n");
    }

    int findMin(int ...array){
        int minVal=9999;
        for (int i:array){
            if(i<minVal){
                minVal=i;
            }
        }
        return minVal;
    }

    int findMax(int ...array){
        int maxVal=-1;
        for (int i:array){
            if(i>maxVal){
                maxVal=i;
            }
        }
        return maxVal;
    }

    void passOne8Connectedness(){
        newMin=9999;
        newMax=0;
        for(int i=rowFrameSize;i<numImgRows+rowFrameSize;i++){
            for(int j=colFrameSize;j<numImgCols+colFrameSize;j++){
                int pixelVal=zeroFramedAry[i][j];
                if(pixelVal>0){
                    int a=zeroFramedAry[i-1][j-1];
                    int b=zeroFramedAry[i-1][j];
                    int c=zeroFramedAry[i-1][j+1];
                    int d=zeroFramedAry[i][j-1];
                    zeroFramedAry[i][j]=findMin(a,b,c,d)+1;
                }
                //Updating newMin and newMax
                if(zeroFramedAry[i][j]>newMax){
                    newMax=zeroFramedAry[i][j];
                }
                if(zeroFramedAry[i][j]<newMin){
                    newMin=zeroFramedAry[i][j];
                }
            }
        }
    }

    void passTwo8Connectedness(){
        newMin=9999;
        newMax=0;
        for(int i=numImgRows+rowFrameSize-1;i>=rowFrameSize;i--){
            for(int j=numImgCols+colFrameSize-1;j>=colFrameSize;j--){
                int pixelVal=zeroFramedAry[i][j];
                if(pixelVal>0){
                    int e=zeroFramedAry[i][j+1];
                    int f=zeroFramedAry[i+1][j-1];
                    int g=zeroFramedAry[i+1][j];
                    int h=zeroFramedAry[i+1][j+1];
                    zeroFramedAry[i][j]=findMin(e+1,f+1,g+1,h+1,pixelVal);
                }
                //Updating newMin and newMax
                if(zeroFramedAry[i][j]>newMax){
                    newMax=zeroFramedAry[i][j];
                }
                if(zeroFramedAry[i][j]<newMin){
                    newMin=zeroFramedAry[i][j];
                }
            }
        }
    }

    boolean isLocalMaxima(int p, int [] neighbours){
        boolean returnVal=true;
        for(int neighbour:neighbours){
            if(p<neighbour){
                returnVal=false;
            }
        }
        return returnVal;
    }

    void localMaxima(){
        newMin=9999;
        newMax=0;
        for(int i=rowFrameSize;i<numImgRows+rowFrameSize;i++){
            for(int j=colFrameSize;j<numImgCols+colFrameSize;j++){
                int pixelVal=zeroFramedAry[i][j];
                int a=zeroFramedAry[i-1][j-1];
                int b=zeroFramedAry[i-1][j];
                int c=zeroFramedAry[i-1][j+1];
                int d=zeroFramedAry[i][j-1];
                int e=zeroFramedAry[i][j+1];
                int f=zeroFramedAry[i+1][j-1];
                int g=zeroFramedAry[i+1][j];
                int h=zeroFramedAry[i+1][j+1];
                int [] neighbours={a,b,c,d,e,f,g,h};
                if(isLocalMaxima(pixelVal,neighbours)){
                    skeletonAry[i][j]=zeroFramedAry[i][j];
                }
                else{
                    skeletonAry[i][j]=0;
                }

                //Updating newMin and newMax
                if(skeletonAry[i][j]>newMax){
                    newMax=zeroFramedAry[i][j];
                }
                if(skeletonAry[i][j]<newMin){
                    newMin=zeroFramedAry[i][j];
                }
            }
        }
    }

    void skeletonImgCompression(BufferedWriter outFile) throws IOException {
        writeHeader(outFile);
        for(int i=rowFrameSize;i<numImgRows+rowFrameSize;i++){
            for(int j=colFrameSize;j<numImgCols+colFrameSize;j++){
                int pixelVal=skeletonAry[i][j];
               if(pixelVal>0){
                   outFile.write((i-rowFrameSize)+" "+(j-colFrameSize)+" "+pixelVal+"\n");
               }
            }
        }
    }

    void expansionPassOne(){
        newMin=9999;
        newMax=0;
        for(int i=rowFrameSize;i<numImgRows+rowFrameSize;i++){
            for(int j=colFrameSize;j<numImgCols+colFrameSize;j++){
               int pixelValue=skeletonAry[i][j];

               if(pixelValue==0){
                   int a=skeletonAry[i-1][j-1];
                   int b=skeletonAry[i-1][j];
                   int c=skeletonAry[i-1][j+1];
                   int d=skeletonAry[i][j-1];
                   int e=skeletonAry[i][j+1];
                   int f=skeletonAry[i+1][j-1];
                   int g=skeletonAry[i+1][j];
                   int h=skeletonAry[i+1][j+1];

                   int max=findMax(a, b, c, d, e,f,g,h)-1;

                 if(skeletonAry[i][j]<max){
                     skeletonAry[i][j]=max;
                 }
               }
                //Updating newMin and newMax
                if(skeletonAry[i][j]>newMax){
                    newMax=zeroFramedAry[i][j];
                }
                if(skeletonAry[i][j]<newMin){
                    newMin=zeroFramedAry[i][j];
                }
            }
        }
    }



    public static void main(String[] args) throws IOException {
        String inputName1 = args[0];
        FileReader inputReader1 = null;
        BufferedReader buffInReader1 = null;
        Scanner imgFile = null;

        String outputName1 = args[1];
        FileWriter outputWriter1 = null;
        BufferedWriter prettyPrintFile = null;

        String outputName2 = "CompressedImg.txt";
        FileWriter outputWriter2 = null;
        BufferedWriter compressedImg = null;

        String outputName3 = "ExpandedImg.txt";
        FileWriter outputWriter3 = null;
        BufferedWriter expandedImg = null;



        try {
            inputReader1 = new FileReader(inputName1);
            buffInReader1 = new BufferedReader(inputReader1);
            imgFile = new Scanner(buffInReader1);


            outputWriter1 = new FileWriter(outputName1);
            prettyPrintFile = new BufferedWriter(outputWriter1);

            outputWriter2 = new FileWriter(outputName2);
            compressedImg = new BufferedWriter(outputWriter2);

            outputWriter3 = new FileWriter(outputName3);
            expandedImg = new BufferedWriter(outputWriter3);

           //Compression steps begins
            DistanceTransformCompression d= new DistanceTransformCompression(imgFile);
            d.passOne8Connectedness();
            prettyPrintFile.write("Pass One: 8 connectness Distance Transform\n");
            d.prettyPrint(prettyPrintFile);

            d.passTwo8Connectedness();
            prettyPrintFile.write("\nPass Two: 8 connectness Distance Transform\n");
            d.prettyPrint(prettyPrintFile);

            d.localMaxima();
            prettyPrintFile.write("\nResult of Local Maxima Operation\n");
            d.prettyPrint(prettyPrintFile,d.skeletonAry);

            d.skeletonImgCompression(compressedImg);

            //Decompression Steps Begins
            d.expansionPassOne();
            d.prettyPrint();

        } finally {
            if (imgFile != null)
                imgFile.close();
            if (prettyPrintFile != null)
                prettyPrintFile.close();
            if (compressedImg != null)
                compressedImg.close();
            if (expandedImg != null)
                expandedImg.close();

        }
    }
}


