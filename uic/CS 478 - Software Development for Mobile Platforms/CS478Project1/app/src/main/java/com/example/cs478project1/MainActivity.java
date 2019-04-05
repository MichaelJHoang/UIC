/*
 * MainActivity.java
 *
 * Author: Jon-Michael Hoang
 * CS 478 - Project 1: Map Application
 * Professor: Ugo Buy
 * Date: 2/11/2019
 *
 */


package com.example.cs478project1;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity
{
    private final String tag = "MainActivity.java"; // default tag for the activity
    final int requestCode = 1;  // request code used to call the second activity
    String userInput = null;    // container for the user input
    boolean RESULT = false;    // container for the RESULT - set to false by default

    // receive any result from the second activity
    @Override
    protected void onActivityResult (int requestCode, int resultCode, Intent data)
    {
        // check the requestCode that was sent back from the second activity
        if (requestCode == 1)
        {
            // extract data provided OK
            if (resultCode == Activity.RESULT_OK)
            {
                RESULT = true;
                userInput =  data.getStringExtra("userAddressInput");   // extract data
            }
            // do nothing if cancelled
            else if (resultCode == Activity.RESULT_CANCELED)
            {
                RESULT = false;
                userInput = null;
            }
        }

        // logcat log to show what result was returned and whether or not it was OK or CANCELED
        Log.i(tag, "onActivityResult activated - the result is: " + resultCode);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        // Required call through to Activity.onCreate()
        // Restore any saved instance state
        super.onCreate(savedInstanceState);

        // set the content view
        setContentView(R.layout.activity_main);

        // initialize the ui elements
        final Button addressButton = (Button)findViewById(R.id.addressButton);
        final Button mapButton = (Button)findViewById(R.id.mapButton);

        // when the addressButton is clicked, start the second activity which allows
        // the user to enter in an address
        addressButton.setOnClickListener(new View.OnClickListener()
        {
            // called when user clicks it
            @Override
            public void onClick(View v)
            {
                try
                {
                    // create a new intent to allow to go to the second activity
                    Intent intent = new Intent(MainActivity.this, AddressInputActivity.class);

                    // start the second intent
                    startActivityForResult(intent, requestCode);

                    // log into the logcat that the thing is about start
                    Log.i(tag, "The second activity is about to start");
                }
                catch (Exception e)
                {
                    // log exception message into the logcat
                    Log.e(tag, e.toString());
                }
            }
        });

        // assign a listener to mapButton
        mapButton.setOnClickListener(new View.OnClickListener()
        {
            // call the map when the user clicks it
            @Override
            public void onClick(View v)
            {
                if (RESULT == true)
                {
                    try
                    {
                        // process the text for network transmission and
                        // encode the userInput with uri encode
                        userInput = Uri.encode(userInput);

                        // create an intent for starting the google maps app
                        Intent geoIntent = new Intent (Intent.ACTION_VIEW, Uri.parse("geo:0,0?q=" + userInput));

                        // use the internet to start
                        startActivity(geoIntent);

                        Log.i(tag, "Initializing the maps activity");
                    }
                    catch (Exception e)
                    {
                        // log the exception message into the logcat
                        Log.e(tag, e.toString());
                    }
                }
                else if (RESULT == false)
                {
                    // notify the user with a toast telling them that they previously did not input anything within the second activity
                    Toast.makeText(MainActivity.this, "Failed to enter location - please try again.", Toast.LENGTH_LONG).show();
                }
            }
        });
    }

    @Override
    protected void onStart()
    {
        super.onStart();
        Log.i(tag, "The MainActivity is about to start");
    }

    @Override
    protected void onRestart()
    {
        super.onRestart();
        Log.i(tag, "The MainActivity is about to restart");
    }

    @Override
    protected void onResume()
    {
        super.onResume();
        Log.i(tag, "This activity has taken focus again and will be resumed");
    }

    @Override
    protected void onPause()
    {
        super.onPause();
        Log.i(tag, "Another activity has taken focus and this one will be put on pause");
    }

    @Override
    protected void onStop()
    {
        super.onStop();
        Log.i(tag, "The activity is no longer visible and will be stopped");
    }

    @Override
    protected void onDestroy()
    {
        super.onDestroy();
        Log.i(tag, "The activity is about to be destroyed.");
    }
}
