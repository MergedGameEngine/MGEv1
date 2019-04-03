///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _MATHTOOL_EXPORT

#include "..\Base\Type.h"
#include "MathTool.h"
#include "string.h"


Quaternion::Quaternion() {
	w = x = y = z = 0.0f;
}

Quaternion::Quaternion(float pw, float px, float py, float pz) {
	w = pw;
	x = px;
	y = py;
	z = pz;
}

Vector3f Quaternion::AsEulerYawPitchRoll() {
	float yaw, pitch, roll;

	if ( x*y + z*w == 0.5 ) {
		//North Pole
		yaw = 2 * atan2(x,w);
		pitch = asinf(2*x*y + 2*z*w);
		roll = 0.0f;
	}
	else if ( x*y + z*w == -0.5 ) {
		//South Pole
		yaw =  -2 * atan2(x,w);
		pitch = asinf(2*x*y + 2*z*w);
		roll = 0.0f;
	}
	else {
		yaw = atan2(2*y*w-2*x*z , 1 - 2*y*y - 2*z*z);
		pitch = asinf(2*x*y + 2*z*w);
		roll = atan2(2*x*w-2*y*z , 1 - 2*x*x - 2*z*z);
	}

	return Vector3f( yaw, pitch, roll );
}

Matrix33f Quaternion::AsMatrix() {
	Matrix33f m33;

	float w2 = w * w;
	float x2 = x * x;
	float y2 = y * y;
	float z2 = z * z;

	m33.m[0][0] = w2 + x2- y2 - z2;
	m33.m[0][1] = 2.0f*x*y - 2.0f*w*z;
	m33.m[0][2] = 2.0f*x*z + 2.0f*w*y;
	
	m33.m[1][0] = 2.0f*x*y + 2.0f*w*z;
	m33.m[1][1] = w2 - x2 + y*y - z2;
	m33.m[1][2] = 2.0f*y*z - 2.0f*w*x;
	
	m33.m[2][0] = 2.0f*x*z - 2.0f*w*y;
	m33.m[2][1] = 2.0f*y*z + 2.0f*w*x;
	m33.m[2][2] = w2 - x2 - y2 + z2;

	return m33;
}

Quaternion Quaternion::Inverse() {
	return Quaternion(w, -x, -y, -z);
}


void Quaternion::fromAxisAngle( Vector3f axis, float angle ) {
	axis = axis.Normalized();
    float s = sin( angle / 2.0f );
    w = cos( angle / 2.0f );
    x = s * axis.x;
    y = s * axis.y;
    z = s * axis.z;
}

void Quaternion::toAxisAngle( Vector3f &axis, float &angle ) {
    float squaredLength = x * x + y * y + z * z;

    if ( squaredLength > 0.0 ) {
        angle = acos( w ) * 2.0f;
        axis.x = x;
        axis.y = y;
        axis.z = z;
		axis /= sqrt( squaredLength );
    } else {
		axis = Vector3f( 1, 0, 0 );
		angle = 0.0f;
    }
}

float &Quaternion::operator[]( unsigned int i ) {
	switch (i) {
		case 0:
			return w;
		case 1:
			return x;
		case 2:
			return y;
		case 3:
			return z;
		default:
			return *(float*)NULL;
	}
}

Quaternion & Quaternion::operator*=( float scale ) {
	(*this) = (*this) * scale;
	return *this;
}

Quaternion Quaternion::operator*( float scale ) {
	Quaternion des;
	des.w = w * scale;
	des.x = x * scale;
	des.y = y * scale;
	des.z = z * scale;
	return des;
}

Quaternion & Quaternion::operator+=( Quaternion & src ) {
	(*this) = (*this) + src;
	return *this;
}

Quaternion Quaternion::operator+( Quaternion & src ) {
	Quaternion des;
	des.w = w + src.w;
	des.x = x + src.x;
	des.y = y + src.y;
	des.z = z + src.z;
	return des;
}

float Quaternion::DotProduct( Quaternion & src ) {
	return w * src.w + x * src.x + y * src.y + z * src.z;
}


Quaternion Quaternion::Slerp (float t, Quaternion& src) {
	float tprime;
	if (t <= 0.5f) {
		tprime = correction(t, DotProduct(src) );
	} else {
		tprime = 1.0f - correction(1.0f - t, DotProduct(src) );
	}
	Quaternion result( lerp(w, src.w, tprime), lerp(x, src.x, tprime),
	lerp(y, src.y, tprime), lerp(z, src.z, tprime));
	fast_normalize(result);
	return result;
}

