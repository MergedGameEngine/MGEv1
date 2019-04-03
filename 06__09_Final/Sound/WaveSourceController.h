///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _WAVESOURCECONTROLLER_H_
#define _WAVESOURCECONTROLLER_H_

extern "C" class _SOUND_API TWaveSourceController : public IObject {
public:
	TWaveSourceController();
	virtual ~TWaveSourceController();
public:
	TRefArray<TWaveSourceObject> waveObjects;
	THashtable waveIndices;
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