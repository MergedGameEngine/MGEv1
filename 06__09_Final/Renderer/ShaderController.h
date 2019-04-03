///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////


#ifndef _SHADERCONTROLLER_H_
#define _SHADERCONTROLLER_H_

#include "..\Base\Type.h"
#include "..\Base\Base.h"
#include "..\MathTool\MathTool.h"

extern "C" class _RENDERER_API TShaderController : public IObject {
protected:
public:
	TRefArray<TShaderObject> shaders;
	THashtable shaderIndices;
public:
	TShaderController();
	virtual ~TShaderController();
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
