package com.example.cs478project4;

import android.widget.Toast;

import java.util.Random;

// skeleton for the gopher hunter game - all it is is that it's a class with a 10x10 matrix that
// follows the single
public class GopherHunter
{
    /*
     *  here,
     *
     *  the variables are STATIC to keep only one instance at all times
     *
     *  VOLATILE to make sure that when threads interact with these things, they are reflected
     *  on other threads
     */


    // "10x10" board that represents the gopher game board
    // it's public so that I don't have to do unnecessary and redundant
    // setters and getters
    public volatile static int[] board = new int[100];

    // static instance - only one instance can exist
    private volatile static GopherHunter GH = null;

    // random number generator to generate random positions in which the gopher is
    private volatile static Random rand = new Random();

    // maintain the current random number (current location of the gopher)
    private volatile static int currentLocation;

    // private constructor to prevent making calls to multiple instances
    // of the gopher hunter game
    private GopherHunter ()
    {
        // sync block to prevent multiple threads to run this
        synchronized (GopherHunter.class)
        {
            // initialize the board to all 0s
            for (int x = 0; x < 100; x++)
            {
                board[x] = 0;
            }
        }

        // after initializing the board to all 0s, choose one random spot in the 10x10 matrix
        // to be one (1) - which marks the location of the gopher
        currentLocation = rand.nextInt(100);

        board[currentLocation]= 1;


    }

    public static GopherHunter getGameInstance()
    {
        if (GH == null)
        {
            // to make the thread safe by blocking multiple threads running this
            synchronized (GopherHunter.class)
            {
                // check again because multiple threads can reach
                // the above step
                if (GH == null)
                    GH = new GopherHunter();
            }
        }
        return GH;
    }

    public static void resetGame()
    {
        // sync block to prevent multiple threads to run this
        synchronized (GopherHunter.class)
        {
            // initialize the board to all 0s
            for (int x = 0; x < 100; x++)
            {
                board[x] = 0;
            }
        }

        // after initializing the board to all 0s, choose one random spot in the 10x10 matrix
        // to be one (1) - which marks the location of the gopher
        currentLocation = rand.nextInt(100);

        board[currentLocation]= 1;
    }

    // debugging function to test functionality
    public static int getLocation()
    {
        return currentLocation;
    }

    // function that takes in a user click position and determines whether or not they're
    // at or near the gopher
    public static int determine(int position)
    {
        // gopher found
        if (position == currentLocation)
            return 1;
        // close guess
        else if (position == (currentLocation - 20) ||
                position == (currentLocation + 20) ||
                position == (currentLocation - 2) ||
                position == (currentLocation + 2) ||
                position == (currentLocation - 21) ||
                position == (currentLocation - 19) ||
                position == (currentLocation + 19) ||
                position == (currentLocation + 21))
        {
            return 3;
        }
        // near miss
        // check all eight directions
        else if (position == (currentLocation - 10) ||
                position == (currentLocation + 10) ||
                position == (currentLocation - 1) ||
                position == (currentLocation + 1) ||
                position == (currentLocation - 11) ||
                position == (currentLocation - 9) ||
                position == (currentLocation + 9) ||
                position == (currentLocation + 11))
        {
            return 2;
        }
        // disaster
        else if (board[position] == -1)
        {
            return -1;
        }

        // complete miss
        return 0;
    }
}
