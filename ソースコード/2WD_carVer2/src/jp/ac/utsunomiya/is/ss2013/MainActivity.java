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

//�Z���T�[
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
		 // SensorManager�̃C���X�^���X���擾����
        mSensorManager = (SensorManager)getSystemService(SENSOR_SERVICE);
        // TextView�̃C���X�^���X���擾����
        txt_x = (TextView) findViewById(R.id.editText1);
        txt_y=(TextView) findViewById(R.id.editText2);
        
        listener = new SampleSensorEventListener();
    }
    
    //SensorManager�̎擾
    @Override
    protected void onResume(){
    	super.onResume();
    	mSensorManager = (SensorManager)getSystemService(SENSOR_SERVICE);
    	sensor  = mSensorManager.getDefaultSensor( Sensor.TYPE_ACCELEROMETER );
    	mSensorManager.registerListener(listener, sensor, SensorManager.SENSOR_DELAY_NORMAL );
    }
    
    //�Z���T�[�I��
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

   
	
	//�l�b�g���[�N�ڑ��{�^��
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
       
    //�I���{�^��
	private View.OnClickListener exitButtonListener = new View.OnClickListener() {
		public void onClick(View v) {
			thisActivity.finish();
		}
    };


    //�Z���T�[�𗘗p
    class SampleSensorEventListener implements SensorEventListener{
		@Override
		public void onSensorChanged(SensorEvent e) {
			if(e.sensor.getType() == Sensor.TYPE_ACCELEROMETER ){
				if(connected){
					txt_x.setText("X:" + (int)e.values[0]);
					txt_y.setText("Y:" + (int)e.values[1]);
					
					//���E�̃��[�^�̐���
					if( temp2 !=(int)e.values[1]){
						temp2=(int)e.values[1];
						if(temp2>=1) {
							int torque = -( temp2*100 ) - 500;
							Log.d("motor", "Left turn torque=" + torque);
							fc.setMotorTorque(1, 1000, torque);//����
						} else if(temp2<=-1) {
							int torque = ( temp2*100 ) -500;
							Log.d("motor", "Right turn torque=" + torque);
							fc.setMotorTorque(0, 1000, torque);//�E��
						} else {
							//��~
							fc.setMotorTorque(0, 1000, 0);
						    fc.setMotorTorque(1, 1000, 0);
						}
					}
					
					//�O�i�E���
					else if( temp1 !=(int)e.values[0]){
						temp1=(int)e.values[0];
						if(temp1<=4){
							fc.setMotorTorque(1, 1000, ( temp1*100 ) - 1000);//����
							fc.setMotorTorque(0, 1000, ( temp1*100 ) - 1000);//�E��
							Log.d("motor", "temp1=" + temp1);
						}
						else if(temp1>=7)
						{
							fc.setMotorTorque(1, 1000, ( temp1*100 ) -100);//����
							fc.setMotorTorque(0, 1000, ( temp1*100 ) -100);//�E��
							Log.d("motor", "temp2=" + temp1);
						}
						else{
							fc.setMotorTorque(1, 1000, 0);//����
							fc.setMotorTorque(0, 1000, 0);//�E��
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
    
    

