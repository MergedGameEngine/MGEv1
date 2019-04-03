///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _MESH_H_
#define _MESH_H_

#include "ModelObject.h"
#include "Skin.h"
#include "Bone.h"

extern "C" template class _BASE_API TArray<unsigned short>;
typedef TArray<unsigned short> TUShortArray;
extern "C" template class _BASE_API TRefArray<TUShortArray>;
extern "C" template class _BASE_API TRefArray<TString>;
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


extern "C" class _MODEL_API TMesh : public TModelObject {
protected:
protected:
	unsigned short numVertices;
	BOOL8 hasVertices;
	BOOL8 hasNormals;
	BOOL8 hasBinormals;
	BOOL8 hasTangents;
	TArray<Vector3f> vertices;
	TArray<Vector3f> normals;
	TArray<Vector3f> binormals;
	TArray<Vector3f> tangents;
	Vector3f center;
	float radius;
	BOOL8 hasUV;
	TArray<TexCoord2f> uvMap;

	unsigned int numTriangles;
	unsigned short numStrips;
	BOOL8 hasTriangles;
	BOOL8 hasStrips;
	TArray<Triangle> triangles;
	TArray<unsigned short> stripLengths;
	TRefArray<TUShortArray> strips;

	Vector3f translation;
	Matrix33f rotation;
	float scale;
	Vector3f boneTranslation;
	Matrix33f boneRotation;
	float boneScale;
	unsigned short numSkins;
	TRefArray<TSkin> skins;
	unsigned short numBones;
	TRefArray<TBone> bones;
	TRefArray<TString> boneBlockIndices;
	TArray<Matrix44f> boneMatrices;

	TRefArray<TBoneTreeNode> boneNodes;
public:
	BOOL8 HasVertices();
	BOOL8 HasNormals();
	BOOL8 HasBinormals();
	BOOL8 HasTangents();
	TArray<Vector3f> &GetVertices();
	TArray<Vector3f> &GetNormals();
	TArray<Vector3f> &GetBinormals();
	TArray<Vector3f> &GetTangents();
	Vector3f &GetCenter();
	float &GetRadius();
	BOOL8 HasUV();
	TArray<TexCoord2f> &GetUVMap();

	BOOL8 HasTriangles();
	BOOL8 HasStrips();
	TArray<Triangle> &GetTriangles();
	TArray<unsigned short> &GetStripLengths();
	TRefArray<TUShortArray> &GetStrips();

	Vector3f &GetTranslation();
	Matrix33f &GetRotation();
	float &GetScale();
	Vector3f &GetBoneTranslation();
	Matrix33f &GetBoneRotation();
	float &GetBoneScale();
	TRefArray<TSkin> &GetSkins();
	TRefArray<TBone> &GetBones();
	TRefArray<TString> &GetBoneBlockIndices();
	TArray<Matrix44f> &GetBoneMatrices();

	TRefArray<TBoneTreeNode> &GetBoneNodes();

	unsigned short GetNumVertices();
	void SetNumVertices(unsigned short num);
	unsigned int GetNumTriangles();
	void SetNumTriangles(unsigned short num);
	unsigned short GetNumStrips();
	void SetNumStrips(unsigned short num);
public:
	void BuildTangentsBinormals();
	void CopyBoneBlockIndices(TMesh &tar);
public:
	TMesh();
	virtual ~TMesh();
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
