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
#include "Mesh.hpp"

_MODEL_API TMesh::TMesh() {
	numVertices = 0;
	hasVertices = FALSE;
	hasNormals = FALSE;
	hasBinormals = FALSE;
	hasTangents = FALSE;
	vertices.Resize(0);
	normals.Resize(0);
	binormals.Resize(0);
	tangents.Resize(0);
	hasUV = FALSE;
	uvMap.Resize(0);

	numTriangles = 0;
	numStrips = 0;
	hasTriangles = FALSE;
	hasStrips = FALSE;
	triangles.Resize(0);
	stripLengths.Resize(0);
	strips.Resize(0);

	boneBlockIndices.Resize(0);
	boneMatrices.Resize(0);
	skins.Resize(0);
	bones.Resize(0);
	numSkins = 0;
	numBones = 0;
}

_MODEL_API TMesh::~TMesh() {
	vertices.Resize(0);
	normals.Resize(0);
	binormals.Resize(0);
	tangents.Resize(0);
	hasUV = FALSE;
	uvMap.Resize(0);

	triangles.Resize(0);
	stripLengths.Resize(0);
	strips.DeleteAll();
	strips.Resize(0);

	boneBlockIndices.Resize(0);
	boneMatrices.Resize(0);
	skins.Resize(0);
	bones.Resize(0);
}

char _MODEL_API *TMesh::GetClassName() {
	return "TMesh";
}

int _MODEL_API TMesh::GetClassCode() {
	return CLSID_TMesh;
}

int _MODEL_API TMesh::GetHashCode() {
	return 1;
}

BOOL32 _MODEL_API TMesh::IsInstanceof(const char* className) {
	if (strcmp("TMesh", className) == 0) {
		return TRUE;
	}
	return TModelObject::IsInstanceof(className);
}

BOOL32 _MODEL_API TMesh::IsEqualto(IObject &obj) {
	return FALSE;
}

