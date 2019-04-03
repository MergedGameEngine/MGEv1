///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////


#ifndef _TEXTURECONTROLLER_H_
#define _TEXTURECONTROLLER_H_

#include "..\Base\Type.h"
#include "..\Base\Base.h"
#include "..\MathTool\MathTool.h"

extern "C" class _RENDERER_API TTextureController : public IObject {
protected:
public:
	TRefArray<TTextureObject> textures;
	THashtable textureIndices;
public:
	TTextureController();
	virtual ~TTextureController();
public:
	void ActiveTexture0();
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
