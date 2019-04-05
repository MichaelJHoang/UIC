package edu.uic.cs478.BroadcastReceiver3WithResult;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.widget.Toast;

public class MyReceiver3 extends BroadcastReceiver {

	@Override
	public void onReceive(Context arg0, Intent arg1) {
		// TODO Auto-generated method stub
		Toast.makeText(arg0, "Receiver III saving data... ",
				Toast.LENGTH_LONG).show() ;
		String s = getResultData() ;
		if (s == null) {
			setResultData("Receiver 3")  ; 
		}
		else {
			setResultData(s + " and then Receiver 3") ;
		}
	}

}
