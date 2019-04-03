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
#include "TextureObject.h"
#undef _ARRAY_API
#define _ARRAY_API _RENDERER_API
#include "TextureController.hpp"

_RENDERER_API TTextureController::TTextureController() {
	textures.Resize(0);
}

_RENDERER_API TTextureController::~TTextureController() {
	textures.DeleteAll();
	textures.Resize(0);
}

char _RENDERER_API *TTextureController::GetClassName() {
	return "TTextureController";
}

int _RENDERER_API TTextureController::GetClassCode() {
	return CLSID_TTextureController;
}

int _RENDERER_API TTextureController::GetHashCode() {
	return 1;
}

BOOL32 _RENDERER_API TTextureController::IsInstanceof(const char* className) {
	if (strcmp("TTextureController", className) == 0) {
		return TRUE;
	} else if (strcmp("IObject", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

BOOL32 _RENDERER_API TTextureController::IsEqualto(IObject &obj) {
	return FALSE;
}

void _RENDERER_API TTextureController::Serialize(IIOStream &iio) {
}

void _RENDERER_API TTextureController::Wait() {
}

void _RENDERER_API TTextureController::Notify() {
}

void _RENDERER_API TTextureController::ActiveTexture0() {
	glActiveTexture(GL_TEXTURE0);
}
