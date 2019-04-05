package com.example.cs478project2;

import android.content.Intent;
import android.net.Uri;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.ContextMenu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity
{
    private final String tag = "MainActivity.java"; // default tag for the activity

    // initializing the views
    ListView listView;
    TextView bigText;
    TextView smallText;

    // initialize the string array of phones that are going to be used
    String[] phoneNames = {"Google Pixel 3", "Samsung Galaxy S9", "iPhone XS Max", "OnePlus 6", "Huawei Nova 4", "Moto Z3"};
    // and their screen sizes and prices, too
    String[] smallTextDesc = {"5.5\" display at $899", "5.8\" display at $720", "6.5\" display at $1,349", "6.28\" display at $529", "6.4\" display at $492", "6.01\" display at $480"};

    // list of websites for the phones respectively
    String[] websites = {"https://store.google.com/us/product/pixel_3?hl=en-US",
                         "https://www.samsung.com/global/galaxy/galaxy-s9/",
                         "https://www.apple.com/shop/buy-iphone/iphone-xs",
                         "https://www.oneplus.com/6",
                         "https://consumer.huawei.com/my/phones/nova4/",
                         "https://www.motorola.com/us/products/moto-z-gen-3"};

    // list of RAM for the respective phones
    String[] RAM = {"4GB LPDDR4",
                    "4 GB",
                    "4 GB",
                    "6/8 GB LPDDR4X",
                    "8 GB",
                    "4 GB"};

    // list of storage spaces for the phones
    String[] phoneStorage = {"64/128 GB Internal",
                             "64 GB Internal",
                             "64/256/512 GB Internal",
                             "UFS 2.1 2-LANE 64/128/256 GB",
                             "128 GB Internal",
                             "64 GB Internal"};

    // list of resolutions available to the respective phones
    String[] phoneResolutions = {"2160x1080-pixel resolution OLED (443 ppi)",
                                 "Quad HD+ Super AMOLED (2960x1440) 570 ppi",
                                 "2688x1241-pixel resolution at 458 ppi",
                                 "2280x1080 pixels",
                                 "1080x2310 pixels",
                                 "Super AMOLED, Full HD+ 2160x1080 pixels"};

    // list of release dates for the respective phones
    String[] releaseDates = {"October 18th, 2018",
                             "March 16th, 2018",
                             "September 12th, 2018",
                             "May 22nd, 2018",
                             "January 15th, 2019",
                             "August 16th, 2018"};

    // get the drawables and their IDs
    int[] phoneImages = {R.drawable.googlepixel3,
                        R.drawable.samsunggalaxys9,
                        R.drawable.iphonexsmax,
                        R.drawable.oneplus6,
                        R.drawable.huaweinova4,
                        R.drawable.motoz3};

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // assign the ListView
        listView = (ListView) findViewById(R.id.listView);

        // assign the text views
        bigText = (TextView) findViewById(R.id.BIGTEXT);
        smallText = (TextView) findViewById(R.id.SMALLTEXT);

        // initialize programmer's custom adapter
        CustomAdapter customAdapter = new CustomAdapter(MainActivity.this, phoneNames, phoneImages, smallTextDesc);
        listView.setAdapter(customAdapter);

        // set the listener so that when the user clicks on it, it sends them to another
        // activity that enlarges the thumbnail and allows them to be taken to the
        // manufacturer's site when clicked.
        try
        {
            listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
                @Override
                public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                    Intent intent = new Intent(MainActivity.this, SecondActivity.class);

                    // pack the phone images and their websites to be sent to the second activity
                    intent.putExtra("phoneImage", phoneImages[position]);
                    intent.putExtra("websites", websites[position]);
                    startActivity(intent);
                }
            });
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }

        // register the listView for the context menu
        registerForContextMenu(listView);

        // set the listener so that when the user LONG clicks it, it pops up the context menus
        // which allows them to go places.
        try
        {
            listView.setOnLongClickListener(new View.OnLongClickListener()
            {
                @Override
                public boolean onLongClick(View v)
                {
                    return false;
                }
            });
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }

    }

    // call to make the context menu
    @Override
    public void onCreateContextMenu (ContextMenu menu, View v, ContextMenu.ContextMenuInfo menuInfo)
    {
        super.onCreateContextMenu(menu, v, menuInfo);

        getMenuInflater().inflate(R.menu.project2_contextmenu, menu);
    }

    // allow selection of the context menu items
    @Override
    public boolean onContextItemSelected (MenuItem item)
    {
        // based on the ListView item that was selected, get its info
        AdapterView.AdapterContextMenuInfo acmi = (AdapterView.AdapterContextMenuInfo)item.getMenuInfo();

        // switch case to check what the user selected within that context menu
        switch (item.getItemId())
        {
            case R.id.specs:
                // go to a new activity containing the some of the phone's respective specs
                try
                {
                    // preparing to go to the third activity
                    Intent intent = new Intent(MainActivity.this, ThirdActivity.class);
                    intent.putExtra("RAM", RAM[acmi.position]);
                    intent.putExtra("phoneStorage", phoneStorage[acmi.position]);
                    intent.putExtra("phoneResolution", phoneResolutions[acmi.position]);
                    intent.putExtra("releaseDate", releaseDates[acmi.position]);
                    startActivity(intent);
                }
                catch (Exception e)
                {
                    e.printStackTrace();
                }
                break;
            case R.id.fullImage:
                // instead of creating a new activity, start the second activity instead
                try
                {
                    Intent intent = new Intent(MainActivity.this, SecondActivity.class);
                    intent.putExtra("phoneImage", phoneImages[acmi.position]);
                    intent.putExtra("websites", websites[acmi.position]);
                    startActivity(intent);
                }
                catch (Exception e)
                {
                    e.printStackTrace();
                }
                break;
            case R.id.contextWebsite:
                // pull up the phone's respective website
                try
                {
                    Intent browserIntent = new Intent(Intent.ACTION_VIEW, Uri.parse(websites[acmi.position]));
                    startActivity(browserIntent);
                }
                catch (Exception e)
                {
                    e.printStackTrace();
                }
                break;
            // default case just in case the user didn't click anything
            default:
                return false;
        }
        return super.onContextItemSelected(item);
    }

    @Override
    protected void onStart ()
    {
        super.onStart();
        Log.i(tag, "The MainActivity is about to start");
    }

    @Override
    protected void onRestart()
    {
        super.onRestart();
        Log.i(tag, "The MainActivity is about to restart");
    }

    @Override
    protected void onResume()
    {
        super.onResume();
        Log.i(tag, "This activity has taken focus again and will be resumed");
    }

    @Override
    protected void onPause()
    {
        super.onPause();
        Log.i(tag, "Another activity has taken focus and this one will be put on pause");
    }

    @Override
    protected void onStop()
    {
        super.onStop();
        Log.i(tag, "The activity is no longer visible and will be stopped");
    }

    @Override
    protected void onDestroy()
    {
        super.onDestroy();
        Log.i(tag, "The activity is about to be destroyed.");
    }
}
