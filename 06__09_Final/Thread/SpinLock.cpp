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

_THREAD_API TSpinLock::TSpinLock() {
}
_THREAD_API TSpinLock::~TSpinLock() {
}

char _THREAD_API *TSpinLock::GetClassName() {
	return "TSpinLock";
}
int _THREAD_API TSpinLock::GetClassCode() {
	return CLSID_TSpinLock;
}
int _THREAD_API TSpinLock::GetHashCode() {
	return 1;
}
BOOL32 _THREAD_API TSpinLock::IsInstanceof(const char* className) {
	if (strcmp("TSpinLock", className) == 0) {
		return TRUE;
	} else if (strcmp("IObject", className) == 0) {
		return TRUE;
	}
	return FALSE;
}
BOOL32 _THREAD_API TSpinLock::IsEqualto(IObject &obj) {
	return FALSE;
}
void _THREAD_API TSpinLock::Serialize(IIOStream &iio) {
}
void _THREAD_API TSpinLock::Wait() {
}
void _THREAD_API TSpinLock::Notify() {
}

int _THREAD_API TSpinLock::Init(int pshared) {
	return pthread_spin_init (&lock, pshared);
}
int _THREAD_API TSpinLock::Destroy() {
	return pthread_spin_destroy (&lock);
}
int _THREAD_API TSpinLock::Lock() {
	return pthread_spin_lock (&lock);
}
int _THREAD_API TSpinLock::TryLock() {
	return pthread_spin_trylock (&lock);
}
int _THREAD_API TSpinLock::Unlock() {
	return pthread_spin_unlock (&lock);
}
