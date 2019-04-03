///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

//
//		Network Package import
//

#ifndef _NETWORKIMORT_H_
#define _NETWORKIMORT_H_

#include "../Network/Blowfish.h"
#include "../Network/Packet.h"
#include "../Network/TSocket.h"
#include "../Network/Client.h"
#include "../Network/ClientHandler.h"
#include "../Network/Server.h"
#ifdef _ARRAY_API
#ifdef TRefArray
extern "C" template class _NETWORK_API TRefArray<TPacket>;
extern "C" template class _NETWORK_API TRefArray<TClient>;
extern "C" template class _NETWORK_API TRefArray<TClientHandler>;
extern "C" template class _NETWORK_API TRefArray<TServer>;
#endif
#endif

#endif