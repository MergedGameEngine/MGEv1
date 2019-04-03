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

_MODEL_API TBoneTreeNode::TBoneTreeNode() {
	boneId = 0;
	hasNextNode = FALSE;
	hasSubNode = FALSE;
	nextBoneId = 0;
	subBoneId = 0;
	nextNode = NULL;
	subNode = NULL;
}
_MODEL_API TBoneTreeNode::TBoneTreeNode(TBoneTreeNode *p, THashtable *table) {
	boneId = 0;
	hasNextNode = FALSE;
	hasSubNode = FALSE;
	nextBoneId = 0;
	subBoneId = 0;
	nextNode = NULL;
	subNode = NULL;
	parent = p;
	boneTable = table;
}

_MODEL_API TBoneTreeNode::~TBoneTreeNode() {
}

char _MODEL_API *TBoneTreeNode::GetClassName() {
	return "TBoneTreeNode";
}

int _MODEL_API TBoneTreeNode::GetClassCode() {
	return CLSID_TBoneTreeNode;
}

int _MODEL_API TBoneTreeNode::GetHashCode() {
	return 1;
}

BOOL32 _MODEL_API TBoneTreeNode::IsInstanceof(const char* className) {
	if (strcmp("TBoneTreeNode", className) == 0) {
		return TRUE;
	}
	return TModelObject::IsInstanceof(className);
}

BOOL32 _MODEL_API TBoneTreeNode::IsEqualto(IObject &obj) {
	return FALSE;
}

void _MODEL_API TBoneTreeNode::Serialize(IIOStream &iio) {
	TModelObject::Serialize(iio);
	if ( iio.GetLoadStore() == IIOStream::load ) {
		if ( ( version == 0x00000001 ) && ( subVersion == 0x00000000 ) ) {
			name.Load(iio);
			iio.ReadBuffer(&translation, 3, sizeof(float));
			iio.ReadBuffer(&rotation, 9, sizeof(float));
			iio.Read(&scale, sizeof(float));

			iio.Read(&boneId, sizeof(unsigned short));
			iio.Read(&hasSubNode, sizeof(BOOL8));
			iio.Read(&hasNextNode, sizeof(BOOL8));
			if (hasSubNode) {
				iio.Read(&subBoneId, sizeof(unsigned short));
			}
			if (hasNextNode) {
				iio.Read(&nextBoneId, sizeof(unsigned short));
			}

			if (hasSubNode) {
				TString btnClassName;
				btnClassName.Load(iio);
				subNode = new TBoneTreeNode(this, boneTable);
				subNode->version = version;
				subNode->subVersion = subVersion;
				subNode->Serialize(iio);
			}

			if (hasNextNode) {
				TString btnClassName;
				btnClassName.Load(iio);
				nextNode = new TBoneTreeNode(this, boneTable);
				nextNode->version = version;
				nextNode->subVersion = subVersion;
				nextNode->Serialize(iio);
			}

			if (boneTable != NULL) {
				boneTable->Add(name, this);
			}

			transform = Transform(translation, rotation, 1.0f);
			aTransform = Transform(Vector3f(), Matrix33f(), 1.0f);
			iTransform = transform.Inverse();
		}
	} else {
		name.Store(iio);
		iio.WriteBuffer(&translation, 3, sizeof(float));
		iio.WriteBuffer(&rotation, 9, sizeof(float));
		iio.Write(&scale, sizeof(float));

		iio.Write(&boneId, sizeof(unsigned short));
		iio.Write(&hasSubNode, sizeof(BOOL8));
		iio.Write(&hasNextNode, sizeof(BOOL8));
		if (hasSubNode) {
			iio.Write(&subBoneId, sizeof(unsigned short));
		}
		if (hasNextNode) {
			iio.Write(&nextBoneId, sizeof(unsigned short));
		}

		if (hasSubNode) {
			TString btnClassName(subNode->GetClassName());
			btnClassName.Store(iio);
			subNode->Serialize(iio);
		}

		if (hasNextNode) {
			TString btnClassName(nextNode->GetClassName());
			btnClassName.Store(iio);
			nextNode->Serialize(iio);
		}

	}
}

