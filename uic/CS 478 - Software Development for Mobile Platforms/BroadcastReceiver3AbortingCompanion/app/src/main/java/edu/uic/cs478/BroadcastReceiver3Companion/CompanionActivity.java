package edu.uic.cs478.BroadcastReceiver3Companion;

// import edu.uic.cs478.BroadcastReceiver1.R;
// import edu.uic.cs478.BroadcastReceiver3.R;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.IntentFilter;
import android.os.Bundle;

public class CompanionActivity extends Activity
{
	// private Button mButton ;
	private static final String TOAST_INTENT = 
			"edu.uic.cs478.BroadcastReceiver3.showToast";

	// Comment following 2 lines for static receiver definition
	BroadcastReceiver mReceiver = new ForeignReceiver() ;
	IntentFilter mFilter = new IntentFilter(TOAST_INTENT) ;

	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        mFilter.setPriority(100) ;
        // Comment out for static receiver definition
        registerReceiver(mReceiver,mFilter) ;
    }

    protected void onDestroy() {
        super.onDestroy() ;
        unregisterReceiver(mReceiver) ;
    }
}
