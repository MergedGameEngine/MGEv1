///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _CLIENTHANDLER_H_
#define _CLIENTHANDLER_H_

#include "../Thread/Thread.h"

class TPackage;

extern "C" class _NETWORK_API TClientHandler : public TThread {
public:
	TClientHandler();
	virtual ~TClientHandler();
public:
public:
	TSocket clientSocket;
public:
	BOOL32 Send(TPacket &pkt);
	BOOL32 Receive(TPacket &pkt);
	virtual void Run();
	BOOL32 Cleanup();
	BOOL32 NonBlockReceive(TPacket &pkt);
	virtual void PacketHandler(char *buf);
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