void _MODEL_API TBoneTreeNode::Wait() {
}

void _MODEL_API TBoneTreeNode::Notify() {
}

Vector3f _MODEL_API &TBoneTreeNode::GetTranslation() {
	return translation;
}

Matrix33f _MODEL_API &TBoneTreeNode::GetRotation() {
	return rotation;
}

float _MODEL_API &TBoneTreeNode::GetScale() {
	return scale;
}

unsigned short _MODEL_API TBoneTreeNode::GetBoneId() {
	return boneId;
}

void _MODEL_API TBoneTreeNode::SetBoneId(unsigned short id) {
	boneId = id;
}

BOOL8 _MODEL_API TBoneTreeNode::HasNextNode() {
	return hasNextNode;
}

BOOL8 _MODEL_API TBoneTreeNode::HasSubNode() {
	return hasSubNode;
}

TBoneTreeNode _MODEL_API &TBoneTreeNode::GetNextNode() {
	return *nextNode;
}

TBoneTreeNode _MODEL_API &TBoneTreeNode::GetSubNode() {
	return *subNode;
}

TBoneTreeNode _MODEL_API &TBoneTreeNode::GetParentNode() {
	return *parent;
}

void _MODEL_API TBoneTreeNode::SetNextNode(TBoneTreeNode *src) {
	if (src != NULL) {
		hasNextNode = TRUE;
		if ((nextNode != NULL) && (nextNode != src)) {
			delete nextNode;
			nextNode = NULL;
		}
		nextNode = src;
		nextBoneId = src->boneId;
	} else {
		hasNextNode = FALSE;
		if (nextNode != NULL) {
			delete nextNode;
			nextNode = NULL;
		}
	}
}

void _MODEL_API TBoneTreeNode::SetSubNode(TBoneTreeNode *src) {
	if (src != NULL) {
		hasSubNode = TRUE;
		if ((subNode != NULL) && (subNode != src)) {
			delete subNode;
			subNode = NULL;
		}
		subNode = src;
		subBoneId = src->boneId;
	} else {
		hasSubNode = FALSE;
		if (subNode != NULL) {
			delete subNode;
			subNode = NULL;
		}
	}
}

void _MODEL_API TBoneTreeNode::SetParentNode(TBoneTreeNode *src) {
	parent = src;
}

THashtable _MODEL_API &TBoneTreeNode::GetBoneHashtable() {
	return *boneTable;
}

Transform _MODEL_API &TBoneTreeNode::GetInvertedTransform() {
	return iTransform;
}

Transform _MODEL_API &TBoneTreeNode::GetAnimationTransform() {
	return aTransform;
}

Transform _MODEL_API &TBoneTreeNode::GetTransform() {
	return transform;
}

Transform _MODEL_API &TBoneTreeNode::GetFastTransform() {
	return fast;
}

void _MODEL_API TBoneTreeNode::CopyInstance(TBoneTreeNode &btn) {
	btn.name = name;

	btn.translation = translation;
	btn.rotation = rotation;
	btn.scale = scale;

	btn.boneId = boneId;
	btn.hasNextNode = hasNextNode;
	btn.hasSubNode = hasSubNode;
	btn.nextBoneId = nextBoneId;
	btn.subBoneId = subBoneId;
	if (hasSubNode) {
		btn.subNode = new TBoneTreeNode(&btn, btn.boneTable);
		btn.subNode->version = subNode->version;
		btn.subNode->subVersion = subNode->subVersion;
		subNode->CopyInstance(*btn.subNode);
	}

	if (hasNextNode) {
		btn.nextNode = new TBoneTreeNode(&btn, btn.boneTable);
		btn.nextNode->version = nextNode->version;
		btn.nextNode->subVersion = nextNode->subVersion;
		nextNode->CopyInstance(*btn.nextNode);
	}

	if (btn.boneTable != NULL) {
		btn.boneTable->Add(name, &btn);
	}
}
