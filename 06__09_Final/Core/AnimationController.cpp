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
#include "AnimationController.hpp"

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

#include "../Renderer/TextureObject.h"
#include "../Renderer/TextureController.h"
#include "../Renderer/MeshObject.h"
#include "../Renderer/MeshController.h"

extern "C" template class _RENDERER_API TRefArray<TMeshObject>;

_CORE_API TAnimationController::TAnimationController() {
	rwLock.AttribInit();
	rwLock.Init();
	count = 0;
	parentController = NULL;

	directionAngle = 0.0f;

	innerstate = 0;
}
_CORE_API TAnimationController::~TAnimationController() {
	rwLock.Unlock();
	rwLock.Destroy();
	rwLock.AttribDestroy();
	animations.Resize(0);
}
char _CORE_API *TAnimationController::GetClassName() {
	return "TAnimationController";
}
int _CORE_API TAnimationController::GetClassCode() {
	return CLSID_TAnimationController;
}
int _CORE_API TAnimationController::GetHashCode() {
	return 1;
}
BOOL32 _CORE_API TAnimationController::IsInstanceof(const char* className) {
	if (strcmp("TAnimationController", className)) {
		return TRUE;
	}
	return TThread::IsInstanceof(className);
}
BOOL32 _CORE_API TAnimationController::IsEqualto(IObject &obj) {
	return FALSE;
}
void _CORE_API TAnimationController::Serialize(IIOStream &iio) {
}
void _CORE_API TAnimationController::Wait() {
}
void _CORE_API TAnimationController::Notify() {
}

void _CORE_API TAnimationController::Run() {
	if ( currentime > 1.33f ) {
		currentime = 0.0f;
		count ++;
	} else {
		currentime = currentime + 0.01f;
	}
	rwLock.WriteLock();
	animations[0].LoadAnimationMatrix(boneController.GetBoneController().GetBoneRoot(), currentime);
	boneController.GetBoneController().DoAnimation();
	rwLock.Unlock();
}

void _CORE_API TAnimationController::Flush(float delta) {
	if ( currentime > 1.33f ) {
		currentime = 0.0f;
		count ++;
	} else {
		currentime = currentime + delta;
	}
	rwLock.WriteLock();
	animations[0].LoadAnimationMatrix(boneController.GetBoneController().GetBoneRoot(), currentime);
	boneController.GetBoneController().DoAnimation();
	rwLock.Unlock();
}

void _CORE_API TAnimationController::RotationAxisZ(float angle) {
	directionAngle += angle;
	direction.fromEuler(0.0f, 0.0f, directionAngle);
}

void _CORE_API TAnimationController::Velocity(float delta) {
	Vector3f dir(1.0f, 0.0f, 0.0f);
	float vz = velocity.z;
	velocity = direction * dir * delta;
	velocity.z = vz;
	position = positionCurrent + velocity;
	velocity = Vector3f();
}

void _CORE_API TAnimationController::CommitVelocity() {
}

void _CORE_API TAnimationController::Commit() {
	positionCurrent = position;
}

void _CORE_API TAnimationController::Gravity(float delta) {
	if ( delta == 0.0f ) {
		acceleration = Vector3f();
		velocity.z = 0.0f;
		position = positionCurrent;
	} else {
		acceleration = Vector3f(0.0f, 0.0f, -delta);
		velocity += acceleration;
		position = positionCurrent + velocity;
	}
}
	
void _CORE_API TAnimationController::CommitGravity() {
}
