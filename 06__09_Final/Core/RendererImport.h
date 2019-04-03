///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _RENDERERIMPORT_H_
#define _RENDERERIMPORT_H_

#include "../Renderer/GLTypes.h"

#include "../Renderer/ViewPort.h"

#include "../Renderer/ShaderParameter.h"
#include "../Renderer/ShaderObject.h"
#include "../Renderer/ShaderController.h"
#include "../Renderer/FrameObject.h"
#include "../Renderer/MultiPassShader.h"

#include "../Renderer/LightObject.h"
#include "../Renderer/LightController.h"

#include "../Renderer/TextureObject.h"
#include "../Renderer/TextureController.h"
#include "../Renderer/MultiTexture.h"

#include "../Renderer/MeshObject.h"
#include "../Renderer/MeshController.h"

#ifdef _ARRAY_API
#ifdef TRefArray
extern "C" template class _RENDERER_API TRefArray<TShaderParameter>;
extern "C" template class _RENDERER_API TRefArray<TShaderObject>;
extern "C" template class _RENDERER_API TRefArray<TShaderController>;
extern "C" template class _RENDERER_API TRefArray<TFrameObject>;

extern "C" template class _RENDERER_API TRefArray<TLightObject>;
extern "C" template class _RENDERER_API TRefArray<TLightController>;

extern "C" template class _RENDERER_API TRefArray<TTextureObject>;
extern "C" template class _RENDERER_API TRefArray<TTextureController>;

extern "C" template class _RENDERER_API TRefArray<TMeshObject>;
extern "C" template class _RENDERER_API TRefArray<TMeshController>;
#endif
#endif

#endif