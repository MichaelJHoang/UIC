import java.io.*;
import java.util.*;

public class Game
{
    private String name;
    private ArrayList<Place> placeList = new ArrayList<Place>();
    
    // name the game
    public Game (String name)
    {
        this.name = name;
    }
    
    // allows places to be added into the arraylist placeList
    protected void addPlace (Place place)
    {
        placeList.add(place);
    }
    
    // function that allows the player to interact with the game.
    // loops infinitely until player reaches an exit or exits the game. 
    protected void play ()
    {
        // allow for user input
        Scanner scan = new Scanner (System.in);
        
        String userInput = "";
        
        /*
            // below this comment is the hardcode for the six dungeons map - including everything such as the descriptions, rooms,
            // directions, locked doors, etc.
            // ID numbers for new directions are arbitrary whereas Place IDs are specified s.t. n-1 = actual place
            placeList.add (new Place (1, "Entrance Hall", "You are standing in the entrance hall of the great six-room dungeon\n"
                                                         +"There are doors to the east and north, and a stairway leading down\n"
                                                         +"The main exit ( from the game ) is to the west"));
            placeList.add (new Place (2, "Pool of Enchantment", "You are in a round room with a clear enchanting pool of water.\n"
                                                               +"There are doors to the north and west\n"
                                                               +"There is a slide leading downwards to the floor below"));
            placeList.add (new Place (3, "Treasure Storeroom", "You have found a storeroom full of gold, jewels, and treasure!\n"
                                                              +"There are doors to the north and south"));
            placeList.add (new Place (4, "Ogre's Lair", "You have entered the Ogre's Lair! Better leave before he wakes up . . .\n"
                                                       +"There are doors to the south and the east"));
            placeList.add (new Place (5, "Potions Storeroom", "This room has shelves full of bottles and jars\n"
                                                             +"Some labels read \"Powdered bat's wings\" and \"Toad eyes\".\n"
                                                             +"There is a door to the east, and a stairway leading up."));
            placeList.add (new Place (6, "Potions Lab", "There is a cauldron of thick green goop here,\n"
                                                       +"bubbling slowly over a cool blue flame.\n"
                                                       +"Doors lead to the west and east."));
            placeList.add (new Place (0, "Exit", "This is the exit to the dungeon")); // exit ID = 0 and not 1
            
            // Entrance Hall
            placeList.get(0).addDirection (new Direction (11, placeList.get(3), placeList.get(3), "N"));
            placeList.get(0).addDirection (new Direction (12, placeList.get(1), placeList.get(1), "E"));
            placeList.get(0).addDirection (new Direction (13, placeList.get(4), placeList.get(4), "D"));
            placeList.get(0).addDirection (new Direction (14, placeList.get(0), placeList.get(6), "W"));
            
            
            // Pool of Enchantment
            placeList.get(1).addDirection (new Direction (21, placeList.get(2), placeList.get(2), "N"));
            placeList.get(1).lockDirection(0); // lock pool -> treasure room
            placeList.get(1).addDirection (new Direction (22, placeList.get(1), placeList.get(5), "D"));
            placeList.get(1).addDirection (new Direction (23, placeList.get(0), placeList.get(0), "W"));
            
            // Treasure Storeroom
            placeList.get(2).addDirection (new Direction (31, placeList.get(2), placeList.get(3), "N"));
            placeList.get(2).addDirection (new Direction (32, placeList.get(1), placeList.get(1), "S"));
            placeList.get(2).addDirection (new Direction (33, placeList.get(3), placeList.get(2), "x"));
            
            // Ogre's Lair
            placeList.get(3).addDirection (new Direction (41, placeList.get(2), placeList.get(3), "x"));
            placeList.get(3).addDirection (new Direction (42, placeList.get(3), placeList.get(2), "E"));
            placeList.get(3).addDirection (new Direction (43, placeList.get(0), placeList.get(0), "S"));
            
            // Potions Storeroom
            placeList.get(4).addDirection (new Direction (51, placeList.get(0), placeList.get(0), "U"));
            placeList.get(4).addDirection (new Direction (52, placeList.get(5), placeList.get(5), "E"));
            placeList.get(4).lockDirection(1); // lock potion storeroom -> lab
            
            // Potions Lab
            placeList.get(5).addDirection (new Direction (61, placeList.get(1), placeList.get(5), "x"));
            placeList.get(5).addDirection (new Direction (62, placeList.get(4), placeList.get(4), "W"));
            placeList.get(5).addDirection (new Direction (63, placeList.get(5), placeList.get(6), "E"));
            placeList.get(5).lockDirection(2); // lock potion lab -> exit
            */
           
        // initialize the player's location
        Place playerLocation = placeList.get(0);
       
        // loop the game forever until parameters no longer match
        while (!userInput.equalsIgnoreCase("quit") && !userInput.equalsIgnoreCase ("exit") && playerLocation.getID() != 0)
        {
            System.out.print ("You are playing the game, please enter a command -> ");
            userInput = scan.nextLine (); // get user input
            
            // provided that the player wants to examine where they are, print the information related to it
            if (userInput.equalsIgnoreCase("look") || userInput.equalsIgnoreCase("debug") || userInput.equalsIgnoreCase("display"))
            {
                System.out.println ("\n***************************************************");
                System.out.println ("You are currently located in: " + playerLocation.getName() + "\n");
                System.out.println (playerLocation.getDesc());
                System.out.println ("***************************************************\n");
            }
            
            // changes the player's location IFF followDirection is true
            playerLocation = playerLocation.followDirection(userInput);
            
        }
        
        // exit messages based on how the player finishes the game
        if (playerLocation.getID() == 0)
        {
            System.out.println ("\n--------------------------------------------------");
            System.out.println ("You have successfully exited the dungeon.");
            System.out.println ("--------------------------------------------------\n");
        }
        else
        {
            System.out.println ("\n--------------------------------------------------");
            System.out.println ("You have successfully exited the game.");
            System.out.println ("--------------------------------------------------\n");
        }
    }
}