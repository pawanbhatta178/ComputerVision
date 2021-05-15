
import java.io.*;
import java.util.Scanner;


public class ChainCoding {

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


        if(chainCodeFile!=null){
            chainCodeFile.close();
        }

        //reading from the newly created Chain Code file and
        chainCodeInputFileReader=new FileReader(chainCodeInputFileName);
        chainCodeInputFileBuffReader=new BufferedReader(chainCodeInputFileReader);
        chainCodeInputFile=new Scanner(chainCodeInputFileBuffReader);

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
