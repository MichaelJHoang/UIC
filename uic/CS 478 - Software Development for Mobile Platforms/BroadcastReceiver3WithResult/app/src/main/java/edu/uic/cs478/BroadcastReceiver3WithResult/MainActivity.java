package edu.uic.cs478.BroadcastReceiver3WithResult;

// import edu.uic.cs478.BroadcastReceiver1.R;
// import edu.uic.cs478.BroadcastReceiver3.R;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.widget.Toast;
import android.app.Activity;
import android.widget.Button ;
import android.os.Bundle;
import android.view.View ;

public class MainActivity extends Activity
{
	private Button mButton ;
	private static final String TOAST_INTENT = 
			"edu.uic.cs478.BroadcastReceiver3WithResult.showToast";

	private MyReceiver mReceiver1 ;
	private MyReceiver2 mReceiver2 ;
	private MyReceiver3 mReceiver3 ;
	private IntentFilter mFilter1 ;
	private IntentFilter mFilter2 ;
	private IntentFilter mFilter3 ;

	/** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

		// UB:  Look what I have to do for Oreo...
		mReceiver1 = new MyReceiver() ;
		mReceiver2 = new MyReceiver2() ;
		mReceiver3 = new MyReceiver3() ;
		mFilter1 = new IntentFilter(TOAST_INTENT) ;
		mFilter1.setPriority(1);
		mFilter2 = new IntentFilter(TOAST_INTENT) ;
		mFilter2.setPriority(10);
		mFilter3 = new IntentFilter(TOAST_INTENT) ;
		mFilter3.setPriority(20);
		registerReceiver(mReceiver1, mFilter1) ;
		registerReceiver(mReceiver2, mFilter2) ;
		registerReceiver(mReceiver3, mFilter3) ;

		mButton = (Button) findViewById(R.id.button1) ;
        
        mButton.setOnClickListener(new View.OnClickListener() {
        		public void onClick(View v) {
        			Intent aIntent = new Intent(TOAST_INTENT) ;
        			sendOrderedBroadcast(aIntent, null, 
        					new BroadcastReceiver() {  public void onReceive(Context context, Intent intent) {
        								String s = getResultData() ;
        								Toast.makeText(context, s, Toast.LENGTH_LONG).show();
        							}
        					},
        					null, 0, null, null) ;
        		}
        }) ;
    }

    protected void onDestroy() {
    	super.onDestroy() ;
    	unregisterReceiver(mReceiver1) ;
		unregisterReceiver(mReceiver2) ;
		unregisterReceiver(mReceiver3) ;
	}
}
