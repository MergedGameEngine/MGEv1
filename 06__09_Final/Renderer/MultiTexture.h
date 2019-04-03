///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////


#ifndef _MULTITEXTURE_H_
#define _MULTITEXTURE_H_

#include "..\Base\Type.h"
#include "..\Base\Base.h"
#include "..\MathTool\MathTool.h"
#include "TextureObject.h"

extern "C" class _RENDERER_API TMultiTexture : public TTextureObject {
protected:
protected:
	TRefArray<TTextureObject>	textures;
	unsigned char				currentLayer;
	BOOL8						isCubeMap;
public:
	TMultiTexture();
	virtual ~TMultiTexture();
public:
	void SetCubeMap();
	BOOL32 IsCubeMap();

	TRefArray<TTextureObject> &GetTextures();

	virtual void SetTextureBuffer(unsigned int height, unsigned int width, unsigned char colordeepth, unsigned char typesize, const void *src);
	virtual void SetTarget(GLenum tar);

	virtual void GenTexture();
	virtual void TextureParameter(GLenum pname, GLenum param);
	virtual void TextureImage2D(GLint level, GLint internalformat, GLint border, GLenum format, GLenum type);
	virtual void BindTexture();
	virtual void ActiveTexture();

	virtual GLuint GetTextureIndex();

public:
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
