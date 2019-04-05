// Copyright (c) Ugo Buy, 2012.  All rights reserved.

package com.ugobuy.simplecounter4;

import android.app.Activity;
import android.os.Bundle;
import android.content.Intent;

// import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.SeekBar;
import android.widget.Button;
import android.widget.SeekBar.OnSeekBarChangeListener;
// import android.widget.TextView;

// the main class of the SimpleCounter app
public class SimpleCounterActivity4 extends Activity {
	
	// Fields to be bound to GUI widgets
	protected Button up ; 				// the "Up" button in the GUI
	protected Button down ; 			// the "Down" button in the GUI
	protected Button tip;				// the "tip calc" button in the GUI
	protected SeekBar slider ;			// the seek bar in the GUI
	protected EditText textField ;		// the edit text in the GUI
	protected int counterValue ;		// the value stored in the counter
	
	// The key into the "saved state" bundle
	protected static final String counterKey = "COUNTER_VALUE" ;
	protected static final String clicksKey = "TOTAL_CLICKS" ;

	// A hidden state variable not visible in the UI
	protected int totalClicks = 0 ;
	
    /** Called by the OS when the activity is first created. */
    @Override
   public void onCreate(Bundle savedInstanceState) {
    	
    	// Always do this
        super.onCreate(savedInstanceState);
        
        // Inflate the main layout (from the res folder)
        setContentView(R.layout.main);

		// Bind the interface elements to the corresponding fields
		up = (Button) findViewById(R.id.upButton);
		down = (Button) findViewById(R.id.downButton) ;
		textField = (EditText) findViewById(R.id.editText1) ;
		slider = (SeekBar) findViewById(R.id.theSlider) ;
		tip = (Button) findViewById(R.id.tipButton) ;
        // Are we running from scratch?  Yes
        if (savedInstanceState == null) {
        	counterValue = 0;
        }
        // No, there is a previously-saved state
        else {
        	counterValue = savedInstanceState.getInt(counterKey) ;
        	totalClicks = savedInstanceState.getInt(clicksKey) ;
        	Log.i("SimpleCounter4", "Saved state retrieved with " + totalClicks + " total clicks!!!") ;
        }
        
        // Set up listeners for the buttons and the slider; 
        // Actual listeners are created below as instances of 
        // anonymous classes
        slider.setOnSeekBarChangeListener(sliderListener) ;
        up.setOnClickListener(upListener) ;
        down.setOnClickListener(downListener) ;
        tip.setOnClickListener(tipListener) ;
        
        // Update the initial display
        updateField() ;

		Log.i("SimpleCounterActivity4", "Activity completed onCreate method") ;
        
    }
    
    // This will be called when the app loses focus; save
    // current state
    @Override
    public void onSaveInstanceState(Bundle outState) {
    	// Always do this
    	super.onSaveInstanceState(outState)  ;

    	// Save the counter's state
    	outState.putInt(counterKey, counterValue) ;
    	outState.putInt(clicksKey, totalClicks) ;
    }

    // Listener for the up button
    public View.OnClickListener upListener = new View.OnClickListener() {
		
    	// Called when up button is selected
		@Override
		public void onClick(View v) {
			
			incrementCount() ;
			totalClicks++ ;
			
		}
	} ;
    
	// Listener for the down button   
    public View.OnClickListener downListener = new View.OnClickListener() {
		
		// Called when down Button is selected
    	@Override
		public void onClick(View v) {
			
			decrementCount() ;
			totalClicks++ ;
			
		}
	} ;
  
	// Listener for tip calculator button
	public View.OnClickListener tipListener = new View.OnClickListener() {
		
		// Called with Tip Calc button is selected
		@Override
		public void onClick(View v) {
			
			switchToStateList() ;
		}
		
	};


	
	private void switchToStateList() {
		Intent i = new Intent(SimpleCounterActivity4.this, StateListActivity.class) ;
		startActivityForResult(i,1); ;
	}

	protected void onActivityResult(int code, int result_code, Intent i) {
		super.onActivityResult(code, result_code, i);
		Log.i("SimpleCounterActivity4: ", "Returned result is: " + result_code) ;
	}

	private void incrementCount() {
		
		counterValue++ ;					// increment the current counter
		slider.setProgress(counterValue) ;	// update the position of the slider
		textField.setText(String.format("%d", counterValue)) ;
											// update the content of the edit text widget
		Log.i("SimpleCounterActivity4", "Just incremented the count") ;

	}
	
	protected void decrementCount() {
		
		if (counterValue > 0) {counterValue-- ;} 					// decrement the current counter
		slider.setProgress(counterValue) ;	// update the position of the slider
		textField.setText(String.format("%d", counterValue)) ;
											// update the edit text content		
	}
    
    // The listener for the slider
	public OnSeekBarChangeListener sliderListener = new OnSeekBarChangeListener() {
		
		// Must be here, but do nothing
		@Override
		public void onStopTrackingTouch(SeekBar seekBar) {
			// TODO Auto-generated method stub
			
		}
		
		// Must be here, but do nothing
		@Override
		public void onStartTrackingTouch(SeekBar seekBar) {
			// TODO Auto-generated method stub
			
		}
		
		// Called when slider is changed
		@Override
		public void onProgressChanged(SeekBar seekBar, int x, boolean b) {

			counterValue = slider.getProgress() ;	// get current state (also in x)
			updateField() ;							// update the edit text content
			
		}
	};
	
	protected void updateField() {
		
		// update content of edit text field
		textField.setText(String.format("%d", counterValue)) ;
		
	}
}
