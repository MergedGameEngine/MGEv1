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
#define _ARRAY_API _MODEL_API
#include "Sequence.hpp"

_MODEL_API TSequence::TSequence() {
	keyFrames.Resize(0);
	weight = 0;
	cycleType = 0;
	frequency = 0;
	startTime = 0;
	stopTime = 0;

	numControlledBlocks = 0;
}

_MODEL_API TSequence::~TSequence() {
	keyFrames.DeleteAll();
	keyFrames.Resize(0);
}

char _MODEL_API *TSequence::GetClassName() {
	return "TSequence";
}

int _MODEL_API TSequence::GetClassCode() {
	return CLSID_TSequence;
}

int _MODEL_API TSequence::GetHashCode() {
	return 1;
}

BOOL32 _MODEL_API TSequence::IsInstanceof(const char* className) {
	if (strcmp("TSequence", className) == 0) {
		return TRUE;
	}
	return TModelObject::IsInstanceof(className);
}

BOOL32 _MODEL_API TSequence::IsEqualto(IObject &obj) {
	return FALSE;
}

void _MODEL_API TSequence::Serialize(IIOStream &iio) {
	TModelObject::Serialize(iio);
	if ( iio.GetLoadStore() == IIOStream::load ) {
		if ( ( version == 0x00000001 ) && ( subVersion == 0x00000000 ) ) {
			name.Load(iio);
			iio.Read(&weight, sizeof(float));
			iio.Read(&cycleType, sizeof(byte)); 
			iio.Read(&frequency, sizeof(float));
			iio.Read(&startTime, sizeof(float));
			iio.Read(&stopTime, sizeof(float));
			targetName.Load(iio);

			iio.Read(&numControlledBlocks, sizeof(unsigned int));
			keyFrames.Resize(numControlledBlocks);
			keyFrames.CreateAll();
			for (int i1 = 0 ; i1 < numControlledBlocks ; i1 ++ ) {
				TString kClassName;
				kClassName.Load(iio);
				keyFrames[i1].SetVersion(version);
				keyFrames[i1].SetSubVersion(subVersion);
				keyFrames[i1].Serialize(iio);
			}
			for (int i2 = 0 ; i2 < numControlledBlocks ; i2 ++ ) {
				controlledNodes.Add(keyFrames[i2].GetName(), &keyFrames[i2]);
			}
		}
	} else {
		name.Store(iio);
		iio.Write(&weight, sizeof(float));
		iio.Write(&cycleType, sizeof(byte)); 
		iio.Write(&frequency, sizeof(float));
		iio.Write(&startTime, sizeof(float));
		iio.Write(&stopTime, sizeof(float));
		targetName.Store(iio);

		numControlledBlocks = keyFrames.GetLength();
		iio.Write(&numControlledBlocks, sizeof(unsigned int));
		for (int i1 = 0 ; i1 < numControlledBlocks ; i1 ++ ) {
			TString kClassName(keyFrames[i1].GetClassName());
			kClassName.Store(iio);
			keyFrames[i1].Serialize(iio);
		}
	}
}

void _MODEL_API TSequence::Wait() {
}

void _MODEL_API TSequence::Notify() {
}

float _MODEL_API &TSequence::GetWeight() {
	return weight;
}

byte _MODEL_API TSequence::GetCycleType() {
	return cycleType;
}

void _MODEL_API TSequence::SetCycleType(byte ctype) {
	cycleType = ctype;
}

float _MODEL_API &TSequence::GetFrequency() {
	return frequency;
}

float _MODEL_API &TSequence::GetStartTime() {
	return startTime;
}

float _MODEL_API &TSequence::GetStopTime() {
	return stopTime;
}

TString _MODEL_API &TSequence::GetTargetName() {
	return targetName;
}

TRefArray<TKeyFrame> _MODEL_API &TSequence::GetKeyFrames() {
	return keyFrames;
}

THashtable _MODEL_API &TSequence::GetControlledNodes() {
	return controlledNodes;
}


//	
//		========================	Developped by hacker	==================================
//	
static inline float ISqrt_approx_in_neighborhood(float s) {
   static const float NEIGHBORHOOD = 0.959066f;
   static const float SCALE = 1.000311f;
   static const float ADDITIVE_CONSTANT = SCALE / (float)sqrt(NEIGHBORHOOD);
   static const float FACTOR = SCALE * (-0.5f / (NEIGHBORHOOD * (float)sqrt(NEIGHBORHOOD)));
   return ADDITIVE_CONSTANT + (s - NEIGHBORHOOD) * FACTOR;
}

static inline void fast_normalize(Quaternion &q) {
   float s = q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3];
   float k = ISqrt_approx_in_neighborhood(s);
   if (s <= 0.91521198f) {
      k *= ISqrt_approx_in_neighborhood(k * k * s);
      if (s <= 0.65211970f) {
         k *= ISqrt_approx_in_neighborhood(k * k * s);
      }
   }
   q[0] *= k; q[1] *= k; q[2] *= k; q[3] *= k;
}

static inline float lerp(float v0, float v1, float perc) {
   return v0 + perc * (v1 - v0);
}

static inline float correction(float t, float fCos) {
   const float s = 0.8228677f;
   const float kc = 0.5855064f;
   float factor = 1.0f - s * fCos;
   float k = kc * factor * factor;
   return t * ( k * t * ( 2.0f * t - 3.0f ) + 1.0f + k );
}

