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
#include "ShaderController.hpp"
#include "MultiPassShader.h"

_RENDERER_API TMultiPassShader::TMultiPassShader() {
	shaders.Resize(0);
	frames.Resize(0);
	textures.Resize(0);
}

_RENDERER_API TMultiPassShader::~TMultiPassShader() {
	shaders.DeleteAll();
	shaders.Resize(0);
	frames.DeleteAll();
	frames.Resize(0);
	textures.DeleteAll();
	textures.Resize(0);
}

char _RENDERER_API *TMultiPassShader::GetClassName() {
	return "TMultiPassShader";
}

int _RENDERER_API TMultiPassShader::GetClassCode() {
	return CLSID_TMultiPassShader;
}

int _RENDERER_API TMultiPassShader::GetHashCode() {
	return 1;
}

BOOL32 _RENDERER_API TMultiPassShader::IsInstanceof(const char* className) {
	if (strcmp("TMultiPassShader", className) == 0) {
		return TRUE;
	}
	return TShaderObject::IsInstanceof(className);
}

BOOL32 _RENDERER_API TMultiPassShader::IsEqualto(IObject &obj) {
	return FALSE;
}

void _RENDERER_API TMultiPassShader::Serialize(IIOStream &iio) {
}

void _RENDERER_API TMultiPassShader::Wait() {
}

void _RENDERER_API TMultiPassShader::Notify() {
}

void _RENDERER_API TMultiPassShader::CreateShaders(unsigned int num) {
	shaders.Resize(num);
	shaders.CreateAll();
}
void _RENDERER_API TMultiPassShader::CreateFrameBuffers(unsigned int num) {
	frames.Resize(num);
	frames.CreateAll();
}
void _RENDERER_API TMultiPassShader::CreateTextures(unsigned int num) {
	textures.Resize(num);
	textures.CreateAll();
}

void _RENDERER_API TMultiPassShader::GenFragmentBuffer() {
	glGenBuffers(1, &fragmentBufferIndex);
}
void _RENDERER_API TMultiPassShader::BindFragmentBuffer() {
	glBindBuffer(fragmentTarget, fragmentBufferIndex);
}
void _RENDERER_API TMultiPassShader::FragmentBufferData(GLsizeiptr size, const GLvoid *buf, GLenum usage) {
	glBufferData(fragmentTarget, size, buf, usage);
}
void _RENDERER_API TMultiPassShader::UnbindFragmentBuffer() {
	glBindBuffer(fragmentTarget, 0);
}

void _RENDERER_API TMultiPassShader::SetFragmentTarget(GLenum target) {
	fragmentTarget = target;
}
GLuint _RENDERER_API TMultiPassShader::GetFragmentBufferIndex() {
	return fragmentBufferIndex;
}

void _RENDERER_API TMultiPassShader::GenRenderBuffer() {
	glGenRenderbuffersEXT(1, &renderBufferIndex);
}
void _RENDERER_API TMultiPassShader::BindRenderbuffer() {
	glBindRenderbufferEXT(renderTarget, renderBufferIndex);
}
void _RENDERER_API TMultiPassShader::RenderBufferStorage(GLenum internalformat) {
	glRenderbufferStorageEXT(renderTarget, internalformat, frameWidth, frameHeight);
}

void _RENDERER_API TMultiPassShader::DeleteRenderbuffer() {
		glDeleteRenderbuffersEXT(1, &renderBufferIndex);
}
void _RENDERER_API TMultiPassShader::UnbindRenderbuffer() {
}

void _RENDERER_API TMultiPassShader::SetRenderTarget(GLenum target) {
	renderTarget = target;
}
GLuint _RENDERER_API TMultiPassShader::GetRenderBufferIndex() {
	return renderBufferIndex;
}

void _RENDERER_API TMultiPassShader::SetFrameWidth(GLsizei width) {
	frameWidth = width;
}
void _RENDERER_API TMultiPassShader::SetFrameHeight(GLsizei height) {
	frameHeight = height;
}

TRefArray<TShaderObject> _RENDERER_API &TMultiPassShader::GetShaders() {
	return shaders;
}
TRefArray<TFrameObject> _RENDERER_API &TMultiPassShader::GetFrameBuffers() {
	return frames;
}
TRefArray<TTextureObject> _RENDERER_API &TMultiPassShader::GetBufferTextures() {
	return textures;
}
