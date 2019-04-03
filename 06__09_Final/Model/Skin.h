///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _SKIN_H_
#define _SKIN_H_

#include "ModelObject.h"

extern "C" template class _BASE_API TArray<unsigned short>;
extern "C" template class _BASE_API TArray<float>;
typedef TArray<unsigned short> TUShortArray;
extern "C" template class _BASE_API TRefArray<TUShortArray>;
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

extern "C" class _MODEL_API TSkin : public TModelObject {
protected:
protected:
	unsigned short numVertices;
	unsigned int numTriangles;
	unsigned short numStrips;
	unsigned short numBones;
	unsigned short numWeightPerVertex;
	BOOL8 hasVertexMaps;
	BOOL8 hasTriangles;
	BOOL8 hasStrips;
	BOOL8 hasBones;
	BOOL8 hasVertexWeights;
	BOOL8 hasBoneIndices;
	TArray<unsigned short> vertexMap;
	TArray<Triangle> triangles;
	TArray<unsigned short> stripLengths;
	TRefArray<TUShortArray> strips;
	TArray<unsigned short> bones;
	TArray<float> vertexWeights;
	TArray<unsigned short> boneIndices;

	BOOL8 isExternalMaterial;
	TString fileLinkMtl;
	BOOL8 isExternalPhysical;
	TString fileLinkPhy;
public:
	BOOL8 HasVertexMaps();
	BOOL8 HasTriangles();
	BOOL8 HasStrips();
	BOOL8 HasBones();
	BOOL8 HasVertexWeights();
	BOOL8 HasBoneIndices();
	TArray<unsigned short> &GetVertexMap();
	TArray<Triangle> &GetTriangles();
	TArray<unsigned short> &GetStripLengths();
	TRefArray<TUShortArray> &GetStrips();
	TArray<unsigned short> &GetBones();
	TArray<float> &GetVertexWeights();
	TArray<unsigned short> &GetBoneIndices();

	unsigned short GetNumVertices();
	void SetNumVertices(unsigned short num);
	unsigned int GetNumTriangles();
	void SetNumTriangles(unsigned int num);
	unsigned short GetNumStrips();
	void SetNumStrips(unsigned short num);
	unsigned short GetNumBones();
	void SetNumBones(unsigned short num);
	unsigned short GetNumWeightPerVertex();
	void SetNumWeightPerVertex(unsigned short num);

	void SetFileLinkMtl(TString &fl);
	void SetFileLinkPhy(TString &fl);
	TString &GetFileLinkMtl();
	TString &GetFileLinkPhy();
	BOOL8 IsExternalMaterial();
	BOOL8 IsExternalPhysical();


public:
	TSkin();
	virtual ~TSkin();
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
