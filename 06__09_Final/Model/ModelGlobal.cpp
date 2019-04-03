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
#define _ARRAY_API _MODEL_API
#include "ModelGlobal.hpp"

_MODEL_API TModelGlobal::TModelGlobal() {
	models.Resize(0);
	animations.Resize(0);
	fileType = TModelGlobal::type_model;
	numModels = 0;
	numAnimations = 0;
}

_MODEL_API TModelGlobal::~TModelGlobal() {
//	models.DeleteAll();
	models.Resize(0);
//	animations.DeleteAll();
	animations.Resize(0);
}

char _MODEL_API *TModelGlobal::GetClassName() {
	return "TModelGlobal";
}

int _MODEL_API TModelGlobal::GetClassCode() {
	return CLSID_TModelGlobal;
}

int _MODEL_API TModelGlobal::GetHashCode() {
	return 1;
}

BOOL32 _MODEL_API TModelGlobal::IsInstanceof(const char* className) {
	if (strcmp("TModelGlobal", className) == 0) {
		return TRUE;
	}
	return TModelObject::IsInstanceof(className);
}

BOOL32 _MODEL_API TModelGlobal::IsEqualto(IObject &obj) {
	return FALSE;
}

void _MODEL_API TModelGlobal::Serialize(IIOStream &iio) {
	if ( iio.GetLoadStore() == IIOStream::load ) {
		char *magic = new char[8];
		iio.ReadBuffer(magic, 8, sizeof(char));
		if ( strcmp("MGEMDL\n", magic) != 0 ) {
			return;
		}
		unsigned char endiantype = 0;
		iio.Read(&endiantype, sizeof(unsigned char));
		iio.Read(&version, sizeof(unsigned int));
		iio.Read(&subVersion, sizeof(unsigned int));
		if ( ( version == 0x00000001 ) && ( subVersion == 0x00000000 ) ) {
			iio.Read(&fileType, sizeof(unsigned char));
			if ( ( fileType == TModelGlobal::type_model ) || ( fileType == TModelGlobal::type_animation ) ) {
				iio.Read(&numModels, sizeof(unsigned short));
				models.Resize(numModels);
				models.CreateAll();
				for (unsigned int i1 = 0 ; i1 < numModels ; i1 ++ ) {
					TString className;
					className.Load(iio);
					models[i1].SetVersion(version);
					models[i1].SetSubVersion(subVersion);
					models[i1].Serialize(iio);
				}
				iio.Read(&numAnimations, sizeof(unsigned short));
				animations.Resize(numAnimations);
				animations.CreateAll();
				for (unsigned int i2 = 0 ; i2 < numAnimations ; i2 ++ ) {
					TString aClassName;
					aClassName.Load(iio);
					animations[i2].SetVersion(version);
					animations[i2].SetSubVersion(subVersion);
					animations[i2].Serialize(iio);
				}
			}
			if (fileType == TModelGlobal::type_collision) {
				unsigned int numcdmcs = 0;
				iio.Read(&numcdmcs, sizeof(unsigned int));
				cdmcs.Resize(numcdmcs);
				cdmcs.CreateAll();
				for (unsigned int i2 = 0 ; i2 < numcdmcs ; i2 ++ ) {
					cdmcs[i2].SetVersion(version);
					cdmcs[i2].SetSubVersion(subVersion);
					cdmcs[i2].Serialize(iio);
				}
			}
		}
	} else {
		version = 0x00000001;
		subVersion = 0x00000000;
		unsigned char endiantype = IIOStream::little_endian;
		iio.WriteBuffer("MGEMDL\n\0", 8, sizeof(char));
		iio.Write(&endiantype, sizeof(unsigned char));
		iio.Write(&version, sizeof(unsigned int));
		iio.Write(&subVersion, sizeof(unsigned int));
		iio.Write(&fileType, sizeof(unsigned char));
		if (fileType == TModelGlobal::type_model) {
			numModels = (unsigned short)models.GetLength();
			iio.Write(&numModels, sizeof(unsigned short));
			for (unsigned int i1 = 0 ; i1 < numModels ; i1 ++ ) {
				if ( &models[i1] != NULL ) {
					TString className(models[i1].GetClassName());
					className.Store(iio);
					models[i1].Serialize(iio);
				}
			}
			numAnimations = (unsigned short)animations.GetLength();
			iio.Write(&numAnimations, sizeof(unsigned short));
			for (unsigned int i2 = 0 ; i2 < numAnimations ; i2 ++ ) {
				if ( &animations[i2] != NULL ) {
					TString aClassName(animations[i2].GetClassName());
					aClassName.Store(iio);
					animations[i2].Serialize(iio);
				}
			}
		}
		if (fileType == TModelGlobal::type_animation) {
			numModels = 0;
			iio.Write(&numModels, sizeof(unsigned short));
			numAnimations = (unsigned short)animations.GetLength();
			iio.Write(&numAnimations, sizeof(unsigned short));
			for (unsigned int i2 = 0 ; i2 < numAnimations ; i2 ++ ) {
				if ( &animations[i2] != NULL ) {
					TString aClassName(animations[i2].GetClassName());
					aClassName.Store(iio);
					animations[i2].Serialize(iio);
				}
			}
		}
		if (fileType == TModelGlobal::type_collision) {
			unsigned int numcdmcs = cdmcs.GetLength();
			iio.Write(&numcdmcs, sizeof(unsigned int));
			for (unsigned int i2 = 0 ; i2 < numcdmcs ; i2 ++ ) {
				cdmcs[i2].Serialize(iio);
			}
		}
	}
}

void _MODEL_API TModelGlobal::Wait() {
}

void _MODEL_API TModelGlobal::Notify() {
}

TRefArray<TModel> _MODEL_API &TModelGlobal::GetModels() {
	return models;
}

TRefArray<TSequence> _MODEL_API &TModelGlobal::GetAnimations() {
	return animations;
}

TRefArray<TCollisionDetectingMatricesController> _MODEL_API &TModelGlobal::GetCollisionDetectingMatricesControllers() {
	return cdmcs;
}

byte _MODEL_API TModelGlobal::GetFileType() {
	return fileType;
}

void _MODEL_API TModelGlobal::SetFileType(byte ftype) {
	fileType = ftype;
}
