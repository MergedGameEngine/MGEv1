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
#include "WaveSourceObject.hpp"

_SOUND_API TWaveSourceObject::TWaveSourceObject() {
	uiBuffers = NULL;
	numBuffers = 0;
	uiSource = 0xFFFFFFFF;  
}
_SOUND_API TWaveSourceObject::~TWaveSourceObject() {
	if ( uiBuffers != NULL ) {
		delete uiBuffers;
	}
}

char _SOUND_API *TWaveSourceObject::GetClassName() {
	return "TWaveSourceObject";
}
int _SOUND_API TWaveSourceObject::GetClassCode() {
	return CLSID_TWaveSourceObject;
}
int _SOUND_API TWaveSourceObject::GetHashCode() {
	return 1;
}
BOOL32 _SOUND_API TWaveSourceObject::IsInstanceof(const char* className) {
	if ( strcmp("TWaveSourceObject", className) == 0 ) {
		return TRUE;
	}
	if ( strcmp("IObject", className) == 0 ) {
		return TRUE;
	}
	return FALSE;
}
BOOL32 _SOUND_API TWaveSourceObject::IsEqualto(IObject &obj) {
	return FALSE;
}
void _SOUND_API TWaveSourceObject::Serialize(IIOStream &iio) {
}
void _SOUND_API TWaveSourceObject::Wait() {
}
void _SOUND_API TWaveSourceObject::Notify() {
}

void _SOUND_API TWaveSourceObject::GenBuffers(unsigned short num) {
	uiBuffers = new ALuint[num];
	numBuffers = num;
	palGenBuffers( num, uiBuffers );
}
void _SOUND_API TWaveSourceObject::GenBuffer() {
	uiBuffers = new ALuint[1];
	numBuffers = 1;
	palGenBuffers( 1, uiBuffers );
}
void _SOUND_API TWaveSourceObject::GenSource() {
    palGenSources( 1, &uiSource );
}
void _SOUND_API TWaveSourceObject::BufferData(ALenum format, const ALvoid* data, ALsizei size, ALsizei freq) {
	palBufferData(uiBuffers[0], format, data, size, freq);
}
void _SOUND_API TWaveSourceObject::BufferData(unsigned short idx, ALenum format, const ALvoid* data, ALsizei size, ALsizei freq) {
	if ( idx < numBuffers ) {
		palBufferData(uiBuffers[idx], format, data, size, freq);
	}
}
void _SOUND_API TWaveSourceObject::QueueBuffer(unsigned short idx) {
	if ( idx < numBuffers ) {
		palSourceQueueBuffers(uiSource, 1, &uiBuffers[idx]);
	}
}
void _SOUND_API TWaveSourceObject::Play() {
	palSourcePlay(uiSource);
}
void _SOUND_API TWaveSourceObject::Stop() {
	palSourceStop(uiSource);
}
ALint _SOUND_API TWaveSourceObject::GetIntegerParameter(ALenum param) {
	ALint value = 0;
	palGetSourcei(uiSource, param, &value);
	return value;
}
void _SOUND_API TWaveSourceObject::UnqueueBuffers() {
	palSourceUnqueueBuffers(uiSource, numBuffers, uiBuffers);
}
void _SOUND_API TWaveSourceObject::UnqueueBuffer(unsigned short idx) {
	if ( idx < numBuffers ) {
		palSourceUnqueueBuffers(uiSource, 1, &uiBuffers[idx]);
	}
}
void _SOUND_API TWaveSourceObject::SetIntegerParameter(ALenum param, ALint value) {
	palSourcei(uiSource, param, value);
}
void _SOUND_API TWaveSourceObject::DeleteSources() {
	palDeleteSources( 1, &uiSource );
}
void _SOUND_API TWaveSourceObject::DeleteBuffers() {
	palDeleteBuffers( numBuffers, uiBuffers );
	numBuffers = 0;
	delete []uiBuffers;
	uiBuffers = NULL;
}

void _SOUND_API TWaveSourceObject::AttachBuffer() {
	alSourcei( uiSource, AL_BUFFER, uiBuffers[0] );
}
