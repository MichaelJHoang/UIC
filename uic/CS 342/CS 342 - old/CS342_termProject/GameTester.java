import java.io.*;
import java.util.*;

// main driver for the whole project
public class GameTester
{
    public static void main (String [] args)
    {
        System.out.println ("Class: CS 342\nTerm Project: Video Game Level Designing\nName: Jon-Michael Hoang\nNetID: jhoang6\n");
        
        //Direction directionTemp;
        //Place placeTemp;
        
        Game game = new Game("CS342_HW1");
        
        game.play();
        
        return;
    }
    
    File getCleanFile (String filename)
    {
        ArrayList <String> list = new ArrayList <String> ();
        
        File inputFile = new File (filename);
        
        
        
 
        
        return inputFile;
    }
    
}