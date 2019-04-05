package com.example.cs478project3a1;

import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.widget.Toast;

public class MyReceiver extends BroadcastReceiver
{
    // variable to contain the website string that is received from A3
    private String websiteString;

    @Override
    public void onReceive (Context context, Intent intent)
    {
        websiteString = intent.getStringExtra("phoneWebsite");

        // assuming the website string is not null, that means that we have
        // the ability to go to the phone's respective website
        intent.putExtra("thePhoneWebsite", websiteString);

        Intent i = new Intent(context, SecondActivity.class);

        i.setComponent(new ComponentName("com.example.cs478project3a1", "com.example.cs478project3a1.SecondActivity"));

        // this line of code allows this to be not put in the back stack
        i.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_NO_HISTORY);

        // now start the activity
        context.startActivity(i);
    }
}
