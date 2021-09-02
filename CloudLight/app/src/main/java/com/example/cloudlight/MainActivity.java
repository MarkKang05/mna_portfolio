package com.example.cloudlight;

import androidx.appcompat.app.AppCompatActivity;
import androidx.constraintlayout.widget.ConstraintLayout;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.content.Intent;
import android.content.res.ColorStateList;
import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.Toast;

import com.google.android.material.floatingactionbutton.FloatingActionButton;

import java.nio.charset.StandardCharsets;

import app.akexorcist.bluetotohspp.library.BluetoothSPP;
import app.akexorcist.bluetotohspp.library.BluetoothState;
import app.akexorcist.bluetotohspp.library.DeviceList;

public class MainActivity extends AppCompatActivity {

    private final String AppName = "CloudApp";
    private LinearLayout location1;
    private LinearLayout location2;
    private LinearLayout location3;
    private LinearLayout location4;
    private ImageView image_location1;
    private ImageView image_location2;
    private ImageView image_location3;
    private ImageView image_location4;
    private FloatingActionButton bluetoothBtn;
    private BluetoothSPP bt;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        location1 = findViewById(R.id.loc1);
        location2 = findViewById(R.id.loc2);
        location3 = findViewById(R.id.loc3);
        location4 = findViewById(R.id.loc4);

        image_location1 = findViewById(R.id.img_loc1);
        image_location2 = findViewById(R.id.img_loc2);
        image_location3 = findViewById(R.id.img_loc3);
        image_location4 = findViewById(R.id.img_loc4);


        bluetoothBtn = findViewById(R.id.bluetooth_btn);
        bt = new BluetoothSPP(this);

        View.OnClickListener clickListener = new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                switch (view.getId()){
                    case R.id.loc1:
                        sendBT("1");
                        image_location1.setColorFilter(Color.RED);
                        image_location2.setColorFilter(Color.BLACK);
                        image_location3.setColorFilter(Color.BLACK);
                        image_location4.setColorFilter(Color.BLACK);
                        Log.d(AppName, "loc1");
                        break;
                    case R.id.loc2:
                        sendBT("2");
                        image_location1.setColorFilter(Color.BLACK);
                        image_location2.setColorFilter(Color.RED);
                        image_location3.setColorFilter(Color.BLACK);
                        image_location4.setColorFilter(Color.BLACK);
                        Log.d(AppName, "loc2");
                        break;
                    case R.id.loc3:
                        sendBT("3");
                        image_location1.setColorFilter(Color.BLACK);
                        image_location2.setColorFilter(Color.BLACK);
                        image_location3.setColorFilter(Color.RED);
                        image_location4.setColorFilter(Color.BLACK);
                        Log.d(AppName, "loc3");
                        break;
                    case R.id.loc4:
                        sendBT("4");
                        image_location1.setColorFilter(Color.BLACK);
                        image_location2.setColorFilter(Color.BLACK);
                        image_location3.setColorFilter(Color.BLACK);
                        image_location4.setColorFilter(Color.RED);
                        Log.d(AppName, "loc4");
                        break;
                    default:
                        image_location1.setColorFilter(Color.GREEN);
                        break;


                }
            }
        };


        if (!bt.isBluetoothAvailable()) { //블루투스 사용 불가
            Toast.makeText(getApplicationContext()
                    , "Bluetooth is not available"
                    , Toast.LENGTH_SHORT).show();
            finish();
        }

        bt.setOnDataReceivedListener(new BluetoothSPP.OnDataReceivedListener() { //데이터 수신
            public void onDataReceived(byte[] data, String message) {
                Toast.makeText(MainActivity.this, message, Toast.LENGTH_SHORT).show();
            }
        });

        bt.setBluetoothConnectionListener(new BluetoothSPP.BluetoothConnectionListener() { //연결됐을 때
            public void onDeviceConnected(String name, String address) {
                Toast.makeText(getApplicationContext()
                        , "Connected to " + name + "\n" + address
                        , Toast.LENGTH_SHORT).show();
            }

            public void onDeviceDisconnected() { //연결해제
                Toast.makeText(getApplicationContext()
                        , "Connection lost", Toast.LENGTH_SHORT).show();
            }

            public void onDeviceConnectionFailed() { //연결실패
                Toast.makeText(getApplicationContext()
                        , "Unable to connect", Toast.LENGTH_SHORT).show();
            }
        });

        bluetoothBtn.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                if (bt.getServiceState() == BluetoothState.STATE_CONNECTED) {
                    bt.disconnect();
                } else {
                    Intent intent = new Intent(getApplicationContext(), DeviceList.class);
                    startActivityForResult(intent, BluetoothState.REQUEST_CONNECT_DEVICE);
                }
            }
        });

        location1.setOnClickListener(clickListener);
        location2.setOnClickListener(clickListener);
        location3.setOnClickListener(clickListener);
        location4.setOnClickListener(clickListener);

        bluetoothBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if (bt.getServiceState() == BluetoothState.STATE_CONNECTED) {
                    bt.disconnect();
                } else {
                    Intent intent = new Intent(getApplicationContext(), DeviceList.class);
                    startActivityForResult(intent, BluetoothState.REQUEST_CONNECT_DEVICE);
                }
            }
        });

    }





    public void onDestroy() {
        super.onDestroy();
        bt.stopService();
    }

    public void onStart() {
        super.onStart();
        if (!bt.isBluetoothEnabled()) { //
            Intent intent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(intent, BluetoothState.REQUEST_ENABLE_BT);
        } else {
            if (!bt.isServiceAvailable()) {
                bt.setupService();
                bt.startService(BluetoothState.DEVICE_OTHER);
                setup();
            }
        }
    }

    public void setup() {
//        bluetoothBtn.setOnClickListener(new View.OnClickListener() {
//            public void onClick(View v) {
////                bt.send("255.255.255", false);
//            }
//        });
    }

    public void sendBT(String text){
        bt.send(text.getBytes(StandardCharsets.UTF_8), false);
        bt.send(",".getBytes(StandardCharsets.UTF_8), false);
    }


    public String toHexColor(int color){
        String hexColor = String.format("#%06X", (0xFFFFFF & color));

        return hexColor;
    }


    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == BluetoothState.REQUEST_CONNECT_DEVICE) {
            if (resultCode == Activity.RESULT_OK)
                bt.connect(data);
        } else if (requestCode == BluetoothState.REQUEST_ENABLE_BT) {
            if (resultCode == Activity.RESULT_OK) {
                bt.setupService();
                bt.startService(BluetoothState.DEVICE_OTHER);
                setup();
            } else {
                Toast.makeText(getApplicationContext()
                        , "Bluetooth was not enabled."
                        , Toast.LENGTH_SHORT).show();
                finish();
            }
        }
    }


}