void _MODEL_API TMesh::Serialize(IIOStream &iio) {
	TModelObject::Serialize(iio);
	if ( iio.GetLoadStore() == IIOStream::load ) {
		if ( ( version == 0x00000001 ) && ( subVersion == 0x00000000 ) ) {
			name.Load(iio);
			iio.Read(&numVertices, sizeof(unsigned short));
			iio.Read(&hasVertices, sizeof(BOOL8));
			iio.Read(&hasNormals, sizeof(BOOL8));
			iio.Read(&hasBinormals, sizeof(BOOL8));
			iio.Read(&hasTangents, sizeof(BOOL8));
			if (hasVertices) {
				vertices.Resize(numVertices);
				iio.ReadBuffer(vertices.GetBuffer(), numVertices * 3, sizeof(float));
			}
			if (hasNormals) {
				normals.Resize(numVertices);
				iio.ReadBuffer(normals.GetBuffer(), numVertices * 3, sizeof(float));
			}
			if (hasBinormals) {
				binormals.Resize(numVertices);
				iio.ReadBuffer(binormals.GetBuffer(), numVertices * 3, sizeof(float));
			}
			if (hasTangents) {
				tangents.Resize(numVertices);
				iio.ReadBuffer(tangents.GetBuffer(), numVertices * 3, sizeof(float));
			}
			iio.ReadBuffer(&center, 3, sizeof(float));
			iio.Read(&radius, sizeof(float));
			iio.Read(&hasUV, sizeof(BOOL8));
			if (hasUV) {
				uvMap.Resize(numVertices);
				iio.ReadBuffer(uvMap.GetBuffer(), numVertices * 2, sizeof(float));
			}

			iio.Read(&numTriangles, sizeof(unsigned int));
			iio.Read(&numStrips, sizeof(unsigned short));
			iio.Read(&hasTriangles, sizeof(BOOL8));
			iio.Read(&hasStrips, sizeof(BOOL8));
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

			iio.ReadBuffer(&translation, 3, sizeof(float));
			iio.ReadBuffer(&rotation, 9, sizeof(float));
			iio.Read(&scale, sizeof(float));
			iio.Read(&numSkins, sizeof(unsigned short));
			skins.Resize(numSkins);
			skins.CreateAll();
			for (unsigned int i1 = 0 ; i1 < numSkins ; i1 ++ ) {
				TString sClassName;
				sClassName.Load(iio);
				skins[i1].SetVersion(version);
				skins[i1].SetSubVersion(subVersion);
				skins[i1].Serialize(iio);
			}
			iio.ReadBuffer(&boneTranslation, 3, sizeof(float));
			iio.ReadBuffer(&boneRotation, 9, sizeof(float));
			iio.Read(&boneScale, sizeof(float));
			iio.Read(&numBones, sizeof(unsigned short));
			bones.Resize(numBones);
			bones.CreateAll();
			for (unsigned int i2 = 0 ; i2 < numBones ; i2 ++ ) {
				TString bClassName;
				bClassName.Load(iio);
				bones[i2].SetVersion(version);
				bones[i2].SetSubVersion(subVersion);
				bones[i2].Serialize(iio);
			}
			if (numBones > 0) {
				boneBlockIndices.Resize(numBones);
				boneBlockIndices.CreateAll();
				for (unsigned int i3 = 0 ; i3 < numBones ; i3 ++ ) {
					boneBlockIndices[i3].Load(iio);
				}
			}
		}
	} else {
		hasVertices = ((numVertices != 0) && (vertices.GetLength() >= numVertices));
		hasNormals = ((numVertices != 0) && (normals.GetLength() >= numVertices));
		hasBinormals = ((numVertices != 0) && (binormals.GetLength() >= numVertices));
		hasTangents = ((numVertices != 0) && (tangents.GetLength() >= numVertices));

		hasUV = ((numVertices != 0) && (uvMap.GetLength() >= numVertices));

		hasTriangles = ((numTriangles != 0) && (triangles.GetLength() >= numTriangles));
		hasStrips = ((numStrips != 0) && (strips.GetLength() == numStrips));

		name.Store(iio);
		iio.Write(&numVertices, sizeof(unsigned short));
		iio.Write(&hasVertices, sizeof(BOOL8));
		iio.Write(&hasNormals, sizeof(BOOL8));
		iio.Write(&hasBinormals, sizeof(BOOL8));
		iio.Write(&hasTangents, sizeof(BOOL8));
		if (hasVertices) {
			iio.WriteBuffer(vertices.GetBuffer(), numVertices * 3, sizeof(float));
		}
		if (hasNormals) {
			iio.WriteBuffer(normals.GetBuffer(), numVertices * 3, sizeof(float));
		}
		if (hasBinormals) {
			iio.WriteBuffer(binormals.GetBuffer(), numVertices * 3, sizeof(float));
		}
		if (hasTangents) {
			iio.WriteBuffer(tangents.GetBuffer(), numVertices * 3, sizeof(float));
		}
		iio.WriteBuffer(&center, 3, sizeof(float));
		iio.Write(&radius, sizeof(float));
		iio.Write(&hasUV, sizeof(BOOL8));
		if (hasUV) {
			iio.WriteBuffer(uvMap.GetBuffer(), numVertices * 2, sizeof(float));
		}

		iio.Write(&numTriangles, sizeof(unsigned int));
		iio.Write(&numStrips, sizeof(unsigned short));
		iio.Write(&hasTriangles, sizeof(BOOL8));
		iio.Write(&hasStrips, sizeof(BOOL8));
		if (hasTriangles) {
			iio.WriteBuffer(triangles.GetBuffer(), numTriangles * 3, sizeof(unsigned short));
		}
		if (hasStrips) {
			iio.WriteBuffer(stripLengths.GetBuffer(), numStrips, sizeof(unsigned short));
			for (int i1 = 0 ; i1 < numStrips ; i1 ++ ) {
				iio.WriteBuffer(strips[i1].GetBuffer(), stripLengths[i1], sizeof(unsigned short));
			}
		}

		iio.WriteBuffer(&translation, 3, sizeof(float));
		iio.WriteBuffer(&rotation, 9, sizeof(float));
		iio.Write(&scale, sizeof(float));
		numSkins = (unsigned short)skins.GetLength();
		iio.Write(&numSkins, sizeof(unsigned short));
		for (unsigned int i1 = 0 ; i1 < numSkins ; i1 ++ ) {
			TString sClassName(skins[i1].GetClassName());
			sClassName.Store(iio);
			skins[i1].Serialize(iio);
		}
		iio.WriteBuffer(&boneTranslation, 3, sizeof(float));
		iio.WriteBuffer(&boneRotation, 9, sizeof(float));
		iio.Write(&boneScale, sizeof(float));
		numBones = (unsigned short)bones.GetLength();
		iio.Write(&numBones, sizeof(unsigned short));
		for (unsigned int i1 = 0 ; i1 < numBones ; i1 ++ ) {
			TString bClassName(bones[i1].GetClassName());
			bClassName.Store(iio);
			bones[i1].Serialize(iio);
		}
		for (unsigned int i2 = 0 ; i2 < numBones ; i2 ++ ) {
			boneBlockIndices[i2].Store(iio);
		}
	}
}

