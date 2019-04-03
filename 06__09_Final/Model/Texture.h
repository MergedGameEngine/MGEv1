///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "..\Base\Base.h"

extern "C" class _MODEL_API TTexture : public IObject {
public:
	TTexture();
	virtual ~TTexture();
public:
	unsigned short	width;	// width in pixels
	unsigned short	height;	// height in pixels
	unsigned char	colordeepth;
	void *buffer;
public:
	virtual void Set(unsigned short width, unsigned short height, unsigned char colordeepth, void *buffer);
	virtual void Get(unsigned short &width, unsigned short &height, unsigned char &colordeepth, void *&buffer);
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