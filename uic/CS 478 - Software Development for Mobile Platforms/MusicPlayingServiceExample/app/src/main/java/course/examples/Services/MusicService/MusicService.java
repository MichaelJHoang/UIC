package course.examples.Services.MusicService;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Intent;
import android.media.MediaPlayer;
import android.media.MediaPlayer.OnCompletionListener;
import android.os.Build;
import android.os.IBinder;
import android.support.v4.app.NotificationCompat;

public class MusicService extends Service {

	@SuppressWarnings("unused")
	private final String TAG = "MusicService";

	private static final int NOTIFICATION_ID = 1;
	private MediaPlayer mPlayer;
	private int mStartID;
	private Notification notification ;

	private static String CHANNEL_ID = "Music player style" ;


	@Override
	public void onCreate() {
		super.onCreate();

		// UB: Starting in Oreo notifications have a notification channel
		//     The channel defines basic properties of
		this.createNotificationChannel();

		// Create a notification area notification so the user
		// can get back to the MusicServiceClient

		final Intent notificationIntent = new Intent(getApplicationContext(),
				MusicServiceClient.class);

		final PendingIntent pendingIntent = PendingIntent.getActivity(this, 0,
				notificationIntent, 0) ;

		notification =
		new NotificationCompat.Builder(getApplicationContext(), CHANNEL_ID)
				.setSmallIcon(android.R.drawable.ic_media_play)
				.setOngoing(true).setContentTitle("Music Playing")
				.setContentText("Click to Access Music Player")
				.setTicker("Music is playing!")
				.setFullScreenIntent(pendingIntent, false)
				.build();

		// Set up the Media Player
		mPlayer = MediaPlayer.create(this, R.raw.badnews);

		if (null != mPlayer) {

			mPlayer.setLooping(false);

			// Stop Service when music has finished playing
			mPlayer.setOnCompletionListener(new OnCompletionListener() {

				@Override
				public void onCompletion(MediaPlayer mp) {

					// stop Service if it was started with this ID
					// Otherwise let other start commands proceed
					stopSelf(mStartID);

				}
			});
		}


		// Put this Service in a foreground state, so it won't 
		// readily be killed by the system  
		startForeground(NOTIFICATION_ID, notification);

	}

	// UB 11-12-2018:  Now Oreo wants communication channels...
	private void createNotificationChannel() {
		// Create the NotificationChannel, but only on API 26+ because
		// the NotificationChannel class is new and not in the support library
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
			CharSequence name = "Music player notification";
			String description = "The channel for music player notifications";
			int importance = NotificationManager.IMPORTANCE_DEFAULT;
			NotificationChannel channel = new NotificationChannel(CHANNEL_ID, name, importance);
			channel.setDescription(description);
			// Register the channel with the system; you can't change the importance
			// or other notification behaviors after this
			NotificationManager notificationManager = getSystemService(NotificationManager.class);
			notificationManager.createNotificationChannel(channel);
		}
	}
	
	@Override
	public int onStartCommand(Intent intent, int flags, int startid) {

		if (null != mPlayer) {

			// ID for this start command
			mStartID = startid;

			if (mPlayer.isPlaying()) {

				// Rewind to beginning of song
				mPlayer.seekTo(0);

			} else {

				// Start playing song
				mPlayer.start();

			}

		}

		// Don't automatically restart this Service if it is killed
		return START_NOT_STICKY;
	}

	@Override
	public void onDestroy() {

		if (null != mPlayer) {

			mPlayer.stop();
			mPlayer.release();

		}
	}

	// Can't bind to this Service
	@Override
	public IBinder onBind(Intent intent) {

		return null;

	}
}
