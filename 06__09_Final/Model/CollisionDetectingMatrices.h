///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _COLLISIONDETECTINGMATRICES_H_
#define _COLLISIONDETECTINGMATRICES_H_

#include "ModelObject.h"

extern "C" template class _MATHTOOL_API TArray<Matrix44f>;

extern "C" class _MODEL_API TCollisionDetectingMatrices : public TModelObject {
protected:
protected:
	TArray<Matrix44f> cdms;
	Vector3f position;
	BOOL32 isOuter;
	Matrix44f recommendation;
public:
	TCollisionDetectingMatrices();
	virtual ~TCollisionDetectingMatrices();
public:
	BOOL32 IsCollision(Vector3f &src, Vector3f &varify);
	BOOL32 IsCollision(Vector4f &src, Vector4f &varify);
public:
	BOOL32 IsMatricesZEqual(Matrix44f &src1, Matrix44f &src2, float delta);
	unsigned int BuildCollisionDetectingMatrices(TMesh &msh);
	void Scale(float ratio);
public:
	Vector3f &GetPosition();
	Matrix44f &GetRecommendation();
	TArray<Matrix44f> &GetCDMs();
	void SetOuterFlag(BOOL32 flag);
	BOOL32 IsOuter();
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
