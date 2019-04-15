package com.example.cs478project4;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.BaseAdapter;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.Toast;

public class CustomAdapter extends BaseAdapter
{
    private int images [];

    private Context context;

    private LayoutInflater inflater;

    protected ImageView holeImage;

    public CustomAdapter (Context context, int images[])
    {
        this.context = context;
        this.images = images;
    }

    @Override
    public int getCount ()
    {
        return images.length;
    }

    @Override
    public Object getItem (int position)
    {
        return images[position];
    }

    @Override
    public long getItemId (int position)
    {
        return position;
    }

    @Override
    public View getView (int position, View convertView, ViewGroup parent)
    {
        View gridView = convertView;

        if (convertView == null)
        {
            inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);

            gridView = inflater.inflate(R.layout.custom_layout, null);
        }

        ImageView holeImage = (ImageView) gridView.findViewById(R.id.customLayoutImage);

        holeImage.setImageResource(images[position]);

        return gridView;
    }
}
