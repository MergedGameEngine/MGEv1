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
#include "LightController.hpp"
#include "..\MathTool\MathTool.h"

_RENDERER_API TLightController::TLightController() {
	lights.Resize(0);
}

_RENDERER_API TLightController::~TLightController() {
	lights.DeleteAll();
	lights.Resize(0);
}

char _RENDERER_API *TLightController::GetClassName() {
	return "TLightController";
}

int _RENDERER_API TLightController::GetClassCode() {
	return CLSID_TLightController;
}

int _RENDERER_API TLightController::GetHashCode() {
	return 1;
}

BOOL32 _RENDERER_API TLightController::IsInstanceof(const char* className) {
	if (strcmp("TLightController", className) == 0) {
		return TRUE;
	} else if (strcmp("IObject", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

BOOL32 _RENDERER_API TLightController::IsEqualto(IObject &obj) {
	return FALSE;
}

void _RENDERER_API TLightController::Serialize(IIOStream &iio) {
}

void _RENDERER_API TLightController::Wait() {
}

void _RENDERER_API TLightController::Notify() {
}

