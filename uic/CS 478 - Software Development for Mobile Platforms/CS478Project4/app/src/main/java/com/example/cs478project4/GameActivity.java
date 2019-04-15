package com.example.cs478project4;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.AdapterView;
import android.widget.GridView;
import android.widget.Toast;

public class GameActivity extends AppCompatActivity
{
    GridView gridView;

    int holeImages [] = new int [100];

    @Override
    public void onCreate (Bundle saved)
    {
        for (int x = 0; x < 100; x++)
        {
            holeImages[x] = R.drawable.dirt_hole;
        }

        // basic required stuff
        super.onCreate(saved);
        setContentView(R.layout.activity_game);

        gridView = (GridView) findViewById(R.id.game_gridView);

        CustomAdapter adapter = new CustomAdapter (GameActivity.this, holeImages);

        gridView.setAdapter(adapter);

        gridView.setOnItemClickListener(new AdapterView.OnItemClickListener()
        {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id)
            {
                Toast.makeText(GameActivity.this, "Hole " + position + " Clicked!", Toast.LENGTH_SHORT).show();
            }
        });
    }
}
