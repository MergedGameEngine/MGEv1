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

#include "../Renderer/GLee.h"
#undef GetClassName
#undef PostMessage
#include "string.h"
#include "../Base/Type.h"
#include "../Base/Base.h"
#define _ARRAY_API _CORE_API
#include "Area.hpp"
#include "BaseImport.h"
#include "MathToolImport.h"
#include "FileImport.h"
#include "ModelImport.h"
#include "RendererImport.h"


_CORE_API TArea::TArea() {
}
_CORE_API TArea::~TArea() {
	prototypes.DeleteAll();
	prototypes.Resize(0);
	renderPrototypes.DeleteAll();
	renderPrototypes.Resize(0);
	renderTextures.DeleteAll();
	renderTextures.Resize(0);

	modelControllers.DeleteAll();
	modelControllers.Resize(0);

	animationPrototypes.DeleteAll();
	animationPrototypes.Resize(0);

}
char _CORE_API *TArea::GetClassName() {
	return "TArea";
}
int _CORE_API TArea::GetClassCode() {
	return CLSID_TArea;
}
int _CORE_API TArea::GetHashCode() {
	return 1;
}
BOOL32 _CORE_API TArea::IsInstanceof(const char* className) {
	if (strcmp("TArea", className)) {
		return TRUE;
	}
	if (strcmp("IObject", className)) {
		return TRUE;
	}
	return FALSE;
}
BOOL32 _CORE_API TArea::IsEqualto(IObject &obj) {
	return FALSE;
}
void _CORE_API TArea::Serialize(IIOStream &iio) {
}
void _CORE_API TArea::Wait() {
}
void _CORE_API TArea::Notify() {
}

void _CORE_API TArea::LoadModelPrototype(TString &filepathname) {
}
void _CORE_API TArea::LoadTexture(TString &filepathname) {
}


void _CORE_API TArea::LoadSingleTexture(TString &fn, TTextureObject &tar) {
	char filepathname[256];
	fn.GetStringASC(filepathname);
	TFile file;
	file.SetFilePathNameASC(filepathname);
	file.SetOpenMode(TFile::modeRead | TFile::typeBinary );
	if(!(file.Open())) {
		printf ("  Can't open inputfile \n");
	}
	TFileIOStream fio;
	fio.SetFile(&file);
	fio.SetLoadStore(TFileIOStream::load);
	fio.SetEndian(TFileIOStream::little_endian);
	TDDSTexture dds;
	dds.Serialize(fio);
	unsigned short _w = 0,_h = 0;
	unsigned char _cd = 0;
	void *_buf = NULL;
	dds.Get(_w, _h, _cd, _buf);
	if ( _cd == 4 ) {
		dds.ConvertARGBtoRGBA(TRUE);
	}
	tar.SetBuffer(_buf);
	tar.SetHeight(_h);
	tar.SetWidth(_w);
	if ( _cd == 1 ) {
		tar.TextureImage2D(0, GL_LUMINANCE, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE);
	}
	if ( _cd == 3 ) {
		tar.TextureImage2D(0, GL_RGB, 0, GL_BGR, GL_UNSIGNED_BYTE);
	}
	if ( _cd == 4 ) {
		tar.TextureImage2D(0, GL_RGBA, 0, GL_RGBA, GL_UNSIGNED_BYTE);
	}
	fio.Close();
	file.Close();
}

void _CORE_API TArea::LoadShaderText(TString &fn, char *&shadertext) {
	char fileName[256];
	fn.GetStringASC(fileName);
    GLint shaderLength = 0;
    FILE *fp;

    fp = fopen(fileName, "r");
    if (fp != NULL)
    {
        while (fgetc(fp) != EOF)
        {
            shaderLength ++;
        }
        rewind(fp);
        shadertext = new char[shaderLength + 1];
        if (shadertext != NULL)
        {
            fread(shadertext, 1, shaderLength, fp);
        }
        shadertext[shaderLength] = '\0';
        fclose(fp);
    }
}

void _CORE_API TArea::LoadModelData(TString &fn, TModel *&model) {
	char fileName[256];
	fn.GetStringASC(fileName);
	TFile *file = new TFile();
	file->SetFilePathNameASC(fileName);
	file->SetOpenMode(TFile::modeRead | TFile::typeBinary );
	file->Open();
	TFileIOStream fio;
	fio.SetFile(file);
	fio.SetLoadStore(TFileIOStream::load);
	fio.SetEndian(TFileIOStream::little_endian);
	TModelGlobal tobj;
	tobj.Serialize(fio);
	fio.Close();
	file->Close();
	delete file;
	if ( tobj.GetModels().GetLength() > 0 ) {
		model = &tobj.GetModels()[0];
	} else {
		model = NULL;
	}
}

