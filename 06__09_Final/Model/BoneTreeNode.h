///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _BONETREENODE_H_
#define _BONETREENODE_H_

#include "ModelObject.h"

extern "C" class _MODEL_API TBoneTreeNode : public TModelObject {
protected:
protected:
	Vector3f translation;
	Matrix33f rotation;
	float scale;

	unsigned short boneId;
	BOOL8 hasNextNode;
	BOOL8 hasSubNode;
	unsigned short nextBoneId;
	unsigned short subBoneId;

	TBoneTreeNode *nextNode;
	TBoneTreeNode *subNode;
	TBoneTreeNode *parent;
	THashtable *boneTable;
	unsigned short *indexCount;

	Transform iTransform;
	Transform aTransform;
	Transform transform;

	Transform fast;
public:
	Vector3f &GetTranslation();
	Matrix33f &GetRotation();
	float &GetScale();

	unsigned short GetBoneId();
	void SetBoneId(unsigned short id);
	BOOL8 HasNextNode();
	BOOL8 HasSubNode();
	TBoneTreeNode &GetNextNode();
	TBoneTreeNode &GetSubNode();
	TBoneTreeNode &GetParentNode();
	void SetNextNode(TBoneTreeNode *src);
	void SetSubNode(TBoneTreeNode *src);
	void SetParentNode(TBoneTreeNode *src);
	THashtable &GetBoneHashtable();

	Transform &GetInvertedTransform();
	Transform &GetAnimationTransform();
	Transform &GetTransform();

	Transform &GetFastTransform();
public:
	void CopyInstance(TBoneTreeNode &bc);
public:
	TBoneTreeNode();
	TBoneTreeNode(TBoneTreeNode *p, THashtable *table);
	virtual ~TBoneTreeNode();
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
