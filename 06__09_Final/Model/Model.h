///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _MODEL_H_
#define _MODEL_H_

#include "ModelObject.h"
#include "Mesh.h"
#include "BoneController.h"

#define MAX_MESHNUM 256

extern "C" class _MODEL_API TModel : public TModelObject {
protected:
protected:
	Vector3f translation;
	Matrix33f rotation;
	float scale;

	unsigned short numMeshes;
	TRefArray<TMesh> meshes;
	BOOL8 hasBoneController;
	TBoneController *boneController;
public:
	Vector3f &GetTranslation();
	Matrix33f &GetRotation();
	float &GetScale();

	TRefArray<TMesh> &GetMeshes();
	BOOL8 HasBoneController();
	TBoneController &GetBoneController();
	void SetBoneController(TBoneController *src);
	unsigned short GetNumMeshes();
	void SetNumMeshes(unsigned short num);
public:
	void CopyBoneBlockIndices(TModel &tar);
	void LinkBoneNodes();
	void CopyAnimationController(TModel &tar);
	void BuildAnimationController(TModel &tar, TString &rootbonename, Transform &trans, Transform &itrans);
	void SetAnimationControllerBoneRoot(TString &newname, Transform &trans, Transform &itrans);
public:
	TModel();
	virtual ~TModel();
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
