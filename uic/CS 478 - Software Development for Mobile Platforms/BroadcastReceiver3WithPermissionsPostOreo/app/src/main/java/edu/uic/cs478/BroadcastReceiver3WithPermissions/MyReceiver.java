package edu.uic.cs478.BroadcastReceiver3WithPermissions;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.widget.Toast;

public class MyReceiver extends BroadcastReceiver {

	@Override
	public void onReceive(Context arg0, Intent arg1) {
		// TODO Auto-generated method stub
		Log.i("BroadcastReceiver3 app", "Programmic Receiver 1 called into action.") ;
		Toast.makeText(arg0, "Programmatic receiver in action! ",
				Toast.LENGTH_LONG).show() ;

	}

}
