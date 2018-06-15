//
// Created by Grishka on 19.06.16.
//

#ifndef LIBTGVOIP_AUDIOOUTPUTAUDIOUNIT_H
#define LIBTGVOIP_AUDIOOUTPUTAUDIOUNIT_H

#include <AudioUnit/AudioUnit.h>
#include "../../audio/AudioOutput.h"

class CAudioUnitIO;

class CAudioOutputAudioUnit : public CAudioOutput{
public:
	CAudioOutputAudioUnit(CAudioUnitIO* io);
	virtual ~CAudioOutputAudioUnit();
	virtual void Configure(uint32_t sampleRate, uint32_t bitsPerSample, uint32_t channels);
	virtual bool IsPhone();
	virtual void EnableLoudspeaker(bool enabled);
	virtual void Start();
	virtual void Stop();
	virtual bool IsPlaying();
    virtual float GetLevel();
	void HandleBufferCallback(AudioBufferList* ioData);

private:
	bool isPlaying;
	unsigned char remainingData[10240];
	size_t remainingDataSize;
	CAudioUnitIO* io;
    float level;
    int16_t absMax;
    int count;
};


#endif //LIBTGVOIP_AUDIOOUTPUTAUDIOUNIT_H
