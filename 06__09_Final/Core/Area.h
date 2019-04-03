///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _AREA_H_
#define _AREA_H_

#include "../Base/Type.h"
#include "../Base/Base.h"

class TConfigFile;

extern "C" class _CORE_API TArea : public IObject {
public:
	TArea();
	virtual ~TArea();
public:
	unsigned short areaId;
public:
	TRefArray<TModel> prototypes;
	TRefArray<TMeshController> renderPrototypes;
	TRefArray<TTextureController> renderTextures;
	THashtable prototypeIndices;
	THashtable renderPrototypeIndices;
	THashtable renderTextureIndices;

	TRefArray<TModelController> modelControllers;

	TRefArray<TSequence> animationPrototypes;
	THashtable animationPrototypeIndices;
public:
public:
	void LoadModelPrototype(TString &filepathname);
	void LoadTexture(TString &filepathname);

public:
	void LoadSingleTexture(TString &fn, TTextureObject &tar);
	void LoadShaderText(TString &fn, char *&shadertext);
	void LoadCollisionDetectingMatricesControllerData(TString &fn, TCollisionDetectingMatricesController *&cdmc);
	void LoadModelData(TString &fn, TModel *&model);
	void LoadAnimationData(TString &fn, TSequence *&ani);
	void LoadTextureController(TConfigFile &lfn, TConfigFile &mfn, TTextureController &tc);
	void LoadMeshController(TMeshController &mc, TModel &mdl);
	void LoadConfigFile(TString &fn, TConfigFile &cf);

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