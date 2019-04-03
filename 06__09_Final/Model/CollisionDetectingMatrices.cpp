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
#include "math.h"
#include "..\Base\Type.h"
#include "..\Base\Base.h"
#undef _ARRAY_API
#define _ARRAY_API _MODEL_API
#include "CollisionDetectingMatrices.hpp"

_MODEL_API TCollisionDetectingMatrices::TCollisionDetectingMatrices() {
	cdms.Resize(0);
	isOuter = TRUE;
}

_MODEL_API TCollisionDetectingMatrices::~TCollisionDetectingMatrices() {
	cdms.Resize(0);
}

char _MODEL_API *TCollisionDetectingMatrices::GetClassName() {
	return "TCollisionDetectingMatrices";
}

int _MODEL_API TCollisionDetectingMatrices::GetClassCode() {
	return CLSID_TCollisionDetectingMatrices;
}

int _MODEL_API TCollisionDetectingMatrices::GetHashCode() {
	return 1;
}

BOOL32 _MODEL_API TCollisionDetectingMatrices::IsInstanceof(const char* className) {
	if (strcmp("TCollisionDetectingMatrices", className) == 0) {
		return TRUE;
	}
	return TModelObject::IsInstanceof(className);
}

BOOL32 _MODEL_API TCollisionDetectingMatrices::IsEqualto(IObject &obj) {
	return FALSE;
}

void _MODEL_API TCollisionDetectingMatrices::Serialize(IIOStream &iio) {
	if ( iio.GetLoadStore() == IIOStream::load ) {
		if ( ( version == 0x00000001 ) && ( subVersion == 0x00000000 ) ) {
			iio.ReadBuffer(&position, 3, sizeof(float));
			iio.ReadBuffer(&recommendation, 16, sizeof(float));
			iio.Read(&isOuter, sizeof(BOOL32));
			unsigned int numcdms = 0;
			iio.Read(&numcdms, sizeof(unsigned int));
			cdms.Resize(numcdms);
			iio.ReadBuffer(cdms.GetBuffer(), 16 * numcdms, sizeof(float));
		}
	} else {
		iio.WriteBuffer(&position, 3, sizeof(float));
		iio.WriteBuffer(&recommendation, 16, sizeof(float));
		iio.Write(&isOuter, sizeof(BOOL32));
		unsigned int numcdms = cdms.GetLength();
		iio.Write(&numcdms, sizeof(unsigned int));
		iio.WriteBuffer(cdms.GetBuffer(), 16 * numcdms, sizeof(float));
	}
}

void _MODEL_API TCollisionDetectingMatrices::Wait() {
}

void _MODEL_API TCollisionDetectingMatrices::Notify() {
}

BOOL32 _MODEL_API TCollisionDetectingMatrices::IsCollision(Vector3f &src, Vector3f &varify) {
	if ( isOuter ) {
		unsigned int numcdms = cdms.GetLength();
		for ( unsigned int i1 = 0 ; i1 < numcdms ; i1 ++ ) {
			if ( cdms[i1].MultiZ(src) > 0 ) {
				return FALSE;
			}
		}
		varify = recommendation * src;
		return TRUE;
	} else {
		unsigned int numcdms = cdms.GetLength();
		for ( unsigned int i1 = 0 ; i1 < numcdms ; i1 ++ ) {
			if ( cdms[i1].MultiZ(src) < 0 ) {
				varify = recommendation * src;
				return TRUE;
			}
		}
		return FALSE;
	}
}
BOOL32 _MODEL_API TCollisionDetectingMatrices::IsCollision(Vector4f &src, Vector4f &varify) {
	if ( isOuter ) {
		unsigned int numcdms = cdms.GetLength();
		for ( unsigned int i1 = 0 ; i1 < numcdms ; i1 ++ ) {
			if ( cdms[i1].MultiZ(src) > 0 ) {
				return FALSE;
			}
		}
		varify = recommendation * src;
		return TRUE;
	} else {
		unsigned int numcdms = cdms.GetLength();
		for ( unsigned int i1 = 0 ; i1 < numcdms ; i1 ++ ) {
			if ( cdms[i1].MultiZ(src) < 0 ) {
				varify = recommendation * src;
				return TRUE;
			}
		}
		return FALSE;
	}
}

