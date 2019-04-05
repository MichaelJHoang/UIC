package com.example.cs478project3a3;

import android.content.ComponentName;
import android.content.Intent;
import android.content.res.Configuration;
import android.net.Uri;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.ContextMenu;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.widget.AdapterView;
import android.widget.FrameLayout;
import android.widget.LinearLayout;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity implements PhoneNamesFragment.ListSelectionListener
{
    // toast intent
    private static final String TOAST_INTENT = "com.example.cs478project3";

    // array to hold the names of the phones
    static String[] phoneNameArray;

    // array to hold the ids and references to the phone images
    static int[] phoneImageArray = {R.drawable.googlepixel3,
                                    R.drawable.samsunggalaxys9,
                                    R.drawable.iphonexsmax,
                                    R.drawable.oneplus6,
                                    R.drawable.huaweinova4,
                                    R.drawable.motoz3};

    // list of websites for the phones respectively
    static String[] websites = {"https://store.google.com/us/product/pixel_3?hl=en-US",
                                "https://www.samsung.com/global/galaxy/galaxy-s9/",
                                "https://www.apple.com/shop/buy-iphone/iphone-xs",
                                "https://www.oneplus.com/6",
                                "https://consumer.huawei.com/my/phones/nova4/",
                                "https://www.motorola.com/us/products/moto-z-gen-3"};

    // don't include this line of code or it will crash
    //private PhoneNamesFragment phoneNamesFragment;

    // instantiate the fragment to be used within the activity
    private PhoneImagesFragment phoneImgFragment = new PhoneImagesFragment();

    private FragmentManager mFragmentManager;

    private FrameLayout nameFrameLayout, imageFrameLayout;
    private static final int MATCH_PARENT = LinearLayout.LayoutParams.MATCH_PARENT;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        // get the string array of phone names from the strings.xml file
        phoneNameArray = getResources().getStringArray(R.array.phoneNameStrings);

        setContentView(R.layout.activity_main);

        // get a reference to the phone images and names fragments
        // phoneImgFragment = (PhoneImagesFragment)getSupportFragmentManager().findFragmentById(R.id.imageFragmentID);
        nameFrameLayout = (FrameLayout) findViewById(R.id.nameContainer);
        imageFrameLayout = (FrameLayout) findViewById(R.id.imageContainer);

        // get reference to support manager instead of fragment manager
        mFragmentManager = getSupportFragmentManager();

        // don't include this line of code or it will crash
        //phoneNamesFragment = (PhoneNamesFragment)getSupportFragmentManager().findFragmentById(R.id.nameFragmentID);

        // start new transaction with backwards compatibility
        FragmentTransaction transaction = mFragmentManager.beginTransaction();

        // add the name fragment to the layout
        transaction.replace(R.id.nameContainer, new PhoneNamesFragment());

        // commit the transaction
        transaction.commit();

        // Add a OnBackStackChangedListener to reset the layout when the back stack changes
        mFragmentManager.addOnBackStackChangedListener(
                new FragmentManager.OnBackStackChangedListener()
                {
                    @Override
                    public void onBackStackChanged()
                    {
                        setLayout();
                    }
                }
        );
    }

    private void setLayout()
    {
        // determine whether or not the image fragment has been added
        if (!phoneImgFragment.isAdded())
        {
            // make the name fragment occupy the entire layout
            nameFrameLayout.setLayoutParams(new LinearLayout.LayoutParams(
                    MATCH_PARENT, MATCH_PARENT));
            imageFrameLayout.setLayoutParams(new LinearLayout.LayoutParams(0,
                    MATCH_PARENT));
        }
        else
        {
            // if the phone's orientation is in landscape...
            if (getResources().getConfiguration().orientation == Configuration.ORIENTATION_LANDSCAPE)
            {
                // make the name layout take 1/3 of the screen
                nameFrameLayout.setLayoutParams(new LinearLayout.LayoutParams(0,
                        MATCH_PARENT, 1f));

                // make the image layout take 2/3's of the screen
                imageFrameLayout.setLayoutParams(new LinearLayout.LayoutParams(0,
                        MATCH_PARENT, 2f));
            }
            // otherwise portrait is...
            else if (getResources().getConfiguration().orientation == Configuration.ORIENTATION_PORTRAIT)
            {
                // make the name layout take none of the screen
                nameFrameLayout.setLayoutParams(new LinearLayout.LayoutParams(0,
                        0, 0f));

                // make the image layout take the whole screen
                imageFrameLayout.setLayoutParams(new LinearLayout.LayoutParams(0,
                        MATCH_PARENT, 1f));
            }
        }
    }

    // implement listSelectionListener interface
    // called by PhoneNamesFragment when the user selects an item in the fragment
    @Override
    public void onListSelection (int index)
    {
        // if the image fragment has not been added, add it now
        if (!phoneImgFragment.isAdded())
        {
            // start a new transaction
            FragmentTransaction transaction = mFragmentManager.beginTransaction();

            // add the image fragment to the layout
            transaction.replace(R.id.imageContainer, phoneImgFragment);

            // add the transaction to the backstack
            transaction.addToBackStack(null);

            // commit the transaction
            transaction.commit();

            // force android to execute the committed transaction
            mFragmentManager.executePendingTransactions();
        }

        if (phoneImgFragment.getShownIndex() != index)
        {
            // tell the image fragment to show the details at the index
            phoneImgFragment.showImageAtIndex(index);
        }
    }

    // create the options menu in the action bar
    @Override
    public boolean onCreateOptionsMenu (Menu menu)
    {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.action_menu, menu);

        return true;
    }

    // process clicks within the options menu
    @Override
    public boolean onOptionsItemSelected (MenuItem item)
    {
        switch (item.getItemId())
        {
            // sends an ordered broadcast intent to the other applications in which:
            // A2 will display a toast message indicating that it was activated from A3
            // A1 will display the web page of the currently selected smartphone.
            //
            // if none are selected, only the toast message would appear.
            case R.id.launchOtherApps:
                // prepare to send the broadcast intent
                Intent intent = new Intent(TOAST_INTENT);

                // now broadcast
                sendOrderedBroadcast(intent, null);

                intent = new Intent (Intent.ACTION_VIEW);

                // get the website of the thing that the user has had selected and pack it in as an extra
                // also, make sure that the user has had selected something
                // otherwise, this part gets skipped
                if (phoneImgFragment.getShownIndex() != -1)
                {
                    intent.putExtra("phoneWebsite", websites[phoneImgFragment.getShownIndex()]);
                }

                // initially I wanted to send broadcasts but I gave up because it was too difficult to figure out
                intent.setData(Uri.parse(websites[phoneImgFragment.getShownIndex()]));

                // start the website instead
                startActivity(intent);

                return true;

            // user clicks on the exit button -> exit this application
            case R.id.exit:
                finish();
                return true;

            // user clicks something that is not one of the two things above
            default:
                return false;
        }
    }
}
