///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////


#ifndef _VIEWPORT_H_
#define _VIEWPORT_H_

#include "..\Base\Type.h"
#include "..\Base\Base.h"
#include "..\MathTool\MathTool.h"

extern "C" class _RENDERER_API TViewPort : public IObject {
protected:
public:
	Vector3f camera;
	Vector3f center;
	Vector3f cameraup;
	Matrix33f viewcoord;

	Vector3f position;
	Vector3f lookAt;

	Vector3f forward;
	Vector3f up;
	Vector3f right;

	float yaw;
	float pitch;

public:
	Matrix44f invertModelView;
	TString imvParamName;
public:
	TViewPort();
	virtual ~TViewPort();
public:
	void CameraCentered(Vector3f &cam, float _distance, float _ha, float _va);
	void ObjectCentered(Vector3f &obj, float _distance, float _ha, float _va);
	void CameraCentered(Vector3f &cam, float _distance, float _ha, float _va, float _aa);
	void ObjectCentered(Vector3f &obj, float _distance, float _ha, float _va, float _aa);
	void CameraCenteredOrbit(Vector3f &cam, float _distance, float _ha, float _va, float _aa);
	void ObjectCenteredOrbit(Vector3f &obj, float _distance, float _ha, float _va, float _aa);
public:
	void GenViewCoordinate();
	void LookAt();
	void RotateViewPort(float x, float y, float z);
	void TranslateViewPort(Vector3f &trans);

	void MoveForward(float scale);
	void MoveBackward(float scale);
	void MoveLeft(float scale);
	void MoveRight(float scale);
	void MoveUp(float scale);
	void MoveDown(float scale);

	void RotateHorizontal(float angle);
	void RotateVertical(float angle);
	void RotateAxis(float angle);
public:
	

public:
	virtual char* GetClassName();
	virtual int GetClassCode();
	virtual int GetHashCode();
	virtual BOOL32 IsInstanceof(const char* className);
	virtual BOOL32 IsEqualto(IObject &obj);
	virtual void Serialize(IIOStream &iio);
	virtual void Wait();
	virtual void Notify();
};

#endif
