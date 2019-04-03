///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _BASE_IMPORT
#define _MATHTOOL_IMPORT
#define _MODEL_EXPORT

#include "string.h"
#include "..\Base\Type.h"
#include "..\Base\Base.h"
#undef _ARRAY_API
#define _ARRAY_API _MODEL_API
#include "Bone.hpp"

_MODEL_API TBone::TBone() {
	numVertices = 0;
	vertexIndices.Resize(0);
	weights.Resize(0);
}

_MODEL_API TBone::TBone(TBoneTreeNode *sc) {
	numVertices = 0;
	vertexIndices.Resize(0);
	weights.Resize(0);

	shortCut = sc;
}

_MODEL_API TBone::~TBone() {
	vertexIndices.Resize(0);
	weights.Resize(0);
}

char _MODEL_API *TBone::GetClassName() {
	return "TBone";
}

int _MODEL_API TBone::GetClassCode() {
	return CLSID_TBone;
}

int _MODEL_API TBone::GetHashCode() {
	return 1;
}

BOOL32 _MODEL_API TBone::IsInstanceof(const char* className) {
	if (strcmp("TBone", className) == 0) {
		return TRUE;
	}
	return TModelObject::IsInstanceof(className);
}

BOOL32 _MODEL_API TBone::IsEqualto(IObject &obj) {
	return FALSE;
}

void _MODEL_API TBone::Serialize(IIOStream &iio) {
	TModelObject::Serialize(iio);
	if ( iio.GetLoadStore() == IIOStream::load ) {
		if ( ( version == 0x00000001 ) && ( subVersion == 0x00000000 ) ) {
			name.Load(iio);
			iio.ReadBuffer(&translation, 3, sizeof(float));
			iio.ReadBuffer(&rotation, 9, sizeof(float));
			iio.Read(&scale, sizeof(float));
			iio.ReadBuffer(&boundingSphereOffset, 3, sizeof(float));
			iio.Read(&boundingSphereRadius, sizeof(float));

			
			iio.Read(&numVertices, sizeof(unsigned short));
			if (numVertices > 0) {
				vertexIndices.Resize(numVertices);
				iio.ReadBuffer(vertexIndices.GetBuffer(), numVertices, sizeof(unsigned short));
				weights.Resize(numVertices);
				iio.ReadBuffer(weights.GetBuffer(), numVertices, sizeof(float));
			}

		}
	} else {
		name.Store(iio);
		iio.WriteBuffer(&translation, 3, sizeof(float));
		iio.WriteBuffer(&rotation, 9, sizeof(float));
		iio.Write(&scale, sizeof(float));
		iio.WriteBuffer(&boundingSphereOffset, 3, sizeof(float));
		iio.Write(&boundingSphereRadius, sizeof(float));

		iio.Write(&numVertices, sizeof(unsigned short));
		if (numVertices > 0) {
			iio.WriteBuffer(vertexIndices.GetBuffer(), numVertices, sizeof(unsigned short));
			iio.WriteBuffer(weights.GetBuffer(), numVertices, sizeof(float));
		}
	}
}

void _MODEL_API TBone::Wait() {
}

void _MODEL_API TBone::Notify() {
}

Vector3f _MODEL_API &TBone::GetTranslation() {
	return translation;
}

Matrix33f _MODEL_API &TBone::GetRotation() {
	return rotation;
}

float _MODEL_API &TBone::GetScale() {
	return scale;
}

Vector3f _MODEL_API &TBone::GetBoundingSphereOffset() {
	return boundingSphereOffset;
}

float _MODEL_API &TBone::GetBoundingSphereRadius() {
	return boundingSphereRadius;
}

TArray<unsigned short> _MODEL_API &TBone::GetVertexIndices() {
	return vertexIndices;
}

TArray<float> _MODEL_API &TBone::GetWeights() {
	return weights;
}

TBoneTreeNode _MODEL_API &TBone::GetBoneNode() {
	return *shortCut;
}

void _MODEL_API TBone::SetNumVertices(unsigned short num) {
	numVertices = num;
	weights.Resize(num);
	vertexIndices.Resize(num);
}

unsigned short _MODEL_API TBone::GetNumVertices() {
	return numVertices;
}
