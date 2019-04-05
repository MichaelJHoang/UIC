package com.ugobuy.simplecounter4;

import android.app.ListActivity;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;

import java.util.ArrayList;

public class StateListActivity extends ListActivity {
	
	private ListView listView ;
	private ArrayAdapter<String> mAdapter ;	
	private ArrayList<Uri> mUriList = new ArrayList<Uri>();
	private String[] mStateList ;	
	
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState) ;
				
		listView = getListView();
		mStateList = getResources().getStringArray(R.array.stateList) ;
		
		mAdapter = new ArrayAdapter<String>(this, R.layout.list_item, mStateList) ;
		setListAdapter(mAdapter) ;
		
		initializeStateUris() ;
		

		listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {

			public void onItemClick(AdapterView<?> parent,
									View view, int position, long it) {

				Uri aUri = mUriList.get(position) ;
				Intent aIntent = new Intent(Intent.ACTION_VIEW);
				aIntent.setData(aUri) ;
				aIntent.addCategory(Intent.CATEGORY_BROWSABLE) ;
				startActivity(aIntent) ;
			}
		}) ;

	}
	
//	public void onListItemClick(ListView parent,
//								View view, int position, long resourceID) {
//
//		Uri aUri = mUriList.get(position) ;
//		Intent aIntent = new Intent(Intent.ACTION_VIEW);
//		aIntent.setData(aUri) ;
//		aIntent.addCategory(Intent.CATEGORY_BROWSABLE) ;
//		startActivity(aIntent) ;
//	}

	private void initializeStateUris() {

		mUriList.add(Uri.parse("http://www.mass.gov")) ;
		mUriList.add(Uri.parse(getString(R.string.Connecticut_URI))) ;
		mUriList.add(Uri.parse("http://www.ri.gov/")) ;
		mUriList.add(Uri.parse("http://www.vermont.gov")) ;
		mUriList.add(Uri.parse("http://www.nh.gov")) ;
		mUriList.add(Uri.parse(getString(R.string.Main_URI))) ;
		mUriList.add(Uri.parse("http://www.patriots.com")) ;
	}

	protected void onPause() {
		super.onPause() ;
		setResult(RESULT_OK) ;
		// finish() ;
	}
}
