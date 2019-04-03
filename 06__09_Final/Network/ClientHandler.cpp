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


_NETWORK_API TClientHandler::TClientHandler() {
}

_NETWORK_API TClientHandler::~TClientHandler() {
}

char _NETWORK_API *TClientHandler::GetClassName() {
	return "TClientHandler";
}
int _NETWORK_API TClientHandler::GetClassCode() {
	return CLSID_TClientHandler;
}
int _NETWORK_API TClientHandler::GetHashCode() {
	return 1;
}
BOOL32 _NETWORK_API TClientHandler::IsInstanceof(const char* className) {
	if (strcmp("TClientHandler", className) == 0) {
		return TRUE;
	}
	return TThread::IsInstanceof(className);
}
BOOL32 _NETWORK_API TClientHandler::IsEqualto(IObject &obj) {
	return FALSE;
}
void _NETWORK_API TClientHandler::Serialize(IIOStream &iio) {
}
void _NETWORK_API TClientHandler::Wait() {
}
void _NETWORK_API TClientHandler::Notify() {
}

BOOL32 _NETWORK_API TClientHandler::Send(TPacket &pkt) {
	unsigned int paklen = 0;
	printf("\nNEW SOCKET = [%4X]\n", clientSocket.sock);
	if ( clientSocket.Send((char*)pkt.GetBuffer(paklen), pkt.GetLength(), 0) == FALSE ) {
		OutputDebugStringA("\nSEND FAILED\n");
		return FALSE;
	}
	return TRUE;
}

BOOL32 _NETWORK_API TClientHandler::NonBlockReceive(TPacket &pkt) {
	clientSocket.SetInterval(0, 0);
	int rcv = 0;
	unsigned int paklen = 0;
	clientSocket.Select(TRUE, FALSE, FALSE, TRUE);
	if(clientSocket.IsReadable()) {
		rcv = clientSocket.Receive((char*)pkt.GetBuffer(paklen), paklen, 0);
		if ( rcv >= 0 ) {
			PacketHandler((char*)pkt.GetBuffer(paklen));
		} else {
		}
	} else {
	}
	return TRUE;
}

BOOL32 _NETWORK_API TClientHandler::Receive(TPacket &pkt) {
	return TRUE;
}
void _NETWORK_API TClientHandler::Run() {
}

BOOL32 _NETWORK_API TClientHandler::Cleanup() {
	clientSocket.CloseSocket();
	clientSocket.Cleanup();
	return TRUE;
}

void _NETWORK_API TClientHandler::PacketHandler(char *buf) {
}
