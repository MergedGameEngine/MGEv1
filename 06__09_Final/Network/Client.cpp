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
#include "Client.hpp"


_NETWORK_API TClient::TClient() {
}

_NETWORK_API TClient::~TClient() {
}

char _NETWORK_API *TClient::GetClassName() {
	return "TClient";
}
int _NETWORK_API TClient::GetClassCode() {
	return CLSID_TClient;
}
int _NETWORK_API TClient::GetHashCode() {
	return 1;
}
BOOL32 _NETWORK_API TClient::IsInstanceof(const char* className) {
	if (strcmp("TClient", className) == 0) {
		return TRUE;
	}
	return TThread::IsInstanceof(className);
}
BOOL32 _NETWORK_API TClient::IsEqualto(IObject &obj) {
	return FALSE;
}
void _NETWORK_API TClient::Serialize(IIOStream &iio) {
}
void _NETWORK_API TClient::Wait() {
}
void _NETWORK_API TClient::Notify() {
}


BOOL32 _NETWORK_API TClient::Startup() {
	unsigned short version = MAKEWORD(2,0);
	int retCode = clientSocket.Startup(version);
	if ( retCode != 0 ) {
		printf("\n WSAStartup Error \n");
		return FALSE;
	}
	clientSocket.Socket(AF_INET,SOCK_STREAM,0);
	if ( clientSocket.Connect() == FALSE ) {//主动连接服务器
		clientSocket.CloseSocket();
		OutputDebugStringA("\nCONNECT FAILED\n");
		return FALSE;
	}
	return TRUE;
}

BOOL32 _NETWORK_API TClient::Send(TPacket &pkt) {
	unsigned int paklen = 0;
	printf("\nNEW SOCKET = [%4X]\n", clientSocket.sock);
	if ( clientSocket.Send((char*)pkt.GetBuffer(paklen), pkt.GetLength(), 0) == FALSE ) {
		OutputDebugStringA("\nSEND FAILED\n");
		return FALSE;
	}
	return TRUE;
}
BOOL32 _NETWORK_API TClient::Receive(TPacket &pkt) {
	return TRUE;
}
void _NETWORK_API TClient::Run() {
}

BOOL32 _NETWORK_API TClient::Cleanup() {
	clientSocket.CloseSocket();
	clientSocket.Cleanup();
	return TRUE;
}

