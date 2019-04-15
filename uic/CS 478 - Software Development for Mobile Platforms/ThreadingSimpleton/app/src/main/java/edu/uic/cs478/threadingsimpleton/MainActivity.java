package edu.uic.cs478.threadingsimpleton;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    Button button1, button2 ;
    EditText text1, text2 ;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        button1 = (Button) findViewById(R.id.button1) ;
        button2 = (Button) findViewById(R.id.button2) ;
        text1 = (EditText) findViewById(R.id.editText) ;
        text2 = (EditText) findViewById(R.id.editText2) ;

        button1.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {

                Thread t1 = new Thread(new Runnable() {

                    public void run() {
                        try {
                            Thread.sleep(3000);
                        } catch (InterruptedException e) {
                        }
                        ;

                        // text1.setVisibility(View.VISIBLE);
                        try {
                            Thread.sleep(3000);
                        } catch (InterruptedException e) {
                        }
                        ;

                        //  text1.setVisibility(View.INVISIBLE);


                        Toast.makeText(MainActivity.this, "First toast! ", Toast.LENGTH_LONG).show();

                    }

                });

                t1.start();
            }

        });

        button2.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {

                Toast.makeText(MainActivity.this, "Second toast! ", Toast.LENGTH_LONG).show();

            }
        }) ;
    }
}
