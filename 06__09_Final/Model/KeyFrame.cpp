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
#include "KeyFrame.hpp"

_MODEL_API TKeyFrame::TKeyFrame() {
	rotationType = 0;
	quatInterpolatType = 0;
	transInterpolatType = 0;
	scalesInterpolatType = 0;
	numFrames = 0;
	numQuaternion = 0;
	timeLineQuat.Resize(0);
	quaternions.Resize(0);
	numTrans = 0;
	timeLineTrans.Resize(0);
	translations.Resize(0);
	numScales = 0;
	timeLineScales.Resize(0);
	scales.Resize(0);
}

_MODEL_API TKeyFrame::~TKeyFrame() {
	timeLineQuat.Resize(0);
	quaternions.Resize(0);
	numTrans = 0;
	timeLineTrans.Resize(0);
	translations.Resize(0);
	numScales = 0;
	timeLineScales.Resize(0);
	scales.Resize(0);
}

char _MODEL_API *TKeyFrame::GetClassName() {
	return "TKeyFrame";
}

int _MODEL_API TKeyFrame::GetClassCode() {
	return CLSID_TKeyFrame;
}

int _MODEL_API TKeyFrame::GetHashCode() {
	return 1;
}

BOOL32 _MODEL_API TKeyFrame::IsInstanceof(const char* className) {
	if (strcmp("TKeyFrame", className) == 0) {
		return TRUE;
	}
	return TModelObject::IsInstanceof(className);
}

BOOL32 _MODEL_API TKeyFrame::IsEqualto(IObject &obj) {
	return FALSE;
}

void _MODEL_API TKeyFrame::Serialize(IIOStream &iio) {
	TModelObject::Serialize(iio);
	if ( iio.GetLoadStore() == IIOStream::load ) {
		if ( ( version == 0x00000001 ) && ( subVersion == 0x00000000 ) ) {
			name.Load(iio);
			iio.ReadBuffer(&translation, 3, sizeof(float));
			iio.ReadBuffer(&rotation, 4, sizeof(float));
			iio.Read(&scale, sizeof(float));
			iio.Read(&rotationType, sizeof(byte));
			iio.Read(&quatInterpolatType, sizeof(byte));
			iio.Read(&transInterpolatType, sizeof(byte));
			iio.Read(&scalesInterpolatType, sizeof(byte));
			iio.Read(&numFrames, sizeof(unsigned int));
			iio.Read(&numQuaternion, sizeof(unsigned int));
			iio.Read(&numTrans, sizeof(unsigned int));
			iio.Read(&numScales, sizeof(unsigned int));
			if ( numQuaternion > 0 ) {
				timeLineQuat.Resize(numQuaternion);
				quaternions.Resize(numQuaternion);
				iio.ReadBuffer(timeLineQuat.GetBuffer(), numQuaternion, sizeof(float));
				iio.ReadBuffer(quaternions.GetBuffer(), numQuaternion * 4, sizeof(float));
			}
			if ( numTrans > 0 ) {
				timeLineTrans.Resize(numTrans);
				translations.Resize(numTrans);
				iio.ReadBuffer(timeLineTrans.GetBuffer(), numTrans, sizeof(float));
				iio.ReadBuffer(translations.GetBuffer(), numTrans * 3, sizeof(float));
			}
			if ( numScales > 0 ) {
				timeLineScales.Resize(numScales);
				scales.Resize(numScales);
				iio.ReadBuffer(timeLineScales.GetBuffer(), numScales, sizeof(float));
				iio.ReadBuffer(scales.GetBuffer(), numScales, sizeof(float));
			}
		}
	} else {
		name.Store(iio);
		iio.WriteBuffer(&translation, 3, sizeof(float));
		iio.WriteBuffer(&rotation, 4, sizeof(float));
		iio.Write(&scale, sizeof(float));
		iio.Write(&rotationType, sizeof(byte));
		iio.Write(&quatInterpolatType, sizeof(byte));
		iio.Write(&transInterpolatType, sizeof(byte));
		iio.Write(&scalesInterpolatType, sizeof(byte));
		iio.Write(&numFrames, sizeof(unsigned int));
		iio.Write(&numQuaternion, sizeof(unsigned int));
		iio.Write(&numTrans, sizeof(unsigned int));
		iio.Write(&numScales, sizeof(unsigned int));
		if ( numQuaternion > 0 ) {
			iio.WriteBuffer(timeLineQuat.GetBuffer(), numQuaternion, sizeof(float));
			iio.WriteBuffer(quaternions.GetBuffer(), numQuaternion * 4, sizeof(float));
		}
		if ( numTrans > 0 ) {
			iio.WriteBuffer(timeLineTrans.GetBuffer(), numTrans, sizeof(float));
			iio.WriteBuffer(translations.GetBuffer(), numTrans * 3, sizeof(float));
		}
		if ( numScales > 0 ) {
			iio.WriteBuffer(timeLineScales.GetBuffer(), numScales, sizeof(float));
			iio.WriteBuffer(scales.GetBuffer(), numScales, sizeof(float));
		}
	}
}

