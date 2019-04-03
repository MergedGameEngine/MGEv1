///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _BASE_IMPORT
#define _MODEL_EXPORT

#include "string.h"
#include "stdlib.h"
#include "..\Base\CRC32.h"
#include "..\Base\Base.h"
#include "string.h"
#include "..\Base\Type.h"
#include "..\Base\Base.h"
#undef _ARRAY_API
#define _ARRAY_API _MODEL_API
#include "TGATexture.hpp"


_MODEL_API TTGATexture::TTGATexture() {
}

_MODEL_API TTGATexture::~TTGATexture() {
	if (buffer!=NULL) {
		free(buffer);
	}
}


char _MODEL_API *TTGATexture::GetClassName() {
	return "TTGATexture";
}
int _MODEL_API TTGATexture::GetClassCode() {
	return CLSID_TTGATexture;
}
int _MODEL_API TTGATexture::GetHashCode() {
	return TTexture::GetHashCode();
}
BOOL32 _MODEL_API TTGATexture::IsInstanceof(const char* className) {
	if (strcmp("TTGATexture", className) == 0) {
		return TRUE;
	}
	return TTexture::IsInstanceof(className);
}
BOOL32 _MODEL_API TTGATexture::IsEqualto(IObject &obj) {
	return FALSE;
}
void _MODEL_API TTGATexture::Serialize(IIOStream &iio) {
	if (iio.GetLoadStore() == IIOStream::load) {
		unsigned long lImageSize;		// Size in bytes of image

		// Default/Failed values
		width = 0;
		height = 0;
		//*eFormat = GL_BGR_EXT;
		//*iComponents = GL_RGB8;

		iio.Read(&identsize, sizeof(unsigned char));		// Size of ID field that follows header (0)
		iio.Read(&colorMapType, sizeof(unsigned char));		// 0 = None, 1 = paletted
		iio.Read(&imageType, sizeof(unsigned char));		// 0 = none, 1 = indexed, 2 = rgb, 3 = grey, +8=rle
		iio.Read(&colorMapStart, sizeof(unsigned short));	// First colour map entry
		iio.Read(&colorMapLength, sizeof(unsigned short));	// Number of colors
		iio.Read(&colorMapBits, sizeof(unsigned char));		// bits per palette entry
  		iio.Read(&xstart, sizeof(unsigned short));			// image x origin
		iio.Read(&ystart, sizeof(unsigned short));			// image y origin
 		iio.Read(&width, sizeof(unsigned short));			// width in pixels
		iio.Read(&height, sizeof(unsigned short));			// height in pixels
		iio.Read(&bits, sizeof(unsigned char));				// bits per pixel (8 16, 24, 32)
		iio.Read(&descriptor, sizeof(unsigned char));		// image descriptor

		// Get width, height, and depth of texture
		colordeepth = (unsigned char)(bits / 8);

		// Put some validity checks here. Very simply, I only understand
		// or care about 8, 24, or 32 bit targa's.
		if(bits != 8 && bits != 24 && bits != 32) {
			width = 0;
			height = 0;
			colordeepth = 0;
			buffer = NULL;
			return;
		}

		// Calculate size of image buffer
		lImageSize = width * height * colordeepth;

		// Allocate memory and check for success
		buffer = malloc(lImageSize);
		if(buffer == NULL) {
			width = 0;
			height = 0;
			colordeepth = 0;
			buffer = NULL;
			return;
		}

		// Read in the bits
		// Check for read error. This should catch RLE or other 
		// weird formats that I don't want to recognize
		iio.ReadBuffer(buffer, lImageSize, sizeof(unsigned char));
		return;
	}
	if (iio.GetLoadStore() == IIOStream::store) {
		bits = (unsigned char)(colordeepth * 8);
		iio.Write(&identsize, sizeof(unsigned char));		// Size of ID field that follows header (0)
		iio.Write(&colorMapType, sizeof(unsigned char));		// 0 = None, 1 = paletted
		iio.Write(&imageType, sizeof(unsigned char));		// 0 = none, 1 = indexed, 2 = rgb, 3 = grey, +8=rle
		iio.Write(&colorMapStart, sizeof(unsigned short));	// First colour map entry
		iio.Write(&colorMapLength, sizeof(unsigned short));	// Number of colors
		iio.Write(&colorMapBits, sizeof(unsigned char));		// bits per palette entry
  		iio.Write(&xstart, sizeof(unsigned short));			// image x origin
		iio.Write(&ystart, sizeof(unsigned short));			// image y origin
 		iio.Write(&width, sizeof(unsigned short));			// width in pixels
		iio.Write(&height, sizeof(unsigned short));			// height in pixels
		iio.Write(&bits, sizeof(unsigned char));				// bits per pixel (8 16, 24, 32)
		iio.Write(&descriptor, sizeof(unsigned char));		// image descriptor

		int lImageSize = width * height * colordeepth;
		iio.WriteBuffer(buffer, lImageSize, sizeof(unsigned char));
	    
		// Success!
		return;
	}
}
void _MODEL_API TTGATexture::Wait() {
}
void _MODEL_API TTGATexture::Notify() {
}








