package com.example.kasok;



import android.app.Activity;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;

import android.widget.TextView;


public class MainActivity extends Activity  {

	private SensorManager       manager;
	private Sensor              sensor;
	private SensorEventListener sample_listener;

    TextView tv_x;
    TextView tv_y;
    TextView tv_z;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        setContentView(R.layout.activity_main);

        tv_x = (TextView) findViewById(R.id.editText1);
        tv_y = (TextView) findViewById(R.id.editText2);
        tv_z = (TextView) findViewById(R.id.editText3);


        sample_listener = new SampleSensorEventListener();
    }
    @Override
    protected void onResume(){
    	super.onResume();
    	manager = (SensorManager)getSystemService(SENSOR_SERVICE);
    	sensor  = manager.getDefaultSensor( Sensor.TYPE_ACCELEROMETER );
    	manager.registerListener(sample_listener, sensor, SensorManager.SENSOR_DELAY_NORMAL );
    }
    @Override
    protected void onPause(){
    	super.onPause();
    	manager.unregisterListener(sample_listener);
    }

    class SampleSensorEventListener implements SensorEventListener{

		@Override
		public void onSensorChanged(SensorEvent e) {
			if(e.sensor.getType() == Sensor.TYPE_ACCELEROMETER ){
				
				String str_x = "X:" + e.values[0];
				tv_x.setText(str_x);				
				
				String str_y = "Y:" + e.values[1];
				tv_y.setText( str_y );
				String str_z = "Z:" + e.values[2];
				tv_z.setText( str_z );

			}
		}

		@Override
		public void onAccuracyChanged(Sensor arg0, int arg1) {
		}

    }

}