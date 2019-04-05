package com.example.cs478project2;

import android.content.Intent;
import android.net.Uri;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;

public class SecondActivity extends AppCompatActivity
{
    ImageView image;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_second);

        // instantiate the image ImageView so that there's a spot for the image to be in
        image = (ImageView)findViewById(R.id.IMAGEVIEW2);

        // receive the bundle's extras, if any - in which there should be
        // to show the large images
        final Bundle bundle = getIntent().getExtras();

        if (bundle != null)
        {
            // use setImageResource because Android gives a unique id for each drawable and
            // when this activity receives the extra bundles, it receives the drawables which
            // can be identified with the ids that Android gave them
            image.setImageResource(bundle.getInt("phoneImage"));
        }

        // allow the user to click on the image to pull up the phone's respective
        // website
        image.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                // same concept as mentioned before: because the first activity stores the phoneImages and their websites
                // in a key-value pair, we can simply pull up its respective information.
                try
                {
                    Intent browserIntent = new Intent(Intent.ACTION_VIEW, Uri.parse(bundle.getString("websites")));
                    startActivity(browserIntent);
                }
                catch (Exception e)
                {
                    e.printStackTrace();
                }
            }
        });
    }
}