void _CORE_API TArea::LoadCollisionDetectingMatricesControllerData(TString &fn, TCollisionDetectingMatricesController *&cdmc) {
	char fileName[256];
	fn.GetStringASC(fileName);
	TFile *file = new TFile();
	file->SetFilePathNameASC(fileName);
	file->SetOpenMode(TFile::modeRead | TFile::typeBinary );
	file->Open();
	TFileIOStream fio;
	fio.SetFile(file);
	fio.SetLoadStore(TFileIOStream::load);
	fio.SetEndian(TFileIOStream::little_endian);
	TModelGlobal tobj;
	tobj.Serialize(fio);
	fio.Close();
	file->Close();
	delete file;
	if ( tobj.GetCollisionDetectingMatricesControllers().GetLength() > 0 ) {
		cdmc = &tobj.GetCollisionDetectingMatricesControllers()[0];
	} else {
		cdmc = NULL;
	}
}

void _CORE_API TArea::LoadAnimationData(TString &fn, TSequence *&ani) {
	char fileName[256];
	fn.GetStringASC(fileName);
	TFile *file = new TFile();
	file->SetFilePathNameASC(fileName);
	file->SetOpenMode(TFile::modeRead | TFile::typeBinary );
	file->Open();
	TFileIOStream fio;
	fio.SetFile(file);
	fio.SetLoadStore(TFileIOStream::load);
	fio.SetEndian(TFileIOStream::little_endian);
	TModelGlobal tobj;
	tobj.Serialize(fio);
	fio.Close();
	file->Close();
	delete file;
	if ( tobj.GetAnimations().GetLength() > 0 ) {
		ani = &tobj.GetAnimations()[0];
	} else {
		ani = NULL;
	}
}

void _CORE_API TArea::LoadTextureController(TConfigFile &lfn, TConfigFile &mfn, TTextureController &tc) {
	THashtable linktable;
	TConfig *cfg;
	TString filepathname("FilePathName");
	TString texturetype("TextureType");
	TString strindex("Index");
	TString fndest;
	int index = 0;
	unsigned int numtexturefile = lfn.GetNames().GetLength();
	tc.textures.Resize(numtexturefile);
	tc.textures.CreateAll();
	for (unsigned int i2 = 0 ; i2 < numtexturefile ; i2 ++ ) {
		cfg = &lfn.GetValues()[i2];
		if ( cfg != NULL ) {
			if ( cfg->ParseInt(strindex, index) ) {
			}
			tc.textures[i2].GenTexture();
			tc.textures[i2].SetIndex(index);
			tc.textures[i2].SetTarget(GL_TEXTURE_2D);
			tc.textures[i2].ActiveTexture();
			tc.textures[i2].BindTexture();
			tc.textures[i2].TextureParameter();
			if ( cfg->GetString(filepathname, fndest) ) {
				LoadSingleTexture(fndest, tc.textures[i2]);
			}
			if ( cfg->GetString(texturetype, tc.textures[i2].typeName) ) {
			}
		}
		linktable.Add(lfn.GetNames()[i2], &tc.textures[i2]);
	}
	tc.ActiveTexture0();

	TString tarname;
	unsigned int numparts = mfn.GetNames().GetLength();
	for (unsigned int i3 = 0 ; i3 < numparts ; i3 ++ ) {
		cfg = &mfn.GetValues()[i3];
		if ( cfg != NULL ) {
			unsigned int nl = cfg->GetNames().GetLength();
			for ( unsigned int i7 = 0 ; i7 < nl ; i7 ++ ) {
				cfg->GetString(cfg->GetNames()[i7], tarname);
				TTextureObject *to = (TTextureObject*)linktable.Get(tarname);
				tc.textureIndices.Add(cfg->GetNames()[i7], to);
			}
		}
	}
}

