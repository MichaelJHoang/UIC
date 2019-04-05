package edu.uic.cs478.BroadcastReceiver3WithResult;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.widget.Toast;

public class MyReceiver2 extends BroadcastReceiver {

	@Override
	public void onReceive(Context arg0, Intent arg1) {
		// TODO Auto-generated method stub
		Toast.makeText(arg0, "Receiver II saving data! ",
				Toast.LENGTH_SHORT).show() ;
		String s = getResultData() ;
		if (s == null) {
			setResultData("Receiver 2")  ; 
		}
		else {
			setResultData(s + " and then Receiver 2") ;
		}

	}

}
