//
// Created by Grishka on 17.06.16.
//

#ifndef LIBTGVOIP_AUDIOOUTPUT_H
#define LIBTGVOIP_AUDIOOUTPUT_H

#include <stdint.h>
#include "../MediaStreamItf.h"

class CAudioOutput : public CMediaStreamItf{
public:
	virtual ~CAudioOutput();
	virtual void Configure(uint32_t sampleRate, uint32_t bitsPerSample, uint32_t channels)=0;
	virtual bool IsPlaying()=0;
    virtual float GetLevel()=0;
	static CAudioOutput* Create();
	static int32_t GetEstimatedDelay();

#if defined(__ANDROID__)
	static int systemVersion;
#endif
};


#endif //LIBTGVOIP_AUDIOOUTPUT_H
