///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _ARRAY_H_
#define _ARRAY_H_

#ifdef _ARRAY_API

struct IObject;

template <typename T>
class _ARRAY_API TArray : public IObject {
protected:
	T* buffer;
	unsigned int length;
	BOOL32 isBufferLocked;
public:
	TArray();
	TArray(unsigned int size);
	virtual ~TArray();
public:
	void Resize(unsigned int size);
	T &operator[](unsigned int index);
	TArray operator + (const TArray &src);
	TArray &operator = (const TArray &src);
	TArray &operator += (const TArray &src);
	TArray SubArray(const unsigned int begin, const unsigned int count);
	unsigned int GetLength();
	const void *GetBuffer();
public:
	virtual char* GetClassName();
	virtual int GetClassCode();
	virtual int GetHashCode();
	virtual BOOL32 IsInstanceof(const char* className);
	virtual BOOL32 IsEqualto(IObject &obj);
	virtual void Serialize(IIOStream &iio);
	virtual void Wait();
	virtual void Notify();
};

#endif

#endif