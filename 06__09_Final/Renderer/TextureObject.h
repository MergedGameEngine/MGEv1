///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////


#ifndef _TEXTUREOBJECT_H_
#define _TEXTUREOBJECT_H_

#include "..\Base\Type.h"
#include "..\Base\Base.h"
#include "..\MathTool\MathTool.h"

extern "C" class _RENDERER_API TTextureObject : public IObject {
protected:
protected:
	GLuint			textureIndex;
	unsigned char	typesize;
	void			*textureBuffer;
	unsigned int	height;
	unsigned int	width;
	unsigned char	colordeepth;
	unsigned char	index;
	GLenum			target;
public:
	TString typeName;
public:
	enum {
		_wrap_uv_clamp = 0x2900,//GL_CLAMP,
		_wrap_uv_repeat = 0x2901//GL_REPEAT
	};
	enum {
		_min_filter_mipmap = 0x2703//GL_LINEAR_MIPMAP_LINEAR
	};
	enum {
		_mag_filter_linear = 0x2601//GL_LINEAR
	};
	enum {
		_mipmap_true = 0x1,//GL_TRUE,
		_mipmap_false = 0x0//GL_FALSE
	};
public:
	TTextureObject();
	virtual ~TTextureObject();
public:
	void SetTextureBuffer(unsigned int height, unsigned int width, unsigned char colordeepth, unsigned char typesize, const void *src);
	void SetTarget(GLenum tar);

	void GenTexture();
	void TextureParameter(GLenum pname, GLenum param);
	void TextureImage2D(GLint level, GLint internalformat, GLint border, GLenum format, GLenum type);
	void CompressedTexImage2D(GLint level, GLenum internalformat, GLint border, GLsizei imageSize);
	void ReadPixels(GLenum format, GLenum type);
	void ReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *buffer);
	void GenerateMipmap();
	void BindTexture();
	void ActiveTexture();

	void TextureParameter(unsigned int swarp, unsigned int twarp, unsigned int minl, unsigned int magl, unsigned int isgm);
	void TextureParameter();

	void UnbindTexture();
	void DeleteTexture();

	GLuint GetTextureIndex();

	void SetIndex(unsigned char index);
	unsigned char GetIndex();

	void SetHeight(unsigned int height);
	void SetWidth(unsigned int width);
	void SetBuffer(void *buf);
	unsigned int GetHeight();
	unsigned int GetWidth();
	void *GetBuffer();
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
