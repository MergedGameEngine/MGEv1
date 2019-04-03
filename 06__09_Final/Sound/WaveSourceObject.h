///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _WAVESOURCEOBJECT_H_
#define _WAVESOURCEOBJECT_H_

extern "C" class _SOUND_API TWaveSourceObject : public IObject {
public:
	TWaveSourceObject();
	virtual ~TWaveSourceObject();
public:
	ALuint		*uiBuffers;
	unsigned short	numBuffers;
	ALuint		uiSource;  
//	ALint		iState;

public:
	void GenBuffers(unsigned short num);
	void GenBuffer();
	void GenSource();
	void BufferData(ALenum format, const ALvoid* data, ALsizei size, ALsizei freq);
	void BufferData(unsigned short idx, ALenum format, const ALvoid* data, ALsizei size, ALsizei freq);
	void QueueBuffer(unsigned short idx);
	void Play();
	void Stop();
	ALint GetIntegerParameter(ALenum param);
	void UnqueueBuffers();
	void UnqueueBuffer(unsigned short idx);
	void SetIntegerParameter(ALenum param, ALint value);
	void DeleteSources();
	void DeleteBuffers();

	void AttachBuffer();

public:
	virtual char* GetClassName();
	virtual int GetClassCode();
	virtual int GetHashCode();
	virtual BOOL32 IsInstanceof(const char* className);
	virtual BOOL32 IsEqualto(IObject &obj);
	virtual void Serialize(IIOStream &iio);
	virtual void Wait();
	virtual void Notify();
};

#endif