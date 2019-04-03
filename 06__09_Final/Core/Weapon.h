///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "../Base/Type.h"
#include "../Base/Base.h"
#include "ModelController.h"

extern "C" class _CORE_API TWeapon : public TModelController {
public:
	TWeapon();
	virtual ~TWeapon();
public:

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