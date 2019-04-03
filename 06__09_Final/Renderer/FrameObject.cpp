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
#include "FrameObject.hpp"

_RENDERER_API TFrameObject::TFrameObject() {
}

_RENDERER_API TFrameObject::~TFrameObject() {
}

char _RENDERER_API *TFrameObject::GetClassName() {
	return "TFrameObject";
}

int _RENDERER_API TFrameObject::GetClassCode() {
	return CLSID_TFrameObject;
}

int _RENDERER_API TFrameObject::GetHashCode() {
	return 1;
}

BOOL32 _RENDERER_API TFrameObject::IsInstanceof(const char* className) {
	if (strcmp("TFrameObject", className) == 0) {
		return TRUE;
	} else if (strcmp("IObject", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

BOOL32 _RENDERER_API TFrameObject::IsEqualto(IObject &obj) {
	return FALSE;
}

void _RENDERER_API TFrameObject::Serialize(IIOStream &iio) {
}

void _RENDERER_API TFrameObject::Wait() {
}

void _RENDERER_API TFrameObject::Notify() {
}

void _RENDERER_API TFrameObject::SetRenderBufferIndex(GLuint index) {
	renderBufferIndex = index;
}
void _RENDERER_API TFrameObject::SetTarget(GLenum target) {
	frameTarget = target;
}
GLuint _RENDERER_API TFrameObject::GetFrameBufferIndex() {
	return frameBufferIndex;
}

void _RENDERER_API TFrameObject::GenFrameBuffer() {
	glGenFramebuffersEXT(1, &frameBufferIndex);
}
void _RENDERER_API TFrameObject::BindFrameBuffer() {
	glBindFramebufferEXT(frameTarget, frameBufferIndex);
}
void _RENDERER_API TFrameObject::DrawBuffer(GLenum attachment) {
	glDrawBuffers(1, &attachment);
}
void _RENDERER_API TFrameObject::FrameBufferRenderBuffer(GLenum attachment, GLenum renderbuffertarget) {
	glFramebufferRenderbufferEXT(frameTarget, attachment, renderbuffertarget, renderBufferIndex);
}
void _RENDERER_API TFrameObject::FrameBufferTexture2D(GLenum attachment, GLenum textarget, GLuint texture, GLint level) {
	glFramebufferTexture2DEXT(frameTarget, attachment, textarget, texture, level);
}

void _RENDERER_API TFrameObject::DeleteFramebuffer() {
	glDeleteFramebuffersEXT(1, &frameBufferIndex);
}
void _RENDERER_API TFrameObject::UnbindFrameBuffer() {
	glBindFramebufferEXT(frameTarget, 0);
}
