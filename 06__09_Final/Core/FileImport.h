///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

//
//		File Package import
//

#ifndef _FILEIMORT_H_
#define _FILEIMORT_H_

#include "../File/File.h"
#include "../File/FileIOStream.h"
#include "../File/Config.h"
#include "../File/ConfigFile.h"

#ifdef _ARRAY_API
#ifdef TRefArray
extern "C" template class _BASE_API TRefArray<TConfig>;
#endif
#endif

#endif