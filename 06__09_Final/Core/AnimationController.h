///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _ANIMATIONCONTROLLER_H_
#define _ANIMATIONCONTROLLER_H_

#include "../Thread/Thread.h"
#include "BaseImport.h"
#include "MathToolImport.h"
#include "ModelImport.h"
#include "RendererImport.h"


class TSequence;
class TBoneController;

extern "C" class _CORE_API TAnimationController : public TThread {
public:
	TAnimationController();
	virtual ~TAnimationController();
public:
	Vector3f positionCurrent;
	Vector3f position;
	Matrix33f direction;
	float directionAngle;
	Vector3f velocityCurrent;
	Vector3f velocity;
	Vector3f accelerationCurrent;
	Vector3f acceleration;
public:
	unsigned int innerstate;
public:
	void RotationAxisZ(float angle);
	void Velocity(float delta);
	void CommitVelocity();
	void Gravity(float delta);
	void CommitGravity();
	void Commit();
public:
	float currentime;
	TRWLock rwLock;
	TRefArray<TSequence> animations;
	TModel boneController;
	TAnimationController *parentController;
	int count;
public:
	virtual void Run();
	virtual void Flush(float delta);
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