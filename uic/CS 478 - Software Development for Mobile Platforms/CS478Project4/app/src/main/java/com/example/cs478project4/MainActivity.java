package com.example.cs478project4;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity
{
    // instantiate the manual and automatic start buttons
    private Button manualStart;
    private Button automaticStart;

    private static final boolean AUTOMODE = false;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        // basic required stuff
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // initialize the buttons to their respective XML/id counterparts
        manualStart = (Button) findViewById(R.id.startManualModeButton);
        automaticStart = (Button) findViewById(R.id.startAutoModeButton);

        // when the user clicks the manual button...
        manualStart.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                Intent intent = new Intent(MainActivity.this, GameActivity.class);

                // tell the user through the toast the selection they've made
                Toast.makeText(MainActivity.this, "Start mode: [ Player vs. Computer ]", Toast.LENGTH_LONG).show();

                startActivity(intent);
            }
        });

        // when the user clicks the automatic button...
        automaticStart.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                Intent intent = new Intent(MainActivity.this, GameActivity.class);

                // tell the user through the toast the selection they've made
                Toast.makeText(MainActivity.this, "Start mode: [ Computer vs. Computer ]", Toast.LENGTH_LONG).show();

                startActivity(intent);
            }
        });
    }
}
