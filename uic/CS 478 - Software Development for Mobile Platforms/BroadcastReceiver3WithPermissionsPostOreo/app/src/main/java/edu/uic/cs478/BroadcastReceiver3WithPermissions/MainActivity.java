package edu.uic.cs478.BroadcastReceiver3WithPermissions;

// import edu.uic.cs478.BroadcastReceiver1.R;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

public class MainActivity extends Activity
{
	private Button mButton ;
	private BroadcastReceiver mReceiver1;
    private BroadcastReceiver mReceiver2;
    private BroadcastReceiver mReceiver3;
	private IntentFilter mFilter ;
	private static final String TOAST_INTENT = 
			"edu.uic.cs478.BroadcastReceiver3.showToast";
	private static final String UGOS_PERMISSION =
			"edu.uic.cs478.UgosPermission" ;
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        mButton = (Button) findViewById(R.id.button1) ;
        
        mButton.setOnClickListener(new View.OnClickListener() {
        		public void onClick(View v) {
                    checkPermissionAndBroadcast();
        		}
        }) ;
    }

    protected void onResume() {
        super.onResume() ;

        mFilter = new IntentFilter(TOAST_INTENT) ;
        mFilter.setPriority(1) ;
        mReceiver1 = new MyReceiver() ;
        registerReceiver(mReceiver1, mFilter) ;

        mFilter = new IntentFilter(TOAST_INTENT) ;
        mFilter.setPriority(10) ;
        mReceiver2 = new MyReceiver2() ;
        registerReceiver(mReceiver2, mFilter) ;

        mFilter = new IntentFilter(TOAST_INTENT) ;
        mFilter.setPriority(20) ;
        mReceiver3 = new MyReceiver3() ;
        registerReceiver(mReceiver3, mFilter) ;

    }
    private void checkPermissionAndBroadcast() {
        if (ContextCompat.checkSelfPermission(this, UGOS_PERMISSION)
                == PackageManager.PERMISSION_GRANTED) {
            Intent aIntent = new Intent(TOAST_INTENT) ;
            sendOrderedBroadcast(aIntent, UGOS_PERMISSION) ;
        }
        else {
            ActivityCompat.requestPermissions(this, new String[]{UGOS_PERMISSION}, 0) ;
        }

    }

    public void onRequestPermissionsResult(int code, String[] permissions, int[] results) {
        if (results.length > 0) {
            if (results[0] == PackageManager.PERMISSION_GRANTED) {
                Intent aIntent = new Intent(TOAST_INTENT) ;
                sendOrderedBroadcast(aIntent, UGOS_PERMISSION)  ;
            }
            else {
                Toast.makeText(this, "Bummer: No permission", Toast.LENGTH_SHORT)
                    .show();
            }
        }
    }

    protected void onPause() {
        super.onPause() ;
        unregisterReceiver(mReceiver1) ;
        unregisterReceiver(mReceiver2) ;
        unregisterReceiver(mReceiver3) ;

    }
}
