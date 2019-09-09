import java.io.*;
import java.util.*;

public class Direction
{
    private int ID;
    private Place from;
    private Place to;
    private String dir;
    private boolean lock = false;
        
    public Direction (int ID, Place from, Place to, String dir)
    {
        this.ID = ID;
        this.from = from;
        this.to = to;
        this.dir = dir;
    }
    
    // split directions into elements of the array and runs matching
    // algorithm to see if there exists a valid direction
    protected boolean match (String s)
    {
        String [] directions = dir.split("\\s+");
        
        
        for (int x = 0; x < directions.length; x++)
            if (s.equalsIgnoreCase(directions[x]))
                return true;
        
       /*
        for (Object x : directions)
            if (x.equalsIgnoreCase(s))
                return true;
        */
        return false;
    }
    
    protected void lock ()
    {
        lock = true;
    }
    
    protected void unlock ()
    {
        lock = false;
    }
    
    protected boolean isLocked ()
    {
        return lock;
    }
    
    protected Place follow ()
    {
        return (to != null && !lock) ? to : from;
    }
    
    protected void print ()
    {
        System.out.println ("Direction " + dir + "\nTo: " + to.getName() + "\nFrom: " + from.getName() + "Lock status: " + lock);
    }
    
    // returns a previous location
    protected Place getFrom ()
    {
        return from;
    }
    
    // returns a location that is probably next accessible
    protected Place getTo ()
    {
        return to;
    }
    
}
