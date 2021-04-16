import java.io.*;
import java.util.Scanner;

public class Decode {
   int numCols;
   int numRows;
   int minVal;
   int maxVal;

   int startCol, startRow,greyScale,length;
   int [][] img;

   Decode(Scanner input){
   loadHeader(input);
   }


    void loadHeader(Scanner imgFile) {
        numCols = imgFile.nextInt();
        numRows = imgFile.nextInt();
        minVal = imgFile.nextInt();
        maxVal = imgFile.nextInt();
    }

    void decoding(Scanner input, BufferedWriter output) throws IOException {
    int row=0;

    while(row<numRows && input.hasNextLine() ){
        int col=0;
        startRow=input.nextInt();
        startCol=input.nextInt();
        greyScale= input.nextInt();
        length=input.nextInt();
        int i=1;
        while(i<=length){
            output.write(greyScale+" ");
            i++;
            col++;
        }
        if(col>=numCols){
            output.write("\n");
        }
        row++;
    }




    }

    public static void main(String[] args) throws IOException{
        String inputName=args[0];
        FileReader inputReader=null;
        BufferedReader buffReader=null;
        Scanner input=null;

        String decodedFileName=args[1];
        FileWriter decodedFileWriter=null;
        BufferedWriter decodedFile=null;

        String debugFileName=args[2];
        FileWriter debugFileWriter=null;
        BufferedWriter debugFile=null;


        try {
           inputReader = new FileReader(inputName);
           buffReader = new BufferedReader(inputReader);
           input = new Scanner(buffReader);


           decodedFileWriter=new FileWriter(decodedFileName);
           decodedFile=new BufferedWriter(decodedFileWriter);

            debugFileWriter=new FileWriter(debugFileName);
            debugFile=new BufferedWriter(debugFileWriter);

            Decode d=new Decode(input);
            decodedFile.write(d.numRows+" "+d.numCols+" "+d.minVal+" "+d.maxVal+"\n");
            d.decoding(input, decodedFile);
        }

       finally{
         if(input!=null){
             input.close();
         }
         if(decodedFile!=null){
             decodedFile.close();
         }
         if(debugFile!=null){
             debugFile.close();
         }

       }
    }

}
