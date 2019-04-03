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
#include "Section.hpp"

_CORE_API TSection::TSection() {
}
_CORE_API TSection::~TSection() {
}
char _CORE_API *TSection::GetClassName() {
	return "TSection";
}
int _CORE_API TSection::GetClassCode() {
	return CLSID_TSection;
}
int _CORE_API TSection::GetHashCode() {
	return 1;
}
BOOL32 _CORE_API TSection::IsInstanceof(const char* className) {
	if (strcmp("TSection", className)) {
		return TRUE;
	}
	if (strcmp("IObject", className)) {
		return TRUE;
	}
	return FALSE;
}
BOOL32 _CORE_API TSection::IsEqualto(IObject &obj) {
	return FALSE;
}
void _CORE_API TSection::Serialize(IIOStream &iio) {
}
void _CORE_API TSection::Wait() {
}
void _CORE_API TSection::Notify() {
}
