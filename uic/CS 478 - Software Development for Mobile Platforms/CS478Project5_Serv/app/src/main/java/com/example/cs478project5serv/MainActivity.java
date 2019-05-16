package com.example.cs478project5serv;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.Toast;

// pretty much this is the "Client" activity
public class MainActivity extends Activity
{
    // handle spinner selections
    public static String selection = null;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        // basic thing to have when setting up a view
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // intent to handle music intents
        final Intent musicIntent = new Intent(getApplicationContext(), ClipServer.class);

        // drop down spinner to allow the user to select the song that they want to listen to
        Spinner spinner = (Spinner) findViewById(R.id.spinner);

        // pretty much set the adapter for the spinner
        ArrayAdapter<CharSequence> spinnerAdapter = ArrayAdapter.createFromResource(this,
                R.array.songs, android.R.layout.simple_spinner_item);

        spinnerAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);

        spinner.setAdapter(spinnerAdapter);

        // handle user selections
        spinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener()
        {
            @Override
            public void onItemSelected(AdapterView<?> adapterView, View view, int i, long l)
            {
                // retrieve user selection and create a toast to show that the correct choice
                // was handled
                selection = (String) adapterView.getItemAtPosition(i);

                Toast.makeText(getApplicationContext(), selection, Toast.LENGTH_LONG).show();
                return;
            }

            @Override
            public void onNothingSelected(AdapterView<?> adapterView)
            {
                // nothing to do
            }
        });

        // pretty much start the service for the music
        Button startServiceButton = (Button) findViewById(R.id.startServiceButton);

        startServiceButton.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                startService(musicIntent);
            }
        });

        // ...and basically stops the service
        Button stopServiceButton = (Button) findViewById(R.id.stopServiceButton);
        stopServiceButton.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                stopService(musicIntent);
            }
        });

        // ...pause
        Button pauseButton = (Button) findViewById(R.id.pauseButton);
        pauseButton.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                // make sure to check if the music is currently playing otherwise
                // this thing would do crazy stuff
                if (ClipServer.mediaPlayer.isPlaying())
                {
                    ClipServer.mediaPlayer.pause();
                }
            }
        });

        // TODO: handle grayed out button...in which i didn't have enough time for
        //       ...this button resumes the service
        Button resumeButton = (Button) findViewById(R.id.resumeButton);
        if (true)
        {
            resumeButton.setClickable(true);

            resumeButton.setOnClickListener(new View.OnClickListener()
            {
                @Override
                public void onClick(View v)
                {
                    if (!ClipServer.mediaPlayer.isPlaying())
                    {
                        startService(musicIntent);
                    }
                }
            });
        }
        else
        {
            resumeButton.setClickable(false);
        }

        // stops music playback
        // TODO: fix the crashing problem
        Button stopPlaybackButton = (Button) findViewById(R.id.stopPlaybackButton);
        stopPlaybackButton.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (ClipServer.mediaPlayer != null)
                    ClipServer.mediaPlayer.stop();
                else
                    return;
            }
        });
    }
}
