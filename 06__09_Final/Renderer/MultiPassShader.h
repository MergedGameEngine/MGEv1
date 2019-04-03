///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////


#ifndef _MULTIPASSSHADER_H_
#define _MULTIPASSSHADER_H_

#include "..\Base\Type.h"
#include "..\Base\Base.h"
#include "..\MathTool\MathTool.h"
#include "ShaderObject.h"
#include "TextureObject.h"

extern "C" class _RENDERER_API TMultiPassShader : public TShaderObject {
protected:
protected:
	TRefArray<TShaderObject> shaders;
	TRefArray<TFrameObject> frames;
	TRefArray<TTextureObject> textures;
	GLenum fragmentTarget;
	GLuint fragmentBufferIndex;
	GLenum renderTarget;
	GLuint renderBufferIndex;
	GLsizei frameWidth;
	GLsizei frameHeight;
public:
	TMultiPassShader();
	virtual ~TMultiPassShader();
public:
	void CreateShaders(unsigned int num);
	void CreateFrameBuffers(unsigned int num);
	void CreateTextures(unsigned int num);

	void GenFragmentBuffer();
	void BindFragmentBuffer();
	void FragmentBufferData(GLsizeiptr size, const GLvoid *buf, GLenum usage);
	void UnbindFragmentBuffer();

	void SetFragmentTarget(GLenum target);
	GLuint GetFragmentBufferIndex();

	void GenRenderBuffer();
	void BindRenderbuffer();
	void RenderBufferStorage(GLenum internalformat);

	void DeleteRenderbuffer();
	void UnbindRenderbuffer();

	void SetRenderTarget(GLenum target);
	GLuint GetRenderBufferIndex();

	void SetFrameWidth(GLsizei width);
	void SetFrameHeight(GLsizei height);

	TRefArray<TShaderObject> &GetShaders();
	TRefArray<TFrameObject> &GetFrameBuffers();
	TRefArray<TTextureObject> &GetBufferTextures();

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
