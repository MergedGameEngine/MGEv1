///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _TGATEXTURE_H_
#define _TGATEXTURE_H_

#include "..\Base\Base.h"
#include "Texture.h"

extern "C" class _MODEL_API TTGATexture : public TTexture {
public:
	TTGATexture();
	virtual ~TTGATexture();
public:
	unsigned char	identsize;				// Size of ID field that follows header (0)
	unsigned char	colorMapType;			// 0 = None, 1 = paletted
	unsigned char	imageType;				// 0 = none, 1 = indexed, 2 = rgb, 3 = grey, +8=rle
	unsigned short	colorMapStart;			// First colour map entry
	unsigned short	colorMapLength;			// Number of colors
	unsigned char 	colorMapBits;			// bits per palette entry
	unsigned short	xstart;					// image x origin
	unsigned short	ystart;					// image y origin
	unsigned char	bits;					// bits per pixel (8 16, 24, 32)
	unsigned char	descriptor;				// image descriptor
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