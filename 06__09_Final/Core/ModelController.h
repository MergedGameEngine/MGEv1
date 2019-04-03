///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _MODELCONTROLLER_H_
#define _MODELCONTROLLER_H_

#include "BaseImport.h"
#include "MathToolImport.h"
#include "ModelImport.h"
#include "RendererImport.h"

#include "EventListener.h"

class TModel;
class TMeshController;
class TTextureController;
class TAnimationController;

extern "C" class _CORE_API TModelController : public TEventListener {
public:
	TModelController();
	virtual ~TModelController();
public:
	Vector3f positionCurrent;
	Vector3f position;
	Matrix33f direction;
	float directionAngle;
	Vector3f velocity;
	Vector3f acceleration;
public:
	void RotationAxisZ(float angle);
	void Velocity(float delta);
	void Commit();
public:
	TModel *modelPrototype;
	TMeshController *renderMeshUnit;
	TTextureController *renderTextureUnit;
	TAnimationController *animationController;
	unsigned short numBoneMatrices;
public:
	TRefArray<TModelController> subModelControllers;
public:
	void LinkBoneMatrices();
public:
	virtual void EventHandler(TEvent &e);
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