///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _BONE_H_
#define _BONE_H_

#include "ModelObject.h"
#include "BoneTreeNode.h"

extern "C" template class _BASE_API TArray<unsigned short>;
extern "C" template class _BASE_API TArray<float>;

extern "C" class _MODEL_API TBone : public TModelObject {
protected:
protected:
	Vector3f translation;
	Matrix33f rotation;
	float scale;
	Vector3f boundingSphereOffset;
	float boundingSphereRadius;

	unsigned short numVertices;
	TArray<unsigned short> vertexIndices;
	TArray<float> weights;

	TBoneTreeNode *shortCut;

public:
	Vector3f &GetTranslation();
	Matrix33f &GetRotation();
	float &GetScale();
	Vector3f &GetBoundingSphereOffset();
	float &GetBoundingSphereRadius();
	TArray<unsigned short> &GetVertexIndices();
	TArray<float> &GetWeights();
	TBoneTreeNode &GetBoneNode();

	void SetNumVertices(unsigned short num);
	unsigned short GetNumVertices();

public:
	TBone();
	TBone(TBoneTreeNode *sc);
	virtual ~TBone();

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
