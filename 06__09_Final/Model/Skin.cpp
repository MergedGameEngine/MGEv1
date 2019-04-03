///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _BASE_IMPORT
#define _MATHTOOL_IMPORT
#define _MODEL_EXPORT

#include "string.h"
#include "..\Base\Type.h"
#include "..\Base\Base.h"
#undef _ARRAY_API
#define _ARRAY_API _MODEL_API
#include "Skin.hpp"

_MODEL_API TSkin::TSkin() {
	numVertices = 0;
	numTriangles = 0;
	numStrips = 0;
	numBones = 0;
	numWeightPerVertex = 0;
	hasVertexMaps = FALSE;
	hasTriangles = FALSE;
	hasStrips = FALSE;
	hasBones = FALSE;
	hasVertexWeights = FALSE;
	hasBoneIndices = FALSE;
	vertexMap.Resize(0);
	triangles.Resize(0);
	stripLengths.Resize(0);
	strips.Resize(0);
	bones.Resize(0);
	vertexWeights.Resize(0);
	boneIndices.Resize(0);

	isExternalMaterial = FALSE;
	isExternalPhysical = FALSE;
}

_MODEL_API TSkin::~TSkin() {
	vertexMap.Resize(0);
	triangles.Resize(0);
	stripLengths.Resize(0);
	strips.DeleteAll();
	strips.Resize(0);
	bones.Resize(0);
	vertexWeights.Resize(0);
	boneIndices.Resize(0);
}

char _MODEL_API *TSkin::GetClassName() {
	return "TSkin";
}

int _MODEL_API TSkin::GetClassCode() {
	return CLSID_TSkin;
}

int _MODEL_API TSkin::GetHashCode() {
	return 1;
}

BOOL32 _MODEL_API TSkin::IsInstanceof(const char* className) {
	if (strcmp("TSkin", className) == 0) {
		return TRUE;
	}
	return TModelObject::IsInstanceof(className);
}

BOOL32 _MODEL_API TSkin::IsEqualto(IObject &obj) {
	return FALSE;
}

