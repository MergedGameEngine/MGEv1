///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "../Base/Type.h"
#include "../Base/Base.h"

extern "C" class _CORE_API TLevel : public IObject {
public:
	TLevel();
	virtual ~TLevel();
public:
	unsigned short levelId;

public:
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