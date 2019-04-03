///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "../Thread/Thread.h"

class TPackage;

extern "C" class _NETWORK_API TClient : public TThread {
public:
	TClient();
	virtual ~TClient();
public:
public:
	TSocket clientSocket;
public:
	BOOL32 Startup();
	BOOL32 Send(TPacket &pkt);
	BOOL32 Receive(TPacket &pkt);
	virtual void Run();
	BOOL32 Cleanup();
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