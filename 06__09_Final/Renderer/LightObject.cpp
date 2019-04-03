///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _BASE_IMPORT
#define _MATHTOOL_IMPORT
#define _RENDERER_EXPORT

#include "string.h"
#include "GLee.h"
#undef GetClassName
#include "..\Base\Type.h"
#include "..\Base\Base.h"
#undef _ARRAY_API
#define _ARRAY_API _RENDERER_API
#include "LightObject.hpp"
#include "..\MathTool\MathTool.h"

_RENDERER_API TLightObject::TLightObject() {
}

_RENDERER_API TLightObject::~TLightObject() {
}

char _RENDERER_API *TLightObject::GetClassName() {
	return "TLightObject";
}

int _RENDERER_API TLightObject::GetClassCode() {
	return CLSID_TLightObject;
}

int _RENDERER_API TLightObject::GetHashCode() {
	return 1;
}

BOOL32 _RENDERER_API TLightObject::IsInstanceof(const char* className) {
	if (strcmp("TLightObject", className) == 0) {
		return TRUE;
	} else if (strcmp("IObject", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

BOOL32 _RENDERER_API TLightObject::IsEqualto(IObject &obj) {
	return FALSE;
}

void _RENDERER_API TLightObject::Serialize(IIOStream &iio) {
}

void _RENDERER_API TLightObject::Wait() {
}

void _RENDERER_API TLightObject::Notify() {
}

