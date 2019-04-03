///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _REFARRAY_H_
#define _REFARRAY_H_

#ifdef _ARRAY_API

struct IObject;

template <typename T>
class _ARRAY_API TRefArray : public IObject {
protected:
	T** references;
	unsigned int length;
	BOOL32 isBufferLocked;
public:
	TRefArray();
	TRefArray(unsigned int size);
	virtual ~TRefArray();
public:
	void Resize(unsigned int size);
	T &operator[](unsigned int index);
	TRefArray operator + (const TRefArray &src);
	TRefArray &operator = (const TRefArray &src);
	TRefArray &operator += (const TRefArray &src);
	TRefArray SubArray(const unsigned int begin, const unsigned int count);
	unsigned int GetLength();
	void Set(unsigned int index, T* ref);
	void DeleteAll();
	void Delete(const unsigned int begin, const unsigned int count);
	void CreateAll();
	void Create(const unsigned int begin, const unsigned int count);
	void Exchange(unsigned int i1, unsigned int i2);
	unsigned int Pack();

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