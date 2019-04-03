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
#include "ShaderController.hpp"

_RENDERER_API TShaderController::TShaderController() {
	shaders.Resize(0);
}

_RENDERER_API TShaderController::~TShaderController() {
	shaders.DeleteAll();
	shaders.Resize(0);
}

char _RENDERER_API *TShaderController::GetClassName() {
	return "TShaderController";
}

int _RENDERER_API TShaderController::GetClassCode() {
	return CLSID_TShaderController;
}

int _RENDERER_API TShaderController::GetHashCode() {
	return 1;
}

BOOL32 _RENDERER_API TShaderController::IsInstanceof(const char* className) {
	if (strcmp("TShaderController", className) == 0) {
		return TRUE;
	} else if (strcmp("IObject", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

BOOL32 _RENDERER_API TShaderController::IsEqualto(IObject &obj) {
	return FALSE;
}

void _RENDERER_API TShaderController::Serialize(IIOStream &iio) {
}

void _RENDERER_API TShaderController::Wait() {
}

void _RENDERER_API TShaderController::Notify() {
}

