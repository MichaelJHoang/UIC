/*

    Author: Jon-Michael Hoang | jhoang6
    CS 474: Homework 1
    October 1st, 2019

 */

// import libraries
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import com.typesafe.config.Config;
import com.typesafe.config.ConfigFactory;

import java.io.*;
import java.net.*;
import java.util.logging.*;
import java.util.*;

import static java.lang.System.*;

public class main_driver
{
    myLogger MYLOGGER = new myLogger();
    static LogManager logManager = LogManager.getLogManager();
    static Logger log = logManager.getLogger(Logger.GLOBAL_LOGGER_NAME);

    // function to handle the output stream of the requests
    public static queryResultContainer getOutputStream (HttpURLConnection connection, byte[] databytes)
    {
        log.log(Level.INFO, "getOutputStream() is now handling a request");
        // container for result
        JsonObject jsonObject = new JsonObject();
        JsonParser jsonParser = new JsonParser();

        // start streaming and parsing some data using json
        try (DataOutputStream outputStream = new DataOutputStream(connection.getOutputStream()))
        {
            outputStream.write(databytes);
            outputStream.flush();
            outputStream.close();

            JsonElement root = jsonParser.parse(new InputStreamReader(connection.getInputStream()));
            jsonObject = root.getAsJsonObject();
        }
        catch (Exception e)
        {
            e.printStackTrace();
            log.log(Level.SEVERE, "cannot receive the response");
        }

        // return the query container to be added into the list
        log.log(Level.FINE, "queryResultContainer made");
        return new queryResultContainer(jsonObject);
    }


