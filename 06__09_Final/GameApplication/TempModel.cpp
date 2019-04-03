#define _MATHTOOL_IMPORT
#define _BASE_IMPORT
#define _FILE_IMPORT
#define _CORE_IMPORT
#define _MODEL_IMPORT
#define _RENDERER_IMPORT
#define _THREAD_IMPORT
#define _DLL_IMPORT_API __declspec(dllimport)
#define _DLL_EXPORT_API __declspec(dllimport)

#include "windows.h"
#undef GetClassName

#include "../Base/Type.h"
#include "../Base/Base.h"
#define _ARRAY_API _DLL_IMPORT_API
#include "../Base/Array.h"
#include "../Base/RefArray.h"
#include "../Core/BaseImport.h"
#include "../Core/MathToolImport.h"
#include "../Core/ModelImport.h"
#include "../Core/RendererImport.h"
#include "../Core/FileImport.h"
#include "../Thread/Thread.h"
#include "../CoreV/CoreImport.h"

#include "TempModel.h"

GLchar *LoadShaderText(const char *fileName) {
    GLchar *shaderText = NULL;
    GLint shaderLength = 0;
    FILE *fp;

    fp = fopen(fileName, "r");
    if (fp != NULL)
    {
        while (fgetc(fp) != EOF)
        {
            shaderLength++;
        }
        rewind(fp);
        shaderText = (GLchar *)malloc(shaderLength+1);
        if (shaderText != NULL)
        {
            fread(shaderText, 1, shaderLength, fp);
        }
        shaderText[shaderLength] = '\0';
        fclose(fp);
    }

    return shaderText;
}

void LoadMesh(TModelGlobal &mobj) {
	char *fileName = "E:\\ZHH_SW2T.dat";
	TFile *file = new TFile();
	file->SetFilePathNameASC(fileName);
	file->SetOpenMode(TFile::modeRead | TFile::typeBinary );
	file->Open();
	TFileIOStream fio;
	fio.SetFile(file);
	fio.SetLoadStore(TFileIOStream::load);
	fio.SetEndian(TFileIOStream::little_endian);
	mobj.Serialize(fio);
}

void LoadAni1(TModelGlobal &mani) {
	char *fileName = "E:\\Ani01.dat";
	TFile *file = new TFile();
	file->SetFilePathNameASC(fileName);
	file->SetOpenMode(TFile::modeRead | TFile::typeBinary );
	file->Open();
	TFileIOStream fio;
	fio.SetFile(file);
	fio.SetLoadStore(TFileIOStream::load);
	fio.SetEndian(TFileIOStream::little_endian);
	mani.Serialize(fio);
}

void LoadAni2(TModelGlobal &mani) {
	char *fileName = "E:\\Ani02.dat";
	TFile *file = new TFile();
	file->SetFilePathNameASC(fileName);
	file->SetOpenMode(TFile::modeRead | TFile::typeBinary );
	file->Open();
	TFileIOStream fio;
	fio.SetFile(file);
	fio.SetLoadStore(TFileIOStream::load);
	fio.SetEndian(TFileIOStream::little_endian);
	mani.Serialize(fio);
}

void LoadAni(TModelGlobal &mani, const char *fileName) {
	TFile *file = new TFile();
	file->SetFilePathNameASC(fileName);
	file->SetOpenMode(TFile::modeRead | TFile::typeBinary );
	file->Open();
	TFileIOStream fio;
	fio.SetFile(file);
	fio.SetLoadStore(TFileIOStream::load);
	fio.SetEndian(TFileIOStream::little_endian);
	mani.Serialize(fio);
	fio.Close();
	file->Close();
	delete file;
}

void DoAni(TModel &mdl, TAnimationController &ac, TAnimationController &wac) {
	TBoneTreeNode &boneRoot = mdl.GetBoneController().GetBoneRoot();
	mdl.GetBoneController().ReloadMatrix();
	mdl.GetBoneController().BuildBoneMatrix(boneRoot, Transform(Vector3f(), Matrix33f(), 1.0f));
	mdl.GetBoneController().ReloadInvertedMatrix(boneRoot);
	mdl.GetBoneController().ReloadMatrix(boneRoot);
	mdl.CopyAnimationController(ac.boneController);
	ac.boneController.GetBoneController().ReloadMatrix();
	ac.boneController.GetBoneController().BuildBoneMatrix();
	ac.boneController.GetBoneController().ReloadInvertedMatrix();
	ac.boneController.GetBoneController().ReloadMatrix();
	TBoneTreeNode *weapon = (TBoneTreeNode*)ac.boneController.GetBoneController().GetBoneHashtable().Get(TString("Weapon"));
	if ( weapon != NULL ) {
		weapon->GetInvertedTransform() = Transform();
	}

	wac.parentController = &ac;

	TModelGlobal *mg = NULL;
	TSequence *sq = NULL;
	ac.animations.Resize(6);

	mg = new TModelGlobal();
	LoadAni(*mg, "E:\\ANI01.dat");
	sq = &mg->GetAnimations()[0];
	ac.animations.Set(0, sq);

	mg = new TModelGlobal();
	LoadAni(*mg, "E:\\ANI02.dat");
	sq = &mg->GetAnimations()[0];
	ac.animations.Set(1, sq);

	mg = new TModelGlobal();
	LoadAni(*mg, "E:\\ANI20.dat");
	sq = &mg->GetAnimations()[0];
	ac.animations.Set(2, sq);

	mg = new TModelGlobal();
	LoadAni(*mg, "E:\\ANI21.dat");
	sq = &mg->GetAnimations()[0];
	ac.animations.Set(3, sq);

	mg = new TModelGlobal();
	LoadAni(*mg, "E:\\ANI22.dat");
	sq = &mg->GetAnimations()[0];
	ac.animations.Set(4, sq);

	mg = new TModelGlobal();
	LoadAni(*mg, "E:\\ANI23.dat");
	sq = &mg->GetAnimations()[0];
	ac.animations.Set(5, sq);

	ac.currentime = 0.0f;
	ac.boneController.GetBoneController().DoAnimation();
}
