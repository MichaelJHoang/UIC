package com.example.cs478project3a1;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.PackageManager;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

public class MainActivity extends Activity
{
    // define the permission that the application uses
    private static final String permission = "edu.uic.cs478.s19.kaboom";

    // test string to help me figure out things
    private static final String toastString = "edu.uic.cs478.s19.kaboom";

    private static final String filterString = "com.example.cs478project3";

    // button that takes in user's input to go to the second application
    private Button firstButton;

    // broadcast receiver to allow broadcasts to be sent and received from A2/A3
    private BroadcastReceiver receiver = new MyReceiver();

    // filter to only allow the permission defined above
    private IntentFilter filter = new IntentFilter(filterString);

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        // required things
        super.onCreate(savedInstanceState);

        // set content view
        setContentView(R.layout.activity_main);

        // initialize the button
        firstButton = (Button) findViewById(R.id.firstButton);

        // create a click listener for the button
        firstButton.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                // when user clicks, runs this programmer defined function
                checkPermissionAndBroadcast();
            }
        });
    }

    @Override
    protected void onResume()
    {
        super.onResume();

        // assign filter to only allow the programmer-defined permission
        filter = new IntentFilter(filterString);
        filter.setPriority(10);

        // assign the receiver my own receiver which allows for debugging purposes
        receiver = new MyReceiver();

        // register the receiver
        registerReceiver(receiver, filter);
    }

    // programmer defined function that checks if the permission has been granted to allow the user
    // to go to the second application. If not, request it.
    private void checkPermissionAndBroadcast()
    {
        if (ContextCompat.checkSelfPermission(this, permission)
                == PackageManager.PERMISSION_GRANTED)
        {
            // create the intent
            Intent intent = new Intent(Intent.ACTION_MAIN);
            // set the components for the intent and aim it directly at application 2's first activity
            intent.setComponent(new ComponentName("com.example.cs478project3a2", "com.example.cs478project3a2.MainActivity"));
            // send broadcast
            sendOrderedBroadcast(intent, permission);
            // start
            startActivity(intent);
        }
        else
        {
            // reguest permission
            ActivityCompat.requestPermissions(this, new String[]{permission}, 0);
        }
    }

    // callback function that takes the users' response to the permission request
    public void onRequestPermissionsResult(int code, String[] permissions, int[] results)
    {
        // check to see if they've actually responded
        if (results.length > 0)
        {
            // if the user agrees, then immediately go to the second application
            if (results[0] == PackageManager.PERMISSION_GRANTED)
            {
                // create the intent
                Intent intent = new Intent(Intent.ACTION_MAIN);
                // set the components for the intent and aim it directly at application 2's first activity
                intent.setComponent(new ComponentName("com.example.cs478project3a2", "com.example.cs478project3a2.MainActivity"));
                // send broadcast
                sendOrderedBroadcast(intent, permission);
                // start
                startActivity(intent);
            }
            else
            {
                // the user has denied giving permission - display a toast saying that access to A2 from A1 is not granted
                Toast.makeText(this, "Permission Denied in A1 - Access to A2 from A1 therefore not granted.", Toast.LENGTH_LONG).show();
            }
        }
    }

    @Override
    protected void onPause()
    {
        super.onPause();
        unregisterReceiver(receiver);
    }
}
