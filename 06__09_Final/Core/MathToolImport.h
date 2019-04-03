///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

//
//		MathTool Package import
//

#ifndef _MATHTOOLIMORT_H_
#define _MATHTOOLIMORT_H_

#include "..\MathTool\MathTool.h"

#ifdef _ARRAY_API
#ifdef TArray
extern "C" template class _MATHTOOL_API TArray<Triangle>;
extern "C" template class _MATHTOOL_API TArray<TexCoord2f>;
extern "C" template class _MATHTOOL_API TArray<Vector3f>;
extern "C" template class _MATHTOOL_API TArray<Vector4f>;
extern "C" template class _MATHTOOL_API TArray<Matrix22f>;
extern "C" template class _MATHTOOL_API TArray<Matrix33f>;
extern "C" template class _MATHTOOL_API TArray<Matrix44f>;
extern "C" template class _MATHTOOL_API TArray<Matrix34f>;
extern "C" template class _MATHTOOL_API TArray<Quaternion>;
extern "C" template class _MATHTOOL_API TArray<Transform>;
#endif
#endif

#endif