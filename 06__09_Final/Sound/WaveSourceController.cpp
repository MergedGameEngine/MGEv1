///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _BASE_IMPORT
#define _SOUND_EXPORT

#include "string.h"
#include "ALee.h"
#undef GetClassName
#include "..\Base\Type.h"
#include "..\Base\Base.h"

#undef _ARRAY_API
#define _ARRAY_API _SOUND_API
#include "WaveSourceController.hpp"

_SOUND_API TWaveSourceController::TWaveSourceController() {
}
_SOUND_API TWaveSourceController::~TWaveSourceController() {
}

char _SOUND_API *TWaveSourceController::GetClassName() {
	return "TWaveSourceController";
}
int _SOUND_API TWaveSourceController::GetClassCode() {
	return CLSID_TWaveSourceController;
}
int _SOUND_API TWaveSourceController::GetHashCode() {
	return 1;
}
BOOL32 _SOUND_API TWaveSourceController::IsInstanceof(const char* className) {
	if ( strcmp("TWaveSourceController", className) == 0 ) {
		return TRUE;
	}
	if ( strcmp("IObject", className) == 0 ) {
		return TRUE;
	}
	return FALSE;
}
BOOL32 _SOUND_API TWaveSourceController::IsEqualto(IObject &obj) {
	return FALSE;
}
void _SOUND_API TWaveSourceController::Serialize(IIOStream &iio) {
}
void _SOUND_API TWaveSourceController::Wait() {
}
void _SOUND_API TWaveSourceController::Notify() {
}
