import java.io.*;
import java.util.Scanner;

public class RunLengthEncoding {
    int inputNumCols;
    int inputNumRows;
    int inputMaxVal;
    int inputMinVal;
    int inputImageBody[][];

    void readBody(Scanner inputFile){
        inputImageBody=new int [inputNumRows][inputNumCols];

        for (int i=0;i<inputNumRows;i++){
            for (int j=0;j<inputNumCols;j++){
                if(inputFile.hasNextInt()){
                    inputImageBody[i][j]=inputFile.nextInt();
                }
            }
        }
    }

    void readHeader(Scanner imgFile){
        if( imgFile.hasNext()){
            inputNumRows=imgFile.nextInt();
        }
        if( imgFile.hasNext()){
            inputNumCols=imgFile.nextInt();
        }
        if( imgFile.hasNext()){
            inputMinVal=imgFile.nextInt();
        }
        if( imgFile.hasNext()){
            inputMaxVal=imgFile.nextInt();
        }
    }

    void printBody(){
        for (int i=0;i<inputNumRows;i++){
            for (int j=0;j<inputNumCols;j++){
                System.out.print(inputImageBody[i][j]);
            }
            System.out.print("\n");
        }
        System.out.print("\n\n");
    }

    void encodeZeroNoWrap(BufferedWriter outFile) throws IOException {//include zero no wrap
        for (int i=0;i<inputNumRows;i++){
            int length=1;
            for(int j=0;j<inputNumCols;j++){
                if(length==1){
                    outFile.write(i+" "+j+" ");
                }
                 int currVal=inputImageBody[i][j];
                 int nextVal=-1;
                 if(j<inputNumCols-1){
                   nextVal=inputImageBody[i][j+1];
                 }

                 if(nextVal==currVal){
                     length++;
                 }
                 else{
                     outFile.write(currVal+" "+length+"\n");
                     length=1;
                 }
            }
        }
    }

    void encodeZeroWrap(BufferedWriter outFile) throws IOException {
        int length=1;
        for (int i=0;i<inputNumRows;i++){
            for(int j=0;j<inputNumCols;j++){
                if(length==1){
                    outFile.write(i+" "+j+" ");
                }
                int currVal=inputImageBody[i][j];
                int nextVal=-1;
                if(j<inputNumCols-1){ //only if next col is valid
                    nextVal=inputImageBody[i][j+1];
                }
                else{
                    if(i<inputNumRows-1){ //only if next row exists
                        nextVal=inputImageBody[i+1][0];
                    }
                }

                if(nextVal==currVal){
                    length++;
                }
                else{
                    outFile.write(currVal+" "+length+"\n");
                    length=1;
                }
            }
        }
    }

    void noZeroNoWrap(BufferedWriter outFile){
        for(int i=0;i<inputNumRows;i++){
            for(int j=0;j<inputNumCols)
        }
    }

    public static void main(String [] args) throws IOException {
        String inputName=args[0];
        FileReader inputReader1=null;
        BufferedReader buffReader1=null;
        Scanner inputFile=null;

        String outputName = args[1];
        FileWriter outputWriter = null;
        BufferedWriter outFile = null;

        try{
            inputReader1=new FileReader(inputName);
            buffReader1=new BufferedReader(inputReader1);
            inputFile=new Scanner(buffReader1);

            outputWriter = new FileWriter(outputName);
            outFile = new BufferedWriter(outputWriter);

            RunLengthEncoding r=new RunLengthEncoding();
            r.readHeader(inputFile);
            r.readBody(inputFile);
            r.printBody();
//            r.encodeZeroNoWrap(outFile);
            r.encodeZeroWrap(outFile);
        }
        finally{
            if(inputFile!=null){
                inputFile.close();
            }
            if(outFile!=null){
                outFile.close();
            }
        }
    }
}
