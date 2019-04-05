package edu.uic.cs478.BroadcastReceiver3;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.widget.Toast;

public class MyReceiver3 extends BroadcastReceiver {

	@Override
	public void onReceive(Context arg0, Intent arg1) {
		// TODO Auto-generated method stub
//		try {
//			Thread.sleep(2000) ;
//		}
//		catch (InterruptedException e){
//			Log.e("BroadcastReceiver3", "Thread interrupted") ;
//		}
		Toast.makeText(arg0, "Static receiver III in action! ",
				Toast.LENGTH_LONG).show() ;
		Log.i("BroadcastReceiver III", "Third receiver in action!!!") ;

	}

}
