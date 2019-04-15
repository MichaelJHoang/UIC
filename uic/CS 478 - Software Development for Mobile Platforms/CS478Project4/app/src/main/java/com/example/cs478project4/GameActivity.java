package com.example.cs478project4;

import android.os.Bundle;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.AdapterView;
import android.widget.GridView;
import android.widget.Toast;

public class GameActivity extends AppCompatActivity
{
    GridView gridView;

    // instantiate the holes and their images
    int holeImages [] = new int [100];

    // handler to handle threads/runnables
    private Handler mainHandler = new Handler();

    @Override
    public void onCreate (Bundle saved)
    {
        // initialize the game
        GopherHunter.getGameInstance();

        // and the hole images itself
        for (int x = 0; x < 100; x++)
        {
            holeImages[x] = R.drawable.dirt_hole;
        }

        // basic required stuff
        super.onCreate(saved);
        setContentView(R.layout.activity_game);

        // grid view since we're dealing with a 10x10 grid
        gridView = (GridView) findViewById(R.id.game_gridView);

        // custom adapter sauce
        CustomAdapter adapter = new CustomAdapter (GameActivity.this, holeImages);

        gridView.setAdapter(adapter);

        // set onclick listeners to determine players' guess' outcomes
        gridView.setOnItemClickListener(new AdapterView.OnItemClickListener()
        {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id)
            {
                // gopher has been found
                if (GopherHunter.determine(position) == 1)
                {
                    Toast.makeText(GameActivity.this, "Success - the gopher has been found!", Toast.LENGTH_SHORT).show();
                    finish();
                }
                // near miss
                else if (GopherHunter.determine(position) == 2)
                {
                    Toast.makeText(GameActivity.this, "Near Miss...you can sense it...", Toast.LENGTH_LONG).show();
                    GopherHunter.board[position] = -1;
                }
                // close guess
                else if (GopherHunter.determine(position) == 3)
                {
                    Toast.makeText(GameActivity.this, "Close guess...you can smell it...", Toast.LENGTH_LONG).show();
                    GopherHunter.board[position] = -1;
                }
                // disaster
                else if (GopherHunter.determine(position) == -1)
                {
                    Toast.makeText(GameActivity.this, "DISASTER - HOLE ALREADY CHOSEN", Toast.LENGTH_LONG).show();
                    GopherHunter.board[position] = -1;
                }
                // complete miss
                else if (GopherHunter.determine(position) == 0)
                {
                    Toast.makeText(GameActivity.this, "Complete miss...you have no idea where it is.", Toast.LENGTH_LONG).show();
                    GopherHunter.board[position] = -1;
                }
            }
        });
    }


    /*
     *
     * Thread stuff generally begins here
     *
     */

    public void startThread (View view)
    {
        CustomThread runnable = new CustomThread();

        new Thread(runnable).start();
    }

    public void stopThread (View view)
    {

    }

    public void startAsyncTask (View v)
    {

    }

    class CustomThread implements Runnable
    {
        int seconds;
        String threadName;

        @Override
        public void run ()
        {
            mainHandler.post(new Runnable()
            {
                @Override
                public void run() {

                }
            });
        }

    }
}