void _CORE_API TArea::LoadMeshController(TMeshController &mc, TModel &mdl) {
	Vector3f *bodyV = NULL;
	Vector3f *bodyN = NULL;
	Vector3f *bodyT = NULL;
	Vector3f *bodyB = NULL;
	unsigned short *bodyBone = NULL;
	float *bodyWeight = NULL;
	TexCoord2f *bodyU = NULL;
	Triangle *bodyTri = NULL;

	TMesh *bodyData = NULL;

	unsigned int numMeshes = mdl.GetMeshes().GetLength();

	//unsigned int i7 = 7;//0,3,5
	//mc.meshes.Resize(1);
	mc.meshes.Resize(numMeshes);
	mc.meshes.CreateAll();

	TString tangent("TANGENT");
	TString binormal("BINORMAL");
	TString boneindex("BONEINDEX");
	TString weight("WEIGHT");
	TString texcoord("TEXCOORD");
	TString transforms("TRANSFORMS");
	TString modelview("MODELVIEW");
	TString light("LIGHT");
	TString halfangle("HALFANGLE");
	TString isparallax("ISP");
	TString decalmap("DECAL");
	TString heightmap("HEIGHT");
	TString normalmap("NORMAL");
	TString vertex("VERTEX");
	TString normal("NORMALVV");

	TString _d("_d");
	TString _h("_h");
	TString _n("_n");
	for ( unsigned int i7 = 0 ; i7 < numMeshes ; i7 ++ ) {
		bodyData = &mdl.GetMeshes()[i7];//17=leg;7=stocking;14=body
		bodyData->BuildTangentsBinormals();
		bodyData->GetBoneMatrices().Resize(70);
		bodyU = (TexCoord2f*)(bodyData->GetUVMap().GetBuffer());
		bodyV = (Vector3f*)(bodyData->GetVertices().GetBuffer());
		bodyN = (Vector3f*)(bodyData->GetNormals().GetBuffer());
		bodyT = (Vector3f*)(bodyData->GetTangents().GetBuffer());
		bodyB = (Vector3f*)(bodyData->GetBinormals().GetBuffer());
		bodyTri = (Triangle*)(bodyData->GetTriangles().GetBuffer());
		if ( bodyData->GetSkins().GetLength() > 0 ) {
			TSkin *s = &(bodyData->GetSkins()[0]);
			bodyBone = (unsigned short*)(s->GetBoneIndices().GetBuffer());
			bodyWeight = (float*)(s->GetVertexWeights().GetBuffer());
		} else {
			bodyBone = NULL;
			bodyWeight = NULL;
		}


		//i7 = 0;
		TMeshObject *mo = &mc.meshes[i7];
		mo->SetNumVertices(bodyData->GetNumVertices());

		mo->SetVerticesBuffer(bodyV, GL_ARRAY_BUFFER);
		mo->GenVerticesBuffer();
		mo->BindVerticesBuffer();
		mo->VerticesBufferData(GL_STATIC_DRAW);

		mo->SetNormalsBuffer(bodyN, GL_ARRAY_BUFFER);
		mo->GenNormalsBuffer();
		mo->BindNormalsBuffer();
		mo->NormalsBufferData(GL_STATIC_DRAW);

		//	判断是否存在
		mo->SetTangentsBuffer(bodyT, GL_ARRAY_BUFFER);
		mo->GenTangentsBuffer();
		mo->BindTangentsBuffer();
		mo->TangentsBufferData(GL_STATIC_DRAW);

		mo->SetBinormalsBuffer(bodyB, GL_ARRAY_BUFFER);
		mo->GenBinormalsBuffer();
		mo->BindBinormalsBuffer();
		mo->BinormalsBufferData(GL_STATIC_DRAW);
		//

		mo->SetTexCoordsBuffer(bodyU, GL_ARRAY_BUFFER);
		mo->GenTexCoordsBuffer();
		mo->BindTexCoordsBuffer();
		mo->TexCoordsBufferData(GL_STATIC_DRAW);

		mo->SetIndicesBuffer((unsigned short*)bodyTri, GL_ELEMENT_ARRAY_BUFFER);
		mo->SetNumIndices(bodyData->GetNumTriangles() * 3);
		mo->GenIndicesBuffer();
		mo->BindIndicesBuffer();
		mo->IndicesBufferData(GL_STATIC_DRAW);

		//	是带有动画还是静态
		mo->SetBoneIndicesBuffer(bodyBone, GL_ARRAY_BUFFER);
		mo->GenBoneIndicesBuffer();
		mo->BindBoneIndicesBuffer();
		mo->BoneIndicesBufferData(GL_STATIC_DRAW);

		mo->SetVertexWeightsBuffer(bodyWeight, GL_ARRAY_BUFFER);
		mo->GenVertexWeightsBuffer();
		mo->BindVertexWeightsBuffer();
		mo->VertexWeightsBufferData(GL_STATIC_DRAW);
		//

		BOOL32 isok = mc.meshIndices.Add(bodyData->GetName(), mo);
		//assert(isok);

		mo->binormalParamName = binormal;
		mo->boneIndexParamName = boneindex;
		mo->normalParamName = normal;
		mo->tangentParamName = tangent;
		mo->vertexParamName = vertex;
		mo->texCoordParamName = texcoord;
		mo->vertexWeightParamName = weight;
		mo->boneMatrixParamName = transforms;
		mo->textureNames.Resize(3);
		mo->textureNames.CreateAll();
		mo->textureNames[0] = bodyData->GetName() + _d;
		mo->textureNames[1] = bodyData->GetName() + _h;
		mo->textureNames[2] = bodyData->GetName() + _n;
		mo->lightNames.Resize(1);
		mo->lightNames.CreateAll();
		mo->lightNames[0] = TString("SIMPLELIGHT");
		mo->shaderName = TString("SKINNING");
	}
}

void _CORE_API TArea::LoadConfigFile(TString &fn, TConfigFile &cf) {
	char fileName[256];
	fn.GetStringASC(fileName);
	TFile fd;
	fd.SetFilePathNameASC(fileName);
	fd.SetOpenMode(TFile::modeRead | TFile::typeBinary);
	fd.Open();
	TFileIOStream fdio;
	fdio.SetFile(&fd);
	fdio.SetEndian(IIOStream::little_endian);
	fdio.SetLoadStore(IIOStream::load);
	cf.Serialize(fdio);
	fdio.Close();
	fd.Close();
}
