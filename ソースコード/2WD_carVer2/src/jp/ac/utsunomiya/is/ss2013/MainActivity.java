package jp.ac.utsunomiya.is.ss2013;



import jp.ac.utsunomiya.is.FPGAController;
import android.os.Bundle;
import android.app.Activity;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

//センサー
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;


public class MainActivity extends Activity  {
	private FPGAController	 	fc;
	private EditText 			editTextIPaddress;
	private Activity			thisActivity;
	private SensorManager 		mSensorManager;
	private Sensor              sensor;
	private SensorEventListener listener;
	private int temp1;
	private int temp2;
	TextView 	txt_x,txt_y;
	

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
        txt_x = (TextView) findViewById(R.id.editText1);
        txt_y=(TextView) findViewById(R.id.editText2);
        
        listener = new SampleSensorEventListener();
    }
    
    //SensorManagerの取得
    @Override
    protected void onResume(){
    	super.onResume();
    	mSensorManager = (SensorManager)getSystemService(SENSOR_SERVICE);
    	sensor  = mSensorManager.getDefaultSensor( Sensor.TYPE_ACCELEROMETER );
    	mSensorManager.registerListener(listener, sensor, SensorManager.SENSOR_DELAY_NORMAL );
    }
    
    //センサー終了
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


    //センサーを利用
    class SampleSensorEventListener implements SensorEventListener{
		@Override
		public void onSensorChanged(SensorEvent e) {
			if(e.sensor.getType() == Sensor.TYPE_ACCELEROMETER ){
				if(connected){
					txt_x.setText("X:" + (int)e.values[0]);
					txt_y.setText("Y:" + (int)e.values[1]);
					
					//左右のモータの制御
					if( temp2 !=(int)e.values[1]){
						temp2=(int)e.values[1];
						if(temp2>=1) {
							int torque = -( temp2*100 ) - 500;
							Log.d("motor", "Left turn torque=" + torque);
							fc.setMotorTorque(1, 1000, torque);//左折
						} else if(temp2<=-1) {
							int torque = ( temp2*100 ) -500;
							Log.d("motor", "Right turn torque=" + torque);
							fc.setMotorTorque(0, 1000, torque);//右折
						} else {
							//停止
							fc.setMotorTorque(0, 1000, 0);
						    fc.setMotorTorque(1, 1000, 0);
						}
					}
					
					//前進・後退
					else if( temp1 !=(int)e.values[0]){
						temp1=(int)e.values[0];
						if(temp1<=4){
							fc.setMotorTorque(1, 1000, ( temp1*100 ) - 1000);//左折
							fc.setMotorTorque(0, 1000, ( temp1*100 ) - 1000);//右折
							Log.d("motor", "temp1=" + temp1);
						}
						else if(temp1>=7)
						{
							fc.setMotorTorque(1, 1000, ( temp1*100 ) -100);//左折
							fc.setMotorTorque(0, 1000, ( temp1*100 ) -100);//右折
							Log.d("motor", "temp2=" + temp1);
						}
						else{
							fc.setMotorTorque(1, 1000, 0);//左折
							fc.setMotorTorque(0, 1000, 0);//右折
						}
					}

						
				}
			}
		}

		@Override
		public void onAccuracyChanged(Sensor arg0, int arg1) {
		}

    }

}
    
    

