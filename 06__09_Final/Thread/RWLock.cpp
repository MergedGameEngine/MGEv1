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

_THREAD_API TRWLock::TRWLock() {
}
_THREAD_API TRWLock::~TRWLock() {
}

char _THREAD_API *TRWLock::GetClassName() {
	return "TRWLock";
}
int _THREAD_API TRWLock::GetClassCode() {
	return CLSID_TRWLock;
}
int _THREAD_API TRWLock::GetHashCode() {
	return 1;
}
BOOL32 _THREAD_API TRWLock::IsInstanceof(const char* className) {
	if (strcmp("TRWLock", className) == 0) {
		return TRUE;
	} else if (strcmp("IObject", className) == 0) {
		return TRUE;
	}
	return FALSE;
}
BOOL32 _THREAD_API TRWLock::IsEqualto(IObject &obj) {
	return FALSE;
}
void _THREAD_API TRWLock::Serialize(IIOStream &iio) {
}
void _THREAD_API TRWLock::Wait() {
}
void _THREAD_API TRWLock::Notify() {
}

int _THREAD_API TRWLock::Init() {
	return pthread_rwlock_init(&lock, &attr);
}
int _THREAD_API TRWLock::Destroy() {
	return pthread_rwlock_destroy(&lock);
}
int _THREAD_API TRWLock::TryReadLock() {
	return pthread_rwlock_tryrdlock(&lock);
}
int _THREAD_API TRWLock::TryWriteLock() {
	return pthread_rwlock_trywrlock(&lock);
}
int _THREAD_API TRWLock::ReadLock() {
	return pthread_rwlock_rdlock(&lock);
}
int _THREAD_API TRWLock::TimedReadLock(const struct timespec *abstime) {
	return pthread_rwlock_timedrdlock(&lock, abstime);
}
int _THREAD_API TRWLock::WriteLock() {
	return pthread_rwlock_wrlock(&lock);
}
int _THREAD_API TRWLock::TimedWriteLock(const struct timespec *abstime) {
	return pthread_rwlock_timedwrlock(&lock, abstime);
}
int _THREAD_API TRWLock::Unlock() {
	return pthread_rwlock_unlock(&lock);
}
int _THREAD_API TRWLock::AttribInit() {
	return pthread_rwlockattr_init (&attr);
}
int _THREAD_API TRWLock::AttribDestroy() {
	return pthread_rwlockattr_destroy (&attr);
}
int _THREAD_API TRWLock::GetpShared(int &pshared) {
	return pthread_rwlockattr_getpshared (&attr, &pshared);
}
int _THREAD_API TRWLock::SetpShared(int pshared) {
	return pthread_rwlockattr_setpshared (&attr, pshared);
}
