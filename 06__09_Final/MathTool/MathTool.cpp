///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

//
//		MathTool Templates
//

#define _BASE_IMPORT
#define _MATHTOOL_EXPORT

#include "string.h"
#include "..\Base\Type.h"
#include "..\Base\Base.h"
#include "..\MathTool\MathTool.h"
#undef _ARRAY_API
#define _ARRAY_API _MATHTOOL_API
#include "..\Base\Array.h"
#include "..\Base\Array.hpp"
#include "..\Base\RefArray.h"
#include "..\Base\RefArray.hpp"
extern "C" template _MATHTOOL_API TArray<Triangle>;
extern "C" template _MATHTOOL_API TArray<TexCoord2f>;
extern "C" template _MATHTOOL_API TArray<Vector3f>;
extern "C" template _MATHTOOL_API TArray<Vector4f>;
extern "C" template _MATHTOOL_API TArray<Matrix22f>;
extern "C" template _MATHTOOL_API TArray<Matrix33f>;
extern "C" template _MATHTOOL_API TArray<Matrix44f>;
extern "C" template _MATHTOOL_API TArray<Matrix34f>;
extern "C" template _MATHTOOL_API TArray<Quaternion>;
extern "C" template _MATHTOOL_API TArray<Transform>;
typedef TArray<Matrix44f> TMatrix44fArray;
extern "C" template _MATHTOOL_API TRefArray<TMatrix44fArray>;
