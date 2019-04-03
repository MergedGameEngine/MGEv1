///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _BASE_IMPORT
#define _MATHTOOL_IMPORT
#define _RENDERER_EXPORT

#include "string.h"
#include "GLee.h"
#undef GetClassName
#include "ViewPort.h"

_RENDERER_API TViewPort::TViewPort() {
	position = Vector3f(0.0f, 0.0f, 0.0f);
	lookAt = Vector3f(0.0f, 0.0f, 1.0f);

	forward = lookAt;
	up = Vector3f(0.0f, 1.0f, 0.0f);
	right = Vector3f(1.0f, 0.0f, 0.0f);

	yaw = 0.0f;
	pitch = 0.0f;
}

_RENDERER_API TViewPort::~TViewPort() {
}

char _RENDERER_API *TViewPort::GetClassName() {
	return "TViewPort";
}

int _RENDERER_API TViewPort::GetClassCode() {
	return CLSID_TViewPort;
}

int _RENDERER_API TViewPort::GetHashCode() {
	return 1;
}

BOOL32 _RENDERER_API TViewPort::IsInstanceof(const char* className) {
	if (strcmp("TViewPort", className) == 0) {
		return TRUE;
	} else if (strcmp("IObject", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

BOOL32 _RENDERER_API TViewPort::IsEqualto(IObject &obj) {
	return FALSE;
}

void _RENDERER_API TViewPort::Serialize(IIOStream &iio) {
}

void _RENDERER_API TViewPort::Wait() {
}

void _RENDERER_API TViewPort::Notify() {
}

void _RENDERER_API TViewPort::GenViewCoordinate() {
	Vector3f f = center - camera;
	f = f.Normalized();
	Vector3f UP = cameraup.Normalized();
	Vector3f s = f ^ UP;
	Vector3f u = s ^ f;
	viewcoord = Matrix33f(s, u, Vector3f(-f.x, -f.y, -f.z)).Transpose();
}

void _RENDERER_API TViewPort::LookAt() {
	Matrix44f mat(Vector3f(), viewcoord);
	glMultMatrixf((GLfloat*)&mat);
	glTranslated (-camera.x, -camera.y, -camera.z);
}

void _RENDERER_API TViewPort::RotateViewPort(float x, float y, float z) {
	Matrix33f mat;
	mat.fromEuler(x, y, z);
	viewcoord = mat * viewcoord;
}
void _RENDERER_API TViewPort::TranslateViewPort(Vector3f &trans) {
	Vector3f delta = viewcoord * trans;
	camera = camera + delta;
}

void _RENDERER_API TViewPort::MoveForward(float scale) {
	TranslateViewPort(Vector3f(0.0f, 0.0f, -scale));
}
void _RENDERER_API TViewPort::MoveBackward(float scale) {
	TranslateViewPort(Vector3f(0.0f, 0.0f, scale));
}
void _RENDERER_API TViewPort::MoveLeft(float scale) {
	TranslateViewPort(Vector3f(-scale, 0.0f, 0.0f));
}
void _RENDERER_API TViewPort::MoveRight(float scale) {
	TranslateViewPort(Vector3f(scale, 0.0f, 0.0f));
}
void _RENDERER_API TViewPort::MoveUp(float scale) {
	TranslateViewPort(Vector3f(0.0f, scale, 0.0f));
}
void _RENDERER_API TViewPort::MoveDown(float scale) {
	TranslateViewPort(Vector3f(0.0f, -scale, 0.0f));
}

void _RENDERER_API TViewPort::RotateHorizontal(float angle) {
	//float sine = sinf(angle);
	//float cosine = cosf(angle);

	//up.y = cosine * up.Magnitude();
	//up.z = sine * up.Magnitude();

	//forward.y = -sine * forward.Magnitude();
	//forward.z = cosine * forward.Magnitude();
	//			x   y      z       p
	//		|   1  0       0       0 |
	//	M = |   0  cos(A) -sin(A)  0 |
	//		|   0  sin(A)  cos(A)  0 |
	//		|   0  0       0       1 |
	RotateViewPort(0.0f, 0.0f, angle);//+L,-R
}
void _RENDERER_API TViewPort::RotateVertical(float angle) {
	//float sine = sinf(angle);
	//float cosine = cosf(angle);
	//
	//right.x = cosine * right.Magnitude();
	//right.z = sine * right.Magnitude();

	//forward.x = -sine * forward.Magnitude();
	//forward.z = cosine * forward.Magnitude();
	/*	   x      y    z      p
         |  cos(A)  0  -sin(A)  0 |
     M = |  0       1   0       0 |
         |  sin(A)  0   cos(A)  0 |
         |  0       0   0       1 |
	*/
	RotateViewPort(0.0f, angle, 0.0f);//+U,-D
}
void _RENDERER_API TViewPort::RotateAxis(float angle) {
	//float sine = sinf(angle);
	//float cosine = cosf(angle);
	//
	//right.x = cosine * right.Magnitude();
	//right.y = sine * right.Magnitude();

	//up.x = -sine * forward.Magnitude();
	//up.y = cosine * forward.Magnitude();
	/*
         |  cos(A)  -sin(A)   0   0 |
     M = |  sin(A)   cos(A)   0   0 |
         |  0        0        1   0 |
         |  0        0        0   1 |
	*/
	RotateViewPort(angle, 0.0f, 0.0f);//+C,-CC
}

void _RENDERER_API TViewPort::CameraCentered(Vector3f &cam, float _distance, float _ha, float _va) {
	float _cos_ha = cosf(_ha);
	float _sin_ha = sinf(_ha);
	float _cos_va = cosf(_va);
	float _sin_va = sinf(_va);
	camera = cam;
	center = Vector3f(_distance * _cos_ha * _cos_va, _distance * _sin_ha * _cos_va, _distance * _sin_va ) + camera;
	cameraup = Vector3f(- _cos_ha * _sin_va, - _sin_ha * _sin_va, _cos_va );
}
void _RENDERER_API TViewPort::ObjectCentered(Vector3f &obj, float _distance, float _ha, float _va) {
	float _cos_ha = cosf(_ha);
	float _sin_ha = sinf(_ha);
	float _cos_va = cosf(_va);
	float _sin_va = sinf(_va);
	center = obj;
	camera = Vector3f(_distance * _cos_ha * _cos_va, _distance * _sin_ha * _cos_va, _distance * _sin_va ) + center;
	cameraup = Vector3f(- _cos_ha * _sin_va, - _sin_ha * _sin_va, _cos_va );
}
void _RENDERER_API TViewPort::CameraCentered(Vector3f &cam, float _distance, float _ha, float _va, float _aa) {
	CameraCentered(cam, _distance, _ha, _va);
	Vector3f _cx = (center - camera).Normalized();
	Vector3f _cz = cameraup.Normalized();
	Vector3f _cy = _cz ^ _cx;
	Matrix33f mat(_cx, _cy, _cz);
	Matrix33f rot;rot.fromEuler(_aa, 0.0f, 0.0f);
	Matrix33f trans3 = mat * rot;
	_cx = *(Vector3f*)&(trans3.m[0][0]);
	_cy = *(Vector3f*)&(trans3.m[1][0]);
	_cz = *(Vector3f*)&(trans3.m[2][0]);
	center = _cx * _distance + camera;
	cameraup = _cz;
}
void _RENDERER_API TViewPort::ObjectCentered(Vector3f &obj, float _distance, float _ha, float _va, float _aa) {
	ObjectCentered(obj, _distance, _ha, _va);
	Vector3f _cx = (center - camera).Normalized();
	Vector3f _cz = cameraup.Normalized();
	Vector3f _cy = _cz ^ _cx;
	Matrix33f mat(_cx, _cy, _cz);
	Matrix33f rot;rot.fromEuler(_aa, 0.0f, 0.0f);
	Matrix33f trans3 = rot * mat;
	_cx = *(Vector3f*)&(trans3.m[0][0]);
	_cy = *(Vector3f*)&(trans3.m[1][0]);
	_cz = *(Vector3f*)&(trans3.m[2][0]);
	camera = center - _cx * _distance;
	cameraup = _cz;
}
void _RENDERER_API TViewPort::CameraCenteredOrbit(Vector3f &cam, float _distance, float _ha, float _va, float _aa) {
	CameraCentered(cam, _distance, _ha, _va);
	Vector3f _cx = (center - camera).Normalized();
	Vector3f _cz = cameraup.Normalized();
	Vector3f _cy = _cz ^ _cx;
	Matrix33f mat(_cx, _cy, _cz);
	Matrix33f rot;rot.fromEuler(_aa, 0.0f, 0.0f);
	Matrix33f trans3 = rot * mat;
	_cx = *(Vector3f*)&(trans3.m[0][0]);
	_cy = *(Vector3f*)&(trans3.m[1][0]);
	_cz = *(Vector3f*)&(trans3.m[2][0]);
	center = _cx * _distance + camera;
	cameraup = _cz;
}
void _RENDERER_API TViewPort::ObjectCenteredOrbit(Vector3f &obj, float _distance, float _ha, float _va, float _aa) {
	ObjectCentered(obj, _distance, _ha, _va);
	Vector3f _cx = (center - camera).Normalized();
	Vector3f _cz = cameraup.Normalized();
	Vector3f _cy = _cz ^ _cx;
	Matrix33f mat(_cx, _cy, _cz);
	Matrix33f rot;rot.fromEuler(_aa, 0.0f, 0.0f);
	Matrix33f trans3 = mat * rot;
	_cx = *(Vector3f*)&(trans3.m[0][0]);
	_cy = *(Vector3f*)&(trans3.m[1][0]);
	_cz = *(Vector3f*)&(trans3.m[2][0]);
	camera = center - _cx * _distance;
	cameraup = _cz;
}
