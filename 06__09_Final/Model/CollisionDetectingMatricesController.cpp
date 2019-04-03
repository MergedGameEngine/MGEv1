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
#include "CollisionDetectingMatricesController.hpp"

_MODEL_API TCollisionDetectingMatricesController::TCollisionDetectingMatricesController() {
}

_MODEL_API TCollisionDetectingMatricesController::~TCollisionDetectingMatricesController() {
}

char _MODEL_API *TCollisionDetectingMatricesController::GetClassName() {
	return "TCollisionDetectingMatricesController";
}

int _MODEL_API TCollisionDetectingMatricesController::GetClassCode() {
	return CLSID_TCollisionDetectingMatricesController;
}

int _MODEL_API TCollisionDetectingMatricesController::GetHashCode() {
	return 1;
}

BOOL32 _MODEL_API TCollisionDetectingMatricesController::IsInstanceof(const char* className) {
	if (strcmp("TCollisionDetectingMatricesController", className) == 0) {
		return TRUE;
	}
	return TModelObject::IsInstanceof(className);
}

BOOL32 _MODEL_API TCollisionDetectingMatricesController::IsEqualto(IObject &obj) {
	return FALSE;
}

void _MODEL_API TCollisionDetectingMatricesController::Serialize(IIOStream &iio) {
	if ( iio.GetLoadStore() == IIOStream::load ) {
		if ( ( version == 0x00000001 ) && ( subVersion == 0x00000000 ) ) {
			unsigned int numcdms = 0;
			iio.Read(&numcdms, sizeof(unsigned int));
			cdmos.Resize(numcdms);
			cdmos.CreateAll();
			for ( unsigned int i2 = 0 ; i2 < numcdms ; i2 ++ ) {
				cdmos[i2].SetVersion(version);
				cdmos[i2].SetSubVersion(subVersion);
				cdmos[i2].Serialize(iio);
			}
		}
	} else {
		unsigned int numcdms = cdmos.GetLength();
		iio.Write(&numcdms, sizeof(unsigned int));
		for ( unsigned int i2 = 0 ; i2 < numcdms ; i2 ++ ) {
			cdmos[i2].Serialize(iio);
		}
	}
}

void _MODEL_API TCollisionDetectingMatricesController::Wait() {
}

void _MODEL_API TCollisionDetectingMatricesController::Notify() {
}

TRefArray<TCollisionDetectingMatrices> _MODEL_API &TCollisionDetectingMatricesController::GetCDMObjects() {
	return cdmos;
}
THashtable _MODEL_API &TCollisionDetectingMatricesController::GetCDMIndices() {
	return cdmoIndices;
}
TCollisionDetectingMatrices _MODEL_API &TCollisionDetectingMatricesController::GetCDMObject(TString &key) {
	return *(TCollisionDetectingMatrices*)cdmoIndices.Get(key);
}

BOOL32 _MODEL_API TCollisionDetectingMatricesController::IsCollision(Vector4f &src, Vector4f &varify) {
	unsigned int numcdmos = cdmos.GetLength();
	for ( unsigned int i2 = 0 ; i2 < numcdmos ; i2 ++ ) {
		if ( cdmos[i2].IsCollision(src, varify) ) {
			return TRUE;
		}
	}
	return FALSE;
}

BOOL32 _MODEL_API TCollisionDetectingMatricesController::IsCollision(Vector3f &src, Vector3f &varify) {
	unsigned int numcdmos = cdmos.GetLength();
	for ( unsigned int i2 = 0 ; i2 < numcdmos ; i2 ++ ) {
		if ( cdmos[i2].IsCollision(src, varify) ) {
			return TRUE;
		}
	}
	return FALSE;
}

void _MODEL_API TCollisionDetectingMatricesController::Scale(float ratio) {
	unsigned int numcdmos = cdmos.GetLength();
	for ( unsigned int i2 = 0 ; i2 < numcdmos ; i2 ++ ) {
		cdmos[i2].Scale(ratio);
	}
}
