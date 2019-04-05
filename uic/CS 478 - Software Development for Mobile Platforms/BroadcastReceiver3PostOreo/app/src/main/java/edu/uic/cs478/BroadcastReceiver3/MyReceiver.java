package edu.uic.cs478.BroadcastReceiver3;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.widget.Toast;

public class MyReceiver extends BroadcastReceiver {

	@Override
	public void onReceive(Context arg0, Intent arg1) {
		// TODO Auto-generated method stub
		Toast.makeText(arg0, "Static receiver I in action! ",
				Toast.LENGTH_LONG).show() ;
		Log.i("BroadcastReceiver 1", "First receiver in action!!!") ;

	}

}
