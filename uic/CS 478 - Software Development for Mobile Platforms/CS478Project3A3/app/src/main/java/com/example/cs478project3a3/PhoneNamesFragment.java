package com.example.cs478project3a3;

import android.content.Context;
import android.os.Bundle;
import android.support.v4.app.ListFragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ListView;

public class PhoneNamesFragment extends ListFragment
{
    // interface to keep track of user's list selection
    private ListSelectionListener selectionListener = null;

    // keeps track of the index of user's selection
    private int currentIndex = -1;

    // interface to keep track of user's list selection
    public interface ListSelectionListener
    {
        public void onListSelection(int index);
    }

    // called when the user selects an item from the list
    @Override
    public void onListItemClick (ListView lv, View v, int pos, long id)
    {
        // indicate that the selected item has been checked
        getListView().setItemChecked(pos, true);

        // tell the third activity that the item in position pos has been selected
        selectionListener.onListSelection(pos);
    }

    @Override
    public void onAttach (Context activity)
    {
        super.onAttach(activity);

        try
        {
            // set the ListSelectionListener with the third activity
            selectionListener = (ListSelectionListener) activity;
        }
        catch (ClassCastException e)
        {
            throw new ClassCastException(activity.toString() + " has to implement stuff");
        }
    }

    @Override
    public void onCreate (Bundle savedBundleInstanceState)
    {
        super.onCreate(savedBundleInstanceState);

        // retain this fragment across activity reconfigs
        setRetainInstance(true);
    }

    @Override
    public View onCreateView (LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
    {
        //View view = inflater.inflate(R.layout.phone_names, container, false);
        return super.onCreateView(inflater, container, savedInstanceState);
    }

    @Override
    public void onActivityCreated (Bundle savedState)
    {
        super.onActivityCreated(savedState);

        // allow only one choice at a time
        getListView().setChoiceMode(ListView.CHOICE_MODE_SINGLE);

        // set the list adapter for the list view for the names of the phones
        setListAdapter(new ArrayAdapter<String> (getActivity(), R.layout.phone_names, MainActivity.phoneNameArray));

        // if an item was selected, set its checked state
        if (currentIndex != -1)
        {
            getListView().setItemChecked(currentIndex, true);

            selectionListener.onListSelection(currentIndex);
        }
    }
}
