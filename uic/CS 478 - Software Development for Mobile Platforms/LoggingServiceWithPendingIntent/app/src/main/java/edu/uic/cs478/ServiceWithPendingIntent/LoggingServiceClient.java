package edu.uic.cs478.ServiceWithPendingIntent;

import android.app.Activity;
import android.app.PendingIntent;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.Toast;

public class LoggingServiceClient extends Activity {

	static String PENDING_KEY = "PendingKey" ;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		setContentView(R.layout.main);

		final Button messageButton = (Button) findViewById(R.id.message_button);
		messageButton.setOnClickListener(new OnClickListener() {
			public void onClick(View v) {

				// Send a toast message to show that UI Thread is still alive
				Toast.makeText(getApplicationContext(), "Key press noted!!", Toast.LENGTH_SHORT).show() ;

				Intent resultIntent = new Intent(getApplicationContext(), LoggingReceiver.class) ;

				PendingIntent pendingIntent = PendingIntent.getBroadcast(getApplicationContext(), 0, resultIntent, 0) ;

				// Create an Intent for starting the LoggingService
				Intent startServiceIntent = new Intent(getApplicationContext(),
						edu.uic.cs478.ServiceWithPendingIntent.LoggingService.class) ;

				startServiceIntent.putExtra(PENDING_KEY, pendingIntent) ;

				// Put Logging message in intent
				startServiceIntent.putExtra(edu.uic.cs478.ServiceWithPendingIntent.LoggingService.EXTRA_LOG,
						"Ugo was here!");

				// Start the Service
				startService(startServiceIntent);

			}
		});
	}
}