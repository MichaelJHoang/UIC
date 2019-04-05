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
	
	BroadcastReceiver mReceiver = new ForeignReceiver() ;
	IntentFilter mFilter = new IntentFilter(TOAST_INTENT) ;
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        mFilter.setPriority(100);

        registerReceiver(mReceiver, mFilter);
    }

    public void onDestroy() {
        super.onDestroy();
        unregisterReceiver(mReceiver);
    }

    /*public void onResume() {
        super.onResume()  ;
        if (ContextCompat.checkSelfPermission(this, "edu.uic.cs478.UgosPermission") !=
                PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this, new String[]{"edu.uic.cs478.UgosPermission"}, 0);
        }
    }
        
    public void onRequestPermissionsResult(int code, String[] permissions, int[] grantResults) {

        if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {

            // Permission granted, go ahead and display map
            Log.i("BroadcastReceiver3 companion", "Ugo says: The user granted permission!!!") ;
        }
        else {
            Toast.makeText(this, "BUMMER: No Permission :-(", Toast.LENGTH_LONG).show() ;
        }


    }*/
        // mButton = (Button) findViewById(R.id.button1) ;
        
        // mButton.setOnClickListener(new View.OnClickListener() {
        	// 	public void onClick(View v) {
        	//		Intent aIntent = new Intent(TOAST_INTENT) ;
        	//		sendOrderedBroadcast(aIntent, null) ;
        	//	}
        // }) ;

        
}

