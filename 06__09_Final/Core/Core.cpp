///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _CORE_EXPORT

#define _MATHTOOL_IMPORT
#define _BASE_IMPORT
#define _FILE_IMPORT
#define _MODEL_IMPORT
#define _THREAD_IMPORT
#define _RENDERER_IMPORT
#define _NETWORK_IMPORT

#include "../Renderer/GLee.h"
#include "winsock.h"
#undef GetClassName
#undef PostMessage
#include "string.h"
#include "../Base/Type.h"
#include "../Base/Base.h"
#define _ARRAY_API _CORE_API
#include "Core.hpp"


_CORE_API TCore::TCore() {
	messageQueue.Resize(128);
	queueHead = 0;
	queueTail = 0;
	queueLength = messageQueue.GetLength();
	queueRWLock.AttribInit();
	queueRWLock.Init();
}
_CORE_API TCore::~TCore() {
	queueRWLock.Unlock();
	queueRWLock.Destroy();
	queueRWLock.AttribDestroy();
	messageQueue.Resize(0);
}
char _CORE_API *TCore::GetClassName() {
	return "TCore";
}
int _CORE_API TCore::GetClassCode() {
	return CLSID_TCore;
}
int _CORE_API TCore::GetHashCode() {
	return 1;
}
BOOL32 _CORE_API TCore::IsInstanceof(const char* className) {
	if (strcmp("TCore", className)) {
		return TRUE;
	}
	return TThread::IsInstanceof(className);
}
BOOL32 _CORE_API TCore::IsEqualto(IObject &obj) {
	return FALSE;
}
void _CORE_API TCore::Serialize(IIOStream &iio) {
}
void _CORE_API TCore::Wait() {
}
void _CORE_API TCore::Notify() {
}

void _CORE_API TCore::Run() {
	TMessage msg;
	while(TRUE) {
		if ( queueHead != queueTail ) {
			queueRWLock.ReadLock();
			msg = messageQueue[queueTail];
			queueTail ++;
			queueTail = queueTail % queueLength;
			queueRWLock.Unlock();
			MessageHandler(msg);
		}
		Delay(0, interval);
	}
}
void _CORE_API TCore::PostMessage(TMessage &msg) {
	if ( queueTail == ( ( queueHead + 1 ) % queueLength ) ) {
		Delay(0, interval);
	} else {
		queueRWLock.WriteLock();
		messageQueue[queueHead] = msg;
		queueHead ++;
		queueHead = queueHead % queueLength;
		queueRWLock.Unlock();
	}
}
void _CORE_API TCore::MessageHandler(TMessage &msg) {
	TWindow::MessageHandler(msg);
}


void _CORE_API TCore::LoadConfigFile(TString &fn, TConfigFile &cf) {
	char fileName[256];
	fn.GetStringASC(fileName);
	TFile fd;
	fd.SetFilePathNameASC(fileName);
	fd.SetOpenMode(TFile::modeRead | TFile::typeBinary);
	fd.Open();
	TFileIOStream fdio;
	fdio.SetFile(&fd);
	fdio.SetEndian(IIOStream::little_endian);
	fdio.SetLoadStore(IIOStream::load);
	cf.Serialize(fdio);
	fdio.Close();
	fd.Close();
}
void _CORE_API TCore::LoadShader(TConfigFile &cf) {
}
