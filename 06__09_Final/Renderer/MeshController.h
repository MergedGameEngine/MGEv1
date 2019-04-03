///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////


#ifndef _MESHCONTROLLER_H_
#define _MESHCONTROLLER_H_

#include "..\Base\Type.h"
#include "..\Base\Base.h"
#include "..\MathTool\MathTool.h"

extern "C" template class _MATHTOOL_API TArray<Matrix44f>;

extern "C" class _RENDERER_API TMeshController : public IObject {
protected:
public:
public:
	TRefArray<TMeshObject> meshes;
	THashtable meshIndices;
public:
	TMeshController();
	virtual ~TMeshController();
public:
	void RenderUnit(TTextureController &tc, TLightController &lc, TShaderController &sc, TViewPort &vp);
	void RenderUnit(TTextureController &tc, TLightController &lc, TShaderController &sc, TViewPort &vp, TArray<Matrix44f> &bm, TString &pn);
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
