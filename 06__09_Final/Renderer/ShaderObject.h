///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////


#ifndef _SHADEROBJECT_H_
#define _SHADEROBJECT_H_

#include "..\Base\Type.h"
#include "..\Base\Base.h"
#include "..\MathTool\MathTool.h"

extern "C" class _RENDERER_API TShaderObject : public IObject {
protected:
protected:
	TRefArray<TShaderParameter> parameters;
	THashtable	paramIndices;
	unsigned int currentParam;
	GLchar*		vertexProgramText;
	GLchar*		fragmentProgramText;
	GLchar*		geometryProgramText;
	GLuint		fragmentShaderIndex;
	GLuint		vertexShaderIndex; 
	GLuint		programIndex; 
	GLboolean	validated;
public:
	TShaderObject();
	virtual ~TShaderObject();
public:
	void SetVertexShaderText(GLchar *text);
	void CreateVertexShader();
	void VertexShaderSource();
	void CompileVertexShader();
	GLint GetVertexShaderStatus();

	void SetFragmentShaderText(GLchar *text);
	void CreateFragmentShader();
	void FragmentShaderSource();
	void CompileFragmentShader();
	GLint GetFragmentShaderStatus();

	void CreateProgram();
	void AttachVertexShader();
	void AttachFragmentShader();
	void LinkProgram();
	GLint GetProgramStatus(GLenum pname);
	void ValidateProgram();

	void PrepareShader(GLint &vss, GLint &fss, GLint &lps, GLint &vps);

	void DeleteProgram();
	void DeleteVertexShader();
	void DeleteFragmentShader();

	void CreateParameters(unsigned int num);
	void AddParameter(TString &key, GLchar *pname, unsigned short pcode);
	void SetParameter(TString &key, GLint value);
	void SetParameter(TString &key, void *value);
	void SetParameter(TString &key, GLsizei num, GLboolean transpose, void *value);
	void SetParameter(TString &key, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer);
	void SetParameter(GLchar *pname, GLsizei num, float *value);
	void SetParameter(GLchar *pname, GLsizei num, TexCoord2f *value);
	void SetParameter(GLchar *pname, GLsizei num, Vector3f *value);
	void SetParameter(GLchar *pname, GLsizei num, Vector4f *value);
	void SetParameter(GLchar *pname, GLint value);
	void SetParameter(GLchar *pname, GLsizei num, GLboolean transpose, Matrix22f *value);
	void SetParameter(GLchar *pname, GLsizei num, GLboolean transpose, Matrix33f *value);
	void SetParameter(GLchar *pname, GLsizei num, GLboolean transpose, Matrix44f *value);

	void EnableVertexAttribArray(TString &key);
	void DisableVertexAttribArray(TString &key);

	void UseProgram();
	void UnuseProgram();

	TRefArray<TShaderParameter> &GetParameters();

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
