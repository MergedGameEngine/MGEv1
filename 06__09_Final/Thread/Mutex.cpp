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

_THREAD_API TMutex::TMutex() {
}
_THREAD_API TMutex::~TMutex() {
}

char _THREAD_API *TMutex::GetClassName() {
	return "TMutex";
}
int _THREAD_API TMutex::GetClassCode() {
	return CLSID_TMutex;
}
int _THREAD_API TMutex::GetHashCode() {
	return 1;
}
BOOL32 _THREAD_API TMutex::IsInstanceof(const char* className) {
	if (strcmp("TMutex", className) == 0) {
		return TRUE;
	} else if (strcmp("IObject", className) == 0) {
		return TRUE;
	}
	return FALSE;
}
BOOL32 _THREAD_API TMutex::IsEqualto(IObject &obj) {
	return FALSE;
}
void _THREAD_API TMutex::Serialize(IIOStream &iio) {
}
void _THREAD_API TMutex::Wait() {
}
void _THREAD_API TMutex::Notify() {
}


int _THREAD_API TMutex::Init() {
	return pthread_mutex_init (&mutex, &attr);
}
int _THREAD_API TMutex::Destroy() {
	return pthread_mutex_destroy (&mutex);
}
int _THREAD_API TMutex::Lock() {
	return pthread_mutex_lock (&mutex);
}
int _THREAD_API TMutex::TimedLock(const struct timespec *abstime) {
	return pthread_mutex_timedlock(&mutex, abstime);
}
int _THREAD_API TMutex::TryLock() {
	return pthread_mutex_trylock (&mutex);
}
int _THREAD_API TMutex::Unlock() {
	return pthread_mutex_unlock (&mutex);
}
int _THREAD_API TMutex::AttribInit() {
	return pthread_mutexattr_init (&attr);
}
int _THREAD_API TMutex::AttribDestroy() {
	return pthread_mutexattr_destroy (&attr);
}
int _THREAD_API TMutex::GetpShared(int &pshared) {
	return pthread_mutexattr_getpshared (&attr, &pshared);
}
int _THREAD_API TMutex::SetpShared(int pshared) {
	return pthread_mutexattr_setpshared (&attr, pshared);
}
int _THREAD_API TMutex::GetType(int &kind) {
	return pthread_mutexattr_gettype (&attr, &kind);
}
int _THREAD_API TMutex::SetType(int kind) {
	return pthread_mutexattr_settype (&attr, kind);
}


int _THREAD_API TMutex::ConditionInit() {
	return pthread_cond_init (&cond, &condattr);
}
int _THREAD_API TMutex::ConditionDestroy() {
	return pthread_cond_destroy (&cond);
}
int _THREAD_API TMutex::ConditionWait() {
	return pthread_cond_wait (&cond, &mutex);
}
int _THREAD_API TMutex::ConditionTimedwait(const struct timespec *abstime) {
	return pthread_cond_timedwait (&cond, &mutex, abstime);
}
int _THREAD_API TMutex::Signal() {
	return pthread_cond_signal (&cond);
}
int _THREAD_API TMutex::Broadcast() {
	return pthread_cond_broadcast (&cond);
}
int _THREAD_API TMutex::ConditionAttribInit() {
	return pthread_condattr_init (&condattr);
}
int _THREAD_API TMutex::ConditionAttribDestroy() {
	return pthread_condattr_destroy (&condattr);
}
int _THREAD_API TMutex::ConditionAttribGetpShared(int &pshared) {
	return pthread_condattr_getpshared (&condattr, &pshared);
}
int _THREAD_API TMutex::ConditionAttribSetpShared(int pshared) {
	return pthread_condattr_setpshared (&condattr, pshared);
}
