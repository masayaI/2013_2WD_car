/*
 * Copyright (C) 2012 Utsunomiya University
 * Author: Takeshi Ohkawa
 */

//#define	LOCAL_LOG

#include <string.h>
#include <jni.h>

#ifdef	LOCAL_LOG
#include <android/log.h>
#endif

#include "SS2012FPGA.h"
static CORBA_jp_ac_utsunomiya_is_SS2012FPGA _obj;
static CORBA_Environment * ev;
static CORBA_Environment corba_env;
static CORBA_ORB orb;

JNIEXPORT jstring JNICALL
Java_jp_ac_utsunomiya_is_SS2012FPGA_initialize( JNIEnv* env,
                                                  jobject thiz,
						jstring ior) 
{
	//printf("Hello from JNI");

	char *bytes = (*env)->GetStringUTFChars(env, ior, NULL);

	int argc = 1;
	char* argv_word = "";
	char** argv;
	argv[0] = argv_word;

	orb = (CORBA_ORB)CORBA_ORB_init(&argc, argv, 0, &corba_env);
	ev = &corba_env;

	_obj = (CORBA_jp_ac_utsunomiya_is_SS2012FPGA) CORBA_ORB_string_to_object
		(orb, bytes, &corba_env);


	//char objname[256];
	//sprintf(objname, "%x", &_obj);
	jstring strj = (*env)->NewStringUTF(env, "motor");

	(*env)->ReleaseStringUTFChars(env, ior, bytes);
	return strj;
}

JNIEXPORT void JNICALL
Java_jp_ac_utsunomiya_is_SS2012FPGA_setMotorTorque( JNIEnv* env,
                                                  jobject thiz,
						jint motorID,
						jint maxTorque,
						jint torque )
{
#ifdef	LOCAL_LOG
	//__android_log_write(ANDROID_LOG_DEBUG,"Tag","Test Message : __android_log_write() with ANDROID_LOG_DEBUG");
	__android_log_print(ANDROID_LOG_DEBUG,"SS2012FPGA_jni","Called jni-setMotorTorque %d, %d, %d\r\n", motorID, maxTorque, torque);
	__android_log_print(ANDROID_LOG_DEBUG,"SS2012FPGA_jni","_obj=%x, ev=%x\r\n", _obj, ev);
#endif
  jp_ac_utsunomiya_is_SS2012FPGA_setMotorTorque(_obj, motorID, maxTorque, torque, ev);
}

JNIEXPORT void JNICALL
Java_jp_ac_utsunomiya_is_SS2012FPGA_playAlarmSound( JNIEnv* env,
                                                  jobject thiz)
{
   jp_ac_utsunomiya_is_SS2012FPGA_playAlarmSound(_obj, ev);
	//printf("Hello from JNI:Java_jp_ac_utsunomiya_is_SS2012FPGA_playAlarmSound\r\n");

	//jstring strj = (*env)->NewStringUTF(env, "jp_ac_utsunomiya_is_SS2012FPGA_playAlarmSound");
	//return strj;
}

JNIEXPORT jint JNICALL
Java_jp_ac_utsunomiya_is_SS2012FPGA_getAlarmSwitchState( JNIEnv* env,
                                                  jobject thiz)
{
	return jp_ac_utsunomiya_is_SS2012FPGA_getAlarmSwitchState(_obj, ev);

}

JNIEXPORT void JNICALL
Java_jp_ac_utsunomiya_is_SS2012FPGA_sendIrDAdata( JNIEnv* env,
                                                  jobject thiz,
						jint data)
{
   jp_ac_utsunomiya_is_SS2012FPGA_sendIrDAdata(_obj, data, ev);
}
