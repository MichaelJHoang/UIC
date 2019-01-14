/*
 * 
 * Author: Jon-Michael Hoang
 * Date Created: 1/11/2019
 * Program: [ GIVE ME A NAME ]
 * Desc: file parser class to parse a given file and to then return a library of it
 *       planning on turning this into a singleton class
 *       sidenote: have exceptions???
 * 
 */

import java.util.*;
import java.io.*;

public class fileParser
{ 
    // the file
    private File file;
    
    // constructor for fileParser
    public fileParser (String filename)
    {
        file = new File(filename);
    }
    
    // 
    public library parse ()
    {
        return new library();
    }
    
}
    