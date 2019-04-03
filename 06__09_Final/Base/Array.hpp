///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _ARRAY_HPP_
#define _ARRAY_HPP_

#ifdef _ARRAY_API

#include "CRC32.h"

template <typename T> _ARRAY_API TArray<T>::TArray<T>() {
	buffer = NULL;
	length = 0;
	isBufferLocked = FALSE;
}

template <typename T> _ARRAY_API TArray<T>::TArray<T>(unsigned int size) {
	buffer = new T[size];
	length = size;
	isBufferLocked = FALSE;
}

template <typename T> _ARRAY_API TArray<T>::~TArray<T>() {
	if (!isBufferLocked) {
		if (buffer!=NULL) {
			delete []buffer;
			buffer = NULL;
		}
	} else {
		isBufferLocked = FALSE;
	}
}

template <typename T> void _ARRAY_API TArray<T>::Resize(unsigned int size) {
	if (size > 0) {
		T *newBuffer = new T[size];
		if (size < length) {
			memcpy(newBuffer, buffer, sizeof(T) * size);
		} else {
			memcpy(newBuffer, buffer, sizeof(T) * length);
		}
		if (buffer!=NULL) {
			delete []buffer;
			buffer = NULL;
		}
		buffer = newBuffer;
		length = size;
	} else {
		if (buffer!=NULL) {
			delete []buffer;
			buffer = NULL;
		}
		length = 0;
	}
}

template <typename T> T _ARRAY_API &TArray<T>::operator[](unsigned int index) {
	if (index < length) {
		return buffer[index];
	} else {
		return *(T*)NULL;
	}
}

template <typename T> TArray<T> _ARRAY_API TArray<T>::operator + (const TArray<T> &src) {
	TArray<T> desc(length + src.length);
	memcpy(desc.buffer, buffer, sizeof(T) * length);
	memcpy(&(desc.buffer[length]), src.buffer, sizeof(T) * src.length);
	desc.isBufferLocked = TRUE;
	return desc;
}

template <typename T> TArray<T> _ARRAY_API &TArray<T>::operator = (const TArray<T> &src) {
	if ( this != &src ) {
		if (buffer != NULL) {
			delete []buffer;
			buffer = NULL;
		}
		if (src.buffer != NULL) {
			if (src.isBufferLocked) {
				buffer = src.buffer;
			} else {
				buffer = new T[src.length];
				memcpy (buffer, src.buffer, src.length * sizeof(T));
			}
		}
		length = src.length;
	}
	isBufferLocked = FALSE;
	return *this;
}

template <typename T> TArray<T> _ARRAY_API &TArray<T>::operator += (const TArray<T> &src) {
	if ( src.length > 0 ) {
		T *newBuffer = new T[length + src.length];
		memcpy( newBuffer, buffer, sizeof(T) * length );
		memcpy( &(newBuffer[length]), src.buffer, sizeof(T) * src.length);
		length += src.length;
		if (buffer!=NULL) {
			delete []buffer;
		}
		buffer = newBuffer;
	}
	isBufferLocked = FALSE;
	return *this;
}

template <typename T> TArray<T> _ARRAY_API TArray<T>::SubArray(const unsigned int begin, const unsigned int count) {
	TArray des;
	if ((begin + count) <= length) {
		des.Resize(count);
		memcpy(des.buffer, &(buffer[begin]), sizeof(T) * count);
	}
	des.isBufferLocked = TRUE;
	return des;
}

template <typename T> unsigned int _ARRAY_API TArray<T>::GetLength() {
	return length;
}

template <typename T> const void _ARRAY_API *TArray<T>::GetBuffer() {
	return buffer;
}

template <typename T> char _ARRAY_API *TArray<T>::GetClassName() {
	return "TArray";
}

template <typename T> int _ARRAY_API TArray<T>::GetClassCode() {
	return CLSID_TArray;
}

template <typename T> int _ARRAY_API TArray<T>::GetHashCode() {
	return CRC32::GetCRC32(buffer, sizeof(T) * length);
}

template <typename T> BOOL32 _ARRAY_API TArray<T>::IsInstanceof(const char* className) {
	if (strcmp("TArray", className) == 0) {
		return TRUE;
	} else if (strcmp("IObject", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

template <typename T> BOOL32 _ARRAY_API TArray<T>::IsEqualto(IObject &obj) {
	return FALSE;
}

template <typename T> void _ARRAY_API TArray<T>::Serialize(IIOStream &iio) {
}

template <typename T> void _ARRAY_API TArray<T>::Wait() {
}

template <typename T> void _ARRAY_API TArray<T>::Notify() {
}

#endif

#endif