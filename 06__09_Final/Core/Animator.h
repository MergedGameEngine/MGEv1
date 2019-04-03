///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _ANIMATOR_H_
#define _ANIMATOR_H_

#include "../Base/Type.h"
#include "../Base/Base.h"
#include "../Thread/Thread.h"


extern "C" class _CORE_API TAnimator : public TThread {
public:
	TAnimator();
	virtual ~TAnimator();
public:
public:
	TRWLock arrayRWLock;
	float interval;//Unit millisec
	float numCycles;
public:
public:
	TRefArray<TAnimationController> controllers;
public:
public:
	void AddController(TAnimationController &controller);
public:
	virtual void Run();
	virtual void RendererHandler();
public:
	virtual char* GetClassName();
	virtual int GetClassCode();
	virtual int GetHashCode();
	virtual BOOL32 IsInstanceof(const char* className);
	virtual BOOL32 IsEqualto(IObject &obj);
	virtual void Serialize(IIOStream &iio);
	virtual void Wait();
	virtual void Notify();
public:
};


#endif