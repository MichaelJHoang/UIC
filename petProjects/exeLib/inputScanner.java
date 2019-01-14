/*
 * 
 * Author: Jon-Michael Hoang
 * Date Created: 1/8/2019
 * Program: [ GIVE ME A NAME ]
 * Desc: [ ??? ]
 * 
 */

import java.util.Scanner;

public class inputScanner
{
    // a single instance of the inputScanner
    private static inputScanner singleton = null;
    
    // scanner object
    private static Scanner scan;
    
    // input scanner constructor
    private inputScanner ()
    {
        scan = new Scanner (System.in);
    }
    
    // returns the scanner. Creates an instance of the class provided it never existed
    public static Scanner getInputScanner ()
    {
        singleton = singleton == null ? new inputScanner() : singleton;
        
        return scan;
    }
}
