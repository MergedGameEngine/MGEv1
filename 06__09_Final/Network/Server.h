///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _SERVER_H_
#define _SERVER_H_

#include "../Thread/Thread.h"

extern "C" class _NETWORK_API TServer : public TThread {
public:
	TServer();
	virtual ~TServer();
public:
public:
public:
	TSocket serverSocket;
	TRefArray<TClientHandler> clientHandlers;
	TRWLock arrayLock;
public:
	BOOL32 Startup();
	BOOL32 Send(TPacket &pkt);
	BOOL32 Receive(TPacket &pkt);
	virtual void Run();
	BOOL32 Cleanup();

	virtual TClientHandler *NewClientHandler();
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