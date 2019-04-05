package edu.uic.cs478.BroadcastReceiver3Companion;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.widget.Toast;

public class ForeignReceiver extends BroadcastReceiver {

	@Override
	public void onReceive(Context arg0, Intent arg1) {
		// TODO Auto-generated method stub
		Log.i("Companion receiver", "Companion Receiver called into action!");
		Toast.makeText(arg0, "Companion receiver in action! ",
				Toast.LENGTH_LONG).show() ;

	}

}
