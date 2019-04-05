package com.example.cs478project3a3;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;

public class PhoneImagesFragment extends Fragment
{
    private ImageView mImageView = null;
    private int currentIndex = -1;
    private int length;

    private int stateValue = 123;
    private final String stateKey = "fragmentKey";

    @Override
    public void onCreate (Bundle savedInstanceBundle)
    {
        super.onCreate(savedInstanceBundle);

        // retain this fragment across activity reconfigs
        setRetainInstance(true);
    }

    public int getShownIndex ()
    {
        return currentIndex;
    }

    // show the image at the position newIndex
    public void showImageAtIndex (int newIndex)
    {
        if (newIndex < 0 || newIndex >= length)
            return;

        currentIndex = newIndex;
        mImageView.setImageResource(MainActivity.phoneImageArray[currentIndex]);
    }

    // called to create the content view for the fragment
    @Override
    public View onCreateView (LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
    {
        // inflate the images defined in MainActivity.java
        // last parameter is false because the returned view doesn't need to be attached
        View view = inflater.inflate(R.layout.phone_images, container, false);

        if (savedInstanceState != null)
        {
            stateValue = savedInstanceState.getInt(stateKey);
        }

        return view;
    }

    // set up the respective image of the phone that the user has had selected
    @Override
    public void onActivityCreated (Bundle savedInstanceState)
    {
        super.onActivityCreated(savedInstanceState);

        mImageView = (ImageView) getActivity().findViewById(R.id.IMAGEVIEW);
        length = MainActivity.phoneImageArray.length;
        showImageAtIndex(currentIndex);
    }

    // fires when a configuation change occurs and fragment needs to save state
    @Override
    public void onSaveInstanceState (Bundle bundle)
    {
        bundle.putInt(stateKey, stateValue);
        super.onSaveInstanceState(bundle);
    }
}
