//
// Created by Grishka on 19.06.16.
//

#ifndef LIBTGVOIP_AUDIOOUTPUTOPENSLES_H
#define LIBTGVOIP_AUDIOOUTPUTOPENSLES_H

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

#include "../../audio/AudioOutput.h"

class CAudioOutputOpenSLES : public CAudioOutput{
public:
	CAudioOutputOpenSLES();
	virtual ~CAudioOutputOpenSLES();
	virtual void Configure(uint32_t sampleRate, uint32_t bitsPerSample, uint32_t channels);
	virtual bool IsPhone();
	virtual void EnableLoudspeaker(bool enabled);
	virtual void Start();
	virtual void Stop();
	virtual bool IsPlaying();
	virtual float GetLevel();

	static void SetNativeBufferSize(int size);
	static int nativeBufferSize;

private:
	static void BufferCallback(SLAndroidSimpleBufferQueueItf bq, void *context);
	void HandleSLCallback();
	SLEngineItf slEngine;
	SLObjectItf slPlayerObj;
	SLObjectItf slOutputMixObj;
	SLPlayItf slPlayer;
	SLAndroidSimpleBufferQueueItf slBufferQueue;
	int16_t* buffer;
	int16_t* nativeBuffer;
	bool stopped;
	unsigned char remainingData[10240];
	size_t remainingDataSize;
};


#endif //LIBTGVOIP_AUDIOOUTPUTANDROID_H
