import java.io.*;
import java.util.*;

public class Place
{
    private int ID;
    private String name;
    private String desc;
    
    private ArrayList<Direction> directionList = new ArrayList<Direction>();
    
    public Place (int ID, String name, String desc)
    {
        this.ID = ID;
        this.name = name;
        this.desc = desc;
    }
    
    protected String getName ()
    {
        return name;
    }
    
    protected String getDesc ()
    {
        return desc;
    }
    
    protected int getID ()
    {
        return ID;
    }
    
    protected void addDirection (Direction dir)
    {
        directionList.add(dir);
    }
    
    protected void lockDirection (int element)
    {
        directionList.get(element).lock();
    }
    
    // iterates through the directionList to see if there are any valid directions
    // returns where the iterator points and if nothing good is pointed, return this
    protected Place followDirection (String input)
    {
        Iterator <Direction> iter = directionList.iterator();
        //ListIterator <Direction> litr = null;
        
        while (iter.hasNext())
        {
            Direction directionList = iter.next();
            if (directionList.match(input) && !directionList.isLocked())
                return directionList.getTo();
            // this message gets thrown out when there is something locked nearby and when the player is
            // trying to access a locked direction
            else if (directionList.isLocked())
            {
                System.out.println ("\n--------------------------------------------------");
                System.out.println ("Something appears to be locked around here.");
                System.out.println ("--------------------------------------------------\n");  
            }
        }
        
        return this;
    }
    
    protected void print ()
    {
        System.out.println ("Place name: " + name + "\nDesc: " + desc);
    }
}