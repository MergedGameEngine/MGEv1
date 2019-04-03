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
#include "../Base/Type.h"
#include "../Base/Base.h"
#define _ARRAY_API _CORE_API
#include "Level.hpp"

_CORE_API TLevel::TLevel() {
}
_CORE_API TLevel::~TLevel() {
}
char _CORE_API *TLevel::GetClassName() {
	return "TLevel";
}
int _CORE_API TLevel::GetClassCode() {
	return CLSID_TLevel;
}
int _CORE_API TLevel::GetHashCode() {
	return 1;
}
BOOL32 _CORE_API TLevel::IsInstanceof(const char* className) {
	if (strcmp("TLevel", className)) {
		return TRUE;
	}
	if (strcmp("IObject", className)) {
		return TRUE;
	}
	return FALSE;
}
BOOL32 _CORE_API TLevel::IsEqualto(IObject &obj) {
	return FALSE;
}
void _CORE_API TLevel::Serialize(IIOStream &iio) {
}
void _CORE_API TLevel::Wait() {
}
void _CORE_API TLevel::Notify() {
}
