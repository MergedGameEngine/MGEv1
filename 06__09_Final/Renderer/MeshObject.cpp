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
#include "MeshObject.hpp"

_RENDERER_API TMeshObject::TMeshObject() {
	verticesBufferIndex = 0xFFFFFFFF;
	normalsBufferIndex = 0xFFFFFFFF;
	tangentsBufferIndex = 0xFFFFFFFF;
	binormalsBufferIndex = 0xFFFFFFFF;
	texCoordsBufferIndex = 0xFFFFFFFF;
	indicesBufferIndex = 0xFFFFFFFF;

	verticesTarget = 0;
	normalsTarget = 0;
	tangentsTarget = 0;
	binormalsTarget = 0;
	texCoordsTarget = 0;
	indicesTarget = 0;

	//isVBO = TRUE;
	numVertices = 0;
	drawMode = 0;
	numIndices = 0;

	verticesBuffer = NULL;
	normalsBuffer = NULL;
	tangentsBuffer = NULL;
	binormalsBuffer = NULL;
	texCoordsBuffer = NULL;
	boneIndicesBuffer = NULL;
	vertexWeightsBuffer = NULL;
	indicesBuffer = NULL;

	hasTangents = FALSE;
	hasBinormals = FALSE;
	hasWeights = FALSE;
	hasBoneIndices = FALSE;

	hasTransforms = FALSE;
}

_RENDERER_API TMeshObject::~TMeshObject() {
}

char _RENDERER_API *TMeshObject::GetClassName() {
	return "TMeshObject";
}

int _RENDERER_API TMeshObject::GetClassCode() {
	return CLSID_TMeshObject;
}

int _RENDERER_API TMeshObject::GetHashCode() {
	return 1;
}

