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

#include "string.h"
#include "windows.h"
#undef GetClassName
#undef AddParameter
#include "../Base/Type.h"
#include "../Base/Base.h"
#define _ARRAY_API _CORE_API
#include "Animator.hpp"

inline unsigned __int64 GetTimeStamp() {
	_asm {
		RDTSC;//0x0F,0x31
	};
}


_CORE_API TAnimator::TAnimator() {
	arrayRWLock.AttribInit();
	arrayRWLock.Init();
	numCycles = 1.0f;
}
_CORE_API TAnimator::~TAnimator() {
	arrayRWLock.Unlock();
	arrayRWLock.Destroy();
	arrayRWLock.AttribDestroy();
	controllers.Resize(0);
}

void _CORE_API TAnimator::AddController(TAnimationController &controller) {
	arrayRWLock.WriteLock();
	unsigned int l = controllers.GetLength() + 1;
	controllers.Resize(l);
	controllers.Set(l - 1, &controller);
	arrayRWLock.Unlock();
}

void _CORE_API TAnimator::Run() {
	LARGE_INTEGER fq;
	LARGE_INTEGER startc,endc;
	double dfq = 0;
	double delta = 0;
	while (TRUE) {
		QueryPerformanceFrequency(&fq);
		dfq = (double)fq.QuadPart;

		QueryPerformanceCounter(&startc);
		arrayRWLock.ReadLock();
		unsigned int length = controllers.GetLength();
		for ( unsigned int i2 = 0 ; i2 < length ; i2 ++ ) {
			TAnimationController *ac = &controllers[i2];
			if ( ac != NULL ) {
				ac->Flush(interval * numCycles);
			}
		}
		arrayRWLock.Unlock();
		RendererHandler();
		QueryPerformanceCounter(&endc);
		delta = (double)(endc.QuadPart - startc.QuadPart) / dfq / 0.001;

		if ( delta <= interval ) {
			Delay(0, (int)((interval - delta) * 1000000.0));
			numCycles = 1.0f;
		} else {
			unsigned int udelta = (unsigned int)delta;
			unsigned int uinterval = (unsigned int)interval;
			numCycles = (float)(udelta / uinterval + 1);
			Delay(0, (int)(uinterval - udelta / uinterval) * 1000000);
		}
	}
}

void _CORE_API TAnimator::RendererHandler() {
}

char _CORE_API *TAnimator::GetClassName() {
	return "TAnimator";
}
int _CORE_API TAnimator::GetClassCode() {
	return CLSID_TAnimator;
}
int _CORE_API TAnimator::GetHashCode() {
	return 1;
}
BOOL32 _CORE_API TAnimator::IsInstanceof(const char* className) {
	if (strcmp("TAnimator", className)) {
		return TRUE;
	}
	return TThread::IsInstanceof(className);
}
BOOL32 _CORE_API TAnimator::IsEqualto(IObject &obj) {
	return FALSE;
}
void _CORE_API TAnimator::Serialize(IIOStream &iio) {
}
void _CORE_API TAnimator::Wait() {
}
void _CORE_API TAnimator::Notify() {
}

