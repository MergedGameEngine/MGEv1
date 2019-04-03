///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _TSOCKET_H_
#define _TSOCKET_H_

extern "C" class _NETWORK_API TSocket {
public:
	TSocket();
	virtual ~TSocket();
public:
	sockaddr_in addr;
	SOCKET sock;

	fd_set fdrecv;
	fd_set fdsend;
	fd_set fdexcp;
	timeval interval;
public:
public:
	void SetAddress(char *ip);
	void SetFamily(short f);
	void SetPort(unsigned short p);
	int Startup(unsigned short version);
	BOOL32 CloseSocket();
	int Cleanup();

	int Receive(char *buf, int length, int flag);
	int Send(const char *buf, int length, int flag);

	BOOL32 Socket(int family, int type, int protocol);

//	Used by server
	BOOL32 Bind();
	BOOL32 Listen(int backlog);

	BOOL32 Accept(TSocket &tar);

//	Used by client
	BOOL32 Connect();


//	Probo
	void SetInterval(unsigned int sec, unsigned int usec);
	BOOL32 Select(BOOL32 enableread, BOOL32 enablewrite, BOOL32 enableexcept, BOOL32 enabletimeval);
	BOOL32 IsReadable();
	BOOL32 IsWritable();
};

#endif