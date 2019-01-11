/*
 * 
 * Author: Jon-Michael Hoang
 * Date Created: 1/8/2019
 * Program: [ GIVE ME A NAME ]
 * Desc: [ ??? ]
 * 
 */

import java.util.*;
import java.io.*;
import javax.swing.*;

public abstract class mainDriver
{
    public static void main (String [] args) throws FileNotFoundException, IOException
    {
        // basic information on the program
        System.out.println ("Author: Jon-Michael Hoang\nProject: A GUI of sort for games\n");
        System.out.println ("This program is currently executing at: " + System.getProperty("user.dir") + "\n");
        
        // instantiate an empty file
        File file = null;
        
        // call a scanner
        Scanner scan = inputScanner.getInputScanner();
        
        // user input variable
        String userInput = null;
        
        // no command line arguments
        if (args.length == 0)
        {
            userInput = null;
            
            // look to see if there already exists a save file within the same directory
            // if so, ask the user if they want to use it or not - otherwise continue
            // 
            // variables instantiated here to manipulate scope
            File tempFile = new File (System.getProperty("user.dir") + "/savefile.txt");
            boolean useDefault = true;  // flag to see whether or not the user wants to use
                                        // the default save file
            
            if (tempFile.isFile() && useDefault == true)
            {
                System.out.print("Looks like you have a default save file - use it? " +
                                 "\nType [ YES ] or [ NO ]: ");
                userInput = scan.nextLine();
                
                // user wants to use the default save file
                while (true)
                {
                    if (userInput.equalsIgnoreCase("YES"))
                    {
                        System.out.println("\nOpening file...");
                        
                        scan.close();
                        
                        return;
                        // TODO: FIX ME
                    }
                    else if (userInput.equalsIgnoreCase("NO"))
                    {
                        useDefault = false;
                        break;
                    }
                    else
                    {
                        System.out.print("Invalid input - please try again: ");
                        userInput = scan.nextLine();
                    }
                }
                
            }
            
            // ask the user to input a save file
            System.out.print ("\nPlease enter a save file otherwise enter [ NONE ] to continue: ");
            userInput = scan.nextLine();
            
            // open the file
            file = new File(userInput);
            
            // file DNE - ask for input again
            while (!file.exists() && !userInput.equalsIgnoreCase("NONE"))
            {
                System.out.print ("\nFile does not exist, please try again: ");
                userInput = scan.nextLine();
                
                file = new File(userInput);
            }
        }
        // one command line argument
        else if (args.length == 1)
        {
            // 1st argument is assumed to be the file name
            file = new File (args[0]);
            
            userInput = null;
            
            // runs this look IFF args[0] does not yield a valid file
            // asks the user to manually enter it in themselves
            while (!file.exists() && !userInput.equalsIgnoreCase("NONE"))
            {
                System.out.println ("\nCould not open [ " + args[0] + " ]");
                System.out.print ("Please try again: ");
                userInput = scan.nextLine();
                
                file = new File(userInput);
            }
        }
        // more than one command line argument
        else
        {
            System.out.println ("\nToo many command line arguments - exiting program...");
            System.exit (0);
        }
                                                               
        // create a default save file
        if (userInput.equalsIgnoreCase("NONE"))
        {
            //
            // TODO: IFF there already exists one, ask the user if the want to overwrite it?
            //
            System.out.println ("\nCreating new save file...");
            
            // CREATE A FILE HERE
            BufferedWriter writer = new BufferedWriter (new FileWriter(System.getProperty("user.dir") +
                                                        "/savefile.txt"));
            writer.write("Hello World!");
            writer.close();
            
            System.out.println ("Done.");
        }
        
        scan.close();   // close the scanner otherwise there'd be leaks
        
        return;
    }
}