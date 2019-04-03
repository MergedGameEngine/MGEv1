///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

//
//		Model Package import
//

#ifndef _MODELIMORT_H_
#define _MODELIMORT_H_

#include "../Model/ModelObject.h"
#include "../Model/Mesh.h"
#include "../Model/Skin.h"
#include "../Model/Bone.h"
#include "../Model/BoneTreeNode.h"
#include "../Model/BoneController.h"
#include "../Model/Model.h"
#include "../Model/KeyFrame.h"
#include "../Model/Sequence.h"
#include "../Model/CollisionDetectingMatrices.h"
#include "../Model/CollisionDetectingMatricesController.h"
#include "../Model/ModelGlobal.h"
#include "../Model/Texture.h"
#include "../Model/TGATexture.h"
#include "../Model/DDSTexture.h"

#ifdef _ARRAY_API
#ifdef TRefArray
extern "C" template class _MODEL_API TRefArray<TSkin>;
extern "C" template class _MODEL_API TRefArray<TBone>;
extern "C" template class _MODEL_API TRefArray<TBoneTreeNode>;
extern "C" template class _MODEL_API TRefArray<TMesh>;
extern "C" template class _MODEL_API TRefArray<TModel>;
extern "C" template class _MODEL_API TRefArray<TKeyFrame>;
extern "C" template class _MODEL_API TRefArray<TSequence>;

extern "C" template class _MODEL_API TRefArray<TDDSTexture>;

extern "C" template class _MODEL_API TRefArray<TCollisionDetectingMatrices>;
extern "C" template class _MODEL_API TRefArray<TCollisionDetectingMatricesController>;
#endif
#endif

#endif