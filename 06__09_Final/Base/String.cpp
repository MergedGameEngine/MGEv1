///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _BASE_EXPORT


#include "Type.h"
#include "Base.h"
#include "stdio.h"
#include "string.h"
#include "CRC32.h"


_BASE_API TString::TString() {
	buffer = new unsigned short[1];
	buffer[0] = 0;
	length = 0;
	isBufferLocked = FALSE;
}

//_BASE_API TString::TString(const TString& src) {
//	if (this == &src) {
//		isBufferLocked = FALSE;
//	} else {
//		buffer = src.buffer;
//		length = src.length;
//		isBufferLocked = src.isBufferLocked;
//	}
//}

_BASE_API TString::~TString() {
	if (!isBufferLocked) {
		delete []buffer;
	} else {
		isBufferLocked = FALSE;
	}
}

_BASE_API TString::TString(char ascii) {
	if ( (ascii<0x20) || (ascii>0x7E) ) {
		buffer = new unsigned short[2];
		buffer[0] = ascii;
		buffer[1] = 0;
		length = 1;
	} else {
		buffer = new unsigned short[1];
		buffer[0] = 0;
		length = 0;
	}
	isBufferLocked = FALSE;
}

_BASE_API TString::TString(const char* asciiStr) {
	isBufferLocked = FALSE;
	if (asciiStr!=NULL) {
		int len = 0;
		int i = 0 ;
		for ( i = 0 ; i < 65536 ; i ++ ) {
			if ( (asciiStr[i]<0x1) || (asciiStr[i]>0x7E) ) {
				len = i;
				break;
			}
		}
		buffer = new unsigned short[len + 1];
		for ( i = 0 ; i < len ; i ++ ) {
			buffer[i] = asciiStr[i];
		}
		buffer[len] = 0;
		length = len;
	} else {
		buffer = new unsigned short[1];
		buffer[0] = 0;
		length = 0;
	}
}

_BASE_API TString::TString(const unsigned short* wstr) {
	isBufferLocked = FALSE;
	if (wstr!=NULL) {
		int len = 0;
		for ( int i = 0 ; i <65536 ; i ++ ) {
			if (wstr[i] == 0) {
				len = i;
				break;
			}
		}
		buffer = new unsigned short[len + 1];
		memcpy(buffer, wstr, (len + 1)*sizeof(unsigned short));
		length = len;
	} else {
		buffer = new unsigned short[1];
		buffer[0] = 0;
		length = 0;
	}
}

TString _BASE_API TString::operator + (const TString &src) {
	const unsigned short *srcBuffer = src.buffer;
	unsigned short *descBuffer = new unsigned short[length + src.length + 1];
	memcpy(descBuffer, buffer, length * sizeof(unsigned short));
	unsigned short *mpDescBuffer = &(descBuffer[length]);
	memcpy(mpDescBuffer, src.buffer, (src.length + 1) * sizeof(unsigned short));
	TString desc(descBuffer);
	desc.isBufferLocked = TRUE;
	return desc;
}

TString _BASE_API &TString::operator = (const TString& src) {
	if (this != &src) {
		delete []buffer;
		if (src.isBufferLocked) {
			buffer = src.buffer;
		} else {
			buffer = new unsigned short[src.length + 1];
			memcpy (buffer, src.buffer, (src.length + 1) * sizeof(unsigned short));
		}
		length = src.length;
	}
	isBufferLocked = FALSE;
	return *this;
}

TString _BASE_API &TString::operator += (const TString& src) {
	const unsigned short *srcBuffer = src.buffer;
	unsigned short *descBuffer = new unsigned short[length + src.length + 1];
	memcpy(descBuffer, buffer, length * sizeof(unsigned short));
	unsigned short *mpDescBuffer = &(descBuffer[length]);
	memcpy(mpDescBuffer, src.buffer, (src.length + 1) * sizeof(unsigned short));
	delete []buffer;
	buffer = descBuffer;
	isBufferLocked = FALSE;
	return *this;
}

