package jp.ac.utsunomiya.is.ss2013;



import jp.ac.utsunomiya.is.FPGAController;
import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.SeekBar;
import android.widget.SeekBar.OnSeekBarChangeListener;
import android.widget.TextView;

//センサー
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
//

public class MainActivity extends Activity  {
	private FPGAController fc;
	private EditText editTextIPaddress;
	private Activity thisActivity;
	private SensorManager mSensorManager;
	private Sensor              sensor;
	private SensorEventListener listener;
	TextView mTextView;
	
	

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        thisActivity = this;
        setContentView(R.layout.activity_main);
        this.init();
		Button buttonExit = (Button) findViewById(R.id.buttonExit);
		buttonExit.setOnClickListener(exitButtonListener);

		
		 // SensorManagerのインスタンスを取得する
        mSensorManager = (SensorManager)getSystemService(SENSOR_SERVICE);
        // TextViewのインスタンスを取得する
        mTextView = (TextView) findViewById(R.id.editText1);
        listener = new SampleSensorEventListener();
    }
    
    @Override
    protected void onResume(){
    	super.onResume();
    	mSensorManager = (SensorManager)getSystemService(SENSOR_SERVICE);
    	sensor  = mSensorManager.getDefaultSensor( Sensor.TYPE_ACCELEROMETER );
    	mSensorManager.registerListener(listener, sensor, SensorManager.SENSOR_DELAY_NORMAL );
    }
    
    @Override
    protected void onPause(){
    	super.onPause();
    	mSensorManager.unregisterListener(listener);
    }
    
      
    
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }


    
    
    private void init(){
    	setContentView(R.layout.activity_main);
               
        fc = new FPGAController();
		fc.initialize(new String[]{});

		Button buttonConnect = (Button) findViewById(R.id.buttonConnect);
		buttonConnect.setOnClickListener(connectButtonListener);
		editTextIPaddress = (EditText)findViewById(R.id.editTextIPaddress);
		
    }

   
	
	//ネットワーク接続ボタン
	private boolean connected = false;
    private View.OnClickListener connectButtonListener = new View.OnClickListener() {
		public void onClick(View v) {
			if(connected) return;
			if(editTextIPaddress.getText().toString().equals("")) return;
			connected=true;
			
			Button thisButton = (Button) v;
			thisButton.setText("Connected");
			
			try {
				fc.connect(editTextIPaddress.getText().toString());
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
    };
       
    //終了ボタン
	private View.OnClickListener exitButtonListener = new View.OnClickListener() {
		public void onClick(View v) {
			thisActivity.finish();
		}
    };


    class SampleSensorEventListener implements SensorEventListener{

		@Override
		public void onSensorChanged(SensorEvent e) {
			if(e.sensor.getType() == Sensor.TYPE_ACCELEROMETER ){
				if(connected){
				mTextView.setText("X軸の加速度:" + (int)e.values[0]);
				fc.setMotorTorque(1, 1000, ( (int)e.values[0]*100 ) - 1000);
				fc.setMotorTorque(0, 1000, ( (int)e.values[0]*100 ) - 1000);
				}
			}
		}

		@Override
		public void onAccuracyChanged(Sensor arg0, int arg1) {
		}

    }

}
    
    

