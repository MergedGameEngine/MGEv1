///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _BASE_IMPORT
#define _SOUND_EXPORT

#include "string.h"
#include "ALee.h"
#undef GetClassName
#include "..\Base\Type.h"
#include "..\Base\Base.h"

#undef _ARRAY_API
#define _ARRAY_API _SOUND_API
#include "WaveDataObject.hpp"

_SOUND_API TWaveDataObject::TWaveDataObject() {
	ulRIFFSize		=	0;

	ulChunkSize		=	0;	//	==	0x10
	usFormatTag		=	0;	//	Begin FMT
	usChannels		=	0;
	ulSamplesPerSec	=	0;
	ulAvgBytesPerSec	=	0;
	usBlockAlign	=	0;
	usBitsPerSample	=	0;	//	End FMT

	ulDataSize		=	0;
	buffer			=	NULL;
	
	ulListSize		=	0;
	listBuffer		=	NULL;
}
_SOUND_API TWaveDataObject::~TWaveDataObject() {
	if ( buffer != NULL ) {
		delete buffer;
	}
	if ( listBuffer != NULL ) {
		delete listBuffer;
	}
}

char _SOUND_API *TWaveDataObject::GetClassName() {
	return "TWaveDataObject";
}
int _SOUND_API TWaveDataObject::GetClassCode() {
	return CLSID_TWaveDataObject;
}
int _SOUND_API TWaveDataObject::GetHashCode() {
	return 1;
}
BOOL32 _SOUND_API TWaveDataObject::IsInstanceof(const char* className) {
	if ( strcmp("TWaveDataObject", className) == 0 ) {
		return TRUE;
	}
	if ( strcmp("IObject", className) == 0 ) {
		return TRUE;
	}
	return FALSE;
}
BOOL32 _SOUND_API TWaveDataObject::IsEqualto(IObject &obj) {
	return FALSE;
}
void _SOUND_API TWaveDataObject::Serialize(IIOStream &iio) {
	if ( iio.GetLoadStore() == IIOStream::load ) {
		iio.Read(&ulRIFF, sizeof(unsigned long));
		if ( ulRIFF == 0x46464952 ) {
			iio.SetEndian(IIOStream::little_endian);
		} else if ( ulRIFF == 0x52494646 ) {
			iio.SetEndian(IIOStream::big_endian);
		} else {
			return;
		}
		iio.Read(&ulRIFFSize, sizeof(unsigned long));
		iio.ReadBuffer(szWAVE, 4, sizeof(char));szWAVE[4] = 0;
		iio.ReadBuffer(szFormatName, 4, sizeof(char));szFormatName[4] = 0;//	FORMAT chunk
		iio.Read(&ulChunkSize, sizeof(unsigned long));
		iio.Read(&usFormatTag, sizeof(unsigned short));
		iio.Read(&usChannels, sizeof(unsigned short));
		iio.Read(&ulSamplesPerSec, sizeof(unsigned long));
		iio.Read(&ulAvgBytesPerSec, sizeof(unsigned long));
		iio.Read(&usBlockAlign, sizeof(unsigned short));
		iio.Read(&usBitsPerSample, sizeof(unsigned short));
		iio.ReadBuffer(szDataName, 4, sizeof(char));szDataName[4] = 0;//	DATA chunk
		iio.Read(&ulDataSize, sizeof(unsigned long));
		buffer = new unsigned char[ulDataSize];
		iio.ReadBuffer(buffer, ulDataSize / ( usBitsPerSample / 8 ), usBitsPerSample / 8);
		iio.ReadBuffer(szListName, 4, sizeof(char));szListName[4] = 0;//	LIST chunk
		if ( iio.IsEoF() == FALSE ) {
			iio.Read(&ulListSize, sizeof(unsigned long));
			listBuffer = new unsigned char[ulListSize];
			iio.ReadBuffer(listBuffer, ulListSize, sizeof(char));
		} else {
			ulListSize = 0;
			listBuffer = NULL;
		}
	} else {
		iio.SetEndian(IIOStream::little_endian);
		iio.WriteBuffer("RIFF", 4, sizeof(char));
		iio.Write(&ulRIFFSize, sizeof(unsigned long));
		iio.WriteBuffer("WAVE", 4, sizeof(char));
		iio.WriteBuffer("fmt ", 4, sizeof(char));ulChunkSize = 0x10;//	FORMAT chunk
		iio.Write(&ulChunkSize, sizeof(unsigned long));
		iio.Write(&usFormatTag, sizeof(unsigned short));
		iio.Write(&usChannels, sizeof(unsigned short));
		iio.Write(&ulSamplesPerSec, sizeof(unsigned long));
		iio.Write(&ulAvgBytesPerSec, sizeof(unsigned long));
		iio.Write(&usBlockAlign, sizeof(unsigned short));
		iio.Write(&usBitsPerSample, sizeof(unsigned short));
		iio.WriteBuffer("data", 4, sizeof(char));	//	DATA chunk
		iio.Write(&ulDataSize, sizeof(unsigned long));
		iio.WriteBuffer(buffer, ulDataSize / ( usBitsPerSample / 8 ), usBitsPerSample / 8);
		if ( ulListSize != 0 ) {
			iio.WriteBuffer("LIST", 4, sizeof(char));	//	LIST chunk
			iio.Write(&ulListSize, sizeof(unsigned long));
			iio.WriteBuffer(listBuffer, ulListSize, sizeof(char));
		}
	}
}
void _SOUND_API TWaveDataObject::Wait() {
}
void _SOUND_API TWaveDataObject::Notify() {
}

unsigned short _SOUND_API TWaveDataObject::GetFormatTag() {
	return usFormatTag;
}
int _SOUND_API TWaveDataObject::GetOpenALFormat() {
	int fmt = -1;
	if ( ( usChannels == 1 ) && ( usBitsPerSample == 8 ) ) {
		fmt = AL_FORMAT_MONO8;
	}
	if ( ( usChannels == 1 ) && ( usBitsPerSample == 16 ) ) {
		fmt = AL_FORMAT_MONO16;
	}
	if ( ( usChannels == 2 ) && ( usBitsPerSample == 8 ) ) {
		fmt = AL_FORMAT_STEREO8;
	}
	if ( ( usChannels == 2 ) && ( usBitsPerSample == 16 ) ) {
		fmt = AL_FORMAT_STEREO16;
	}
	if ( ( usChannels == 4 ) && ( usBitsPerSample == 16 ) ) {
		fmt = palGetEnumValue("AL_FORMAT_QUAD16");
	}
	return fmt;
}
unsigned short _SOUND_API TWaveDataObject::GetNumChannels() {
	return usChannels;
}
unsigned int _SOUND_API TWaveDataObject::GetFrequency() {
	return (unsigned int)ulSamplesPerSec;
}
unsigned int _SOUND_API TWaveDataObject::GetAverageBytesPerSecond() {
	return (unsigned int)ulAvgBytesPerSec;
}
unsigned short _SOUND_API TWaveDataObject::GetNumBlockAlign() {
	return usBlockAlign;
}
unsigned short _SOUND_API TWaveDataObject::GetBitsPerSample() {
	return usBitsPerSample;
}

const void _SOUND_API *TWaveDataObject::GetDataBuffer() {
	return buffer;
}
unsigned int _SOUND_API TWaveDataObject::GetDataSize() {
	return ulDataSize;
}

const void _SOUND_API *TWaveDataObject::GetListBuffer() {
	return listBuffer;
}
