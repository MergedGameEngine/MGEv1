///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _BASE_EXPORT


#include "Type.h"
#include "Base.h"
#include "stdio.h"
#include "string.h"
#include "CRC32.h"
#define _ARRAY_API _BASE_API
#include "Array.h"
#include "RefArray.h"
#include "RefArray.hpp"

typedef TArray<unsigned short> TUShortArray;
extern "C" template _BASE_API TRefArray<TUShortArray>;
extern "C" template _BASE_API TRefArray<TString>;