void _MODEL_API TSkin::Serialize(IIOStream &iio) {
	TModelObject::Serialize(iio);
	if ( iio.GetLoadStore() == IIOStream::load ) {
		if ( ( version == 0x00000001 ) && ( subVersion == 0x00000000 ) ) {

			iio.Read(&numVertices, sizeof(unsigned short));
			iio.Read(&numTriangles, sizeof(unsigned int));
			iio.Read(&numStrips, sizeof(unsigned short));
			iio.Read(&numBones, sizeof(unsigned short));
			iio.Read(&numWeightPerVertex, sizeof(unsigned short));
			iio.Read(&hasVertexMaps, sizeof(BOOL8));
			iio.Read(&hasTriangles, sizeof(BOOL8));
			iio.Read(&hasStrips, sizeof(BOOL8));
			iio.Read(&hasBones, sizeof(BOOL8));
			iio.Read(&hasVertexWeights, sizeof(BOOL8));
			iio.Read(&hasBoneIndices, sizeof(BOOL8));

			if (hasVertexMaps) {
				vertexMap.Resize(numVertices);
				iio.ReadBuffer(vertexMap.GetBuffer(), numVertices, sizeof(unsigned short));
			}

			if (hasTriangles) {
				triangles.Resize(numTriangles);
				iio.ReadBuffer(triangles.GetBuffer(), numTriangles * 3, sizeof(unsigned short));
			}

			if (hasStrips) {
				strips.Resize(numStrips);
				strips.CreateAll();
				stripLengths.Resize(numStrips);
				iio.ReadBuffer(stripLengths.GetBuffer(), numStrips, sizeof(unsigned short));
				for (int i1 = 0 ; i1 < numStrips ; i1 ++ ) {
					strips[i1].Resize(stripLengths[i1]);
					iio.ReadBuffer(strips[i1].GetBuffer(), stripLengths[i1], sizeof(unsigned short));
				}
			}

			if (hasBones) {
				bones.Resize(numBones);
				iio.ReadBuffer(bones.GetBuffer(), numBones, sizeof(unsigned short));
			}

			if (hasVertexWeights) {
				vertexWeights.Resize(numVertices * numWeightPerVertex);
				iio.ReadBuffer(vertexWeights.GetBuffer(), numVertices * numWeightPerVertex, sizeof(float));
			}

			if (hasBoneIndices) {
				boneIndices.Resize(numVertices * numWeightPerVertex);
				iio.ReadBuffer(boneIndices.GetBuffer(), numVertices * numWeightPerVertex, sizeof(unsigned short));
			}


			iio.Read(&isExternalMaterial, sizeof(BOOL8));
			fileLinkMtl.Load(iio);
			iio.Read(&isExternalPhysical, sizeof(BOOL8));
			fileLinkPhy.Load(iio);
		}
	} else {
		hasVertexMaps = ((numVertices != 0) && (vertexMap.GetLength() >= numVertices));
		hasTriangles = ((numTriangles != 0) && (triangles.GetLength() >= numTriangles));
		hasStrips = ((numStrips != 0) && (strips.GetLength() == numStrips));
		hasBones = ((numBones != 0) && (bones.GetLength() >= numBones));
		hasVertexWeights = (((numVertices * numWeightPerVertex) != 0) && (vertexWeights.GetLength() >= (unsigned int)(numVertices * numWeightPerVertex)));
		hasBoneIndices = (((numVertices * numWeightPerVertex) != 0) && (boneIndices.GetLength() >= (unsigned int)(numVertices * numWeightPerVertex)));

		iio.Write(&numVertices, sizeof(unsigned short));
		iio.Write(&numTriangles, sizeof(unsigned int));
		iio.Write(&numStrips, sizeof(unsigned short));
		iio.Write(&numBones, sizeof(unsigned short));
		iio.Write(&numWeightPerVertex, sizeof(unsigned short));
		iio.Write(&hasVertexMaps, sizeof(BOOL8));
		iio.Write(&hasTriangles, sizeof(BOOL8));
		iio.Write(&hasStrips, sizeof(BOOL8));
		iio.Write(&hasBones, sizeof(BOOL8));
		iio.Write(&hasVertexWeights, sizeof(BOOL8));
		iio.Write(&hasBoneIndices, sizeof(BOOL8));
		if (hasVertexMaps) {
			iio.WriteBuffer(vertexMap.GetBuffer(), numVertices, sizeof(unsigned short));
		}
		if (hasTriangles) {
			iio.WriteBuffer(triangles.GetBuffer(), numTriangles * 3, sizeof(unsigned short));
		}
		if (hasStrips) {
			iio.WriteBuffer(stripLengths.GetBuffer(), numStrips, sizeof(unsigned short));
			for (int i1 = 0 ; i1 < numStrips ; i1 ++ ) {
				iio.WriteBuffer(strips[i1].GetBuffer(), stripLengths[i1], sizeof(unsigned short));
			}
		}
		if (hasBones) {
			iio.WriteBuffer(bones.GetBuffer(), numBones, sizeof(unsigned short));
		}
		if (hasVertexWeights) {
			iio.WriteBuffer(vertexWeights.GetBuffer(), numVertices * numWeightPerVertex, sizeof(float));
		}
		if (hasBoneIndices) {
			iio.WriteBuffer(boneIndices.GetBuffer(), numVertices * numWeightPerVertex, sizeof(unsigned short));
		}

		isExternalMaterial = TRUE;
		isExternalPhysical = TRUE;
		iio.Write(&isExternalMaterial, sizeof(BOOL8));
		fileLinkMtl.Store(iio);
		iio.Write(&isExternalPhysical, sizeof(BOOL8));
		fileLinkPhy.Store(iio);
	}
}

void _MODEL_API TSkin::Wait() {
}

void _MODEL_API TSkin::Notify() {
}

