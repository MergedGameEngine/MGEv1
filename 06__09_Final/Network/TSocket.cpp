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
#undef SetPort
#include "..\Base\Type.h"
#include "..\Base\Base.h"
#include "TSocket.h"

_NETWORK_API TSocket::TSocket() {
	sock = 0;
}
_NETWORK_API TSocket::~TSocket() {
}

void _NETWORK_API TSocket::SetAddress(char *ip) {
	addr.sin_addr.S_un.S_addr = inet_addr(ip);
}
void _NETWORK_API TSocket::SetFamily(short f) {
	addr.sin_family = f;
}
void _NETWORK_API TSocket::SetPort(unsigned short p) {
	addr.sin_port = htons(p);
}

int _NETWORK_API TSocket::Startup(unsigned short version) {
	WSADATA wsaData;
	return WSAStartup(version, &wsaData);
}
BOOL32 _NETWORK_API TSocket::CloseSocket() {
	if ( closesocket(sock) == SOCKET_ERROR ) {
		return FALSE;
	}
	return TRUE;
}
int _NETWORK_API TSocket::Cleanup() {
	return WSACleanup();
}

int _NETWORK_API TSocket::Receive(char *buf, int length, int flag) {
	return recv(sock, buf, length, flag);
}
int _NETWORK_API TSocket::Send(const char *buf, int length, int flag) {
	return send(sock, buf, length, flag);
}

BOOL32 _NETWORK_API TSocket::Socket(int family, int type, int protocol) {
	if ( ( sock = socket(family, type, protocol) ) == INVALID_SOCKET ) {
		return FALSE;
	}
	return TRUE;
}

//	Used by server
BOOL32 _NETWORK_API TSocket::Bind() {
	if ( bind(sock, (sockaddr*)&addr, sizeof(sockaddr)) == SOCKET_ERROR ) {
		return FALSE;
	}
	return TRUE;
}
BOOL32 _NETWORK_API TSocket::Listen(int backlog) {
	if ( listen(sock, backlog) == SOCKET_ERROR ) {
		return FALSE;
	}
	return TRUE; 
}

BOOL32 _NETWORK_API TSocket::Accept(TSocket &tar) {
	int sockaddrlen = sizeof(sockaddr);
	if ( (tar.sock = accept(sock, (sockaddr*)&tar.addr, &sockaddrlen)) == INVALID_SOCKET ) {
		return FALSE;
	}
	return TRUE;
}

//	Used by client
BOOL32 _NETWORK_API TSocket::Connect() {
	if ( connect(sock, (sockaddr*)&addr, sizeof(sockaddr)) == SOCKET_ERROR ) {
		return FALSE;
	}
	return TRUE;
}


//	Probo
void _NETWORK_API TSocket::SetInterval(unsigned int sec, unsigned int usec) {
	interval.tv_sec = (long)sec;
	interval.tv_usec = (long)usec;
}
BOOL32 _NETWORK_API TSocket::Select(BOOL32 enableread, BOOL32 enablewrite, BOOL32 enableexcept, BOOL32 enabletimeval) {
	fd_set *pfdrecv = NULL;
	fd_set *pfdsend = NULL;
	fd_set *pfdexcp = NULL;
	timeval *pinterval = NULL;
	if ( enableread ) {
		FD_ZERO(&fdrecv);
		FD_SET(sock, &fdrecv);
		pfdrecv = &fdrecv;
	}
	if ( enablewrite ) {
		FD_ZERO(&fdsend);
		FD_SET(sock, &fdsend);
		pfdsend = &fdsend;
	}
	if ( enableexcept ) {
		FD_ZERO(&fdexcp);
		FD_SET(sock, &fdexcp);
		pfdexcp = &fdexcp;
	}
	if ( enabletimeval ) {
		pinterval = &interval;
	}
	if ( enableread || enablewrite || enableexcept ) {
		if ( select(0, pfdrecv, pfdsend, pfdexcp, pinterval) == SOCKET_ERROR ) {
			return FALSE;
		}
	} else {
		return FALSE;
	}
	return TRUE;
}
BOOL32 _NETWORK_API TSocket::IsReadable() {
	if(FD_ISSET(sock, &fdrecv)) {
		return TRUE;
	} else {
		return FALSE;
	}
}
BOOL32 _NETWORK_API TSocket::IsWritable() {
	if(FD_ISSET(sock, &fdsend)) {
		return TRUE;
	} else {
		return FALSE;
	}
}
