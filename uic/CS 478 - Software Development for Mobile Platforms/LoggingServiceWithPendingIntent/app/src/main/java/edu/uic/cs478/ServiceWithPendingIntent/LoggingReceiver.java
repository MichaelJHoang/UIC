package edu.uic.cs478.ServiceWithPendingIntent;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.widget.Toast;

/**
 * Created by ugobuy on 4/5/17.
 */

public class LoggingReceiver extends BroadcastReceiver {

    public void onReceive(Context c, Intent i) {
    
        Log.i("Ugo's Receiver", "The receiver got called into action!") ;
        Toast.makeText(c, "Receiver called back!", Toast.LENGTH_LONG).show() ;
    }

}
