///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _CORE_EXPORT

#define _MATHTOOL_IMPORT
#define _BASE_IMPORT
#define _FILE_IMPORT
#define _MODEL_IMPORT
#define _THREAD_IMPORT
#define _RENDERER_IMPORT

#include "string.h"
#include "../Base/Type.h"
#include "../Base/Base.h"
#define _ARRAY_API _CORE_API
#include "ModelController.hpp"
#include "Chest.h"

#include "../Model/ModelObject.h"
#include "../Model/Mesh.h"
#include "../Model/Skin.h"
#include "../Model/Bone.h"
#include "../Model/BoneController.h"
#include "../Model/BoneTreeNode.h"
#include "../Model/Sequence.h"
#include "../Model/KeyFrame.h"
#include "../Model/Model.h"
#include "../Model/ModelGlobal.h"

extern "C" template class _MODEL_API TRefArray<TModel>;
extern "C" template class _MODEL_API TRefArray<TSequence>;
extern "C" template class _MODEL_API TRefArray<TSkin>;
extern "C" template class _MODEL_API TRefArray<TBone>;
extern "C" template class _MODEL_API TRefArray<TMesh>;
extern "C" template class _MODEL_API TRefArray<TKeyFrame>;

_CORE_API TChest::TChest() {
}
_CORE_API TChest::~TChest() {
}
char _CORE_API *TChest::GetClassName() {
	return "TChest";
}
int _CORE_API TChest::GetClassCode() {
	return CLSID_TChest;
}
int _CORE_API TChest::GetHashCode() {
	return 1;
}
BOOL32 _CORE_API TChest::IsInstanceof(const char* className) {
	if (strcmp("TChest", className)) {
		return TRUE;
	}
	return TModelController::IsInstanceof(className);
}
BOOL32 _CORE_API TChest::IsEqualto(IObject &obj) {
	return FALSE;
}
void _CORE_API TChest::Serialize(IIOStream &iio) {
}
void _CORE_API TChest::Wait() {
}
void _CORE_API TChest::Notify() {
}
