//
// Created by Grishka on 13.09.16.
//

#ifndef LIBTGVOIP_AUDIOOUTPUTANDROID_H
#define LIBTGVOIP_AUDIOOUTPUTANDROID_H

#include <jni.h>
#include "../../audio/AudioOutput.h"

class CAudioOutputAndroid : public CAudioOutput{

public:

	CAudioOutputAndroid();
	virtual ~CAudioOutputAndroid();
	virtual void Configure(uint32_t sampleRate, uint32_t bitsPerSample, uint32_t channels);
	virtual void Start();
	virtual void Stop();
	virtual bool IsPlaying() override;
	virtual float GetLevel() override;
	void HandleCallback(JNIEnv* env, jbyteArray buffer);
	static jmethodID initMethod;
	static jmethodID releaseMethod;
	static jmethodID startMethod;
	static jmethodID stopMethod;
	static jclass jniClass;

private:
	jobject javaObject;
	bool running;

};


#endif //LIBTGVOIP_AUDIOOUTPUTANDROID_H
