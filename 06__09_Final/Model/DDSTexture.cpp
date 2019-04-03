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
#include "..\Base\Type.h"
#include "..\Base\Base.h"
#undef _ARRAY_API
#define _ARRAY_API _MODEL_API
#include "DDSTexture.hpp"


_MODEL_API TDDSTexture::TDDSTexture() {
}

_MODEL_API TDDSTexture::~TDDSTexture() {
}

char _MODEL_API *TDDSTexture::GetClassName() {
	return "TDDSTexture";
}
int _MODEL_API TDDSTexture::GetClassCode() {
	return CLSID_TDDSTexture;
}
int _MODEL_API TDDSTexture::GetHashCode() {
	return TTexture::GetHashCode();
}
BOOL32 _MODEL_API TDDSTexture::IsInstanceof(const char* className) {
	if (strcmp("TDDSTexture", className) == 0) {
		return TRUE;
	}
	return TTexture::IsInstanceof(className);
}
BOOL32 _MODEL_API TDDSTexture::IsEqualto(IObject &obj) {
	return FALSE;
}
void _MODEL_API TDDSTexture::Serialize(IIOStream &iio) {
	if (iio.GetLoadStore() == IIOStream::load) {
		iio.Read(&magic, sizeof(unsigned int));
		if (magic == 0x20534444) {
			iio.SetEndian(IIOStream::little_endian);
		} else if (magic == 0x44445320) {
			iio.SetEndian(IIOStream::big_endian);
		} else {
			return;
		}
		iio.ReadBuffer(&dsize, 20, sizeof(unsigned int));
		iio.ReadBuffer(dxtcode, 4, sizeof(char));
		dxtcode[4] = 0;
		iio.ReadBuffer(&bitdepth, 10, sizeof(unsigned int));
		width = (unsigned short)iwidth;
		height = (unsigned short)iheight;
		colordeepth = (unsigned char)(bitdepth / 8);
		if (strcmp("DXT1", dxtcode) == 1) {
			compressformat = TDDSTexture::FORMAT_DXT1;
		} else if (strcmp("DXT2", dxtcode) == 1) {
			compressformat = TDDSTexture::FORMAT_DXT2;
		} else if (strcmp("DXT3", dxtcode) == 1) {
			compressformat = TDDSTexture::FORMAT_DXT3;
		} else if (strcmp("DXT4", dxtcode) == 1) {
			compressformat = TDDSTexture::FORMAT_DXT4;
		} else if (strcmp("DXT5", dxtcode) == 1) {
			compressformat = TDDSTexture::FORMAT_DXT5;
		} else {
			compressformat = TDDSTexture::FORMAT_UNCOMPRESSED;
		}
		unsigned int imagesize = width * height * colordeepth;
		if ( compressformat == TDDSTexture::FORMAT_UNCOMPRESSED ) {
			buffer = new unsigned char[imagesize];
			iio.ReadBuffer(buffer, imagesize, sizeof(unsigned char));
		} else {
			buffer = new unsigned char[linearsize];
			iio.ReadBuffer(buffer, linearsize / 2, sizeof(unsigned short));
		}
		return;
	}
	if (iio.GetLoadStore() == IIOStream::store) {
		iio.WriteBuffer("DDS ", 4, sizeof(char));
		iio.WriteBuffer(&dsize, 20, sizeof(uint32));
	}
}
void _MODEL_API TDDSTexture::Wait() {
}
void _MODEL_API TDDSTexture::Notify() {
}

void _MODEL_API TDDSTexture::ConvertARGBtoRGBA(BOOL32 swapEndian) {
	if ( swapEndian ) {
		if ( colordeepth == 4 ) {
			unsigned int __rgb = 0;
			unsigned int __size = width * height;
			unsigned int __alpha = 0;
			unsigned int *_buf = (unsigned int*)buffer;
			for ( unsigned int i1 = 0 ; i1 < __size ; i1 ++ ) {
				__alpha = _buf[i1];
				__rgb = __alpha << 8;
				__alpha = __alpha >> 24;
				__rgb = (__rgb & 0xFFFFFF00) | (__alpha & 0x000000FF);
				unsigned char *__p = (unsigned char *)&__rgb;
				__alpha = __p[0];__p[0] = __p[3];__p[3] = (unsigned char)__alpha;
				__alpha = __p[1];__p[1] = __p[2];__p[2] = (unsigned char)__alpha;
				_buf[i1] = __rgb;
			}
			redmask		=	0xFF000000;	// mask for the red pixels (usually 0x00ff0000)
			greenmask	=	0x00FF0000;	// mask for the green pixels (usually 0x0000ff00)
			bluemask	=	0x0000FF00;	// mask for the blue pixels (usually 0x000000ff)
			alphamask	=	0x000000FF;	// mask for the alpha value in a pixel // (usually 0xff000000)
		}
	} else {
		if ( colordeepth == 4 ) {
			unsigned int __rgb = 0;
			unsigned int __size = width * height;
			unsigned int __alpha = 0;
			unsigned int *_buf = (unsigned int*)buffer;
			for ( unsigned int i1 = 0 ; i1 < __size ; i1 ++ ) {
				__alpha = _buf[i1];
				__rgb = __alpha << 8;
				__alpha = __alpha >> 24;
				_buf[i1] = (__rgb & 0xFFFFFF00) | (__alpha & 0x000000FF);
			}
			redmask		=	0xFF000000;	// mask for the red pixels (usually 0x00ff0000)
			greenmask	=	0x00FF0000;	// mask for the green pixels (usually 0x0000ff00)
			bluemask	=	0x0000FF00;	// mask for the blue pixels (usually 0x000000ff)
			alphamask	=	0x000000FF;	// mask for the alpha value in a pixel // (usually 0xff000000)
		}
	}
}
