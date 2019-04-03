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

_THREAD_API TSemaphore::TSemaphore() {
}
_THREAD_API TSemaphore::~TSemaphore() {
}

char _THREAD_API *TSemaphore::GetClassName() {
	return "TSemaphore";
}
int _THREAD_API TSemaphore::GetClassCode() {
	return CLSID_TSemaphore;
}
int _THREAD_API TSemaphore::GetHashCode() {
	return 1;
}
BOOL32 _THREAD_API TSemaphore::IsInstanceof(const char* className) {
	if (strcmp("TSemaphore", className) == 0) {
		return TRUE;
	} else if (strcmp("IObject", className) == 0) {
		return TRUE;
	}
	return FALSE;
}
BOOL32 _THREAD_API TSemaphore::IsEqualto(IObject &obj) {
	return FALSE;
}
void _THREAD_API TSemaphore::Serialize(IIOStream &iio) {
}
void _THREAD_API TSemaphore::Wait() {
}
void _THREAD_API TSemaphore::Notify() {
}


int _THREAD_API TSemaphore::Init(int pshared, unsigned int value) {
	return sem_init (&sem, pshared, value);
}
int _THREAD_API TSemaphore::Destroy() {
	return sem_destroy (&sem);
}
int _THREAD_API TSemaphore::TryWait() {
	return sem_trywait (&sem);
}
int _THREAD_API TSemaphore::SemWait() {
	return sem_wait (&sem);
}
int _THREAD_API TSemaphore::TimedWait(const struct timespec * abstime) {
	return sem_timedwait (&sem, abstime);
}
int _THREAD_API TSemaphore::Post() {
	return sem_post (&sem);
}
int _THREAD_API TSemaphore::PostMultiple(int count) {
	return sem_post_multiple (&sem, count);
}
int _THREAD_API TSemaphore::Open(const char * name, int oflag, mode_t &mode, unsigned int value) {
	return sem_open (name, oflag, mode, value);
}
int _THREAD_API TSemaphore::Close() {
	return sem_close (&sem);
}
int _THREAD_API TSemaphore::Unlink(const char * name) {
	return sem_unlink (name);
}
int _THREAD_API TSemaphore::GetValue(int &sval) {
	return sem_getvalue (&sem, &sval);
}
