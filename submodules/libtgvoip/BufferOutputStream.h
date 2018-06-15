//
// Created by Grishka on 31.05.16.
//

#ifndef LIBTGVOIP_BUFFEROUTPUTSTREAM_H
#define LIBTGVOIP_BUFFEROUTPUTSTREAM_H

#include <stdlib.h>

class CBufferOutputStream{

public:
	CBufferOutputStream(size_t size);
	~CBufferOutputStream();
	void WriteByte(unsigned char byte);
	void WriteInt64(int64_t i);
	void WriteInt32(int32_t i);
	void WriteInt16(int16_t i);
	void WriteBytes(char* bytes, size_t count);
	char* GetBuffer();
	size_t GetLength();
	void Reset();

private:
	void ExpandBufferIfNeeded(size_t need);
	char* buffer;
	size_t size;
	size_t offset;
};


#endif //LIBTGVOIP_BUFFEROUTPUTSTREAM_H
