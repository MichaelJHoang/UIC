package com.example.cs478project4;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;

public class GameActivity extends AppCompatActivity
{
    @Override
    public void onCreate (Bundle saved)
    {
        // basic required stuff
        super.onCreate(saved);
        setContentView(R.layout.activity_game);
    }
}
