package com.example.cs478project3a1;

import android.content.BroadcastReceiver;
import android.content.IntentFilter;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;

public class SecondActivity extends AppCompatActivity
{
    private static final String filterString = "com.example.cs478project3";

    // broadcast receiver to accept broadcasts from A3
    // private BroadcastReceiver receiver = new MyReceiver();

    // filter
    // private IntentFilter filter = new IntentFilter(filterString);

    @Override
    protected void onCreate (Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.a1_second_activity);

        // setting low priority so that A2 activates first
        // filter.setPriority(10);

        // registering the receiver with the filter
        // registerReceiver(receiver, filter);
    }
}
