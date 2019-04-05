package com.example.cs478project2;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.ImageView;
import android.widget.TextView;

public class ThirdActivity extends AppCompatActivity
{
    TextView RAMtext, storageText, resolutionText, releaseDateText;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_third);

        // instantiate all the text views for the activity
        RAMtext = (TextView)findViewById(R.id.RAM);
        storageText = (TextView)findViewById(R.id.phoneStorage);
        resolutionText = (TextView)findViewById(R.id.phoneResolution);
        releaseDateText = (TextView)findViewById(R.id.releaseDate);

        // receive bundle extras - in which there should be because the phone's desc.
        // are pushed into the extras
        Bundle bundle = getIntent().getExtras();

        // unpack everything and place them into their respective spots
        if (bundle != null)
        {
            try
            {
                RAMtext.setText("RAM: " + bundle.getString("RAM"));
                storageText.setText("Storage Space: " + bundle.getString("phoneStorage"));
                resolutionText.setText("Resolution: " + bundle.getString("phoneResolution"));
                releaseDateText.setText("Release Date: " + bundle.getString("releaseDate"));
            }
            catch (Exception e)
            {
                e.printStackTrace();
            }
        }
    }
}
