///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _REFARRAY_HPP_
#define _REFARRAY_HPP_

#ifdef _ARRAY_API

template <typename T> _ARRAY_API TRefArray<T>::TRefArray<T>() {
	references = NULL;
	length = 0;
	isBufferLocked = FALSE;
}

template <typename T> _ARRAY_API TRefArray<T>::TRefArray<T>(unsigned int size) {
	references = new T*[size];
	length = size;
	for ( unsigned int i1 = 0 ; i1 < length ; i1 ++ ) {
		references[i1] = NULL;
	}
	isBufferLocked = FALSE;
}

template <typename T> _ARRAY_API TRefArray<T>::~TRefArray<T>() {
	if (!isBufferLocked) {
		if (references!=NULL) {
			delete []references;
			references = NULL;
		}
	} else {
		isBufferLocked = FALSE;
	}
}

template <typename T> void _ARRAY_API TRefArray<T>::Resize(unsigned int size) {
	if (size > 0) {
		T **newReferences = new T*[size];
		if (size < length) {
			memcpy(newReferences, references, sizeof(T*) * size);
		} else {
			if (references != NULL) {
				memcpy(newReferences, references, sizeof(T*) * length);
			}
			for ( unsigned int i1 = length ; i1 < size ; i1 ++ ) {
				newReferences[i1] = NULL;
			}
		}
		if (references != NULL) {
			delete []references;
			references = NULL;
		}
		references = newReferences;
		length = size;
	} else {
		if (references != NULL) {
			delete []references;
			references = NULL;
		}
		length = 0;
	}
}

template <typename T> T _ARRAY_API &TRefArray<T>::operator[](unsigned int index) {
	if (index < length) {
		return *(references[index]);
	} else {
		return *(T*)NULL;
	}
}

template <typename T> TRefArray<T> _ARRAY_API TRefArray<T>::operator + (const TRefArray<T> &src) {
	TRefArray<T> desc(length + src.length);
	memcpy(desc.references, references, sizeof(T*) * length);
	memcpy(&(desc.references[length]), src.references, sizeof(T*) * src.length);
	desc.isBufferLocked = TRUE;
	return desc;
}

template <typename T> TRefArray<T> _ARRAY_API &TRefArray<T>::operator = (const TRefArray<T> &src) {
	if ( this != &src ) {
		if (references != NULL) {
			delete []references;
			references = NULL;
		}
		if (src.references != NULL) {
			if (src.isBufferLocked) {
				references = src.references;
			} else {
				references = new T*[src.length];
				memcpy (references, src.references, src.length * sizeof(T*));
			}
		}
		length = src.length;
	}
	isBufferLocked = FALSE;
	return *this;
}

template <typename T> TRefArray<T> _ARRAY_API &TRefArray<T>::operator += (const TRefArray<T> &src) {
	if ( src.length > 0 ) {
		T **newReferences = new T*[length + src.length];
		memcpy( newReferences, references, sizeof(T*) * length );
		memcpy( &(newReferences[length]), src.references, sizeof(T*) * src.length);
		length += src.length;
		if (references != NULL) {
			delete []references;
			references = NULL;
		}
		references = newReferences;
	}
	isBufferLocked = FALSE;
	return *this;
}

template <typename T> TRefArray<T> _ARRAY_API TRefArray<T>::SubArray(const unsigned int begin, const unsigned int count) {
	TRefArray des;
	if ((begin + count) <= length) {
		des.Resize(count);
		memcpy(des.references, &(references[begin]), sizeof(T*) * count);
	}
	des.isBufferLocked = TRUE;
	return des;
}

template <typename T> unsigned int _ARRAY_API TRefArray<T>::GetLength() {
	return length;
}

template <typename T> void _ARRAY_API TRefArray<T>::Set(unsigned int index, T* ref) {
	if ( index < length ) {
		references[index] = ref;
	}
}

template <typename T> void _ARRAY_API TRefArray<T>::Exchange(unsigned int i1, unsigned int i2) {
	if ( ( i1 < length ) && ( i2 < length ) ) {
		T *ref = references[i1];
		references[i1] = references[i2];
		references[i2] = ref;
	}
}

template <typename T> unsigned int _ARRAY_API TRefArray<T>::Pack() {
	for ( unsigned int i0 = 0 , i1 = 0 , i2 = 0; i2 < length ; i0 ++ ) {
		if ( references[i1] == NULL ) {
			if ( i1 > i2 ) {
				i2 = i1 + 1;
			}
			if ( references[i2] != NULL ) {
				references[i1] = references[i2]; references[i2] = NULL;
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

template <typename T> void _ARRAY_API TRefArray<T>::DeleteAll() {
	for ( unsigned int i1 = 0 ; i1 < length ; i1 ++ ) {
		if ( references[i1] != NULL ) {
			delete references[i1];
			references[i1] = NULL;
		}
	}
}

template <typename T> void _ARRAY_API TRefArray<T>::Delete(const unsigned int begin, const unsigned int count) {
	if ( (begin + count) <= length) {
		unsigned int end = begin + count;
		for ( unsigned int i1 = begin ; i1 < end ; i1 ++ ) {
			if ( references[i1] != NULL ) {
				delete references[i1];
				references[i1] = NULL;
			}
		}
	} else {
		for ( unsigned int i1 = begin ; i1 < length ; i1 ++ ) {
			if ( references[i1] != NULL ) {
				delete references[i1];
				references[i1] = NULL;
			}
		}
	}
}

template <typename T> void _ARRAY_API TRefArray<T>::CreateAll() {
	for ( unsigned int i1 = 0 ; i1 < length ; i1 ++ ) {
		references[i1] = new T();
	}
}

template <typename T> void _ARRAY_API TRefArray<T>::Create(const unsigned int begin, const unsigned int count) {
	if ( (begin + count) <= length) {
		unsigned int end = begin + count;
		for ( unsigned int i1 = begin ; i1 < end ; i1 ++ ) {
			references[i1] = new T();
		}
	} else {
		for ( unsigned int i1 = begin ; i1 < length ; i1 ++ ) {
			references[i1] = new T();
		}
	}
}

template <typename T> char _ARRAY_API *TRefArray<T>::GetClassName() {
	return "TRefArray";
}

template <typename T> int _ARRAY_API TRefArray<T>::GetClassCode() {
	return CLSID_TRefArray;
}

template <typename T> int _ARRAY_API TRefArray<T>::GetHashCode() {
	return 1;
}

template <typename T> BOOL32 _ARRAY_API TRefArray<T>::IsInstanceof(const char* className) {
	if (strcmp("TRefArray", className) == 0) {
		return TRUE;
	} else if (strcmp("IObject", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

template <typename T> BOOL32 _ARRAY_API TRefArray<T>::IsEqualto(IObject &obj) {
	return FALSE;
}

template <typename T> void _ARRAY_API TRefArray<T>::Serialize(IIOStream &iio) {
}

template <typename T> void _ARRAY_API TRefArray<T>::Wait() {
}

template <typename T> void _ARRAY_API TRefArray<T>::Notify() {
}

#endif

#endif