void _MODEL_API TKeyFrame::Wait() {
}

void _MODEL_API TKeyFrame::Notify() {
}

Vector3f _MODEL_API &TKeyFrame::GetTranslation() {
	return translation;
}

Quaternion _MODEL_API &TKeyFrame::GetRotation() {
	return rotation;
}

float _MODEL_API &TKeyFrame::GetScale() {
	return scale;
}

byte _MODEL_API TKeyFrame::GetRotationType() {
	return rotationType;
}

void _MODEL_API TKeyFrame::SetRotationType(byte rtype) {
	rotationType = rtype;
}

byte _MODEL_API TKeyFrame::GetQuatInterpolatType() {
	return quatInterpolatType;
}

void _MODEL_API TKeyFrame::SetQuatInterpolatType(byte itype) {
	quatInterpolatType = itype;
}

byte _MODEL_API TKeyFrame::GetTransInterpolatType() {
	return transInterpolatType;
}

void _MODEL_API TKeyFrame::SetTransInterpolatType(byte itype) {
	transInterpolatType = itype;
}

byte _MODEL_API TKeyFrame::GetScalesInterpolatType() {
	return scalesInterpolatType;
}

void _MODEL_API TKeyFrame::SetScalesInterpolatType(byte itype) {
	scalesInterpolatType = itype;
}

TArray<float> _MODEL_API &TKeyFrame::GetTimeLineQuat() {
	return timeLineQuat;
}

TArray<Quaternion> _MODEL_API &TKeyFrame::GetQuaternions() {
	return quaternions;
}

TArray<float> _MODEL_API &TKeyFrame::GetTimeLineTrans() {
	return timeLineTrans;
}

TArray<Vector3f> _MODEL_API &TKeyFrame::GetTranslations() {
	return translations;
}

TArray<float> _MODEL_API &TKeyFrame::GetTimeLineScales() {
	return timeLineScales;
}

TArray<float> _MODEL_API &TKeyFrame::GetScales() {
	return scales;
}

unsigned int _MODEL_API TKeyFrame::GetNumFrames() {
	return numFrames;
}

void _MODEL_API TKeyFrame::SetNumFrames(unsigned int num) {
	numFrames = num;
}

unsigned int _MODEL_API TKeyFrame::GetNumQuaternions() {
	return numQuaternion;
}

void _MODEL_API TKeyFrame::SetNumQuaternions(unsigned int num) {
	numQuaternion = num;
	timeLineQuat.Resize(num);
	quaternions.Resize(num);
}

unsigned int _MODEL_API TKeyFrame::GetNumTranslations() {
	return numTrans;
}

void _MODEL_API TKeyFrame::SetNumTranslations(unsigned int num) {
	numTrans = num;
	timeLineTrans.Resize(num);
	translations.Resize(num);
}

unsigned int _MODEL_API TKeyFrame::GetNumScales() {
	return numScales;
}

void _MODEL_API TKeyFrame::SetNumScales(unsigned int num) {
	numScales = num;
	timeLineScales.Resize(num);
	scales.Resize(num);
}

Quaternion _MODEL_API &TKeyFrame::GetTemporaryRotation() {
	return temporaryRotation;
}
Vector3f _MODEL_API &TKeyFrame::GetTemporaryTranslation() {
	return temporaryTranslation;
}
