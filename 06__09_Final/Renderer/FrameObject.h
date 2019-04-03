///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////


#ifndef _FRAMEOBJECT_H_
#define _FRAMEOBJECT_H_

#include "..\Base\Type.h"
#include "..\Base\Base.h"
#include "..\MathTool\MathTool.h"

extern "C" class _RENDERER_API TFrameObject : public IObject {
protected:
protected:
	GLuint renderBufferIndex;
	GLenum frameTarget;
	GLuint frameBufferIndex;
public:
	TFrameObject();
	virtual ~TFrameObject();
public:
	void SetRenderBufferIndex(GLuint index);
	void SetTarget(GLenum target);
	GLuint GetFrameBufferIndex();

	void GenFrameBuffer();
	void BindFrameBuffer();
	void DrawBuffer(GLenum attachment);
	void FrameBufferRenderBuffer(GLenum attachment, GLenum renderbuffertarget);
	void FrameBufferTexture2D(GLenum attachment, GLenum textarget, GLuint texture, GLint level);

	void DeleteFramebuffer();
	void UnbindFrameBuffer();
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
