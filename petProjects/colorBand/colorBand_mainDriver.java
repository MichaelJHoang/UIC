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
            file = new File (System.getProperty("user.dir") + "/test.png");
            img = ImageIO.read(file);
        }
        catch (Exception e)
        {
            System.out.println(e + "\n");
            e.printStackTrace();
        }
        
        // get image dimensions
        int width = img.getWidth();
        int height = img.getHeight();
        
        // get the pixel value. getRGB(x,y) takes in the coordinate of a pixel and returns
        // and integer value which can be negative or positive.
        // NOTE: pixelValue is an int that holds the value of the pixel
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
        
        alpha = 255;
        r = 100;
        g = 150;
        b = 200;
        
        // construct a pixel and set it on the img
        pixelValue = (alpha << 24) | (r << 16) | (g << 8) | b;
        img.setRGB(0, 0, pixelValue);
        
        // draw/write the image
        try
        {
            file = new File (System.getProperty("user.dir") + "/testOutput.png");
            ImageIO.write(img, "png", file);
        }
        catch (Exception e)
        {
            System.out.println(e + "\n");
            e.printStackTrace();
        }
        
        return;
    }
}