void _MODEL_API TMesh::Wait() {
}

void _MODEL_API TMesh::Notify() {
}

BOOL8 _MODEL_API TMesh::HasVertices() {
	return hasVertices = ((numVertices != 0) && (vertices.GetLength() >= numVertices));
}

BOOL8 _MODEL_API TMesh::HasNormals() {
	return hasNormals = ((numVertices != 0) && (normals.GetLength() >= numVertices));
}

BOOL8 _MODEL_API TMesh::HasBinormals() {
	return hasBinormals = ((numVertices != 0) && (binormals.GetLength() >= numVertices));
}

BOOL8 _MODEL_API TMesh::HasTangents() {
	return hasTangents = ((numVertices != 0) && (tangents.GetLength() >= numVertices));
}

TArray<Vector3f> _MODEL_API &TMesh::GetVertices() {
	return vertices;
}

TArray<Vector3f> _MODEL_API &TMesh::GetNormals() {
	return normals;
}

TArray<Vector3f> _MODEL_API &TMesh::GetBinormals() {
	return binormals;
}

TArray<Vector3f> _MODEL_API &TMesh::GetTangents() {
	return tangents;
}

Vector3f _MODEL_API &TMesh::GetCenter() {
	return center;
}

float _MODEL_API &TMesh::GetRadius() {
	return radius;
}

BOOL8 _MODEL_API TMesh::HasUV() {
	return hasUV = ((numVertices != 0) && (uvMap.GetLength() >= numVertices));
}

TArray<TexCoord2f> _MODEL_API &TMesh::GetUVMap() {
	return uvMap;
}

BOOL8 _MODEL_API TMesh::HasTriangles() {
	return hasTriangles = ((numTriangles != 0) && (triangles.GetLength() >= numTriangles));
}

BOOL8 _MODEL_API TMesh::HasStrips() {
	return hasStrips = ((numStrips != 0) && (strips.GetLength() == numStrips));
}

TArray<Triangle> _MODEL_API &TMesh::GetTriangles() {
	return triangles;
}

TArray<unsigned short> _MODEL_API &TMesh::GetStripLengths() {
	return stripLengths;
}

TRefArray<TUShortArray> _MODEL_API &TMesh::GetStrips() {
	return strips;
}

Vector3f _MODEL_API &TMesh::GetTranslation() {
	return translation;
}

Matrix33f _MODEL_API &TMesh::GetRotation() {
	return rotation;
}

float _MODEL_API &TMesh::GetScale() {
	return scale;
}

Vector3f _MODEL_API &TMesh::GetBoneTranslation() {
	return boneTranslation;
}

Matrix33f _MODEL_API &TMesh::GetBoneRotation() {
	return boneRotation;
}

float _MODEL_API &TMesh::GetBoneScale() {
	return boneScale;
}

TRefArray<TSkin> _MODEL_API &TMesh::GetSkins() {
	return skins;
}

TRefArray<TBone> _MODEL_API &TMesh::GetBones() {
	return bones;
}

TRefArray<TString> _MODEL_API &TMesh::GetBoneBlockIndices() {
	return boneBlockIndices;
}

TRefArray<TBoneTreeNode> _MODEL_API &TMesh::GetBoneNodes() {
	return boneNodes;
}

unsigned short _MODEL_API TMesh::GetNumVertices() {
	return numVertices;
}

