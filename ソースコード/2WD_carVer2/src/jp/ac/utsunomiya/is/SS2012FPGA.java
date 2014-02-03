package jp.ac.utsunomiya.is;


public class SS2012FPGA {
    static {
        System.loadLibrary("RtORB"); // the order is important!
        System.loadLibrary("SS2012FPGA-jni");
    }

    native public String initialize(String ior);
	native public void setMotorTorque(int motorID, int maxTorque, int torque);
	native public void playAlarmSound();
	native public int getAlarmSwitchState();
	native public void sendIrDAdata(int data);
}

