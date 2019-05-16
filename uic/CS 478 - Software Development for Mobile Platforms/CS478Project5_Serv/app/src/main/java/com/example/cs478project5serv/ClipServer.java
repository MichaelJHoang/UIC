package com.example.cs478project5serv;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.media.MediaPlayer;
import android.media.MediaPlayer.OnCompletionListener;
import android.os.Build;

// name
public class ClipServer extends Service
{
    // instantiate some music player things
    public static MediaPlayer mediaPlayer;
    private int mStartID;
    private Notification notification;

    // instantiate and initialize some things for the drop down notification
    private static final int NOTIFICATION_ID = 1;
    private static String CHANNEL_ID = "Music player style";

    @Override
    public void onCreate()
    {
        super.onCreate();

        this.createNotificationChannel();

        final Intent notificationIntent = new Intent (getApplicationContext(),
                MainActivity.class);

        final PendingIntent pendingIntent = PendingIntent.getActivity(this, 0, notificationIntent, 0);

        // set up the media player
        // and handle user's selection
        if (MainActivity.selection == null)
            mediaPlayer = MediaPlayer.create(this, R.raw.one);
        else
        {
            if (MainActivity.selection.equalsIgnoreCase("one"))
                mediaPlayer = MediaPlayer.create(this, R.raw.one);
            else if (MainActivity.selection.equalsIgnoreCase("two"))
                mediaPlayer = MediaPlayer.create(this, R.raw.two);
            else if (MainActivity.selection.equalsIgnoreCase("three"))
                mediaPlayer = MediaPlayer.create(this, R.raw.three);
            else if (MainActivity.selection.equalsIgnoreCase("four"))
                mediaPlayer = MediaPlayer.create(this, R.raw.four);
            else if (MainActivity.selection.equalsIgnoreCase("five"))
                mediaPlayer = MediaPlayer.create(this, R.raw.five);
            else if (MainActivity.selection.equalsIgnoreCase("six"))
                mediaPlayer = MediaPlayer.create(this, R.raw.six);
            else if (MainActivity.selection.equalsIgnoreCase("seven"))
                mediaPlayer = MediaPlayer.create(this, R.raw.seven);
            else
                mediaPlayer = MediaPlayer.create(this, R.raw.one);
        }

        // and the notification
        notification =
                new Notification.Builder(getApplicationContext(), CHANNEL_ID)
                                .setSmallIcon(android.R.drawable.ic_media_play)
                                .setOngoing(true)
                                .setContentTitle("Currently Playing: " + MainActivity.selection + ".m4a")
                                .setTicker("Music is playing!")
                                .setFullScreenIntent(pendingIntent, false)
                                .build();



        if (null != mediaPlayer)
        {
            mediaPlayer.setLooping(false);

            // stop service when music finishes playing
            mediaPlayer.setOnCompletionListener(new OnCompletionListener()
            {
                @Override
                public void onCompletion(MediaPlayer mp)
                {
                    stopSelf(mStartID);
                }
            });
        }

        // put the service in foreground state, so it won't
        // be killed by the system
        startForeground(NOTIFICATION_ID, notification);
    }

    // allows for the creation of the notification channel because android updates did some things
    // that we now have to follow.
    private void createNotificationChannel ()
    {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O)
        {
            CharSequence name = "Music player notification";
            String desc = "The channel for music player notifications";

            int importance = NotificationManager.IMPORTANCE_DEFAULT;

            NotificationChannel channel = new NotificationChannel(CHANNEL_ID, name, importance);

            channel.setDescription(desc);

            NotificationManager notificationManager = getSystemService(NotificationManager.class);
            notificationManager.createNotificationChannel(channel);
        }
    }

    // TODO: actually implement it
    @Override
    public IBinder onBind (Intent intent)
    {
        return null;
    }

    //
    @Override
    public int onStartCommand (Intent intent, int flags, int id)
    {
        if (null != mediaPlayer)
        {
            // id for the start command
            mStartID = id;

            if (mediaPlayer.isPlaying())
            {
                // rewind to beginning of song
                mediaPlayer.seekTo(0);
            }
            else
            {
                // start playing song
                mediaPlayer.start();
            }
        }

        return START_STICKY;
    }

    // default onDestroy doesn't do this so we have to stop and release the media player
    @Override
    public void onDestroy ()
    {
        if (null != mediaPlayer)
        {
            mediaPlayer.stop();
            mediaPlayer.release();
        }
    }
}