void _MODEL_API TMesh::SetNumVertices(unsigned short num) {
	numVertices = num;
}

unsigned int _MODEL_API TMesh::GetNumTriangles() {
	return numTriangles;
}

void _MODEL_API TMesh::SetNumTriangles(unsigned short num) {
	numTriangles = num;
	triangles.Resize(num);
}

unsigned short _MODEL_API TMesh::GetNumStrips() {
	return numStrips;
}

void _MODEL_API TMesh::SetNumStrips(unsigned short num) {
	numStrips = num;
}

void _MODEL_API TMesh::BuildTangentsBinormals() {
	if ( hasTriangles ) {
		if ( ( !hasNormals ) || ( !hasBinormals ) ) {
			tangents.Resize(numVertices);
			binormals.Resize(numVertices);
			for (unsigned int i1 = 0 ; i1 < numTriangles ; i1 ++ ) {
				Vector3f tangent1(vertices[triangles[i1].c].x - vertices[triangles[i1].a].x, vertices[triangles[i1].c].y - vertices[triangles[i1].a].y, vertices[triangles[i1].c].z - vertices[triangles[i1].a].z);
				tangent1 = tangent1.Normalized();
				Vector3f binormal1 = (tangent1^normals[triangles[i1].a]).Normalized();
				tangents[triangles[i1].a] = tangent1;
				binormals[triangles[i1].a] = binormal1;

				Vector3f tangent2(vertices[triangles[i1].a].x - vertices[triangles[i1].b].x, vertices[triangles[i1].a].y - vertices[triangles[i1].b].y, vertices[triangles[i1].a].z - vertices[triangles[i1].b].z);
				tangent2 = tangent2.Normalized();
				Vector3f binormal2 = (tangent2^normals[triangles[i1].b]).Normalized();
				tangents[triangles[i1].b] = tangent2;
				binormals[triangles[i1].b] = binormal2;

				Vector3f tangent3(vertices[triangles[i1].b].x - vertices[triangles[i1].c].x, vertices[triangles[i1].b].y - vertices[triangles[i1].c].y, vertices[triangles[i1].b].z - vertices[triangles[i1].c].z);
				tangent3 = tangent3.Normalized();
				Vector3f binormal3 = (tangent3^normals[triangles[i1].c]).Normalized();
				tangents[triangles[i1].c] = tangent3;
				binormals[triangles[i1].c] = binormal3;
			}
			hasNormals = TRUE;
			hasBinormals = TRUE;
		}
	} else if ( hasStrips ) {
		if ( ( !hasNormals ) || ( !hasBinormals ) ) {
			if ( stripLengths.GetLength() < 1 ) {
				return;
			}
			if ( strips.GetLength() < 1 ) {
				return;
			}
			tangents.Resize(numVertices);
			binormals.Resize(numVertices);
			unsigned int sl = stripLengths[0] - 1;
			TArray<unsigned short> &strip = strips[0];
			for (unsigned int i1 = 0 ; i1 < sl ; i1 ++ ) {
				Vector3f tangent1(vertices[strip[i1 + 1]].x - vertices[strip[i1]].x, vertices[strip[i1 + 1]].y - vertices[strip[i1]].y, vertices[strip[i1 + 1]].z - vertices[strip[i1]].z);
				tangent1 = tangent1.Normalized();
				Vector3f binormal1 = (tangent1^normals[strip[i1]]).Normalized();
				tangents[strip[i1]] = tangent1;
				binormals[strip[i1]] = binormal1;
			}
			hasNormals = TRUE;
			hasBinormals = TRUE;
		}
	}
}

void _MODEL_API TMesh::CopyBoneBlockIndices(TMesh &tar) {
	tar.name = name;
	unsigned int length = boneBlockIndices.GetLength();
	tar.boneBlockIndices.Resize(length);
	tar.boneBlockIndices.CreateAll();
	for ( unsigned int i2 = 0 ; i2 < length ; i2 ++ ) {
		tar.boneBlockIndices[i2] = boneBlockIndices[i2];
	}
	tar.numBones = length;
}

TArray<Matrix44f> _MODEL_API &TMesh::GetBoneMatrices() {
	return boneMatrices;
}
