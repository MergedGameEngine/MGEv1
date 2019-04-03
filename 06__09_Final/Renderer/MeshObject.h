///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////


#ifndef _MESHOBJECT_H_
#define _MESHOBJECT_H_

#include "..\Base\Type.h"
#include "..\Base\Base.h"
#include "..\MathTool\MathTool.h"

extern "C" template class _BASE_API TRefArray<TString>;

extern "C" class _RENDERER_API TMeshObject : public IObject {
protected:
protected:
	GLuint			verticesBufferIndex;
	GLuint			normalsBufferIndex;
	GLuint			tangentsBufferIndex;
	GLuint			binormalsBufferIndex;
	GLuint			texCoordsBufferIndex;
	GLuint			indicesBufferIndex;

	GLuint			boneIndicesBufferIndex;
	GLuint			vertexWeightsBufferIndex;

	GLenum			verticesTarget;
	GLenum			normalsTarget;
	GLenum			tangentsTarget;
	GLenum			binormalsTarget;
	GLenum			texCoordsTarget;
	GLenum			indicesTarget;

	GLenum			boneIndicesTarget;
	GLenum			vertexWeightsTarget;

	unsigned short	numVertices;
	GLenum			drawMode;
	unsigned int	numIndices;

	Vector3f		*verticesBuffer;
	Vector3f		*normalsBuffer;
	Vector3f		*tangentsBuffer;
	Vector3f		*binormalsBuffer;
	TexCoord2f		*texCoordsBuffer;
	unsigned short	*indicesBuffer;

	unsigned short	*boneIndicesBuffer;
	float			*vertexWeightsBuffer;

	Matrix44f		*boneMatricesBuffer;
	unsigned short	numBoneMatrices;
protected:
	BOOL32	hasTangents;
	BOOL32	hasBinormals;
	BOOL32	hasWeights;
	BOOL32	hasBoneIndices;

	BOOL32	hasTransforms;
public:
	TRefArray<TString> lightNames;
	TRefArray<TString> textureNames;
	TString shaderName;
public:
	TString vertexParamName;
	TString normalParamName;
	TString tangentParamName;
	TString binormalParamName;
	TString texCoordParamName;
	TString boneIndexParamName;
	TString vertexWeightParamName;

	TString boneMatrixParamName;
public:
	TMeshObject();
	virtual ~TMeshObject();
public:
	void SetMode(GLenum mode);
	void CreateBuffers(GLenum vu, GLenum nu, GLenum tu, GLenum bu, GLenum uu, GLenum iu);

	void GenVerticesBuffer();
	void GenNormalsBuffer();
	void GenTangentsBuffer();
	void GenBinormalsBuffer();
	void GenTexCoordsBuffer();
	void GenIndicesBuffer();

	void GenBoneIndicesBuffer();
	void GenVertexWeightsBuffer();

	void BindVerticesBuffer();
	void BindNormalsBuffer();
	void BindTangentsBuffer();
	void BindBinormalsBuffer();
	void BindTexCoordsBuffer();
	void BindIndicesBuffer();

	void BindBoneIndicesBuffer();
	void BindVertexWeightsBuffer();

	void VerticesBufferData(GLenum usage);
	void NormalsBufferData(GLenum usage);
	void TangentsBufferData(GLenum usage);
	void BinormalsBufferData(GLenum usage);
	void TexCoordsBufferData(GLenum usage);
	void IndicesBufferData(GLenum usage);

	void BoneIndicesBufferData(GLenum usage);
	void VertexWeightsBufferData(GLenum usage);

	GLuint GetVerticesBufferIndex();
	GLuint GetNormalsBufferIndex();
	GLuint GetTangentsBufferIndex();
	GLuint GetBinormalsBufferIndex();
	GLuint GetTexCoordsBufferIndex();
	GLuint GetIndicesBufferIndex();

	GLuint GetBoneIndicesBufferIndex();
	GLuint GetVertexWeightsBufferIndex();

	void SetVerticesBuffer(Vector3f *vertices, GLenum target);
	void SetNormalsBuffer(Vector3f *normals, GLenum target);
	void SetTangentsBuffer(Vector3f *tangents, GLenum target);
	void SetBinormalsBuffer(Vector3f *binormals, GLenum target);
	void SetTexCoordsBuffer(TexCoord2f *texcoords, GLenum target);
	void SetBoneIndicesBuffer(unsigned short *boneindices, GLenum target);
	void SetVertexWeightsBuffer(float *vertexweights, GLenum target);
	void SetIndicesBuffer(unsigned short *indices, GLenum target);

	void SetNumVertices(unsigned short num);
	void SetNumIndices(unsigned int num);

	//	Deprecated
	Vector3f *GetVerticesBuffer();
	Vector3f *GetNormalsBuffer();
	Vector3f *GetTangentsBuffer();
	Vector3f *GetBinormalsBuffer();
	TexCoord2f *GetTexCoordsBuffer();
	unsigned short *GetBoneIndicesBuffer();
	float *GetVertexWeightsBuffer();
	unsigned short *GetIndicesBuffer();
	//

	Matrix44f *GetBoneMatricesBuffer();
	unsigned short GetNumBoneMatrices();

	unsigned short GetNumVertices();
	unsigned int GetNumIndices();

public:
	BOOL32	HasTangents();
	BOOL32	HasBinormals();
	BOOL32	HasWeights();
	BOOL32	HasBoneIndices();

	void	SetBoneMatrices(Matrix44f *bm, unsigned short bmsize);
	BOOL32	HasTransforms();
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
