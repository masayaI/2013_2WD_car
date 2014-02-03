package jp.ac.utsunomiya.is;


import jp.go.aist.utils.IORgenerator;
import jp.go.aist.utils.TCPtoUDP;
import jp.go.aist.utils.TransportBridge;
import android.widget.TextView;

public class FPGAController {
	SS2012FPGA ss2012fpga = null;
	TransportBridge bridge = null;
	public TextView textResult[] = new TextView[3];
	public boolean isPlaying = false;

	public String initialize(String[] args) {
		String result = null;

		return result;
	}
	
	public void connect(String ipAddress) {
		String result = null;
		if(ss2012fpga != null) return;
		
		try {
			String ior=null;

			ior = new IORgenerator("jp/ac/utsunomiya/is/SS2012FPGA", "127.0.0.1", "5656").getIORString();
		    System.out.println(ior);

			bridge = new TCPtoUDP(5656, ipAddress, 5656);
			bridge.start();

			ss2012fpga = new jp.ac.utsunomiya.is.SS2012FPGA();
			//ss2012fpga.initialize(ior);
	
			System.out.println("Just before ss2012fpga.initialize(ior)");
			result = ss2012fpga.initialize(ior);
			System.out.println("After init, result="+result);
			
			//ss2012fpga.setMotorTorque(0, 1000, 1000);
			//ss2012fpga.sendIrDAdata(100);
			//result = ss2012fpga.playAlarmSound();
			//System.out.println("After call, result="+result);
		} catch (Exception e) {
		    e.printStackTrace(System.out);
		}
	}
	
	public void disconnect() {
		try{
			//ss2012fpga.disconnect();
		} catch (Exception e) {
			e.printStackTrace(System.out);
		}
	}
	
	public void setMotorTorque(int motorID, int maxTorque, int torque) {
		ss2012fpga.setMotorTorque(motorID, maxTorque, torque);
	}
	
	public void playAlarmSound() {
		ss2012fpga.playAlarmSound();
	}
	
	public int getAlarmSwitchState() {
		return ss2012fpga.getAlarmSwitchState();
	}

}
