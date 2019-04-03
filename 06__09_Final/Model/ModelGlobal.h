///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _MODELGLOBAL_H_
#define _MODELGLOBAL_H_

#include "ModelObject.h"
#include "Sequence.h"

extern "C" class _MODEL_API TModelGlobal : public TModelObject {
protected:
protected:
	TRefArray<TModel> models;
	unsigned short numModels;
	byte fileType;
	unsigned short numAnimations;
	TRefArray<TSequence> animations;
	TRefArray<TCollisionDetectingMatricesController> cdmcs;
public:
	TRefArray<TModel> &GetModels();
	TRefArray<TSequence> &GetAnimations();
	TRefArray<TCollisionDetectingMatricesController> &GetCollisionDetectingMatricesControllers();
	byte GetFileType();
	void SetFileType(byte ftype);
public:
	enum {
		type_model = 0,
		type_skeleton = 1,
		type_animation = 2,
		type_collision = 3
	};
public:
	TModelGlobal();
	virtual ~TModelGlobal();
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
