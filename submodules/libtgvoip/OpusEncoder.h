//
// Created by Grishka on 17.06.16.
//

#ifndef LIBTGVOIP_OPUSENCODER_H
#define LIBTGVOIP_OPUSENCODER_H


#include "MediaStreamItf.h"
#include "opus.h"
#include "threading.h"
#include "BlockingQueue.h"
#include "BufferPool.h"
#include "EchoCanceller.h"

#include <stdint.h>

class COpusEncoder : public CMediaStreamItf{
public:
	COpusEncoder(CMediaStreamItf* source);
	virtual ~COpusEncoder();
	virtual void Start();
	virtual void Stop();
	void SetBitrate(uint32_t bitrate);
	void SetEchoCanceller(CEchoCanceller* aec);
	void SetOutputFrameDuration(uint32_t duration);
	void SetPacketLoss(int percent);
	uint32_t GetBitrate();

private:
	static size_t Callback(unsigned char* data, size_t len, void* param);
	static void* StartThread(void* arg);
	void RunThread();
	void Encode(unsigned char* data, size_t len);
	CMediaStreamItf* source;
	OpusEncoder* enc;
	unsigned char buffer[4096];
	uint32_t requestedBitrate;
	uint32_t currentBitrate;
	tgvoip_thread_t thread;
	CBlockingQueue queue;
	CBufferPool bufferPool;
	CEchoCanceller* echoCanceller;
	int complexity;
	bool running;
	uint32_t frameDuration;
};


#endif //LIBTGVOIP_OPUSENCODER_H
