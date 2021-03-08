import java.io.*;
import java.util.Scanner;




public class ConnectedComponent {
     int inputNumCols;
     int inputNumRows;
     int inputMaxVal;
     int inputMinVal;
     int inputImageBody[][];
    int paddedImageBody[][];
    int connectedArray[][];
    int frameSize;
    int newLabel=0;
    int eqTable[];

     void padWithZero(int frameSize){
         this.frameSize=frameSize;
         paddedImageBody=new int [inputNumRows+2*frameSize][inputNumCols+ 2*frameSize];
         for(int i=frameSize;i<inputNumRows+frameSize;i++){
             for(int j=frameSize;j<inputNumCols+frameSize;j++){
                 paddedImageBody[i][j]=inputImageBody[i-frameSize][j-frameSize];
             }
         }
     }

     boolean areAllEqualOrZero( int... allValues){
         int firstValue=0;

         for(int value:allValues){
             if(value!=0){
                 if(firstValue==0){ //value other than 0 shows up for 1st time
                     firstValue=value; //setting first non zero value
                 }
                 else{//value other than zero shows up for 2nd or more times
                     if(value!=firstValue){
                         return false;
                     }  firstValue=value;
                 }
             }
         }
        return true;
    }

    int getNonZeroValue(int... allValues){
         for (int value:allValues){
             if(value!=0){
                 return value;
             }
         }
         return 0;
    }

    int minExcludeZero(int... allValues){
         int minVal=9999;
         for(int value: allValues){
             if(value!=0 && value<minVal){
                 minVal=value;
             }
         }
         return minVal;
    }

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

    void printBody(){
        for (int i=0;i<inputNumRows;i++){
            for (int j=0;j<inputNumCols;j++){
                   System.out.print(inputImageBody[i][j]);
            }
            System.out.print("\n");
        }
        System.out.print("\n\n");
    }

    void printPaddedBody(){
        for (int i=0;i<inputNumRows+2*frameSize;i++){
            for (int j=0;j<inputNumCols+2*frameSize;j++){
                System.out.print(paddedImageBody[i][j]);
            }
            System.out.print("\n");
        }
        System.out.print("\n\n");
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

    void passOne(){
         eqTable=new int [inputNumRows*inputNumCols/4];
         connectedArray=paddedImageBody;
     for (int i=frameSize;i<inputNumRows+frameSize;i++){
         for (int j=frameSize;j<inputNumCols+frameSize;j++){
          if(paddedImageBody[i][j]>0){
              //8 connectedness
              int a=paddedImageBody[i-1][j-1];
              int b=paddedImageBody[i-1][j];
              int c=paddedImageBody[i-1][j+1];
              int d =paddedImageBody[i][j-1];

              //first case
              if((a==0)&&(b==0)&&(c==0)&&(d==0)){
                  newLabel++;
                  connectedArray[i][j]=newLabel;
                  for(int z=1;z<(eqTable.length);z++){
                      if(eqTable[z]!=0){
                          eqTable[z]=newLabel;
                          break;
                      }
                  }
              }

              //second case
             else if(areAllEqualOrZero(a,b,c,d)){
                  connectedArray[i][j]= getNonZeroValue(a,b,c,d);
              }

             //third case
              else{
                 connectedArray[i][j]= minExcludeZero(a,b,c,d);
              }
          }
         }
     }
    }

    public static void main(String[] args) throws IOException{
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

           ConnectedComponent c=new ConnectedComponent();
           c.readHeader(inputFile);
           c.readBody(inputFile);
           c.printBody();
           c.padWithZero(1);
           c.printPaddedBody();

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
