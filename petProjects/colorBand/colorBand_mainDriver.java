import java.util.*;
import java.io.*;
import java.awt.image.BufferedImage;
import javax.imageio.ImageIO;

public class colorBand_mainDriver
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
        
        // get image dimensions
        int width = img.getWidth();
        int height = img.getHeight();
        
        // get the pixel value. getRGB(x,y) takes in the coordinate of a pixel and returns
        // and integer value which can be negative or positive.
        int pixelValue = img.getRGB (0,0);
        
        // NOTE: 0xff = hexadecimal 255
        // get pixel alpha
        int alpha = (pixelValue >> 24) & 0xff;
        
        // get red - which occupies 8 bits from indices 16-23
        int r = (pixelValue >> 16) & 0xff;
        
        // get green - which occupies 8 from 8-15
        int g = (pixelValue >> 8) & 0xff;
        
        // get blue - which occupies 0-7
        int b = pixelValue & 0xff;
        
        return;
    }
}