BOOL32 _BASE_API TString::operator == (const TString &src) {
	return Equals(src);
}

BOOL32 _BASE_API TString::Equals(const TString &src) {
	if (src.length != length) {
		return FALSE;
	}
	const unsigned short *srcBuffer = src.buffer;
	for (int i = 0 ; i < length ; i ++ ) {
		if (buffer[i] != srcBuffer[i]) {
			return FALSE;
		}
	}
	return TRUE;
}
	
const unsigned short _BASE_API *TString::GetBuffer() {
	return buffer;
}

int _BASE_API TString::GetLength() {
	return length;
}

char _BASE_API *TString::GetStringASC() {
	char *desc = new char[length + 1];
	for ( int i = 0 ; i < length ; i ++ ) {
		if ( (buffer[i]<0x0020) || (buffer[i]>0x007E) ) {
			break;
		} else {
			desc[i] = (char)buffer[i];
		}
	}
	desc[length] = 0;
	return desc;
}

unsigned int _BASE_API TString::GetStringASC(char *desc) {
	for ( int i = 0 ; i < length ; i ++ ) {
		if ( (buffer[i]<0x0020) || (buffer[i]>0x007E) ) {
			break;
		} else {
			desc[i] = (char)buffer[i];
		}
	}
	desc[i] = 0;
	return i;
}

char _BASE_API *TString::GetClassName() {
	return "TString";

}

int _BASE_API TString::GetClassCode() {
	return CLSID_TString;
}

int _BASE_API TString::GetHashCode() {
	return (int)CRC32::GetCRC32(buffer, length * sizeof(unsigned short));
}
	
BOOL32 _BASE_API TString::IsInstanceof(const char* className) {
	if (strcmp("TString", className)) {
		return TRUE;
	}
	return FALSE;
}
	
BOOL32 _BASE_API TString::IsEqualto(IObject &obj) {
	if (obj.GetClassCode() == 3) {
		TString& str = (TString&)obj;
		if (str.GetLength() != length) {
			return FALSE;
		}
		const unsigned short *strBuffer = str.GetBuffer();
		for (int i = 0 ; i < length ; i ++ ) {
			if (buffer[i] != strBuffer[i]) {
				return FALSE;
			}
		}
		return TRUE;
	}
	return FALSE;
}

void  _BASE_API TString::Serialize(IIOStream &iio) {
}
	
void  _BASE_API TString::Wait() {
}
	
void  _BASE_API TString::Notify() {
}


int _BASE_API TString::Read(IIOStream &iio, unsigned int count) {
	if ( count > 0 ) {
		delete buffer;
		buffer = new unsigned short[count + 1];
		length = count;
		buffer[length] = 0;
	} else {
		return -1;
	}
	return iio.ReadBuffer(buffer, count, sizeof(unsigned short)); 
}
int _BASE_API TString::Write(IIOStream &iio, unsigned int count) {
	if (count > 0) {
		return iio.WriteBuffer(buffer, count, sizeof(unsigned short)); 
	}
	return -1;
}
void _BASE_API TString::Load(IIOStream &iio) {
	unsigned int count = 0;
	iio.Read(&count, sizeof(unsigned int));
	Read(iio, count);
}
void _BASE_API TString::Store(IIOStream &iio) {
	iio.Write(&length, sizeof(unsigned int));
	Write(iio, length);
}

//TString Substring(int start, int length);

void  _BASE_API TString::Format(const TString formats, ...) {
}
	
int  _BASE_API TString::ToInt32() {
	return 0;
}
	
short  _BASE_API TString::ToInt16() {
	return 0;
}
	
char  _BASE_API TString::ToInt8() {
	return 0;
}
	
unsigned int  _BASE_API TString::ToUInt32() {
	return 0;
}

unsigned short  _BASE_API TString::ToUInt16() {
	return 0;
}

unsigned char  _BASE_API TString::ToUInt8() {
	return 0;
}

float  _BASE_API TString::ToFloat() {
	return 0.0;
}

double _BASE_API  TString::ToDouble() {
	return 0.0;
}
