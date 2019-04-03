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
#include "TextureObject.hpp"

_RENDERER_API TTextureObject::TTextureObject() {
	textureIndex = 0xFFFFFFFF;
	typesize = 0;
	textureBuffer = NULL;
	height = 0;
	width = 0;
	colordeepth = 0;
	index = 0;
	target = 0;
}

_RENDERER_API TTextureObject::~TTextureObject() {
}

char _RENDERER_API *TTextureObject::GetClassName() {
	return "TTextureObject";
}

int _RENDERER_API TTextureObject::GetClassCode() {
	return CLSID_TTextureObject;
}

int _RENDERER_API TTextureObject::GetHashCode() {
	return 1;
}

BOOL32 _RENDERER_API TTextureObject::IsInstanceof(const char* className) {
	if (strcmp("TTextureObject", className) == 0) {
		return TRUE;
	} else if (strcmp("IObject", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

BOOL32 _RENDERER_API TTextureObject::IsEqualto(IObject &obj) {
	return FALSE;
}

void _RENDERER_API TTextureObject::Serialize(IIOStream &iio) {
}

void _RENDERER_API TTextureObject::Wait() {
}

void _RENDERER_API TTextureObject::Notify() {
}

void _RENDERER_API TTextureObject::SetTextureBuffer(
	unsigned int h, unsigned int w, unsigned char cd, unsigned char ts, const void *src)
{
	height = h;
	width = w;
	colordeepth = cd;
	typesize = ts;
	if ( src != NULL ) {
		memcpy ( textureBuffer, src, h * w * cd * ts );
	} else {
		textureBuffer = 0;
	}
}

void _RENDERER_API TTextureObject::SetTarget(GLenum tar) {
	target = tar;
}


void _RENDERER_API TTextureObject::GenTexture() {
	glGenTextures(1, &textureIndex);
}

void _RENDERER_API TTextureObject::TextureParameter(GLenum pname, GLenum param) {
	glTexParameteri(target, pname, param);
}

void _RENDERER_API TTextureObject::TextureParameter(unsigned int swarp, unsigned int twarp, unsigned int minl, unsigned int magl, unsigned int isgm) {
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, minl);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, magl);
	glTexParameteri(target, GL_TEXTURE_WRAP_S, swarp);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, twarp);
	glTexParameteri(target, GL_GENERATE_MIPMAP, isgm);
}

void _RENDERER_API TTextureObject::TextureParameter() {
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(target, GL_GENERATE_MIPMAP, GL_TRUE);
}

void _RENDERER_API TTextureObject::TextureImage2D(GLint level, GLint internalformat, GLint border, GLenum format, GLenum type) {
	glTexImage2D(target, level, internalformat, width, height, border, format, type, textureBuffer);
}

void _RENDERER_API TTextureObject::CompressedTexImage2D(GLint level, GLenum internalformat, GLint border, GLsizei imageSize) {
	glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, textureBuffer);
}

void _RENDERER_API TTextureObject::ReadPixels(GLenum format, GLenum type) {
	glReadPixels(0, 0, width, height, format, type, NULL);
}

void _RENDERER_API TTextureObject::ReadPixels(GLint x, GLint y, GLsizei w, GLsizei h, GLenum format, GLenum type, GLvoid *buf) {
	glReadPixels(x, y, w, h, format, type, buf);
}

void _RENDERER_API TTextureObject::GenerateMipmap() {
	glGenerateMipmapEXT(target);
}

void _RENDERER_API TTextureObject::BindTexture() {
	glBindTexture(target, textureIndex);
}

void _RENDERER_API TTextureObject::ActiveTexture() {
	glActiveTexture(GL_TEXTURE0 + index);
}

void _RENDERER_API TTextureObject::UnbindTexture() {
}
void _RENDERER_API TTextureObject::DeleteTexture() {
	glDeleteTextures(1, &textureIndex);
}

GLuint _RENDERER_API TTextureObject::GetTextureIndex() {
	return textureIndex;
}

void _RENDERER_API TTextureObject::SetIndex(unsigned char i) {
	index = i % 32;
}

unsigned char _RENDERER_API TTextureObject::GetIndex() {
	return index;
}

void _RENDERER_API TTextureObject::SetHeight(unsigned int h) {
	height = h;
}
void _RENDERER_API TTextureObject::SetWidth(unsigned int w) {
	width = w;
}
void _RENDERER_API TTextureObject::SetBuffer(void *buf) {
	textureBuffer = buf;
}
unsigned int _RENDERER_API TTextureObject::GetHeight() {
	return height;
}
unsigned int _RENDERER_API TTextureObject::GetWidth() {
	return width;
}
void _RENDERER_API *TTextureObject::GetBuffer() {
	return textureBuffer;
}
