import java.io.*;
import java.util.Scanner;

class Image {

}

class CCproperty{

}

class ChainCode {

    public static void main(String[] args) throws IOException {
        String labelFileName = args[0]+".txt";
        FileReader labelFileReader = null;
        BufferedReader labelFileBuffReader= null;
        Scanner labelFile = null;

        String propFileName = args[0]+".txt";
        FileReader propFileReader = null;
        BufferedReader propFileBuffReader = null;
        Scanner propFile = null;

        String chainCodeFileName = args[0]+"_chainCode.txt";
        FileWriter chainCodeFileWriter = null;
        BufferedWriter chainCodeFile = null;

        String boundaryFileName = args[0]+"_Boundary.txt";
        FileWriter boundaryFileWriter = null;
        BufferedWriter boundaryFile = null;


        try {
            labelFileReader = new FileReader(labelFileName);
            labelFileBuffReader = new BufferedReader(labelFileReader);
            labelFile  = new Scanner(labelFileBuffReader);

            propFileReader = new FileReader( propFileName);
            propFileBuffReader = new BufferedReader(propFileReader);
            propFile = new Scanner(propFileBuffReader);

            chainCodeFileWriter = new FileWriter(chainCodeFileName);
            chainCodeFile = new BufferedWriter(chainCodeFileWriter);

            boundaryFileWriter = new FileWriter(boundaryFileName);
            boundaryFile = new BufferedWriter(boundaryFileWriter);



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
