/*
 * AddressInputActivity.java
 *
 * Author: Jon-Michael Hoang
 * CS 478 - Project 1: Map Application
 * Professor: Ugo Buy
 * Date: 2/11/2019
 *
 * NOTE: Hitting the "back" button will not allow RESULT to be sent.
 *       Hit the "return" or "done" key on your soft keyboard to allow RESULT to be sent.
 */

package com.example.cs478project1;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.inputmethod.EditorInfo;
import android.view.inputmethod.InputMethodManager;
import android.widget.EditText;
import android.widget.TextView;

public class AddressInputActivity extends AppCompatActivity
{
    private final String tag = "AddressInputActivity.java"; // tag used to identify the activity
    String userInput = null;    // user input

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        // Required call through to Activity.onCreate()
        // Restore any saved instance state
        super.onCreate(savedInstanceState);

        // set the content view
        setContentView(R.layout.activity_address_input);

        // initializing the ui element
        final EditText addrText = (EditText) findViewById(R.id.addressText);

        // assign the element to a listener for userInput
        addrText.setOnEditorActionListener(new TextView.OnEditorActionListener()
        {
            @Override
            public boolean onEditorAction(TextView v, int actionId, KeyEvent event)
            {
                // flag to check whether or not there's input
                boolean handled = false;

                // checks if the user hits the "done or return" key within the soft keyboard
                if (actionId == EditorInfo.IME_ACTION_DONE)
                {
                    // converts the user's input in the editor to a string
                    userInput = v.getText().toString();

                    // when the user hit's "done" on the soft-keyboard, the keyboard will drop down and hide
                    InputMethodManager inputManager = (InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE);
                    inputManager.hideSoftInputFromWindow(getCurrentFocus().getWindowToken(), InputMethodManager.HIDE_NOT_ALWAYS);

                    // handles whether or not there was any actual user input
                    if (userInput != null && !userInput.trim().isEmpty())
                        handled = true;
                    else
                        handled = false;

                    // create a new intent to go back to the first activity
                    Intent intent = new Intent();

                    // put the userInput into an extra with the key
                    intent.putExtra("userAddressInput", userInput);

                    // return the result based on whether or not there was any user input
                    if (handled)
                        setResult(Activity.RESULT_OK, intent);
                    else
                        setResult(Activity.RESULT_CANCELED, intent);

                    // logcat log to tell notifying that the user is done
                    Log.i(tag, "User has pretty much finished the input and is now returning to the main activity");

                    // finish the activity and return to the main activity
                    finish();
                }

                return handled;
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