Quaternion slerp(float t, Quaternion& p, Quaternion& q) {
   // Copyright (c) 2002 Jonathan Blow
   //  "Hacking Quaternions", The Inner Product, March 2002
   //   http://number-none.com/product/Hacking%20Quaternions/index.html

   float tprime;
   if (t <= 0.5f) {
      tprime = correction(t, p.DotProduct(q) );
   } else {
	   tprime = 1.0f - correction(1.0f - t, p.DotProduct(q) );
   }
   Quaternion result( lerp(p[0], q[0], tprime), lerp(p[1], q[1], tprime),
                lerp(p[2], q[2], tprime), lerp(p[3], q[3], tprime));
   fast_normalize(result);
   return result;
}
//	===========================================================================================

void _MODEL_API TSequence::GetInterpolate(TKeyFrame &kf, Quaternion &q, Vector3f &t, float time) {
	if ( time < 0.0f ) {
		return;
	}
	if ( kf.GetNumQuaternions() == 0 ) {
		Matrix33f mat;
		q = mat.toQuat();
	} else if ( kf.GetNumQuaternions() == 1 ) {
		q = kf.GetQuaternions()[0];
	} else {
		unsigned int i = 0;
		for ( i = 0 ; i < kf.GetNumQuaternions() ; i ++ ) {
			if ( kf.GetTimeLineQuat()[i] > time ) {
				Quaternion prev = kf.GetQuaternions()[i - 1];
				Quaternion next = kf.GetQuaternions()[i];
				float prevtime = kf.GetTimeLineQuat()[i - 1];
				float nexttime = kf.GetTimeLineQuat()[i];
				float ratio = ( time - prevtime ) / ( nexttime - prevtime );
				q = slerp(ratio, prev, next);
				break;
			} else if ( fabsf(kf.GetTimeLineQuat()[i] - time) == 0.00001 ) {
				q = kf.GetQuaternions()[i];
				break;
			}
		}
		if ( i >= kf.GetNumQuaternions()) {
			i = kf.GetNumQuaternions() - 1;
		}
	}
	if ( kf.GetNumTranslations() == 0 ) {
		t = kf.GetTranslation();
	} else if ( kf.GetNumTranslations() == 1 ) {
		t = kf.GetTranslations()[0];
	} else {
		unsigned int i = 0;
		for ( i = 0 ; i < kf.GetNumTranslations() ; i ++ ) {
			if ( kf.GetTimeLineTrans()[i] > time ) {
				Vector3f prev = kf.GetTranslations()[i - 1];
				Vector3f next = kf.GetTranslations()[i];
				float prevtime = kf.GetTimeLineTrans()[i - 1];
				float nexttime = kf.GetTimeLineTrans()[i];
				float ratio = ( time - prevtime ) / ( nexttime - prevtime );
				t = prev + ( next - prev ) * ratio;
				break;
			} else if ( fabsf(kf.GetTimeLineTrans()[i] - time) == 0.00001 ) {
				t = kf.GetTranslations()[i];
				break;
			}
		}
		if ( i >= kf.GetNumTranslations()) {
			i = kf.GetNumTranslations() - 1;
		}
	}
}

void _MODEL_API TSequence::GetInterpolate(TKeyFrame &kfa, TKeyFrame &kfb, Quaternion &q, Vector3f &t, float ratio) {
	if ( ratio < 0.0f ) {
		return;
	}
	q = slerp(ratio, kfa.GetTemporaryRotation(), kfb.GetTemporaryRotation());
	t = kfa.GetTemporaryTranslation() + ( kfb.GetTemporaryTranslation() - kfa.GetTemporaryTranslation() ) * ratio;
}

void _MODEL_API TSequence::LoadAnimationMatrix(TBoneTreeNode &btn, float time) {
	TKeyFrame *kf = (TKeyFrame*)(controlledNodes.Get(btn.GetName()));
	if (kf != NULL) {
		Vector3f t;
		Quaternion q;
		Matrix33f m;
		GetInterpolate(*kf, q, t, time);
		m.fromQuat(q);
		btn.GetTransform() = Transform(t, m, 1.0f);
	}
	if (btn.HasSubNode()) {
		LoadAnimationMatrix(btn.GetSubNode(), time);
	}
	if (btn.HasNextNode()) {
		LoadAnimationMatrix(btn.GetNextNode(), time);
	}
}

void _MODEL_API TSequence::LoadAnimationMatrix(TSequence &sqb, TBoneTreeNode &btn, float ratio) {
	TKeyFrame *kfa = (TKeyFrame*)(controlledNodes.Get(btn.GetName()));
	TKeyFrame *kfb = (TKeyFrame*)(sqb.controlledNodes.Get(btn.GetName()));
	if ( ( kfa != NULL ) && ( kfb != NULL ) ) {
		Vector3f t;
		Quaternion q;
		Matrix33f m;
		GetInterpolate(*kfa, *kfb, q, t, ratio);
		m.fromQuat(q);
		btn.GetTransform() = Transform(t, m, 1.0f);
	}
	if (btn.HasSubNode()) {
		LoadAnimationMatrix(sqb, btn.GetSubNode(), ratio);
	}
	if (btn.HasNextNode()) {
		LoadAnimationMatrix(sqb, btn.GetNextNode(), ratio);
	}
}

void _MODEL_API TSequence::BuildTemporaryAnimation(float time) {
	unsigned int numKFs = keyFrames.GetLength();
	for ( unsigned int i1 = 0 ; i1 < numKFs ; i1 ++ ) {
		TKeyFrame *kf = &(keyFrames[i1]);
		if (kf != NULL) {
			GetInterpolate(*kf, kf->GetTemporaryRotation(), kf->GetTemporaryTranslation(), time);
		}
	}
}

