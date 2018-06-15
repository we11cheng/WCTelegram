//
// Created by Grishka on 31.05.16.
//

#include "BufferOutputStream.h"
#include <string.h>

CBufferOutputStream::CBufferOutputStream(size_t size){
	buffer=(char*) malloc(size);
	offset=0;
	this->size=size;
}

CBufferOutputStream::~CBufferOutputStream(){
	free(buffer);
}

void CBufferOutputStream::WriteByte(unsigned char byte){
	this->ExpandBufferIfNeeded(1);
	buffer[offset++]=byte;
}

void CBufferOutputStream::WriteInt32(int32_t i){
	this->ExpandBufferIfNeeded(4);
	buffer[offset+3]=(char)((i >> 24) & 0xFF);
	buffer[offset+2]=(char)((i >> 16) & 0xFF);
	buffer[offset+1]=(char)((i >> 8) & 0xFF);
	buffer[offset]=(char)(i & 0xFF);
	offset+=4;
}

void CBufferOutputStream::WriteInt64(int64_t i){
	this->ExpandBufferIfNeeded(8);
	buffer[offset+7]=(char)((i >> 56) & 0xFF);
	buffer[offset+6]=(char)((i >> 48) & 0xFF);
	buffer[offset+5]=(char)((i >> 40) & 0xFF);
	buffer[offset+4]=(char)((i >> 32) & 0xFF);
	buffer[offset+3]=(char)((i >> 24) & 0xFF);
	buffer[offset+2]=(char)((i >> 16) & 0xFF);
	buffer[offset+1]=(char)((i >> 8) & 0xFF);
	buffer[offset]=(char)(i & 0xFF);
	offset+=8;
}

void CBufferOutputStream::WriteInt16(int16_t i){
	this->ExpandBufferIfNeeded(2);
	buffer[offset+1]=(char)((i >> 8) & 0xFF);
	buffer[offset]=(char)(i & 0xFF);
	offset+=2;
}

void CBufferOutputStream::WriteBytes(char *bytes, size_t count){
	this->ExpandBufferIfNeeded(count);
	memcpy(buffer+offset, bytes, count);
	offset+=count;
}

char *CBufferOutputStream::GetBuffer(){
	return buffer;
}

size_t CBufferOutputStream::GetLength(){
	return offset;
}

void CBufferOutputStream::ExpandBufferIfNeeded(size_t need){
	if(offset+need>size){
		if(need<1024){
			buffer=(char *) realloc(buffer, size+1024);
			size+=1024;
		}else{
			buffer=(char *) realloc(buffer, size+need);
			size+=need;
		}
	}
}


void CBufferOutputStream::Reset(){
	offset=0;
}

