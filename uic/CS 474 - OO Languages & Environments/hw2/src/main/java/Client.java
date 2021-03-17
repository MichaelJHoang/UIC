import java.io.File;
import java.util.*;
import java.util.logging.LogManager;
import java.util.logging.Logger;

@FacadeAnnotation(name = "Client", clientAccessible = true)
public class Client
{
    // logger
    myLogger MYLOGGER = new myLogger();
    static LogManager logManager = LogManager.getLogManager();
    static Logger log = logManager.getLogger(Logger.GLOBAL_LOGGER_NAME);

    @FacadeAnnotation(name = "Client.main", clientAccessible = true)
    public static void main (String[] args)
    {
        // entry point of the program - print out welcome message
        log.info("Application has started - printing out welcome message");

        System.out.println("Welcome to my CS 474 - Homework 2 submission");
        System.out.println("Where I implement the Facade design pattern and");
        System.out.println("provide 3 implementations with");
        System.out.println("Annotations and Annotation Processors to confirm");
        System.out.println("their design.\n");

        // infinite loop - asking the user for input until they decide to quit
        while (true)
        {
            log.info("Beginning to ask the user for input...");
            System.out.println("Which implementation would you like to test?\n");
            System.out.println("1. Coordinate Facade\n2. Shape Facade\n3. Media Facade\n0. Quit\n\nChoice: ");

            Scanner scanner = new Scanner(System.in);

            int userInput = scanner.nextInt();

            // handle the user's choices

            // coordinate facade
            if (userInput == 1)
            {
                log.info("User has chosen to see the Coordinate Facade");
                new CoordinateFacade();
            }
            // shape facade
            else if (userInput == 2)
            {
                log.info("User has chosen to see the Shape Facade");
                new ShapeFacade();
            }
            // media facade
            else if (userInput == 3)
            {
                log.info("User has chosen to see the Media Facade");
                MediaFacade converter = new MediaFacade();
                File mp4Video = converter.convertVideo("youtube.ogg", "mp4");
            }
            // quit
            else if (userInput == 0)
            {
                log.info("User has chosen to exit...");
                System.out.println("\nThank you for using the application! Exiting...");
                return;
            }
            // invalid input
            else
            {
                log.warning("INCORRECT USER INPUT");
                System.out.println("\nInvalid input - please try again.");
            }
        }
    }
}
