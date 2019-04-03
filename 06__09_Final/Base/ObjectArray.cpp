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

_BASE_API TObjectArray::TObjectArray() {
	objects = NULL;
	length = 0;
	isBufferLocked = FALSE;
}

_BASE_API TObjectArray::TObjectArray(unsigned int size) {
	objects = new IObject*[size];
	length = size;
	for ( unsigned int i1 = 0 ; i1 < length ; i1 ++ ) {
		objects[i1] = NULL;
	}
	isBufferLocked = FALSE;
}

_BASE_API TObjectArray::~TObjectArray() {
	if (!isBufferLocked) {
		if (objects!=NULL) {
			delete []objects;
			objects = NULL;
		}
	} else {
		isBufferLocked = FALSE;
	}
}

void _BASE_API TObjectArray::Resize(unsigned int size) {
	if (size > 0) {
		IObject **newObjects = new IObject*[size];
		if (size < length) {
			memcpy(newObjects, objects, sizeof(IObject*) * size);
			for ( unsigned int i1 = size ; i1 < length ; i1 ++ ) {
				if ( objects[i1] != NULL ) {
					delete objects[i1];
					objects[i1] = NULL;
				}
			}
		} else {
			memcpy(newObjects, objects, sizeof(IObject*) * length);
			for ( unsigned int i1 = length ; i1 < size ; i1 ++ ) {
				newObjects[i1] = NULL;
			}
		}
		if (objects!=NULL) {
			delete []objects;
			objects = NULL;
		}
		objects = newObjects;
		length = size;
	} else {
		for ( unsigned int i1 = 0 ; i1 < length ; i1 ++ ) {
			if ( objects[i1] != NULL ) {
				delete objects[i1];
				objects[i1] = NULL;
			}
		}
		if (objects!=NULL) {
			delete []objects;
			objects = NULL;
		}
		length = 0;
	}
}

const IObject _BASE_API *&TObjectArray::operator[](unsigned int index) {
	if (index < length) {
		return objects[index];
	} else {
		return *(IObject**)NULL;
	}
}
	
TObjectArray _BASE_API TObjectArray::operator + (const TObjectArray &src) {
	TObjectArray desc(length + src.length);
	memcpy(desc.objects, objects, sizeof(IObject*) * length);
	memcpy(&(desc.objects[length]), src.objects, sizeof(IObject*) * src.length);
	desc.isBufferLocked = TRUE;
	return desc;
}

TObjectArray _BASE_API &TObjectArray::operator = (const TObjectArray &src) {
	if ( this != &src ) {
		if (objects!=NULL) {
			delete []objects;
			objects = NULL;
		}
		if (src.objects != NULL) {
			if (src.isBufferLocked) {
				objects = src.objects;
			} else {
				objects = new IObject*[src.length];
				memcpy (objects, src.objects, src.length * sizeof(IObject*));
			}
		}
	}
	isBufferLocked = FALSE;
	return *this;
}

TObjectArray _BASE_API &TObjectArray::operator += (const TObjectArray &src) {
	if ( src.length > 0 ) {
		IObject **newObjects = new IObject*[length + src.length];
		memcpy( newObjects, objects, sizeof(IObject*) * length );
		memcpy( &(newObjects[length]), src.objects, sizeof(IObject*) * src.length);
		length += src.length;
		if (objects!=NULL) {
			delete []objects;
			objects = NULL;
		}
		objects = newObjects;
	}
	isBufferLocked = FALSE;
	return *this;
}

TObjectArray _BASE_API TObjectArray::SubArray(const unsigned int begin, const unsigned int count) {
	TObjectArray des;
	if ((begin + count) <= length) {
		des.Resize(count);
		memcpy(des.objects, &(objects[begin]), sizeof(IObject*) * count);
	}
	des.isBufferLocked = TRUE;
	return des;
}


unsigned int _BASE_API TObjectArray::GetLength() {
	return length;
}

void _BASE_API TObjectArray::DeleteAll() {
	for ( unsigned int i1 = 0 ; i1 < length ; i1 ++ ) {
		if ( objects[i1] != NULL ) {
			delete objects[i1];
			objects[i1] = NULL;
		}
	}
}

unsigned int _BASE_API TObjectArray::Pack() {
	for ( unsigned int i0 = 0 , i1 = 0 , i2 = 0; i2 < length ; i0 ++ ) {
		if ( objects[i1] == NULL ) {
			if ( i1 > i2 ) {
				i2 = i1 + 1;
			}
			if ( objects[i2] != NULL ) {
				objects[i1] = objects[i2]; objects[i2] = NULL;
			} else {
				i2 ++ ;
				if ( i2 >= length ) {
					Resize(i1);
					return length;
				}
			}
		} else {
			i1 ++ ;
			if ( i1 >= length ) {
				break;
			}
		}
	}
	return length;
}

void _BASE_API TObjectArray::Exchange(unsigned int i1, unsigned int i2) {
	if ( ( i1 < length ) && ( i2 < length ) ) {
		IObject *obj = objects[i1];
		objects[i1] = objects[i2];
		objects[i2] = obj;
	}
}

void _BASE_API TObjectArray::Delete(const unsigned int begin, const unsigned int count) {
	if ( (begin + count) <= length) {
		unsigned int end = begin + count;
		for ( unsigned int i1 = begin ; i1 < end ; i1 ++ ) {
			if ( objects[i1] != NULL ) {
				delete objects[i1];
				objects[i1] = NULL;
			}
		}
	} else {
		for ( unsigned int i1 = begin ; i1 < length ; i1 ++ ) {
			if ( objects[i1] != NULL ) {
				delete objects[i1];
				objects[i1] = NULL;
			}
		}
	}
}

char _BASE_API *TObjectArray::GetClassName() {
	return "TObjectArray";
}

int _BASE_API TObjectArray::GetClassCode() {
	return CLSID_TObjectArray;
}

int _BASE_API TObjectArray::GetHashCode() {
	return 1;
}

BOOL32 _BASE_API TObjectArray::IsInstanceof(const char* className) {
	if (strcmp("TObjectArray", className) == 0) {
		return TRUE;
	} else if (strcmp("IObject", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

BOOL32 _BASE_API TObjectArray::IsEqualto(IObject &obj) {
	return FALSE;
}

void _BASE_API TObjectArray::Serialize(IIOStream &iio) {
}

void _BASE_API TObjectArray::Wait() {
}

void _BASE_API TObjectArray::Notify() {
}
