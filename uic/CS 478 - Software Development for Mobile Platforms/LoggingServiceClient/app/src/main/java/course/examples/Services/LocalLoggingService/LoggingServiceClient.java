package course.examples.Services.LocalLoggingService;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.Toast;

public class LoggingServiceClient extends Activity {
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		setContentView(R.layout.main);

		final Button messageButton = (Button) findViewById(R.id.message_button);
		messageButton.setOnClickListener(new OnClickListener() {
			public void onClick(View v) {

				// Send a toast message to show that UI Thread is still alive
				Toast.makeText(getApplicationContext(), "Key press noted!!", Toast.LENGTH_SHORT).show() ;

				// Create an Intent for starting the LoggingService
				Intent startServiceIntent = new Intent(getApplicationContext(),
						LoggingService.class) ;

				// Put Logging message in intent
				startServiceIntent.putExtra(LoggingService.EXTRA_LOG,
						"Ugo was here!");

				// Start the Service
				startService(startServiceIntent);

			}
		});
	}
}