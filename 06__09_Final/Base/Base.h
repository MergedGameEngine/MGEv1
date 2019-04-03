///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _BASE_H_
#define _BASE_H_


#include "Type.h"

#define LITTLE_ENDIAN 0
#define BIG_ENDIAN 1

#define IO_STORE 0
#define IO_LOAD 1

struct IIOStream;

extern "C" struct _BASE_API IObject {
	virtual char* GetClassName() = 0;
	virtual int GetClassCode() = 0;
	virtual int GetHashCode() = 0;
	virtual BOOL32 IsInstanceof(const char* className) = 0;
	virtual BOOL32 IsEqualto(IObject &obj) = 0;
	virtual void Serialize(IIOStream &iio) = 0;
	virtual void Wait() = 0;
	virtual void Notify() = 0;
};

extern "C" struct _BASE_API IIOStream : public IObject {
	virtual BOOL32 Open() = 0;
	virtual void Close() = 0;
	virtual void SetEndian(unsigned int endian) = 0;
	virtual unsigned int GetEndian() = 0;
	virtual void SetLoadStore(unsigned int loadstore) = 0;
	virtual unsigned int GetLoadStore() = 0;
	virtual unsigned int Read(const void* buf, const unsigned int length) = 0;
	virtual unsigned int Write(const void* buf, const unsigned int length) = 0;
	virtual unsigned int ReadBuffer(const void* buf, const unsigned int cells, const unsigned int celllength) = 0;
	virtual unsigned int WriteBuffer(const void* buf, const unsigned int cells, const unsigned int celllength) = 0;
	virtual unsigned int Seek(unsigned int length) = 0;
	virtual unsigned int Seek(unsigned int begin, unsigned int length) = 0;
	virtual unsigned int GetPosition() = 0;
	virtual BOOL32 IsEoF() = 0;
	enum {
		big_endian = 0,
		little_endian = 1
	};

	enum {
		load = 10,
		store = 11
	};
};

extern "C" class _BASE_API TString : public IObject {

private:
	unsigned short* buffer;
	int length;
	BOOL32 isBufferLocked;
protected:

public:

public:
	TString();
//	TString(const TString& src);
	virtual ~TString();
public:
	TString(char chr);
	TString(const char* str);
	TString(const unsigned short* wstr);

public:
	TString operator + (const TString &src);
	TString& operator = (const TString &src);
	TString& operator += (const TString &src);
	BOOL32 operator == (const TString &src);

	BOOL32 Equals(const TString &src);
	const unsigned short *GetBuffer();
	int GetLength();
	char* GetStringASC();
	unsigned int GetStringASC(char *desc);

public:
	virtual char* GetClassName();
	virtual int GetClassCode();
	virtual int GetHashCode();
	virtual BOOL32 IsInstanceof(const char* className);
	virtual BOOL32 IsEqualto(IObject &obj);
	virtual void Serialize(IIOStream &iio);
	virtual void Wait();
	virtual void Notify();

public:
	int Read(IIOStream &iio, unsigned int count);
	int Write(IIOStream &iio, unsigned int count);
	void Load(IIOStream &iio);
	void Store(IIOStream &iio);

public:
	//TString Substring(int start, int length);
	void Format(const TString formats, ...);
	int ToInt32();
	short ToInt16();
	char ToInt8();
	unsigned int ToUInt32();
	unsigned short ToUInt16();
	unsigned char ToUInt8();
	float ToFloat();
	double ToDouble();

};

extern "C" struct THashitem {
	TString key;
	int keyHash;
	IObject *obj;
	int objHash;
};

#define ONE_BLOCK_SIZE 128

extern "C" class _BASE_API THashtable : public IObject {
	
private:
	THashitem items[ONE_BLOCK_SIZE];
	THashtable* nextTable;
	unsigned int itemCount;
private:
	THashitem *NextEmptyItem(unsigned int &index, THashtable *&loc);
	THashitem *NextNonEmptyItem(unsigned int &index, THashtable *&loc);
public:
	THashtable();
	virtual ~THashtable();
public:
	BOOL32 Add(TString &key, const IObject *obj);
	const IObject *Get(TString &key);
	BOOL32 Set(TString &key, const IObject *obj);
	BOOL32 Del(TString &key);
	unsigned int GetCount();
	const IObject *operator[](TString &key);
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

extern "C" class _BASE_API TObjectArray : public IObject {
protected:
	IObject** objects;
	unsigned int length;
	BOOL32 isBufferLocked;
public:
	TObjectArray();
	TObjectArray(unsigned int size);
	virtual ~TObjectArray();
public:
	void Resize(unsigned int size);
	const IObject *&operator[](unsigned int index);
	TObjectArray operator + (const TObjectArray &src);
	TObjectArray &operator = (const TObjectArray &src);
	TObjectArray &operator += (const TObjectArray &src);
	TObjectArray SubArray(const unsigned int begin, const unsigned int count);
	unsigned int GetLength();
	void DeleteAll();
	void Delete(const unsigned int begin, const unsigned int count);
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