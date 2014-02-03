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

public class MainActivity extends Activity {
	private FPGAController fc;
	private EditText editTextIPaddress;
	private Activity thisActivity;
	
	private SeekBar seekBar;
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        thisActivity = this;
        setContentView(R.layout.activity_main);
        this.init();
		Button buttonExit = (Button) findViewById(R.id.buttonExit);
		buttonExit.setOnClickListener(exitButtonListener);
		
		View changeButton1 = this.findViewById(R.id.button1);   
	    changeButton1.setOnClickListener(buttonListener1);
	    
	    View changeButton2 = this.findViewById(R.id.button2);   
	    changeButton2.setOnClickListener(buttonListener2);
		
	    View changeButton3 = this.findViewById(R.id.button3);   
	    changeButton3.setOnClickListener(buttonListener3);
	    
		seekBar = (SeekBar) findViewById(R.id.seekBar1); 
		
		seekBar.setOnSeekBarChangeListener(
        		new OnSeekBarChangeListener(){
        			public void onProgressChanged(SeekBar seekBar,int progress, boolean fromUser){
        				// ツマミをドラッグしたときに呼ばれる
        				}
        			public void onStartTrackingTouch(SeekBar seekBar){
        				// ツマミに触れたときに呼ばれる
        				}
        			public void onStopTrackingTouch(SeekBar seekBar){
        				// ツマミを離したときに呼ばれる
        				}
        			}
        		);
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

    //左折ボタン
    private View.OnClickListener buttonListener1 = new View.OnClickListener(){
    	public int f=0;
    	public int x;
    	public void onClick(View v){
    		Button thisButton = (Button) v;
    		if(f==1){
    			thisButton.setText("　停止　");
    			x=seekBar.getProgress();
    			if(connected){
    			fc.setMotorTorque(0, 1000, x-1000);
    			}
    			f=0;
    		}else{
    			thisButton.setText("　左折　");
    			if(connected){
    			fc.setMotorTorque(0, 1000, 0);//停止
    			}
    			f=1;
    		}
    	}
		
    };
    
    //右折ボタン
	private View.OnClickListener buttonListener2 = new View.OnClickListener(){
		public int f=0;
		public int x;
		public void onClick(View v){
			Button thisButton = (Button) v;
			if(f==1){
				thisButton.setText("　停止　");
				x=seekBar.getProgress();
				if(connected){
					fc.setMotorTorque(1, 1000, x-1000);
				}
				f=0;
			}else{
				thisButton.setText(" 右折　");
				if(connected){
					fc.setMotorTorque(1, 1000, 0);//停止
				}
				f=1;
			}
		}
	
	};
	
	//アクセルボタン
	private View.OnClickListener buttonListener3 = new View.OnClickListener(){
		public int f=0;
		public int x;
		public void onClick(View v){
			Button thisButton = (Button) v;
			if(f==1){
				thisButton.setText("　停止　");
				x=seekBar.getProgress();
				if(connected){
					fc.setMotorTorque(1, 1000, x-1000);
					fc.setMotorTorque(0, 1000, x-1000);
					
				}
				f=0;
			}else{
				thisButton.setText("アクセル");
				if(connected){
					fc.setMotorTorque(1, 1000, 0);//停止
					fc.setMotorTorque(0, 1000, 0);
				}
				f=1;
			}
		}
	
	};
	
	
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
 
  
}
