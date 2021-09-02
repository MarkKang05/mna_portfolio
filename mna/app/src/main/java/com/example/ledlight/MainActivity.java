package com.example.ledlight;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import top.defaults.colorpicker.ColorPickerPopup;

public class MainActivity extends AppCompatActivity {

    private TextView textView;
    private Button button;
    private Button btButton;
    private ConnectedThread mConnectedThread;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        textView = findViewById(R.id.textView);
        button = findViewById(R.id.button);
        btButton = findViewById(R.id.bluetooth_button);

        btButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(getApplicationContext(), Bluetooth.class);
                startActivity(intent);
            }
        });

        button.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v) {
                new ColorPickerPopup.Builder(MainActivity.this)
                        .initialColor(Color.RED)
                        .okTitle("Choose")
                        .cancelTitle("Cancel")
                        .showIndicator(true)
                        .showValue(true)
                        .build()
                        .show(v, new ColorPickerPopup.ColorPickerObserver() {
                            @Override
                            public void onColorPicked(int color) {
                                textView.setTextColor(color);
                            }

                            @Override
                            public void onColor(int color, boolean fromUser) {
                                textView.setTextColor(color);
                                int red = Color.red(color);
                                int blue = Color.blue(color);
                                int green = Color.green(color);
                                System.out.println("Red: " + red +"\tGreen: " + green + "\tBlue: " + blue);

                                //if(mConnectedThread != null)
                                    //mConnectedThread.write("testets");


                            }
                        });
            }
        });
    }
}