package edu.uic.cs478.BroadcastReceiver3;

// import edu.uic.cs478.BroadcastReceiver1.R;

import android.app.Activity;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class MainActivity extends Activity
{
    private Button mButton ;
    private MyReceiver mReceiver1 ;
    private MyReceiver2 mReceiver2 ;
    private MyReceiver3 mReceiver3 ;
    private IntentFilter mFilter1 ;
    private IntentFilter mFilter2 ;
    private IntentFilter mFilter3 ;

    private static final String TOAST_INTENT =
			"edu.uic.cs478.BroadcastReceiver3.showToast"; 
	
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
        			sendOrderedBroadcast(aIntent, null) ;
        		}
        }) ;

        
    }
}