Vector3f _MODEL_API &TCollisionDetectingMatrices::GetPosition() {
	return position;
}
Matrix44f _MODEL_API &TCollisionDetectingMatrices::GetRecommendation() {
	return recommendation;
}
TArray<Matrix44f> _MODEL_API &TCollisionDetectingMatrices::GetCDMs() {
	return cdms;
}
void _MODEL_API TCollisionDetectingMatrices::SetOuterFlag(BOOL32 flag) {
	isOuter = flag;
}
BOOL32 _MODEL_API TCollisionDetectingMatrices::IsOuter() {
	return isOuter;
}

BOOL32 _MODEL_API TCollisionDetectingMatrices::IsMatricesZEqual(Matrix44f &src1, Matrix44f &src2, float delta) {
	if ( fabsf(src1.m[2][0] - src2.m[2][0]) >= delta ) {
		return FALSE;
	}
	if ( fabsf(src1.m[2][1] - src2.m[2][1]) >= delta ) {
		return FALSE;
	}
	if ( fabsf(src1.m[2][2] - src2.m[2][2]) >= delta ) {
		return FALSE;
	}

	if ( fabsf(src1.m[2][3] - src2.m[2][3]) >= delta ) {
		return FALSE;
	}
	return TRUE;
}
unsigned int _MODEL_API TCollisionDetectingMatrices::BuildCollisionDetectingMatrices(TMesh &msh) {
	if ( msh.HasVertices() && msh.HasNormals() && msh.HasTangents() && msh.HasBinormals() ) {
		if ( msh.HasTriangles() ) {
			cdms.Resize(msh.GetNumTriangles());
			unsigned int numcdm = 0;
			unsigned int numtri = msh.GetNumTriangles();
			TArray<Vector3f> &vertices = msh.GetVertices();
			TArray<Vector3f> &tangents = msh.GetTangents();
			TArray<Vector3f> &binormals = msh.GetBinormals();
			TArray<Vector3f> &normals = msh.GetNormals();
			TArray<Triangle> &tris = msh.GetTriangles();
			for ( unsigned int i1 = 0 ; i1 < numtri ; i1 ++ ) {
				Matrix33f coord1(tangents[tris[i1].a], binormals[tris[i1].a], normals[tris[i1].a]);
				Matrix33f coord2(tangents[tris[i1].b], binormals[tris[i1].b], normals[tris[i1].b]);
				Matrix33f coord3(tangents[tris[i1].c], binormals[tris[i1].c], normals[tris[i1].c]);
				Vector3f itr1 = vertices[tris[i1].a] * -1.0f;
				Vector3f itr2 = vertices[tris[i1].b] * -1.0f;
				Vector3f itr3 = vertices[tris[i1].c] * -1.0f;
				Matrix44f cdm1 = Matrix44f(Vector3f(), coord1) * Matrix44f(itr1, Matrix33f());
				Matrix44f cdm2 = Matrix44f(Vector3f(), coord2) * Matrix44f(itr2, Matrix33f());
				Matrix44f cdm3 = Matrix44f(Vector3f(), coord3) * Matrix44f(itr3, Matrix33f());
				BOOL32 hasequal;
				hasequal = FALSE;
				for ( unsigned int i2 = 0 ; i2 < numcdm ; i2 ++ ) {
					if ( IsMatricesZEqual(cdms[i2], cdm1, 0.001f) ) {
						hasequal = TRUE;
						break;
					}
				}
				if ( !hasequal ) {
					cdms[numcdm++] = cdm1;
				}
				
				hasequal = FALSE;
				for ( unsigned int i3 = 0 ; i3 < numcdm ; i3 ++ ) {
					if ( IsMatricesZEqual(cdms[i3], cdm2, 0.001f) ) {
						hasequal = TRUE;
						break;
					}
				}
				if ( !hasequal ) {
					cdms[numcdm++] = cdm2;
				}

				hasequal = FALSE;
				for ( unsigned int i4 = 0 ; i4 < numcdm ; i4 ++ ) {
					if ( IsMatricesZEqual(cdms[i4], cdm3, 0.001f) ) {
						hasequal = TRUE;
						break;
					}
				}
				if ( !hasequal ) {
					cdms[numcdm++] = cdm3;
				}
			}
			cdms.Resize(numcdm);
			return numcdm;
		}
	}
	return cdms.GetLength();
}
void _MODEL_API TCollisionDetectingMatrices::Scale(float ratio) {
	unsigned int numcdms = cdms.GetLength();
	for ( unsigned int i1 = 0 ; i1 < numcdms ; i1 ++ ) {
		cdms[i1].m[2][3] *= ratio;
	}
}

