///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _SEQUENCE_H_
#define _SEQUENCE_H_

#include "ModelObject.h"
#include "KeyFrame.h"
#include "BoneTreeNode.h"

#define MAX_KEYFRAMENUM 256

extern "C" class _MODEL_API TSequence : public TModelObject {
protected:
protected:
	float weight;
	byte cycleType;
	float frequency;
	float startTime;
	float stopTime;
	TString targetName;

	unsigned short numControlledBlocks;
	TRefArray<TKeyFrame> keyFrames;
	THashtable controlledNodes;

public:
	float &GetWeight();
	byte GetCycleType();
	void SetCycleType(byte ctype);
	float &GetFrequency();
	float &GetStartTime();
	float &GetStopTime();
	TString &GetTargetName();

	TRefArray<TKeyFrame> &GetKeyFrames();
	THashtable &GetControlledNodes();
public:
	void GetInterpolate(TKeyFrame &kf, Quaternion &q, Vector3f &t, float time);
	void GetInterpolate(TKeyFrame &kfa, TKeyFrame &kfb, Quaternion &q, Vector3f &t, float ratio);
	void LoadAnimationMatrix(TBoneTreeNode &btn, float time);
	void LoadAnimationMatrix(TSequence &sqb, TBoneTreeNode &btn, float ratio);
	void BuildTemporaryAnimation(float time);
public:
	TSequence();
	virtual ~TSequence();
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
