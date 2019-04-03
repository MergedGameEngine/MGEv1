///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _COLLISIONDETECTINGMATRICESCONTROLLER_H_
#define _COLLISIONDETECTINGMATRICESCONTROLLER_H_

#include "ModelObject.h"

extern "C" class _MODEL_API TCollisionDetectingMatricesController : public TModelObject {
protected:
protected:
	TRefArray<TCollisionDetectingMatrices> cdmos;
	THashtable cdmoIndices;
public:
	TCollisionDetectingMatricesController();
	virtual ~TCollisionDetectingMatricesController();
public:
	TRefArray<TCollisionDetectingMatrices> &GetCDMObjects();
	THashtable &GetCDMIndices();
	TCollisionDetectingMatrices &GetCDMObject(TString &key);
	BOOL32 IsCollision(Vector3f &src, Vector3f &varify);
	BOOL32 IsCollision(Vector4f &src, Vector4f &varify);
	void Scale(float ratio);
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
