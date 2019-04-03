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

_THREAD_API TThread::TThread() {
}
_THREAD_API TThread::~TThread() {
}

char _THREAD_API *TThread::GetClassName() {
	return "TThread";
}
int _THREAD_API TThread::GetClassCode() {
	return CLSID_TThread;
}
int _THREAD_API TThread::GetHashCode() {
	return 1;
}
BOOL32 _THREAD_API TThread::IsInstanceof(const char* className) {
	if (strcmp("TThread", className) == 0) {
		return TRUE;
	} else if (strcmp("IObject", className) == 0) {
		return TRUE;
	}
	return FALSE;
}
BOOL32 _THREAD_API TThread::IsEqualto(IObject &obj) {
	return FALSE;
}
void _THREAD_API TThread::Serialize(IIOStream &iio) {
}
void _THREAD_API TThread::Wait() {
}
void _THREAD_API TThread::Notify() {
}


void  _THREAD_API *TThread::ptEntry(void *arg) {
	TThread &pt = *(TThread*)arg;
	pt.Run();
	return (NULL);
}

void _THREAD_API TThread::Run() {
	unsigned int addr = (unsigned int)this;
	printf("\n Hello World , PThread @ %8X \n ", addr);
}

void _THREAD_API TThread::Exit() {
	pthread_exit (NULL);
}

int _THREAD_API TThread::SetCancelState(int state, int &oldstate) {
	return pthread_setcancelstate (state, &oldstate);
}

int _THREAD_API TThread::SetCancelType(int type, int &oldtype) {
	return pthread_setcanceltype (type, &oldtype);
}

void _THREAD_API TThread::TestCancel() {
	pthread_testcancel();
}

void _THREAD_API TThread::Start() {
	pthread_attr_init(&pthread_custom_attr);
	pthread_create(&pThread, &pthread_custom_attr, TThread::ptEntry, this);
}

int _THREAD_API TThread::Create() {
	return pthread_create(&pThread, &pthread_custom_attr, TThread::ptEntry, this);
}

int _THREAD_API TThread::Cancel() {
	return pthread_cancel(pThread);
}

int _THREAD_API TThread::Detach() {
	return pthread_detach(pThread);
}

int _THREAD_API TThread::Join() {
	return pthread_join(pThread, NULL);
}

int _THREAD_API TThread::Delay(int sec, int nsec) {
	timespec delay;
	delay.tv_sec = sec;
	delay.tv_nsec = nsec;
	return pthread_delay_np( &delay );
}

int _THREAD_API TThread::NumProcessors() {
	return pthread_num_processors_np();
}

int _THREAD_API TThread::AttribInit() {
	return pthread_attr_init (&pthread_custom_attr);
}
int _THREAD_API TThread::AttribDestroy() {
	return pthread_attr_destroy (&pthread_custom_attr);
}
int _THREAD_API TThread::GetDetachState(int &detachstate) {
	return pthread_attr_getdetachstate (&pthread_custom_attr, &detachstate);
}
int _THREAD_API TThread::GetStackAddress(void **stackaddr) {
	return pthread_attr_getstackaddr (&pthread_custom_attr, stackaddr);
}
int _THREAD_API TThread::GetStackSize(unsigned int &stacksize) {
	size_t stks;
	int retcode = pthread_attr_getstacksize (&pthread_custom_attr, &stks);
	stacksize = (unsigned int)stks;
	return retcode;
}
int _THREAD_API TThread::SetDetachState(int detachstate) {
	return pthread_attr_setdetachstate (&pthread_custom_attr, detachstate);
}
int _THREAD_API TThread::SetStackAddress(void *stackaddr) {
	return pthread_attr_setstackaddr (&pthread_custom_attr, stackaddr);
}
int _THREAD_API TThread::SetStackSize(unsigned int stacksize) {
	return pthread_attr_setstacksize (&pthread_custom_attr, (size_t)stacksize);
}
int _THREAD_API TThread::GetSchedParam(int &priority) {
	priority = sche.sched_priority; 
	return pthread_attr_getschedparam (&pthread_custom_attr, &sche);
}
int _THREAD_API TThread::SetSchedParam(int priority) {
	sche.sched_priority = priority;
	return pthread_attr_setschedparam (&pthread_custom_attr, &sche);
}
int _THREAD_API TThread::SetSchedPolicy(int policy) {
	return pthread_attr_setschedpolicy (&pthread_custom_attr, policy);
}
int _THREAD_API TThread::GetSchedPolicy(int &policy) {
	return pthread_attr_getschedpolicy (&pthread_custom_attr, &policy);
}
int _THREAD_API TThread::SetInheritSched(int inheritsched) {
	return pthread_attr_setinheritsched(&pthread_custom_attr, inheritsched);
}
int _THREAD_API TThread::GetInheritSched(int &inheritsched) {
	return pthread_attr_getinheritsched(&pthread_custom_attr, &inheritsched);
}
int _THREAD_API TThread::SetScope(int scope) {
	return pthread_attr_setscope (&pthread_custom_attr, scope);
}
int _THREAD_API TThread::GetScope(int &scope) {
	return pthread_attr_getscope (&pthread_custom_attr, &scope);
}
