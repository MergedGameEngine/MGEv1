///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

//
//		Base Package import
//

#ifndef _BASEIMORT_H_
#define _BASEIMORT_H_

#ifdef _ARRAY_API
#ifdef TArray
extern "C" template class _BASE_API TArray<int>;
extern "C" template class _BASE_API TArray<short>;
extern "C" template class _BASE_API TArray<char>;
extern "C" template class _BASE_API TArray<unsigned int>;
extern "C" template class _BASE_API TArray<unsigned char>;
extern "C" template class _BASE_API TArray<float>;
extern "C" template class _BASE_API TArray<double>;
extern "C" template class _BASE_API TArray<unsigned short>;
typedef TArray<unsigned short> TUShortArray;
#endif
#ifdef TRefArray
extern "C" template class _BASE_API TRefArray<TUShortArray>;
extern "C" template class _BASE_API TRefArray<TString>;
#endif
#endif

#endif