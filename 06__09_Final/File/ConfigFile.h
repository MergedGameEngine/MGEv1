#ifndef _CONFIGFILE_H_
#define _CONFIGFILE_H_

#include "..\Base\Base.h"

extern "C" class _FILE_API TConfigFile : public IObject {
public:
	TConfigFile();
	virtual ~TConfigFile();
protected:
	TRefArray<TString> names;
	TRefArray<TConfig> values;
	THashtable nameIndices;
protected:
	unsigned short errorLine;
	BOOL32 isError;
public:
	TRefArray<TString> &GetNames();
	TRefArray<TConfig> &GetValues();
	TConfig &GetValue(TString &name);
public:
	BOOL32 IsError(unsigned short &eline);
public:
	void Parse(IIOStream &iio);
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