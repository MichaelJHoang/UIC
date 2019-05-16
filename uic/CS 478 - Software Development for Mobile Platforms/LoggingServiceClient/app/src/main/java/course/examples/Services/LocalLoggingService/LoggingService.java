package course.examples.Services.LocalLoggingService;

import android.app.IntentService;
import android.content.Intent;
import android.util.Log;

public class LoggingService extends IntentService {

	public static String EXTRA_LOG = "course.examples.Services.Logging.MESSAGE";
	private static final String TAG = "LoggingService";

	public LoggingService() {
		super(TAG);
	}

	@Override
	protected void onHandleIntent(Intent intent) {

		try {
			Thread.sleep(3000) ;
		}
		catch (Exception e) {
			Log.w(TAG, "Thread was interrupted!") ;
		}
		Log.i(TAG, intent.getStringExtra(EXTRA_LOG));

	}

	public void onDestroy() {
		super.onDestroy()  ;
		Log.i(TAG, "Service was destroyed!!!!") ;
	}
}
