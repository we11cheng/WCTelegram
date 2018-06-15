//
// Created by Grishka on 31.05.16.
//

#ifndef LIBTGVOIP_BUFFERINPUTSTREAM_H
#define LIBTGVOIP_BUFFERINPUTSTREAM_H

#include <stdio.h>
#include <stdint.h>

class CBufferInputStream{

public:
	CBufferInputStream(char* data, size_t length);
	~CBufferInputStream();
	void Seek(size_t offset);
	size_t GetLength();
	size_t GetOffset();
	size_t Remaining();
	unsigned char ReadByte();
	int64_t ReadInt64();
	int32_t ReadInt32();
	int16_t ReadInt16();
	int32_t ReadTlLength();
	void ReadBytes(char* to, size_t count);

private:
	void EnsureEnoughRemaining(size_t need);
	char* buffer;
	size_t length;
	size_t offset;
};


#endif //LIBTGVOIP_BUFFERINPUTSTREAM_H
