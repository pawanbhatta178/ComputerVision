import java.io.*;
import java.util.Scanner;

class DistanceTransformCompression {

    public static void main(String[] args) throws IOException {
        String inputName1 = args[0];
        FileReader inputReader1 = null;
        BufferedReader buffInReader1 = null;
        Scanner imgFile = null;

        String outputName1 = args[1];
        FileWriter outputWriter1 = null;
        BufferedWriter dilateOutFile = null;


        try {
            inputReader1 = new FileReader(inputName1);
            buffInReader1 = new BufferedReader(inputReader1);
            imgFile = new Scanner(buffInReader1);



            outputWriter1 = new FileWriter(outputName1);
            dilateOutFile = new BufferedWriter(outputWriter1);



        } finally {
            if (imgFile != null)
                imgFile.close();
            if (dilateOutFile != null)
                dilateOutFile.close();

        }
    }
}