BOOL32 _RENDERER_API TMeshObject::IsInstanceof(const char* className) {
	if (strcmp("TMeshObject", className) == 0) {
		return TRUE;
	} else if (strcmp("IObject", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

BOOL32 _RENDERER_API TMeshObject::IsEqualto(IObject &obj) {
	return FALSE;
}

void _RENDERER_API TMeshObject::Serialize(IIOStream &iio) {
}

void _RENDERER_API TMeshObject::Wait() {
}

void _RENDERER_API TMeshObject::Notify() {
}

void _RENDERER_API TMeshObject::SetMode(GLenum mode) {
	drawMode = mode;
}


void _RENDERER_API TMeshObject::CreateBuffers(GLenum vu, GLenum nu, GLenum tu, GLenum bu, GLenum uu, GLenum iu) {
	glGenBuffers(1, &verticesBufferIndex);
	glBindBuffer(verticesTarget, verticesBufferIndex);
	glBufferData(verticesTarget, numVertices * 3 * sizeof(float), verticesBuffer, vu);
	verticesBuffer = NULL;

	glGenBuffers(1, &normalsBufferIndex);
	glBindBuffer(normalsTarget, normalsBufferIndex);
	glBufferData(normalsTarget, numVertices * 3 * sizeof(float), normalsBuffer, nu);
	normalsBuffer = NULL;

	if ( tangentsBuffer != NULL ) {
		glGenBuffers(1, &tangentsBufferIndex);
		glBindBuffer(tangentsTarget, tangentsBufferIndex);
		glBufferData(tangentsTarget, numVertices * 3 * sizeof(float), tangentsBuffer, tu);
		tangentsBuffer = NULL;
		hasTangents = TRUE;
	}

	if ( binormalsBuffer != NULL ) {
		glGenBuffers(1, &binormalsBufferIndex);
		glBindBuffer(binormalsTarget, binormalsBufferIndex);
		glBufferData(binormalsTarget, numVertices * 3 * sizeof(float), binormalsBuffer, bu);
		binormalsBuffer = NULL;
		hasBinormals = TRUE;
	}

	glGenBuffers(1, &texCoordsBufferIndex);
	glBindBuffer(texCoordsTarget, texCoordsBufferIndex);
	glBufferData(texCoordsTarget, numVertices * 2 * sizeof(float), texCoordsBuffer, uu);
	texCoordsBuffer = NULL;

	glGenBuffers(1, &indicesBufferIndex);
	glBindBuffer(indicesTarget, indicesBufferIndex);
	glBufferData(indicesTarget, numIndices * sizeof(unsigned short), indicesBuffer, iu);
	indicesBuffer = NULL;
}


void _RENDERER_API TMeshObject::GenVerticesBuffer() {
	glGenBuffers(1, &verticesBufferIndex);
}

void _RENDERER_API TMeshObject::GenNormalsBuffer() {
	glGenBuffers(1, &normalsBufferIndex);
}

void _RENDERER_API TMeshObject::GenTangentsBuffer() {
	glGenBuffers(1, &tangentsBufferIndex);
}

void _RENDERER_API TMeshObject::GenBinormalsBuffer() {
	glGenBuffers(1, &binormalsBufferIndex);
}

void _RENDERER_API TMeshObject::GenTexCoordsBuffer() {
	glGenBuffers(1, &texCoordsBufferIndex);
}

void _RENDERER_API TMeshObject::GenIndicesBuffer() {
	glGenBuffers(1, &indicesBufferIndex);
}

void _RENDERER_API TMeshObject::GenBoneIndicesBuffer() {
	glGenBuffers(1, &boneIndicesBufferIndex);
}
void _RENDERER_API TMeshObject::GenVertexWeightsBuffer() {
	glGenBuffers(1, &vertexWeightsBufferIndex);
}



void _RENDERER_API TMeshObject::BindVerticesBuffer() {
	glBindBuffer(verticesTarget, verticesBufferIndex);
}

void _RENDERER_API TMeshObject::BindNormalsBuffer() {
	glBindBuffer(normalsTarget, normalsBufferIndex);
}

void _RENDERER_API TMeshObject::BindTangentsBuffer() {
	glBindBuffer(tangentsTarget, tangentsBufferIndex);
}

void _RENDERER_API TMeshObject::BindBinormalsBuffer() {
	glBindBuffer(binormalsTarget, binormalsBufferIndex);
}

void _RENDERER_API TMeshObject::BindTexCoordsBuffer() {
	glBindBuffer(texCoordsTarget, texCoordsBufferIndex);
}

void _RENDERER_API TMeshObject::BindIndicesBuffer() {
	glBindBuffer(indicesTarget, indicesBufferIndex);
}

void _RENDERER_API TMeshObject::BindBoneIndicesBuffer() {
	glBindBuffer(boneIndicesTarget, boneIndicesBufferIndex);
}

void _RENDERER_API TMeshObject::BindVertexWeightsBuffer() {
	glBindBuffer(vertexWeightsTarget, vertexWeightsBufferIndex);
}



void _RENDERER_API TMeshObject::VerticesBufferData(GLenum usage) {
	glBufferData(verticesTarget, numVertices * 3 * sizeof(float), verticesBuffer, usage);
	verticesBuffer = NULL;
}

void _RENDERER_API TMeshObject::NormalsBufferData(GLenum usage) {
	glBufferData(normalsTarget, numVertices * 3 * sizeof(float), normalsBuffer, usage);
	normalsBuffer = NULL;
}

void _RENDERER_API TMeshObject::TangentsBufferData(GLenum usage) {
	if ( tangentsBuffer != NULL ) {
		glBufferData(tangentsTarget, numVertices * 3 * sizeof(float), tangentsBuffer, usage);
		tangentsBuffer = NULL;
		hasTangents = TRUE;
	}
}

void _RENDERER_API TMeshObject::BinormalsBufferData(GLenum usage) {
	if ( binormalsBuffer != NULL ) {
		glBufferData(binormalsTarget, numVertices * 3 * sizeof(float), binormalsBuffer, usage);
		binormalsBuffer = NULL;
		hasBinormals = TRUE;
	}
}

void _RENDERER_API TMeshObject::TexCoordsBufferData(GLenum usage) {
	glBufferData(texCoordsTarget, numVertices * 2 * sizeof(float), texCoordsBuffer, usage);
	texCoordsBuffer = NULL;
}

void _RENDERER_API TMeshObject::IndicesBufferData(GLenum usage) {
	glBufferData(indicesTarget, numIndices * sizeof(unsigned short), indicesBuffer, usage);
	indicesBuffer = NULL;
}

void _RENDERER_API TMeshObject::BoneIndicesBufferData(GLenum usage) {
	if ( boneIndicesBuffer != NULL ) {
		glBufferData(boneIndicesTarget, numVertices * 4 * sizeof(unsigned short), boneIndicesBuffer, usage);
		boneIndicesBuffer = NULL;
		hasBoneIndices = TRUE;
	}
}

void _RENDERER_API TMeshObject::VertexWeightsBufferData(GLenum usage) {
	if ( vertexWeightsBuffer != NULL ) {
		glBufferData(vertexWeightsTarget, numVertices * 4 * sizeof(float), vertexWeightsBuffer, usage);
		vertexWeightsBuffer = NULL;
		hasWeights = TRUE;
	}
}

GLuint _RENDERER_API TMeshObject::GetVerticesBufferIndex() {
	return verticesBufferIndex;
}
GLuint _RENDERER_API TMeshObject::GetNormalsBufferIndex() {
	return normalsBufferIndex;
}
GLuint _RENDERER_API TMeshObject::GetTangentsBufferIndex() {
	return tangentsBufferIndex;
}
GLuint _RENDERER_API TMeshObject::GetBinormalsBufferIndex() {
	return binormalsBufferIndex;
}
GLuint _RENDERER_API TMeshObject::GetTexCoordsBufferIndex() {
	return texCoordsBufferIndex;
}
GLuint _RENDERER_API TMeshObject::GetIndicesBufferIndex() {
	return indicesBufferIndex;
}
GLuint _RENDERER_API TMeshObject::GetBoneIndicesBufferIndex() {
	return boneIndicesBufferIndex;
}
GLuint _RENDERER_API TMeshObject::GetVertexWeightsBufferIndex() {
	return vertexWeightsBufferIndex;
}


void _RENDERER_API TMeshObject::SetVerticesBuffer(Vector3f *vertices, GLenum target) {
	verticesBuffer = vertices;
	verticesTarget = target;
}
void _RENDERER_API TMeshObject::SetNormalsBuffer(Vector3f *normals, GLenum target) {
	normalsBuffer = normals;
	normalsTarget = target;
}
void _RENDERER_API TMeshObject::SetTangentsBuffer(Vector3f *tangents, GLenum target) {
	tangentsBuffer = tangents;
	tangentsTarget = target;
}
void _RENDERER_API TMeshObject::SetBinormalsBuffer(Vector3f *binormals, GLenum target) {
	binormalsBuffer = binormals;
	binormalsTarget = target;
}
void _RENDERER_API TMeshObject::SetTexCoordsBuffer(TexCoord2f *texcoords, GLenum target) {
	texCoordsBuffer = texcoords;
	texCoordsTarget = target;
}
void _RENDERER_API TMeshObject::SetIndicesBuffer(unsigned short *indices, GLenum target) {
	indicesBuffer = indices;
	indicesTarget = target;
}
void _RENDERER_API TMeshObject::SetNumVertices(unsigned short num) {
	numVertices = num;
}
void _RENDERER_API TMeshObject::SetNumIndices(unsigned int num) {
	numIndices = num;
}
void _RENDERER_API TMeshObject::SetBoneIndicesBuffer(unsigned short *boneindices, GLenum target) {
	boneIndicesBuffer = boneindices;
	boneIndicesTarget = target;
}
void _RENDERER_API TMeshObject::SetVertexWeightsBuffer(float *vertexweights, GLenum target) {
	vertexWeightsBuffer = vertexweights;
	vertexWeightsTarget = target;
}

unsigned short _RENDERER_API TMeshObject::GetNumVertices() {
	return numVertices;
}
unsigned int _RENDERER_API TMeshObject::GetNumIndices() {
	return numIndices;
}

//	Deprecated
Vector3f _RENDERER_API *TMeshObject::GetVerticesBuffer() {
	return verticesBuffer;
}
Vector3f _RENDERER_API *TMeshObject::GetNormalsBuffer() {
	return normalsBuffer;
}
Vector3f _RENDERER_API *TMeshObject::GetTangentsBuffer() {
	return tangentsBuffer;
}
Vector3f _RENDERER_API *TMeshObject::GetBinormalsBuffer() {
	return binormalsBuffer;
}
TexCoord2f _RENDERER_API *TMeshObject::GetTexCoordsBuffer() {
	return texCoordsBuffer;
}
unsigned short _RENDERER_API *TMeshObject::GetIndicesBuffer() {
	return indicesBuffer;
}
unsigned short _RENDERER_API *TMeshObject::GetBoneIndicesBuffer() {
	return boneIndicesBuffer;
}
float _RENDERER_API *TMeshObject::GetVertexWeightsBuffer() {
	return vertexWeightsBuffer;
}
//

Matrix44f _RENDERER_API *TMeshObject::GetBoneMatricesBuffer() {
	return boneMatricesBuffer;
}

BOOL32 _RENDERER_API TMeshObject::HasTangents() {
	return hasTangents;
}
BOOL32 _RENDERER_API TMeshObject::HasBinormals() {
	return hasBinormals;
}
BOOL32 _RENDERER_API TMeshObject::HasWeights() {
	return hasWeights;
}
BOOL32 _RENDERER_API TMeshObject::HasBoneIndices() {
	return hasBoneIndices;
}

void _RENDERER_API TMeshObject::SetBoneMatrices(Matrix44f *bm, unsigned short bmsize) {
	if ( bm != NULL ) {
		boneMatricesBuffer = bm;
		numBoneMatrices = bmsize;
		hasTransforms = TRUE;
	} else {
		boneMatricesBuffer = NULL;
		numBoneMatrices = 0;
		hasTransforms = FALSE;
	}
}
unsigned short _RENDERER_API TMeshObject::GetNumBoneMatrices() {
	return numBoneMatrices;
}
BOOL32 _RENDERER_API TMeshObject::HasTransforms() {
	return hasTransforms;
}
