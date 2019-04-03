///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////


#ifndef _LIGHTCONTROLLER_H_
#define _LIGHTCONTROLLER_H_

#include "..\Base\Type.h"
#include "..\Base\Base.h"
#include "..\MathTool\MathTool.h"
#include "LightObject.h"

extern "C" class _RENDERER_API TLightController : public IObject {
protected:
public:
	TRefArray<TLightObject> lights;
	THashtable lightIndices;
public:
	TLightController();
	virtual ~TLightController();
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
