///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _BASE_IMPORT
#define _THREAD_IMPORT
#define _NETWORK_EXPORT

#include "string.h"
#include "winsock.h"
#undef GetClassName
#include "..\Base\Type.h"
#include "..\Base\Base.h"

#include "TSocket.h"
#undef _ARRAY_API
#define _ARRAY_API _NETWORK_API
#include "Packet.hpp"
#include "ClientHandler.hpp"
#include "Server.hpp"


_NETWORK_API TServer::TServer() {
	arrayLock.AttribInit();
	arrayLock.Init();
}

_NETWORK_API TServer::~TServer() {
	arrayLock.Destroy();
	arrayLock.AttribDestroy();
}

char _NETWORK_API *TServer::GetClassName() {
	return "TServer";
}
int _NETWORK_API TServer::GetClassCode() {
	return CLSID_TServer;
}
int _NETWORK_API TServer::GetHashCode() {
	return 1;
}
BOOL32 _NETWORK_API TServer::IsInstanceof(const char* className) {
	if (strcmp("TServer", className) == 0) {
		return TRUE;
	}
	return TThread::IsInstanceof(className);
}
BOOL32 _NETWORK_API TServer::IsEqualto(IObject &obj) {
	return FALSE;
}
void _NETWORK_API TServer::Serialize(IIOStream &iio) {
}
void _NETWORK_API TServer::Wait() {
}
void _NETWORK_API TServer::Notify() {
}


BOOL32 _NETWORK_API TServer::Startup() {
	unsigned short version = MAKEWORD(2,0);
	int retCode = serverSocket.Startup(version);
	if ( retCode != 0 ) {
		printf("\n WSAStartup Error \n");
		return FALSE;
	}
	serverSocket.Socket(AF_INET,SOCK_STREAM,0);
	if ( serverSocket.Bind() == FALSE ) {//°ó¶¨
		return FALSE;
	}
	if ( serverSocket.Listen(10) == FALSE ) {//¼àÌý
		return FALSE;
	}
	printf("\nServer is ready\n");

	AttribInit();
	Create();

	return TRUE;
}

BOOL32 _NETWORK_API TServer::Send(TPacket &pkt) {
	return TRUE;
}
BOOL32 _NETWORK_API TServer::Receive(TPacket &pkt) {
	return TRUE;
}
void _NETWORK_API TServer::Run() {
	TPacket pkt;
	pkt.Fill(65536);
	while(TRUE) {
		serverSocket.SetInterval(0, 0);
		serverSocket.Select(TRUE, FALSE, FALSE, TRUE);
		if (serverSocket.IsReadable()) {
			TClientHandler *newbie = NewClientHandler();
			if ( serverSocket.Accept(newbie->clientSocket) == FALSE ) {
				printf("SOCKET serverSocket error\n");
				delete newbie;
			} else {
				printf("Successfully accept a new client\n");
				arrayLock.WriteLock();
				clientHandlers.Resize(clientHandlers.GetLength() + 1);
				clientHandlers.Set(clientHandlers.GetLength() - 1, newbie);
				arrayLock.Unlock();
			}
		}
		for (unsigned int i2 = 0 ; i2 < clientHandlers.GetLength() ; i2 ++) {
			TClientHandler *one = &clientHandlers[i2];
			if ( one != NULL ) {
				one->NonBlockReceive(pkt);
			}
		}
		Delay(0, 50000);
	}
}

BOOL32 _NETWORK_API TServer::Cleanup() {
	serverSocket.CloseSocket();
	serverSocket.Cleanup();
	return TRUE;
}

TClientHandler _NETWORK_API *TServer::NewClientHandler() {
	return new TClientHandler();
}
