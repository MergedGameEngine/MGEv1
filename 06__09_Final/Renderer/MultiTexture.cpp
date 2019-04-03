///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _BASE_IMPORT
#define _MATHTOOL_IMPORT
#define _RENDERER_EXPORT

#include "string.h"
#include "GLee.h"
#undef GetClassName
#include "..\Base\Type.h"
#include "..\Base\Base.h"
#undef _ARRAY_API
#define _ARRAY_API _RENDERER_API
#include "TextureController.hpp"
#include "MultiTexture.h"

_RENDERER_API TMultiTexture::TMultiTexture() {
	currentLayer = 0;
	isCubeMap = FALSE;
	textures.Resize(0);
}

_RENDERER_API TMultiTexture::~TMultiTexture() {
	textures.DeleteAll();
	textures.Resize(0);
}

char _RENDERER_API *TMultiTexture::GetClassName() {
	return "TMultiTexture";
}

int _RENDERER_API TMultiTexture::GetClassCode() {
	return CLSID_TMultiTexture;
}

int _RENDERER_API TMultiTexture::GetHashCode() {
	return 1;
}

BOOL32 _RENDERER_API TMultiTexture::IsInstanceof(const char* className) {
	if (strcmp("TMultiTexture", className) == 0) {
		return TRUE;
	}
	return TTextureObject::IsInstanceof(className);
}

BOOL32 _RENDERER_API TMultiTexture::IsEqualto(IObject &obj) {
	return FALSE;
}

void _RENDERER_API TMultiTexture::Serialize(IIOStream &iio) {
}

void _RENDERER_API TMultiTexture::Wait() {
}

void _RENDERER_API TMultiTexture::Notify() {
}

void _RENDERER_API TMultiTexture::SetCubeMap() {
	textures.Resize(6);
	textures.CreateAll();
	target = GL_TEXTURE_CUBE_MAP;
	isCubeMap = TRUE;
	currentLayer = 0;
}

BOOL32 _RENDERER_API TMultiTexture::IsCubeMap() {
	return isCubeMap;
}

TRefArray<TTextureObject> _RENDERER_API &TMultiTexture::GetTextures() {
	return textures;
}


void _RENDERER_API TMultiTexture::SetTextureBuffer(
	unsigned int h, unsigned int w, unsigned char cd, unsigned char ts, const void *src)
{
	if ( isCubeMap ) {
		switch ( currentLayer ) {
			case 0:
				textures[0].SetTarget(GL_TEXTURE_CUBE_MAP_POSITIVE_X);
				textures[0].SetTextureBuffer(h, w, cd, ts, src);
				currentLayer ++ ;
				break;
			case 1:
				textures[1].SetTarget(GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
				textures[1].SetTextureBuffer(h, w, cd, ts, src);
				currentLayer ++ ;
				break;
			case 2:
				textures[2].SetTarget(GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
				textures[2].SetTextureBuffer(h, w, cd, ts, src);
				currentLayer ++ ;
				break;
			case 3:
				textures[3].SetTarget(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
				textures[3].SetTextureBuffer(h, w, cd, ts, src);
				currentLayer ++ ;
				break;
			case 4:
				textures[4].SetTarget(GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
				textures[4].SetTextureBuffer(h, w, cd, ts, src);
				currentLayer ++ ;
				break;
			case 5:
				textures[5].SetTarget(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);
				textures[5].SetTextureBuffer(h, w, cd, ts, src);
				currentLayer ++ ;
				break;
			default:
				currentLayer = 0 ;
				break;
		}
	}
}

void _RENDERER_API TMultiTexture::SetTarget(GLenum tar) {
}


void _RENDERER_API TMultiTexture::GenTexture() {
	glGenTextures(1, &textureIndex);
}

void _RENDERER_API TMultiTexture::TextureParameter(GLenum pname, GLenum param) {
	glTexParameteri(target, pname, param);
}

void _RENDERER_API TMultiTexture::TextureImage2D(GLint level, GLint internalformat, GLint border, GLenum format, GLenum type) {
	if ( isCubeMap ) {
		switch ( currentLayer ) {
			case 0:
				textures[0].TextureImage2D(level, internalformat, border, format, type);
				currentLayer ++ ;
				break;
			case 1:
				textures[1].TextureImage2D(level, internalformat, border, format, type);
				currentLayer ++ ;
				break;
			case 2:
				textures[2].TextureImage2D(level, internalformat, border, format, type);
				currentLayer ++ ;
				break;
			case 3:
				textures[3].TextureImage2D(level, internalformat, border, format, type);
				currentLayer ++ ;
				break;
			case 4:
				textures[4].TextureImage2D(level, internalformat, border, format, type);
				currentLayer ++ ;
				break;
			case 5:
				textures[5].TextureImage2D(level, internalformat, border, format, type);
				currentLayer ++ ;
				break;
			default:
				currentLayer = 0 ;
				break;
		}
	}
}

void _RENDERER_API TMultiTexture::BindTexture() {
	if ( isCubeMap ) {
		glBindTexture(target, textureIndex);
	}
}

void _RENDERER_API TMultiTexture::ActiveTexture() {
	glActiveTexture(GL_TEXTURE0 + index);
}

GLuint _RENDERER_API TMultiTexture::GetTextureIndex() {
	if ( isCubeMap ) {
		return textureIndex;
	}
	return 0xFFFFFFFF;
}
