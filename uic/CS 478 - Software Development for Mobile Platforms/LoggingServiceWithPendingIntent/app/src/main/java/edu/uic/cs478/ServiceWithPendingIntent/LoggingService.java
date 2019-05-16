package edu.uic.cs478.ServiceWithPendingIntent;

import android.app.IntentService;
import android.app.PendingIntent;
import android.content.Intent;
import android.util.Log;

public class LoggingService extends IntentService {

	public static String EXTRA_LOG = "edu.uic.cs478.ServiceWithPendingIntent.MESSAGE";
	private static final String TAG = "LoggingPendingIntent";

	PendingIntent mPending ;
	public LoggingService() {
		super(TAG);
	}

	@Override
	protected void onHandleIntent(Intent intent) {

		mPending = (PendingIntent) intent.getParcelableExtra(LoggingServiceClient.PENDING_KEY) ;
		try {
			Thread.sleep(1000) ;
		}
		catch (Exception e) {
			Log.w(TAG, "Thread was interrupted!") ;
		}
		Log.i(TAG, intent.getStringExtra(EXTRA_LOG));
		try {
			mPending.send() ;
		}
		catch (PendingIntent.CanceledException e) {
			Log.i("Ugo's Service", "Pending Intent no longer allows intents to be sent.") ;
		}

	}

	public void onDestroy() {
		super.onDestroy()  ;
		Log.i(TAG, "Service was destroyed!!!!") ;
	}
}
