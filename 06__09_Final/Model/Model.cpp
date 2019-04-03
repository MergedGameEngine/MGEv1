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
#include "Model.hpp"

_MODEL_API TModel::TModel() {
	meshes.Resize(0);
	boneController = NULL;
	numMeshes = 0;
	hasBoneController = FALSE;
}

_MODEL_API TModel::~TModel() {
	meshes.DeleteAll();
	meshes.Resize(0);
}

char _MODEL_API *TModel::GetClassName() {
	return "TModel";
}

int _MODEL_API TModel::GetClassCode() {
	return CLSID_TModel;
}

int _MODEL_API TModel::GetHashCode() {
	return 1;
}

BOOL32 _MODEL_API TModel::IsInstanceof(const char* className) {
	if (strcmp("TModel", className) == 0) {
		return TRUE;
	}
	return TModelObject::IsInstanceof(className);
}

BOOL32 _MODEL_API TModel::IsEqualto(IObject &obj) {
	return FALSE;
}

void _MODEL_API TModel::Serialize(IIOStream &iio) {
	TModelObject::Serialize(iio);
	if ( iio.GetLoadStore() == IIOStream::load ) {
		if ( ( version == 0x00000001 ) && ( subVersion == 0x00000000 ) ) {
			name.Load(iio);
			iio.ReadBuffer(&translation, 3, sizeof(float));
			iio.ReadBuffer(&rotation, 9, sizeof(float));
			iio.Read(&scale, sizeof(float));
			iio.Read(&numMeshes, sizeof(unsigned short));
			meshes.Resize(numMeshes);
			meshes.CreateAll();
			for (unsigned int i1 = 0 ; i1 < numMeshes ; i1 ++ ) {
				TString mClassName;
				mClassName.Load(iio);
				meshes[i1].SetVersion(version);
				meshes[i1].SetSubVersion(subVersion);
				meshes[i1].Serialize(iio);
			}
			iio.Read(&hasBoneController, sizeof(BOOL8));
			if ( hasBoneController ) {
				TString bcClassName;
				bcClassName.Load(iio);
				boneController = new TBoneController();
				boneController->SetVersion(version);
				boneController->SetSubVersion(subVersion);
				boneController->Serialize(iio);

				for (unsigned int i2 = 0 ; i2 < numMeshes ; i2 ++ ) {
					TRefArray<TBoneTreeNode> &boneNodes = meshes[i2].GetBoneNodes();
					boneNodes.Resize(meshes[i2].GetBones().GetLength());
					TRefArray<TString> &boneBlockIndices = meshes[i2].GetBoneBlockIndices();
					for (unsigned int i3 = 0 ; i3 < boneNodes.GetLength() ; i3 ++ ) {
						boneNodes.Set(i3, (TBoneTreeNode*)(boneController->GetBoneHashtable().Get(boneBlockIndices[i3])));
					}
				}
			}
		}
	} else {
		name.Store(iio);
		iio.WriteBuffer(&translation, 3, sizeof(float));
		iio.WriteBuffer(&rotation, 9, sizeof(float));
		iio.Write(&scale, sizeof(float));
		numMeshes = (unsigned short)meshes.GetLength();
		iio.Write(&numMeshes, sizeof(unsigned short));
		for (unsigned int i1 = 0 ; i1 < numMeshes ; i1 ++ ) {
			TString mClassName(meshes[i1].GetClassName());
			mClassName.Store(iio);
			meshes[i1].Serialize(iio);
		}
		iio.Write(&hasBoneController, sizeof(BOOL8));
		if ( hasBoneController ) {
			TString bcClassName(boneController->GetClassName());
			bcClassName.Store(iio);
			boneController->Serialize(iio);
		}
	}
}

void _MODEL_API TModel::Wait() {
}

void _MODEL_API TModel::Notify() {
}

Vector3f _MODEL_API &TModel::GetTranslation() {
	return translation;
}

Matrix33f _MODEL_API &TModel::GetRotation() {
	return rotation;
}

float _MODEL_API &TModel::GetScale() {
	return scale;
}

TRefArray<TMesh> _MODEL_API &TModel::GetMeshes() {
	return meshes;
}

BOOL8 _MODEL_API TModel::HasBoneController() {
	return hasBoneController;
}

TBoneController _MODEL_API &TModel::GetBoneController() {
	return *boneController;
}

void _MODEL_API TModel::SetBoneController(TBoneController *src) {
	if (boneController != NULL) {
		delete boneController;
	}
	if (src != NULL) {
		hasBoneController = TRUE;
		boneController = src;
	} else {
		hasBoneController = FALSE;
		boneController = NULL;
	}
}

unsigned short _MODEL_API TModel::GetNumMeshes() {
	return numMeshes;
}

void _MODEL_API TModel::SetNumMeshes(unsigned short num) {
	numMeshes = num;
}

void _MODEL_API TModel::CopyBoneBlockIndices(TModel &tar) {
	unsigned int length = meshes.GetLength();
	tar.meshes.Resize(length);
	tar.meshes.CreateAll();
	for (unsigned int i2 = 0 ; i2 < length ; i2 ++ ) {
		meshes[i2].CopyBoneBlockIndices(tar.meshes[i2]);
	}
	tar.numMeshes = length;
}

void _MODEL_API TModel::LinkBoneNodes() {
	for (unsigned int i2 = 0 ; i2 < numMeshes ; i2 ++ ) {
		TRefArray<TString> &boneBlockIndices = meshes[i2].GetBoneBlockIndices();
		TRefArray<TBoneTreeNode> &boneNodes = meshes[i2].GetBoneNodes();
		boneNodes.Resize(boneBlockIndices.GetLength());
		for (unsigned int i3 = 0 ; i3 < boneNodes.GetLength() ; i3 ++ ) {
			boneNodes.Set(i3, (TBoneTreeNode*)(boneController->GetBoneHashtable().Get(boneBlockIndices[i3])));
		}
	}
}

void _MODEL_API TModel::CopyAnimationController(TModel &tar) {
	CopyBoneBlockIndices(tar);
	if ( tar.boneController == NULL ) {
		tar.boneController = new TBoneController();
	}
	boneController->CopyInstance(*tar.boneController);
	tar.LinkBoneNodes();
}

void _MODEL_API TModel::BuildAnimationController(TModel &tar, TString &rootbonename, Transform &trans, Transform &itrans) {
	CopyBoneBlockIndices(tar);
	if ( tar.boneController == NULL ) {
		tar.boneController = new TBoneController();
		tar.boneController->SetBoneRoot(new TBoneTreeNode());
	} else if ( NULL == &tar.boneController->GetBoneRoot() ) {
		tar.boneController->SetBoneRoot(new TBoneTreeNode());
	} else {
	}
	tar.boneController->GetBoneRoot().GetName() = rootbonename;
	tar.boneController->GetBoneRoot().GetTransform() = trans;
	tar.boneController->GetBoneRoot().GetInvertedTransform() = itrans;
	tar.numMeshes = tar.meshes.GetLength();
	for ( unsigned int i3 = 0 ; i3 < tar.numMeshes ; i3 ++ ) {
		tar.meshes[i3].GetBoneNodes().Resize(1);
		tar.meshes[i3].GetBoneNodes().Set(0, &tar.boneController->GetBoneRoot());
	}
}

void _MODEL_API TModel::SetAnimationControllerBoneRoot(TString &newname, Transform &trans, Transform &itrans) {
	boneController->GetBoneRoot().GetName() = newname;
	boneController->GetBoneRoot().GetTransform() = trans;
	boneController->GetBoneRoot().GetInvertedTransform() = itrans;
}