///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _BASE_IMPORT
#define _THREAD_EXPORT

#include "string.h"
#include "Thread.h"

_THREAD_API TBarrier::TBarrier() {
}
_THREAD_API TBarrier::~TBarrier() {
}

char _THREAD_API *TBarrier::GetClassName() {
	return "TBarrier";
}
int _THREAD_API TBarrier::GetClassCode() {
	return CLSID_TBarrier;
}
int _THREAD_API TBarrier::GetHashCode() {
	return 1;
}
BOOL32 _THREAD_API TBarrier::IsInstanceof(const char* className) {
	if (strcmp("TBarrier", className) == 0) {
		return TRUE;
	} else if (strcmp("IObject", className) == 0) {
		return TRUE;
	}
	return FALSE;
}
BOOL32 _THREAD_API TBarrier::IsEqualto(IObject &obj) {
	return FALSE;
}
void _THREAD_API TBarrier::Serialize(IIOStream &iio) {
}
void _THREAD_API TBarrier::Wait() {
}
void _THREAD_API TBarrier::Notify() {
}

int _THREAD_API TBarrier::Init(unsigned int count) {
	return pthread_barrier_init (&barrier, &attr, count);
}
int _THREAD_API TBarrier::Destroy() {
	return pthread_barrier_destroy (&barrier);
}
int _THREAD_API TBarrier::BarrierWait() {
	return pthread_barrier_wait (&barrier);
}
int _THREAD_API TBarrier::AttribInit() {
	return pthread_barrierattr_init (&attr);
}
int _THREAD_API TBarrier::AttribDestroy() {
	return pthread_barrierattr_destroy (&attr);
}
int _THREAD_API TBarrier::GetpShared(int &pshared) {
	return pthread_barrierattr_getpshared (&attr, &pshared);
}
int _THREAD_API TBarrier::SetpShared(int pshared) {
	return pthread_barrierattr_setpshared (&attr, pshared);
}
