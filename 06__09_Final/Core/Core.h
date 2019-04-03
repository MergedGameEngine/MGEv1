///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _CORE_H_
#define _CORE_H_

#include "../Base/Type.h"
#include "../Base/Base.h"

struct TMessage;

extern "C" class _CORE_API TCore : public TWindow {
public:
	TCore();
	virtual ~TCore();
public:
	TArray<TMessage> messageQueue;
	TRWLock queueRWLock;
	unsigned int queueHead;
	unsigned int queueTail;
	unsigned int queueLength;
public:
	TShaderController shaderController;
	TShaderController HDRShader;
public:
	unsigned int interval;

public:
	virtual void Run();
	void PostMessage(TMessage &msg);
	virtual void MessageHandler(TMessage &msg);

public:
	void LoadConfigFile(TString &fn, TConfigFile &cf);
	void LoadShader(TConfigFile &cf);

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