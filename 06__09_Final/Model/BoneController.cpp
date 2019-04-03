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
#include "BoneTreeNode.hpp"
#include "BoneController.h"

_MODEL_API TBoneController::TBoneController() {
	boneRoot = NULL;
	boneTable.Resize(0);
	numBones = 0;
	indexCount = 0;
}

_MODEL_API TBoneController::~TBoneController() {
	boneTable.Resize(0);
}

char _MODEL_API *TBoneController::GetClassName() {
	return "TBoneController";
}

int _MODEL_API TBoneController::GetClassCode() {
	return CLSID_TBoneController;
}

int _MODEL_API TBoneController::GetHashCode() {
	return 1;
}

BOOL32 _MODEL_API TBoneController::IsInstanceof(const char* className) {
	if (strcmp("TBoneController", className) == 0) {
		return TRUE;
	}
	return TModelObject::IsInstanceof(className);
}

BOOL32 _MODEL_API TBoneController::IsEqualto(IObject &obj) {
	return FALSE;
}

void _MODEL_API TBoneController::Serialize(IIOStream &iio) {
	TModelObject::Serialize(iio);
	if ( iio.GetLoadStore() == IIOStream::load ) {
		if ( ( version == 0x00000001 ) && ( subVersion == 0x00000000 ) ) {
			name.Load(iio);
			iio.ReadBuffer(&translation, 3, sizeof(float));
			iio.ReadBuffer(&rotation, 9, sizeof(float));
			iio.Read(&scale, sizeof(float));
			iio.Read(&numBones, sizeof(unsigned short));
			TString btnClassName;
			btnClassName.Load(iio);
			boneRoot = new TBoneTreeNode(NULL, &boneHashtable);
			boneRoot->SetVersion(version);
			boneRoot->SetSubVersion(subVersion);
			boneRoot->Serialize(iio);
		}
	} else {
		name.Store(iio);
		iio.WriteBuffer(&translation, 3, sizeof(float));
		iio.WriteBuffer(&rotation, 9, sizeof(float));
		iio.Write(&scale, sizeof(float));
		iio.Write(&numBones, sizeof(unsigned short));
		TString btnClassName(boneRoot->GetClassName());
		btnClassName.Store(iio);
		boneRoot->Serialize(iio);
	}
}

void _MODEL_API TBoneController::Wait() {
}

void _MODEL_API TBoneController::Notify() {
}

TBoneTreeNode _MODEL_API &TBoneController::GetBoneRoot() {
	return *boneRoot;
}

Vector3f _MODEL_API &TBoneController::GetTranslation() {
	return translation;
}

Matrix33f _MODEL_API &TBoneController::GetRotation() {
	return rotation;
}

float _MODEL_API &TBoneController::GetScale() {
	return scale;
}

TRefArray<TBoneTreeNode> _MODEL_API &TBoneController::GetBoneTable() {
	return boneTable;
}

THashtable _MODEL_API &TBoneController::GetBoneHashtable() {
	return boneHashtable;
}

void _MODEL_API TBoneController::SetBoneRoot(TBoneTreeNode *src) {
	if (boneRoot!= NULL) {
		delete boneRoot;
		boneRoot = NULL;
	}
	boneRoot = src;
}

void _MODEL_API TBoneController::BuildBoneMatrix(TBoneTreeNode &btn, Transform &src) {
	btn.GetTransform() = src * btn.GetTransform();
	if (btn.HasSubNode()) {
		BuildBoneMatrix(btn.GetSubNode(), btn.GetTransform());
	}
	if (btn.HasNextNode()) {
		BuildBoneMatrix(btn.GetNextNode(), src);
	}
}

void _MODEL_API TBoneController::ReloadMatrix(TBoneTreeNode &btn) {
	btn.GetTransform() = Transform(btn.GetTranslation(), btn.GetRotation(), 1.0f);
	if (btn.HasSubNode()) {
		ReloadMatrix(btn.GetSubNode());
	}
	if (btn.HasNextNode()) {
		ReloadMatrix(btn.GetNextNode());
	}
}

void _MODEL_API TBoneController::ReloadInvertedMatrix(TBoneTreeNode &btn) {
	btn.GetInvertedTransform() = btn.GetTransform().Inverse();
	if (btn.HasSubNode()) {
		ReloadInvertedMatrix(btn.GetSubNode());
	}
	if (btn.HasNextNode()) {
		ReloadInvertedMatrix(btn.GetNextNode());
	}
}

void _MODEL_API TBoneController::DoAnimation(TBoneTreeNode &btn, Transform &src) {
//	btn.GetFastTransform() = src * btn.GetTransform() * btn.GetAnimationTransform();
	btn.GetFastTransform() = src * btn.GetTransform();
	if (btn.HasSubNode()) {
		DoAnimation(btn.GetSubNode(), btn.GetFastTransform());
	}
	if (btn.HasNextNode()) {
		DoAnimation(btn.GetNextNode(), src);
	}
	btn.GetFastTransform() = btn.GetFastTransform() * btn.GetInvertedTransform();
}

void _MODEL_API TBoneController::BuildBoneMatrix() {
	BuildBoneMatrix(*boneRoot, Transform(Vector3f(), Matrix33f(), 1.0f));
}

void _MODEL_API TBoneController::ReloadMatrix() {
	ReloadMatrix(*boneRoot);
}

void _MODEL_API TBoneController::ReloadInvertedMatrix() {
	ReloadInvertedMatrix(*boneRoot);
}

void _MODEL_API TBoneController::DoAnimation() {
	DoAnimation(*boneRoot, Transform(Vector3f(), Matrix33f(), 1.0f));
}

void _MODEL_API TBoneController::CopyInstance(TBoneController &bc) {
	bc.name = name;

	bc.translation = translation;
	bc.rotation = rotation;
	bc.scale = scale;
	
	bc.numBones = numBones;

	bc.boneRoot = new TBoneTreeNode(NULL, &bc.boneHashtable);
	bc.boneRoot->SetVersion(version);
	bc.boneRoot->SetSubVersion(subVersion);
	boneRoot->CopyInstance(*bc.boneRoot);

	bc.boneTable.Resize(boneTable.GetLength());
	unsigned int i3 = boneTable.GetLength();
	for ( unsigned int i2 = 0 ; i2 < i3 ; i2 ++ ) {
		bc.boneTable.Set(i2, (TBoneTreeNode*)(bc.boneHashtable.Get(boneTable[i2].GetName())));
	}
}

void _MODEL_API TBoneController::CopyBoneTransform(TBoneTreeNode &btn) {
	TBoneTreeNode *lbtn = (TBoneTreeNode*)boneHashtable.Get(btn.GetName());
	if ( lbtn != NULL ) {
		btn.GetTransform() = lbtn->GetFastTransform();
	}
}
