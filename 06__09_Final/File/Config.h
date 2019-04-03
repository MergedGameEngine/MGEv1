#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "..\Base\Base.h"
#include "..\MathTool\MathTool.h"

extern "C" template class _BASE_API TRefArray<TString>;

extern "C" class _FILE_API TConfig : public IObject {
public:
	TConfig();
	virtual ~TConfig();
protected:
	TRefArray<TString> names;
	TRefArray<TString> values;
	THashtable nameIndices;
public:
	TRefArray<TString> &GetNames();
	TRefArray<TString> &GetValues();
	THashtable &GetNameIndices();
public:
	double	StringtoDouble(TString &src);
	BOOL32	ParseInt(TString &key, int &des);
	BOOL32	ParseDouble(TString &key, double &des);
	BOOL32	ParseVector3f(TString &key, Vector3f &des);
	BOOL32	ParseVector4f(TString &key, Vector4f &des);
	BOOL32	ParseMatrix33f(TString &key, Matrix33f &des);
	BOOL32	ParseMatrix44f(TString &key, Matrix44f &des);
	BOOL32	GetString(TString &key, TString &des);
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