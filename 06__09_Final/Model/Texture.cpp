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
#include "..\Base\CRC32.h"
#include "..\Base\Type.h"
#include "..\Base\Base.h"
#undef _ARRAY_API
#define _ARRAY_API _MODEL_API
#include "Texture.hpp"

_MODEL_API TTexture::TTexture() {
}

_MODEL_API TTexture::~TTexture() {
}


char _MODEL_API *TTexture::GetClassName() {
	return "TTexture";
}
int _MODEL_API TTexture::GetClassCode() {
	return CLSID_TTexture;
}
int _MODEL_API TTexture::GetHashCode() {
	return (int)CRC32::GetCRC32(buffer, width * height * colordeepth);
}
BOOL32 _MODEL_API TTexture::IsInstanceof(const char* className) {
	if (strcmp("TTexture", className) == 0) {
		return TRUE;
	} else if (strcmp("IObject", className) == 0) {
		return TRUE;
	}
	return FALSE;
}
BOOL32 _MODEL_API TTexture::IsEqualto(IObject &obj) {
	return FALSE;
}
void _MODEL_API TTexture::Serialize(IIOStream &iio) {
}
void _MODEL_API TTexture::Wait() {
}
void _MODEL_API TTexture::Notify() {
}

void _MODEL_API TTexture::Set(unsigned short w, unsigned short h, unsigned char cd, void *buf) {
	width = w;
	height = h;
	colordeepth = cd;
	buffer = buf;
}
void _MODEL_API TTexture::Get(unsigned short &w, unsigned short &h, unsigned char &cd, void *&buf) {
	w = width;
	h = height;
	cd = colordeepth;
	buf = buffer;
}

