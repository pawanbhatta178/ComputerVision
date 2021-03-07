import java.io.*;
import java.util.Scanner;

public class ConnectedComponent {

    public static void main(String[] args) throws IOException{
       String inputName=args[0];
       FileReader inputReader1=null;
       BufferedReader buffReader1=null;
       Scanner inputFile=null;

       try{
           inputReader1=new FileReader(inputName);
           buffReader1=new BufferedReader(inputReader1);
           inputFile=new Scanner(buffReader1);


       }
       finally{

       }
    }
}
