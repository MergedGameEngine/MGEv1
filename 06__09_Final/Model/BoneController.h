///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _BONECONTROLLER_H_
#define _BONECONTROLLER_H_

#include "ModelObject.h"

extern "C" class _MODEL_API TBoneController : public TModelObject {
protected:
protected:
	TBoneTreeNode *boneRoot;

	Vector3f translation;
	Matrix33f rotation;
	float scale;
	
	TRefArray<TBoneTreeNode> boneTable;
	THashtable boneHashtable;
	unsigned short numBones;
	unsigned short indexCount;
public:
	TBoneTreeNode &GetBoneRoot();
	Vector3f &GetTranslation();
	Matrix33f &GetRotation();
	float &GetScale();
	TRefArray<TBoneTreeNode> &GetBoneTable();
	THashtable &GetBoneHashtable();
	void SetBoneRoot(TBoneTreeNode *src);
public:
	void BuildBoneMatrix(TBoneTreeNode &btn, Transform &src);
	void ReloadMatrix(TBoneTreeNode &btn);
	void ReloadInvertedMatrix(TBoneTreeNode &btn);
	void DoAnimation(TBoneTreeNode &btn, Transform &src);
	void BuildBoneMatrix();
	void ReloadMatrix();
	void ReloadInvertedMatrix();
	void DoAnimation();
public:
	void CopyInstance(TBoneController &bc);
	void CopyBoneTransform(TBoneTreeNode &btn);
public:
	TBoneController();
	virtual ~TBoneController();
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
