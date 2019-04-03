///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _KEYFRAME_H_
#define _KEYFRAME_H_

#include "ModelObject.h"

extern "C" template class _BASE_API TArray<unsigned short>;
extern "C" template class _BASE_API TArray<float>;
extern "C" template class _MATHTOOL_API TArray<Triangle>;
extern "C" template class _MATHTOOL_API TArray<TexCoord2f>;
extern "C" template class _MATHTOOL_API TArray<Vector3f>;
extern "C" template class _MATHTOOL_API TArray<Vector4f>;
extern "C" template class _MATHTOOL_API TArray<Matrix22f>;
extern "C" template class _MATHTOOL_API TArray<Matrix33f>;
extern "C" template class _MATHTOOL_API TArray<Matrix44f>;
extern "C" template class _MATHTOOL_API TArray<Matrix34f>;
extern "C" template class _MATHTOOL_API TArray<Quaternion>;
extern "C" template class _MATHTOOL_API TArray<Transform>;

extern "C" class _MODEL_API TKeyFrame : public TModelObject {
protected:
protected:
	Vector3f translation;
	Quaternion rotation;
	float scale;
	byte rotationType;
	byte quatInterpolatType;
	byte transInterpolatType;
	byte scalesInterpolatType;
	unsigned int numFrames;
	unsigned int numQuaternion;
	TArray<float> timeLineQuat;
	TArray<Quaternion> quaternions;
	unsigned int numTrans;
	TArray<float> timeLineTrans;
	TArray<Vector3f> translations;
	unsigned int numScales;
	TArray<float> timeLineScales;
	TArray<float> scales;

	Quaternion temporaryRotation;
	Vector3f temporaryTranslation;
public:
	Vector3f &GetTranslation();
	Quaternion &GetRotation();
	float &GetScale();
	byte GetRotationType();
	void SetRotationType(byte rtype);
	byte GetQuatInterpolatType();
	void SetQuatInterpolatType(byte itype);
	byte GetTransInterpolatType();
	void SetTransInterpolatType(byte itype);
	byte GetScalesInterpolatType();
	void SetScalesInterpolatType(byte itype);
	TArray<float> &GetTimeLineQuat();
	TArray<Quaternion> &GetQuaternions();
	TArray<float> &GetTimeLineTrans();
	TArray<Vector3f> &GetTranslations();
	TArray<float> &GetTimeLineScales();
	TArray<float> &GetScales();

	unsigned int GetNumFrames();
	void SetNumFrames(unsigned int num);
	unsigned int GetNumQuaternions();
	void SetNumQuaternions(unsigned int num);
	unsigned int GetNumTranslations();
	void SetNumTranslations(unsigned int num);
	unsigned int GetNumScales();
	void SetNumScales(unsigned int num);

	Quaternion &GetTemporaryRotation();
	Vector3f &GetTemporaryTranslation();
public:
	TKeyFrame();
	virtual ~TKeyFrame();
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
