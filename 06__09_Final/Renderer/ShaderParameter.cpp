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
#include "ShaderParameter.hpp"

_RENDERER_API TShaderParameter::TShaderParameter() {
}

_RENDERER_API TShaderParameter::~TShaderParameter() {
}

char _RENDERER_API *TShaderParameter::GetClassName() {
	return "TShaderParameter";
}

int _RENDERER_API TShaderParameter::GetClassCode() {
	return CLSID_TShaderParameter;
}

int _RENDERER_API TShaderParameter::GetHashCode() {
	return 1;
}

BOOL32 _RENDERER_API TShaderParameter::IsInstanceof(const char* className) {
	if (strcmp("TShaderParameter", className) == 0) {
		return TRUE;
	} else if (strcmp("IObject", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

BOOL32 _RENDERER_API TShaderParameter::IsEqualto(IObject &obj) {
	return FALSE;
}

void _RENDERER_API TShaderParameter::Serialize(IIOStream &iio) {
}

void _RENDERER_API TShaderParameter::Wait() {
}

void _RENDERER_API TShaderParameter::Notify() {
}


void _RENDERER_API TShaderParameter::SetCode(unsigned short code) {
	parameterCode = code;
}
void _RENDERER_API TShaderParameter::SetName(GLchar *name) {
	if ( strlen (name) < 127 ) {
		strcpy(parameterName, name);
	}
}
void _RENDERER_API TShaderParameter::SetLocation(GLuint program) {
	if ( ( parameterCode & 0xFF00 ) == 0x0000 ) {
		location = glGetAttribLocation(program, parameterName);
	} else {
		location = glGetUniformLocation(program, parameterName);
	}
}
unsigned short _RENDERER_API TShaderParameter::GetCode() {
	return parameterCode;
}
GLchar _RENDERER_API *TShaderParameter::GetName() {
	return parameterName;
}
GLint _RENDERER_API TShaderParameter::GetLocation() {
	return location;
}