    public static void main(String[] args) throws IOException
    {
        //Config conf = ConfigFactory.parseResources("resource.conf");

        log.log(Level.INFO, "Program is starting...");
        // initialize basic variables for I/O
        inputScan intScanner = inputScan.getInstance();
        inputScan stringScanner = inputScan.getInstance();
        int userInput;
        String usernameInput = null;
        String repoInput = null;

        // create this object to allow saved inputs
        CareTaker careTaker = new CareTaker();

        // create a container that holds all the queries for the program
        ArrayList<queryResultContainer> queryList = new ArrayList<>();

        // initialize connection variables to be able to make requests
        URL url = null;
        HttpURLConnection connection = null;

        // basically loops infinitely until the user decides to quit
        log.log(Level.INFO, "Now about to run while loop that prompts for user inputs, etc.");
        while (true)
        {
            // welcome message + selection prompt
            System.out.println ("\nWelcome to Jon-Michael Hoang's miniGQL application:" +
                                "\n 1. Pull the author's github information." +
                                "\n 2. Search for a specific username's repo" +
                                (queryList.size() > 0 ? "\n 3. Show all previous repositories accessed" : "") +
                                (usernameInput != null && repoInput != null ? "\n 4. Save previous input" : "") +
                                (careTaker.get(0) != null ? "\n 5. Run from saved inputs" : "") +
                                "\n 0. Quit");

            // record the user's input
            System.out.print("userInput: ");
            userInput = intScanner.nextInt();
            System.out.println("");

            // try-catch block to set up the connection to make a  request github and graphql
            // needs to do this every time there's a request
            try
            {
                log.log(Level.INFO, "Attempting to connect...");
                url = new URL("https://api.github.com/graphql");
                connection = (HttpURLConnection) url.openConnection();

                connection.setRequestProperty("Authorization", "Bearer 2afd2aa2b7f677b408c2d0e249c3ba1aba532898");
                connection.setRequestProperty("Accept", "application/json");
                connection.setRequestMethod("POST");
                connection.setDoOutput(true);
                log.log(Level.FINE, "connection established");
            }
            catch (Exception e)
            {
                e.printStackTrace();
                log.log(Level.SEVERE, "cannot connect - no internet or bad fields");
            }

            // handle user input
            if (userInput == 1)
            {
                log.log(Level.INFO, "handling choice 1...");

                // default query
                String input =  "{ repository(owner: " + (usernameInput = "MichaelJHoang") + ", name: " + (repoInput = "UIC") + ") { id name collaborators(first: 100, affiliation: ALL) { edges { permission node { id login name } } } object(expression: master) {... on Commit { history { totalCount } } } } }";

                // the user's input query gets injected into here
                String gqlReq = new String("{\"query\":\"" + input + "\"}");

                // extracted the response in terms of bytes
                byte[] databytes = gqlReq.getBytes("UTF-8");

                // make a call to the function, in which the function returns a query container
                queryList.add(getOutputStream(connection, databytes));

                // check if the list is not empty and if not, what the following line does is that everytime
                // a new query container is made, it is added to the tail. Therefore, all appropriate queries
                // that are printed are at the end of the list
                log.log(Level.INFO, "printing query...");
                if (queryList != null || queryList.size() != 0)
                    queryList.get(queryList.size() - 1).printQuery();
            }
            else if (userInput == 2)
            {
                log.log(Level.INFO, "handling choice 2...");

                // prompt the user to enter in a username and a repository that said username has
                System.out.print("Enter the username: ");
                stringScanner = inputScan.getInstance();
                usernameInput = stringScanner.nextLine();

                System.out.print("Enter the repository name: ");
                repoInput = stringScanner.nextLine();

                connection.setDoOutput(true);

                // inject into the input string
                String input =  "{ repository(owner: " + usernameInput + ", name: " + repoInput + ") { id name collaborators(first: 100, affiliation: ALL) { edges { permission node { id login name } } } object(expression: master) {... on Commit { history { totalCount } } } } }";

                // inject the input into the query encapsulator
                String gqlReq = new String("{\"query\":\"" + input + "\"}");

                // get the response in terms of bytes
                byte[] databytes = gqlReq.getBytes("UTF-8");

                // make a call to the function, in which the function returns a query container
                queryList.add(getOutputStream(connection, databytes));

                // check if the list is not empty and if not, what the following line does is that everytime
                // a new query container is made, it is added to the tail. Therefore, all appropriate queries
                // that are printed are at the end of the list
                log.log(Level.INFO, "printing query...");
                if (queryList != null || queryList.size() != 0)
                    queryList.get(queryList.size() - 1).printQuery();
            }
            else if (userInput == 3 && queryList.size() > 0)
            {
                log.log(Level.INFO, "handling choice 3...");

                for (int x = 0; x < queryList.size(); x++)
                {
                    System.out.println("\nRepository name: " + queryList.get(x).getRepoName() + "\nRepository ID: "
                                     + queryList.get(x).getRepoId() + "\n");
                }

            }
            else if (userInput == 4 && usernameInput != null && repoInput != null)
            {
                log.log(Level.INFO, "handling choice 4...");
                log.log(Level.INFO, "saving input...");

                // saves the user's previous inputs into the memento
                System.out.println("\nSaving...\n");
                careTaker.add((new savedInput(usernameInput, repoInput)).saveInputToMemento());
                System.out.println("Saved.\n");
            }
            else if (userInput == 5 && careTaker.get(0) != null )
            {
                log.log(Level.INFO, "handling choice 5...");
                log.log(Level.INFO, "pulling info from the caretaker...");

                // provided that the memento is filled, prints out all the saves
                System.out.println("Username Input : Repository Input");
                System.out.println("----------------------------------------------------------------------------------");
                for (int x = 0; x < careTaker.mementoSize(); x++)
                {
                    System.out.println(x + ". " + careTaker.get(x).getState().usernameInput + " : " + careTaker.get(x).getState().repoInput);
                }

                System.out.print("\nWhich save would you like to run: ");
                userInput = intScanner.nextInt();

                if (userInput >= 0 && userInput <= careTaker.mementoSize())
                {
                    usernameInput = careTaker.get(userInput).getState().usernameInput;
                    repoInput = careTaker.get(userInput).getState().repoInput;

                    String input =  "{ repository(owner: " + usernameInput + ", name: " + repoInput + ") { id name collaborators(first: 100, affiliation: ALL) { edges { permission node { id login name } } } object(expression: master) {... on Commit { history { totalCount } } } } }";

                    String gqlReq = new String("{\"query\":\"" + input + "\"}");

                    byte[] databytes = gqlReq.getBytes("UTF-8");

                    getOutputStream(connection, databytes).printQuery();

                    System.out.println("\n\n***** SAVED QUERY NOT SAVED INTO LIST AS IT WAS ALREADY SAVED *****\n");
                }
                else
                {
                    // invalid input
                    log.log(Level.WARNING, "invalid input");
                    System.out.println ("\nInvalid input.");
                }
            }
            else if (userInput == 0)
            {
                // exit
                log.log(Level.FINEST, "exiting successfully");
                System.out.println("Thank you for using my application. Exiting...");
                exit(0);
            }
            else
            {
                log.log(Level.WARNING, "invalid input");
                System.out.println("Invalid input - please try again");
            }
        }
    }
}