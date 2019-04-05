package com.example.cs478project2;

import android.content.Context;
import android.support.annotation.NonNull;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.TextView;

// adapter to customize the ListView
public class CustomAdapter extends ArrayAdapter<String>
{
    String [] phoneNames;
    String [] smallTextDesc;
    int [] phoneImages;

    Context mContext;

    // constructor to hold the custom layout that will hold the images and the
    // texts
    public CustomAdapter(Context context, String[] phoneNames, int[] phoneImages, String[] smallTextDesc)
    {
        // call the super constructor to make our custom_layout
        super(context, R.layout.custom_layout);

        // initialize out things
        this.phoneNames = phoneNames;
        this.smallTextDesc = smallTextDesc;
        this.phoneImages = phoneImages;
        this.mContext = context;
    }

    // get the clickable area/length (?)
    // if this is forgotten, the adapter will not know the size of the list
    @Override
    public int getCount()
    {
        return phoneNames.length;
    }

    @NonNull
    @Override
    public View getView(int position, View convertView, ViewGroup parent)
    {
        // initialize the view holder
        ViewHolder mViewHolder = new ViewHolder();

        // check if there is no instances of the convert view.
        // if not, inflate and set the view holders
        if (convertView == null)
        {
            // inflater
            LayoutInflater inflater = (LayoutInflater) mContext.getSystemService(Context.LAYOUT_INFLATER_SERVICE);

            // convert view
            convertView = inflater.inflate(R.layout.custom_layout, parent, false);

            // set the view holder
            mViewHolder.phoneImage = (ImageView) convertView.findViewById(R.id.IMAGEVIEW);
            mViewHolder.bigText = (TextView) convertView.findViewById(R.id.BIGTEXT);
            mViewHolder.smallText = (TextView) convertView.findViewById(R.id.SMALLTEXT);

            // set the convert view's tags to the view holder
            convertView.setTag(mViewHolder);
        }
        // else, that means that there is a convert view so all that is needed to do is to
        // convert it to the view holder.
        else
        {
            mViewHolder = (ViewHolder)convertView.getTag();
        }

        // set the custom_layout elements
        mViewHolder.phoneImage.setImageResource(phoneImages[position]);
        mViewHolder.bigText.setText(phoneNames[position]);
        mViewHolder.smallText.setText(smallTextDesc[position]);

        // return view once things are done
        return convertView;
    }

    // create a view holder so that the OS will not constantly make calls to findViewById
    // which is the source for lag and high RAM consumption
    static class ViewHolder
    {
        ImageView phoneImage;
        TextView bigText;
        TextView smallText;
    }

}
