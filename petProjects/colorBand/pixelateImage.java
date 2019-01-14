import java.util.*;
import java.io.*;
import java.awt.image.BufferedImage;
import javax.imageio.ImageIO;

public class pixelateImage
{
    public static void main (String [] args) throws FileNotFoundException, IOException
    {
        // userInput variables
        Scanner scan = inputScanner.getInputScanner();
        String userInput = null;
        
        // file variables
        BufferedImage img = null;
        File file = null;
        
        // read in the image
        try
        {
            file = new File ("");
            img = ImageIO.read(file);
        }
        catch (IOException e)
        {
            System.out.println(e + "\n");
            e.printStackTrace();
        }
        
        
        return;
    }
}