BOOL8 _MODEL_API TSkin::HasVertexMaps() {
	return hasVertexMaps = ((numVertices != 0) && (vertexMap.GetLength() >= numVertices));
}

BOOL8 _MODEL_API TSkin::HasTriangles() {
	return hasTriangles = ((numTriangles != 0) && (triangles.GetLength() >= numTriangles));
}

BOOL8 _MODEL_API TSkin::HasStrips() {
	return hasStrips = ((numStrips != 0) && (strips.GetLength() == numStrips));
}

BOOL8 _MODEL_API TSkin::HasBones() {
	return hasBones = ((numBones != 0) && (bones.GetLength() >= numBones));
}

BOOL8 _MODEL_API TSkin::HasVertexWeights() {
	return hasVertexWeights = (((numVertices * numWeightPerVertex) != 0) 
		&& (vertexWeights.GetLength() >= (unsigned int)(numVertices * numWeightPerVertex)));
}

BOOL8 _MODEL_API TSkin::HasBoneIndices() {
	return hasBoneIndices = (((numVertices * numWeightPerVertex) != 0) 
		&& (boneIndices.GetLength() >= (unsigned int)(numVertices * numWeightPerVertex)));
}

TArray<unsigned short> _MODEL_API &TSkin::GetVertexMap() {
	return vertexMap;
}

TArray<Triangle> _MODEL_API &TSkin::GetTriangles() {
	return triangles;
}

TArray<unsigned short> _MODEL_API &TSkin::GetStripLengths() {
	return stripLengths;
}

TRefArray<TUShortArray> _MODEL_API &TSkin::GetStrips() {
	return strips;
}

TArray<unsigned short> _MODEL_API &TSkin::GetBones() {
	return bones;
}

TArray<float> _MODEL_API &TSkin::GetVertexWeights() {
	return vertexWeights;
}

TArray<unsigned short> _MODEL_API &TSkin::GetBoneIndices() {
	return boneIndices;
}

unsigned short _MODEL_API TSkin::GetNumVertices() {
	return numVertices;
}

void _MODEL_API TSkin::SetNumVertices(unsigned short num) {
	numVertices = num;
}

unsigned int _MODEL_API TSkin::GetNumTriangles() {
	return numTriangles;
}

void _MODEL_API TSkin::SetNumTriangles(unsigned int num) {
	numTriangles = num;
}

unsigned short _MODEL_API TSkin::GetNumStrips() {
	return numStrips;
}

void _MODEL_API TSkin::SetNumStrips(unsigned short num) {
	numStrips = num;
}

unsigned short _MODEL_API TSkin::GetNumBones() {
	return numBones;
}

void _MODEL_API TSkin::SetNumBones(unsigned short num) {
	numBones = num;
}

unsigned short _MODEL_API TSkin::GetNumWeightPerVertex() {
	return numWeightPerVertex;
}

void _MODEL_API TSkin::SetNumWeightPerVertex(unsigned short num) {
	numWeightPerVertex = num;
}

void _MODEL_API TSkin::SetFileLinkMtl(TString &fl) {
	fileLinkMtl = fl;
	if (fl.GetLength() == 0) {
		isExternalMaterial = FALSE;
	} else {
		isExternalMaterial = TRUE;
	}
}

void _MODEL_API TSkin::SetFileLinkPhy(TString &fl) {
	fileLinkPhy = fl;
	if (fl.GetLength() == 0) {
		isExternalPhysical = FALSE;
	} else {
		isExternalPhysical = TRUE;
	}
}

TString _MODEL_API &TSkin::GetFileLinkMtl() {
	return fileLinkMtl;
}

TString _MODEL_API &TSkin::GetFileLinkPhy() {
	return fileLinkPhy;
}

BOOL8 _MODEL_API TSkin::IsExternalMaterial() {
	return isExternalMaterial;
}

BOOL8 _MODEL_API TSkin::IsExternalPhysical() {
	return isExternalPhysical;
}
