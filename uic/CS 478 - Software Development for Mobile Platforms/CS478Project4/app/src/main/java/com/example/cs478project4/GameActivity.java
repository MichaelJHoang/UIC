package com.example.cs478project4;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.AdapterView;
import android.widget.GridView;
import android.widget.Switch;
import android.widget.Toast;
import android.widget.ToggleButton;

import java.util.Random;

public class GameActivity extends AppCompatActivity
{
    GridView gridView;

    // instantiate the holes and their images
    int holeImages [] = new int [100];

    // variable to handle the mode type
    private String mode;

    // values used by handlers
    public static final int HANDLER_PRERESULT = 0, HANDLER_PROCESSING = 1, HANDLER_RESULT_DONE = 3;



    // handler to handle threads/runnables
    private Handler handler = new Handler()
    {
        public void handleMessage (Message msg)
        {
            int what = msg.what;

            switch (what)
            {
                case HANDLER_PRERESULT:
                    break;
                case HANDLER_PROCESSING:
                    break;
                case HANDLER_RESULT_DONE:
                    break;
                default:
                    break;
            }
        }
    };

    @Override
    public void onCreate (Bundle saved)
    {
        // initialize the game
        GopherHunter.getGameInstance();
        GopherHunter.resetGame();

        // get the string that was stored in the intent into the variable
        mode = getIntent().getExtras().getString("playMode");

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

    class CustomRunnable implements Runnable
    {
        int seconds;
        String threadName;

        @Override
        public void run ()
        {
            handler.post(new Runnable()
            {
                @Override
                public void run()
                {
                    // get a message instance with target set to UI thread's message queue
                    Message msg = handler.obtainMessage(GameActivity.HANDLER_PRERESULT);
                    handler.sendMessage(msg);

                    try
                    {
                        Thread.sleep(1000);
                    }
                    catch (Exception e)
                    {
                        e.printStackTrace();
                    }

                    // and again...
                    msg = handler.obtainMessage(GameActivity.HANDLER_PROCESSING);
                    handler.sendMessage(msg);

                    try
                    {
                        Thread.sleep(1000);
                    }
                    catch (Exception e)
                    {
                        e.printStackTrace();
                    }

                    /*
                     *
                     *
                     *
                     * the work is done here
                     *
                     *
                     *
                     */

                    Random rand = new Random();
                    int decision = rand.nextInt();

                    // gopher has been found
                    if (GopherHunter.determine(decision) == 1)
                    {
                        Toast.makeText(GameActivity.this, "Success - the gopher has been found!", Toast.LENGTH_SHORT).show();
                        finish();
                    }
                    // near miss
                    else if (GopherHunter.determine(decision) == 2)
                    {
                        Toast.makeText(GameActivity.this, "Near Miss...you can sense it...", Toast.LENGTH_LONG).show();
                        GopherHunter.board[decision] = -1;
                    }
                    // close guess
                    else if (GopherHunter.determine(decision) == 3)
                    {
                        Toast.makeText(GameActivity.this, "Close guess...you can smell it...", Toast.LENGTH_LONG).show();
                        GopherHunter.board[decision] = -1;
                    }
                    // disaster
                    else if (GopherHunter.determine(decision) == -1)
                    {
                        Toast.makeText(GameActivity.this, "DISASTER - HOLE ALREADY CHOSEN", Toast.LENGTH_LONG).show();
                        GopherHunter.board[decision] = -1;
                    }
                    // complete miss
                    else if (GopherHunter.determine(decision) == 0)
                    {
                        Toast.makeText(GameActivity.this, "Complete miss...you have no idea where it is.", Toast.LENGTH_LONG).show();
                        GopherHunter.board[decision] = -1;
                    }

                    // and one last time
                    msg = handler.obtainMessage(GameActivity.HANDLER_RESULT_DONE);
                    handler.sendMessage(msg);
                }
            });
        }

    }
}
