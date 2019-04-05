package com.example.cs478project3a2;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.widget.Toast;

public class MySecondReceiver extends BroadcastReceiver
{
    // this part runs specifically when A3 sends a broadcast
    @Override
    public void onReceive (Context arg0, Intent arg1)
    {
        Toast.makeText(arg0, "A broadcast was sent and application A2's BroadcastReceiver caught it!", Toast.LENGTH_LONG).show();
    }
}
