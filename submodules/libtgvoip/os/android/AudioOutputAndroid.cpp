//
// Created by Grishka on 13.09.16.
//

#include "AudioOutputAndroid.h"
#include <stdio.h>
#include "../../logging.h"

extern JavaVM* sharedJVM;

jmethodID CAudioOutputAndroid::initMethod;
jmethodID CAudioOutputAndroid::releaseMethod;
jmethodID CAudioOutputAndroid::startMethod;
jmethodID CAudioOutputAndroid::stopMethod;
jclass CAudioOutputAndroid::jniClass;

CAudioOutputAndroid::CAudioOutputAndroid(){
	JNIEnv* env=NULL;
	bool didAttach=false;
	sharedJVM->GetEnv((void**) &env, JNI_VERSION_1_6);
	if(!env){
		sharedJVM->AttachCurrentThread(&env, NULL);
		didAttach=true;
	}

	jmethodID ctor=env->GetMethodID(jniClass, "<init>", "(J)V");
	jobject obj=env->NewObject(jniClass, ctor, (jlong)(intptr_t)this);
	javaObject=env->NewGlobalRef(obj);

	if(didAttach){
		sharedJVM->DetachCurrentThread();
	}
	running=false;
}

CAudioOutputAndroid::~CAudioOutputAndroid(){
	JNIEnv* env=NULL;
	bool didAttach=false;
	sharedJVM->GetEnv((void**) &env, JNI_VERSION_1_6);
	if(!env){
		sharedJVM->AttachCurrentThread(&env, NULL);
		didAttach=true;
	}

	env->CallVoidMethod(javaObject, releaseMethod);
	env->DeleteGlobalRef(javaObject);
	javaObject=NULL;

	if(didAttach){
		sharedJVM->DetachCurrentThread();
	}
}

void CAudioOutputAndroid::Configure(uint32_t sampleRate, uint32_t bitsPerSample, uint32_t channels){
	JNIEnv* env=NULL;
	bool didAttach=false;
	sharedJVM->GetEnv((void**) &env, JNI_VERSION_1_6);
	if(!env){
		sharedJVM->AttachCurrentThread(&env, NULL);
		didAttach=true;
	}

	env->CallVoidMethod(javaObject, initMethod, sampleRate, bitsPerSample, channels, 960*2);

	if(didAttach){
		sharedJVM->DetachCurrentThread();
	}
}

void CAudioOutputAndroid::Start(){
	JNIEnv* env=NULL;
	bool didAttach=false;
	sharedJVM->GetEnv((void**) &env, JNI_VERSION_1_6);
	if(!env){
		sharedJVM->AttachCurrentThread(&env, NULL);
		didAttach=true;
	}

	env->CallVoidMethod(javaObject, startMethod);

	if(didAttach){
		sharedJVM->DetachCurrentThread();
	}
	running=true;
}

void CAudioOutputAndroid::Stop(){
	running=false;
	JNIEnv* env=NULL;
	bool didAttach=false;
	sharedJVM->GetEnv((void**) &env, JNI_VERSION_1_6);
	if(!env){
		sharedJVM->AttachCurrentThread(&env, NULL);
		didAttach=true;
	}

	env->CallVoidMethod(javaObject, stopMethod);

	if(didAttach){
		sharedJVM->DetachCurrentThread();
	}
}

void CAudioOutputAndroid::HandleCallback(JNIEnv* env, jbyteArray buffer){
	if(!running)
		return;
	unsigned char* buf=(unsigned char*) env->GetByteArrayElements(buffer, NULL);
	size_t len=(size_t) env->GetArrayLength(buffer);
	InvokeCallback(buf, len);
	env->ReleaseByteArrayElements(buffer, (jbyte *) buf, 0);
}


bool CAudioOutputAndroid::IsPlaying(){
	return false;
}

float CAudioOutputAndroid::GetLevel(){
	return 0;
}
