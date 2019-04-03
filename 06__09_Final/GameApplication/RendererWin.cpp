#define _MATHTOOL_IMPORT
#define _BASE_IMPORT
#define _FILE_IMPORT
#define _CORE_IMPORT
#define _MODEL_IMPORT
#define _RENDERER_IMPORT
#define _THREAD_IMPORT
#define _DLL_IMPORT_API __declspec(dllimport)
#define _DLL_EXPORT_API __declspec(dllimport)

#include "../Renderer/GLee.h"
#include "stdafx.h"
#include "windows.h"
#undef GetClassName
#undef PostMessage

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
#include "RendererWin.h"


GLint		windowWidth = 1440;                // window size
GLint		windowHeight = 900;
GLdouble	cameraZoom = 0.4;
float light_rotation = 0;

TTextureController *_tc;
TShaderController *_sc;
TLightController *_lc;
TMeshController *_mc;
TViewPort *view;
TModelController *_mdlc;

TTextureController *_wtc;
TMeshController *_wmc;
TModelController *_wmdlc;

TTextureController *_archtc;
TMeshController *_archmc;
TModelController *_archmdlc;

TCollisionDetectingMatricesController *_cdm1;
TCollisionDetectingMatricesController *_cdm2;

Matrix44f _wmat;
Matrix44f _archmat;

TArea *area = NULL;

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

bool isOneFrameFinished = true;
bool isShutDown = false;

Sync::Sync() {selector = 0;dselector = 0;dratio = 0.0f;};
Sync::~Sync() {};
void Sync::Run() {
	while (TRUE) {
		if ( currentime > 1.66f ) {
			currentime = 0.0f;
			count ++;
		} else {
			currentime = currentime + 0.01f;
		}
		rwLock.WriteLock();
		animations[0].LoadAnimationMatrix(boneController.GetBoneController().GetBoneRoot(), currentime);
		boneController.GetBoneController().GetBoneRoot().GetTransform() = Transform();
		boneController.GetBoneController().DoAnimation();
		rwLock.Unlock();
		if ( !isOneFrameFinished ) {
			isOneFrameFinished = true;
		} else {
			while (isOneFrameFinished) {
				Delay(0, 1000);
			}
		}
	}
}

void Sync::Flush(float delta) {
	if ( selector == dselector ) {
		if ( parentController == NULL ) {
			if ( currentime > animations[selector].GetStopTime() - 0.01 ) {
				currentime = 0.0f;
				count ++;
			} else {
				currentime = currentime + delta / 1000.0f;
			}
		}
		rwLock.WriteLock();
		//TBoneTreeNode *weapon = (TBoneTreeNode*)boneController.GetBoneController().GetBoneHashtable().Get(TString("Weapon"));
		//if ( weapon != NULL ) {
		//	weapon->GetInvertedTransform() = Transform();
		//}
		if ( parentController != NULL ) {
		//	_wmat = Matrix44f(weapon->GetFastTransform().translation, weapon->GetFastTransform().rotation);
			parentController->boneController.GetBoneController().CopyBoneTransform(boneController.GetBoneController().GetBoneRoot());
			boneController.GetBoneController().DoAnimation();
		} else {
			animations[selector].LoadAnimationMatrix(boneController.GetBoneController().GetBoneRoot(), currentime);
			if ( innerstate != 0 ) {
				if ( innerstate == 1 ) {
					Velocity(0.1f);
				}
				if ( innerstate == 2 ) {
					Velocity(-0.1f);
				}
				innerstate = 0;
			}
			if ( _cdm1->IsCollision(position, position) ) {
				//Gravity(0.0f);
				Commit();
				//if ( innerstate == 1 ) {
				//	Velocity(0.1f);
				//}
				//if ( innerstate == 2 ) {
				//	Velocity(-0.1f);
				//}
				//Commit();
			} else {
				Commit();
				Gravity(0.001f);
			}
			if ( innerstate != 0 ) {
				innerstate = 0;
			}
			Vector3f spos = positionCurrent / 0.015f;
			Transform rt(spos, direction, 1.0f);
			boneController.GetBoneController().GetBoneRoot().GetTransform() = rt;
			boneController.GetBoneController().DoAnimation();
		}
		rwLock.Unlock();
	} else {
		if ( parentController == NULL ) {
			if ( dratio > 1.0f ) {
				selector = dselector;
				currentime = 0.0f;
			} else {
				dratio = dratio + delta / 1000.0f;
			}
		}
		rwLock.WriteLock();
		//TBoneTreeNode *weapon = (TBoneTreeNode*)boneController.GetBoneController().GetBoneHashtable().Get(TString("Weapon"));
		//if ( weapon != NULL ) {
		//	weapon->GetInvertedTransform() = Transform();
		//}
		if ( parentController != NULL ) {
		//	_wmat = Matrix44f(weapon->GetFastTransform().translation, weapon->GetFastTransform().rotation);
			parentController->boneController.GetBoneController().CopyBoneTransform(boneController.GetBoneController().GetBoneRoot());
			boneController.GetBoneController().DoAnimation();
		} else {
			animations[selector].BuildTemporaryAnimation(currentime);
			animations[selector].LoadAnimationMatrix(animations[dselector], boneController.GetBoneController().GetBoneRoot(), dratio);
			if ( innerstate != 0 ) {
				if ( innerstate == 1 ) {
					Velocity(0.1f);
				}
				if ( innerstate == 2 ) {
					Velocity(-0.1f);
				}
				innerstate = 0;
			}
			if ( _cdm1->IsCollision(position, position) ) {
				//Gravity(0.0f);
				Commit();
				//if ( innerstate == 1 ) {
				//	Velocity(0.1f);
				//}
				//if ( innerstate == 2 ) {
				//	Velocity(-0.1f);
				//}
				//Commit();
			} else {
				Commit();
				Gravity(0.001f);
			}
			if ( innerstate != 0 ) {
				innerstate = 0;
			}
			Vector3f spos = positionCurrent / 0.015f;
			Transform rt(spos, direction, 1.0f);
			boneController.GetBoneController().GetBoneRoot().GetTransform() = rt;
			boneController.GetBoneController().DoAnimation();
		}
		//if ( weapon != NULL ) {
		//	_wmat = Matrix44f(weapon->GetFastTransform().translation, weapon->GetFastTransform().rotation);
		//}
		rwLock.Unlock();
	}
}
Sync *ac = NULL;
Sync *wac = NULL;

ANCSync::ANCSync() {};
ANCSync::~ANCSync() {};
void ANCSync::RendererHandler() {
	if ( !isOneFrameFinished ) {
		isOneFrameFinished = true;
	} else {
		while (isOneFrameFinished) {
			Delay(0, 1000);
		}
	}
}

ANCSync *ant = NULL;

CoreSync::CoreSync() {_x = 0; _y = 0; _dx = 0; _dy = 0; _oha = 0.0f; _ova = 0.0f; _dist = 5.0f; objpos = Vector3f();};
CoreSync::~CoreSync() {};
void CoreSync::OnMouseMove(short x, short y) {
	_dx = x - _x; _x = x;
	_dy = y - _y; _y = y;
	float _ha = - _dx / 360.0f;
	float _va = _dy / 360.0f;
	_oha += _ha;
	_ova += _va;
	float _distance = 1.0f;
	Vector3f cam(10.0f, 0.0f, 0.0f);

//	view.CameraCentered(Vector3f(10.0f, 0.0f, 0.0f) , _dist, _oha, _ova);
	//view->ObjectCentered(objpos, _dist, _oha, _ova);
	view->ObjectCentered(ac->positionCurrent, _dist, _oha, _ova);
	view->GenViewCoordinate();
}
void CoreSync::OnKeyDown(unsigned char key) {
	switch(key) {
		case 'W':
			{
				//bak = objpos;
				//bak.x += 0.1f;
				ac->innerstate = 1;
				//if ( _cdm1->IsCollision(ac->position, Vector3f()) ) {
				//} else {
				//	ac->Commit();
				//}
			}
			break;
		case 'S':
			{
				//bak = objpos;
				//bak.x -= 0.1f;
				ac->innerstate = 2;
				//if ( _cdm1->IsCollision(ac->position, Vector3f()) ) {
				//} else {
				//	ac->Commit();
				//}
			}
			break;
		case 'A':
			{
				//bak = objpos;
				//bak.y += 0.1f;
				ac->RotationAxisZ(0.05f);
				//if ( _cdm1->IsCollision(bak, Vector3f()) ) {
				//} else {
				//	objpos = bak;
				//}
			}
			break;
		case 'D':
			{
				//bak = objpos;
				//bak.y -= 0.1f;
				ac->RotationAxisZ(-0.05f);
				//if ( _cdm1->IsCollision(bak, Vector3f()) ) {
				//} else {
				//	objpos = bak;
				//}
			}
			break;
		case 'C':
			{
				//bak = objpos;
				//bak.z += 0.1f;
				if ( _cdm1->IsCollision(bak, Vector3f()) ) {
				} else {
					objpos = bak;
				}
			}
			break;
		case 'Z':
			{
				//bak = objpos;
				//bak.z -= 0.1f;
				if ( _cdm1->IsCollision(bak, Vector3f()) ) {
				} else {
					objpos = bak;
				}
			}
			break;
		case '1':
			{
				ac->dselector = 0;
				ac->dratio = 0.0f;
			}
			break;
		case '2':
			{
				ac->dselector = 1;
				ac->dratio = 0.0f;
			}
			break;
		case '3':
			{
				ac->dselector = 2;
				ac->dratio = 0.0f;
			}
			break;
		case '4':
			{
				ac->dselector = 3;
				ac->dratio = 0.0f;
			}
			break;
		case '5':
			{
				ac->dselector = 4;
				ac->dratio = 0.0f;
			}
			break;
		case '6':
			{
				ac->dselector = 5;
				ac->dratio = 0.0f;
			}
			break;
		default:
			break;
	}
	view->ObjectCentered(ac->positionCurrent, _dist, _oha, _ova);
	view->GenViewCoordinate();
}
void CoreSync::OnMouseWheel(short zdelta) {
	_dist += zdelta * 0.005f;
//	view.CameraCentered(Vector3f(10.0f, 0.0f, 0.0f) , _dist, _oha, _ova);
	view->ObjectCentered(ac->positionCurrent, _dist, _oha, _ova);
	view->GenViewCoordinate();
}
CoreSync *cs = NULL;

void ChangeSize(GLsizei w, GLsizei h) {
	GLfloat nRange = 100.0f;
	GLfloat fAspect;

	// Prevent a divide by zero
	if(h == 0)
		h = 1;

	fAspect = (GLfloat)w/(GLfloat)h;

	// Set Viewport to window dimensions
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);

	// Reset coordinate system
	glLoadIdentity();

	// Setup perspective for viewing
	gluPerspective(17.5f,fAspect,1,300);

	// Viewing transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void RenderScene() {
	//if (!isOneFrameFinished) {
	//	return;
	//}
//	ac.Run();
//	GLenum err;
	Vector3f l(1.0f , 1.0f , -1.0f);

	l = l.Normalized();
	//quaternionf q(vec3f(0,0,1), light_rotation);
	//q.mult_vec(*(vec3f*)&l); 
	Vector3f eye(0.0f , 0.0f , 1.0f);
	Vector3f h = l + eye;
	h = h.Normalized();
	TLightObject *lo = &_lc->lights[0];
	lo->direction = l;
	lo->halfAngle = h;

	// set vertex program inputs
//	rShaders[0].UseProgram();
//	glUniform1i(rShaders[0].parameters[7].location, 0);//rTextures[0].textureIndex); 
//	glUniform1i(rShaders[0].parameters[8].location, 1);//rTextures[1].textureIndex); 
//	glUniform1i(rShaders[0].parameters[9].location, 2);//rTextures[2].textureIndex); 
//	glUniform1i(rShaders[0].parameters[6].location, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (windowWidth > windowHeight)	{
		GLdouble ar = (GLdouble)windowWidth / (GLdouble)windowHeight;
		glFrustum(-ar * cameraZoom, ar * cameraZoom, -cameraZoom, cameraZoom, 1.0, 1000.0);
	} else {
		GLdouble ar = (GLdouble)windowHeight / (GLdouble)windowWidth;
		glFrustum(-cameraZoom, cameraZoom, -ar * cameraZoom, ar * cameraZoom, 1.0, 1000.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
//	gluLookAt(0.0f , 0.0f , -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	view->LookAt();
	ac->rwLock.ReadLock();
	_mdlc->numBoneMatrices = 70;
	_mdlc->LinkBoneMatrices();
	ac->rwLock.Unlock();
	wac->rwLock.ReadLock();
	_wmdlc->numBoneMatrices = 1;
	_wmdlc->LinkBoneMatrices();
	wac->rwLock.Unlock();
	Matrix44f mat;
	glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)&mat);
	view->invertModelView = mat.Inverse();
	_archmc->RenderUnit(*_archtc, *_lc, *_sc, *view);
	_mc->RenderUnit(*_tc, *_lc, *_sc, *view);
	_wmc->RenderUnit(*_wtc, *_lc, *_sc, *view);
//	glFlush();
	//isOneFrameFinished = false;
}

void Initialization() {
}

void Init_SC(TShaderController &sc) {
	char *vfilename = "./shaders/skinning.vs";
	char *ffilename = "./shaders/skinning.fs";

	sc.shaders.Resize(3);
	sc.shaders.CreateAll();

	sc.shaders[0].SetVertexShaderText(LoadShaderText(vfilename));
	sc.shaders[0].SetFragmentShaderText(LoadShaderText(ffilename));

	GLint vss, fss, lps, vps;
	sc.shaders[0].PrepareShader(vss, fss, lps, vps);

	sc.shaders[0].CreateParameters(15);

	sc.shaders[0].AddParameter(tangent, "tangent", TShaderParameter::sp_attribute_tangent);
	sc.shaders[0].AddParameter(binormal, "binormal", TShaderParameter::sp_attribute_binormal);
	sc.shaders[0].AddParameter(boneindex, "boneindex", TShaderParameter::sp_attribute_custom_vector4);
	sc.shaders[0].AddParameter(weight, "weight", TShaderParameter::sp_attribute_custom_vector4);
	sc.shaders[0].AddParameter(texcoord, "texcoord", TShaderParameter::sp_attribute_texcoord);
	sc.shaders[0].AddParameter(transforms, "transforms", TShaderParameter::sp_uniform_custom_matrix44);
	sc.shaders[0].AddParameter(modelview, "modelViewI", TShaderParameter::sp_uniform_model_matrix44);
	sc.shaders[0].AddParameter(light, "light", TShaderParameter::sp_uniform_light_position);
	sc.shaders[0].AddParameter(halfangle, "halfAngle", TShaderParameter::sp_uniform_custom_vector3);
	sc.shaders[0].AddParameter(isparallax, "parallaxMapping", TShaderParameter::sp_uniform_custom_int);
	sc.shaders[0].AddParameter(decalmap, "decalMap", TShaderParameter::sp_uniform_diffuse_map);
	sc.shaders[0].AddParameter(heightmap, "heightMap", TShaderParameter::sp_uniform_height_map);
	sc.shaders[0].AddParameter(normalmap, "normalMap", TShaderParameter::sp_uniform_normal_map);
	sc.shaders[0].AddParameter(vertex, "vertexAttrib", TShaderParameter::sp_attribute_vertex);
	sc.shaders[0].AddParameter(normal, "normalAttrib", TShaderParameter::sp_attribute_normal);

	sc.shaderIndices.Add(TString("SKINNING"), &sc.shaders[0]);

	vfilename = "./shaders/norm.vs";
	ffilename = "./shaders/norm.fs";

	sc.shaders[1].SetVertexShaderText(LoadShaderText(vfilename));
	sc.shaders[1].SetFragmentShaderText(LoadShaderText(ffilename));

	sc.shaders[1].PrepareShader(vss, fss, lps, vps);

	sc.shaders[1].CreateParameters(15);

	sc.shaders[1].AddParameter(tangent, "tangent", TShaderParameter::sp_attribute_tangent);
	sc.shaders[1].AddParameter(binormal, "binormal", TShaderParameter::sp_attribute_binormal);
	sc.shaders[1].AddParameter(boneindex, "boneindex", TShaderParameter::sp_attribute_custom_vector4);
	sc.shaders[1].AddParameter(weight, "weight", TShaderParameter::sp_attribute_custom_vector4);
	sc.shaders[1].AddParameter(texcoord, "texcoord", TShaderParameter::sp_attribute_texcoord);
	sc.shaders[1].AddParameter(transforms, "transforms", TShaderParameter::sp_uniform_custom_matrix44);
	sc.shaders[1].AddParameter(modelview, "modelViewI", TShaderParameter::sp_uniform_model_matrix44);
	sc.shaders[1].AddParameter(light, "light", TShaderParameter::sp_uniform_light_position);
	sc.shaders[1].AddParameter(halfangle, "halfAngle", TShaderParameter::sp_uniform_custom_vector3);
	sc.shaders[1].AddParameter(isparallax, "parallaxMapping", TShaderParameter::sp_uniform_custom_int);
	sc.shaders[1].AddParameter(decalmap, "decalMap", TShaderParameter::sp_uniform_diffuse_map);
	sc.shaders[1].AddParameter(heightmap, "heightMap", TShaderParameter::sp_uniform_height_map);
	sc.shaders[1].AddParameter(normalmap, "normalMap", TShaderParameter::sp_uniform_normal_map);
	sc.shaders[1].AddParameter(vertex, "vertexAttrib", TShaderParameter::sp_attribute_vertex);
	sc.shaders[1].AddParameter(normal, "normalAttrib", TShaderParameter::sp_attribute_normal);

	sc.shaderIndices.Add(TString("NORM"), &sc.shaders[1]);

	vfilename = "./shaders/stransform.vs";
	ffilename = "./shaders/stransform.fs";

	sc.shaders[2].SetVertexShaderText(LoadShaderText(vfilename));
	sc.shaders[2].SetFragmentShaderText(LoadShaderText(ffilename));

	sc.shaders[2].PrepareShader(vss, fss, lps, vps);

	sc.shaders[2].CreateParameters(15);

	sc.shaders[2].AddParameter(tangent, "tangent", TShaderParameter::sp_attribute_tangent);
	sc.shaders[2].AddParameter(binormal, "binormal", TShaderParameter::sp_attribute_binormal);
	sc.shaders[2].AddParameter(boneindex, "boneindex", TShaderParameter::sp_attribute_custom_vector4);
	sc.shaders[2].AddParameter(weight, "weight", TShaderParameter::sp_attribute_custom_vector4);
	sc.shaders[2].AddParameter(texcoord, "texcoord", TShaderParameter::sp_attribute_texcoord);
	sc.shaders[2].AddParameter(transforms, "transform", TShaderParameter::sp_uniform_custom_matrix44);
	sc.shaders[2].AddParameter(modelview, "modelViewI", TShaderParameter::sp_uniform_model_matrix44);
	sc.shaders[2].AddParameter(light, "light", TShaderParameter::sp_uniform_light_position);
	sc.shaders[2].AddParameter(halfangle, "halfAngle", TShaderParameter::sp_uniform_custom_vector3);
	sc.shaders[2].AddParameter(isparallax, "parallaxMapping", TShaderParameter::sp_uniform_custom_int);
	sc.shaders[2].AddParameter(decalmap, "decalMap", TShaderParameter::sp_uniform_diffuse_map);
	sc.shaders[2].AddParameter(heightmap, "heightMap", TShaderParameter::sp_uniform_height_map);
	sc.shaders[2].AddParameter(normalmap, "normalMap", TShaderParameter::sp_uniform_normal_map);
	sc.shaders[2].AddParameter(vertex, "vertexAttrib", TShaderParameter::sp_attribute_vertex);
	sc.shaders[2].AddParameter(normal, "normalAttrib", TShaderParameter::sp_attribute_normal);

	sc.shaderIndices.Add(TString("STRANS"), &sc.shaders[2]);

}

void LoadSingleTexture(const char * filepathname, TTextureObject &tar) {
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

void Init_TC(TTextureController &tc) {
	tc.textures.Resize(19);
	tc.textures.CreateAll();

	tc.textures[0].GenTexture();
	tc.textures[0].SetIndex(0);
	tc.textures[0].SetTarget(GL_TEXTURE_2D);
	tc.textures[0].ActiveTexture();
	tc.textures[0].BindTexture();
	tc.textures[0].TextureParameter();

	tc.textures[0].typeName = decalmap;
	LoadSingleTexture(".\\_Texture\\handfemale.dds", tc.textures[0]);
	tc.textureIndices.Add(TString("Hand_d"), &tc.textures[0]);

	tc.textures[1].GenTexture();
	tc.textures[1].SetIndex(0);
	tc.textures[1].SetTarget(GL_TEXTURE_2D);
	tc.textures[1].ActiveTexture();
	tc.textures[1].BindTexture();
	tc.textures[1].TextureParameter();

	tc.textures[1].typeName = decalmap;
	LoadSingleTexture(".\\_Texture\\zhh_head.dds", tc.textures[1]);
	tc.textureIndices.Add(TString("face_d"), &tc.textures[1]);
	tc.textureIndices.Add(TString("eyes_d"), &tc.textures[1]);
	tc.textureIndices.Add(TString("hair1_d"), &tc.textures[1]);
	tc.textureIndices.Add(TString("decor2_d"), &tc.textures[1]);
	tc.textureIndices.Add(TString("hair2_d"), &tc.textures[1]);


	tc.textures[2].GenTexture();
	tc.textures[2].SetIndex(0);
	tc.textures[2].SetTarget(GL_TEXTURE_2D);
	tc.textures[2].ActiveTexture();
	tc.textures[2].BindTexture();
	tc.textures[2].TextureParameter();

	tc.textures[2].typeName = decalmap;
	LoadSingleTexture(".\\_Texture\\PantyHose03.dds", tc.textures[2]);
	tc.textureIndices.Add(TString("Hand2_d"), &tc.textures[2]);
	tc.textureIndices.Add(TString("stockings1_d"), &tc.textures[2]);
	tc.textureIndices.Add(TString("stockings2_d"), &tc.textures[2]);
	tc.textureIndices.Add(TString("stockings3_d"), &tc.textures[2]);
	tc.textureIndices.Add(TString("gloves_d"), &tc.textures[2]);


	tc.textures[3].GenTexture();
	tc.textures[3].SetIndex(0);
	tc.textures[3].SetTarget(GL_TEXTURE_2D);
	tc.textures[3].ActiveTexture();
	tc.textures[3].BindTexture();
	tc.textures[3].TextureParameter();

	tc.textures[3].typeName = decalmap;
	LoadSingleTexture(".\\_Texture\\footfemale.dds", tc.textures[3]);
	tc.textureIndices.Add(TString("legs_d"), &tc.textures[3]);
	tc.textureIndices.Add(TString("foot_d"), &tc.textures[3]);
	tc.textureIndices.Add(TString("body_d"), &tc.textures[3]);
	tc.textureIndices.Add(TString("Legs01_d"), &tc.textures[3]);


	tc.textures[4].GenTexture();
	tc.textures[4].SetIndex(0);
	tc.textures[4].SetTarget(GL_TEXTURE_2D);
	tc.textures[4].ActiveTexture();
	tc.textures[4].BindTexture();
	tc.textures[4].TextureParameter();

	tc.textures[4].typeName = decalmap;
	LoadSingleTexture(".\\_Texture\\shinyblackheels.dds", tc.textures[4]);
	tc.textureIndices.Add(TString("highheels_d"), &tc.textures[4]);

	tc.textures[5].GenTexture();
	tc.textures[5].SetIndex(0);
	tc.textures[5].SetTarget(GL_TEXTURE_2D);
	tc.textures[5].ActiveTexture();
	tc.textures[5].BindTexture();
	tc.textures[5].TextureParameter();

	tc.textures[5].typeName = decalmap;
	LoadSingleTexture(".\\_Texture\\blackandgold.dds", tc.textures[5]);
	tc.textureIndices.Add(TString("dress_d"), &tc.textures[5]);
	tc.textureIndices.Add(TString("sleeves_d"), &tc.textures[5]);

  
	tc.textures[6].GenTexture();
	tc.textures[6].SetIndex(0);
	tc.textures[6].SetTarget(GL_TEXTURE_2D);
	tc.textures[6].ActiveTexture();
	tc.textures[6].BindTexture();
	tc.textures[6].TextureParameter();

	tc.textures[6].typeName = decalmap;
	LoadSingleTexture(".\\_Texture\\PantyHose03.dds", tc.textures[6]);
	tc.textureIndices.Add(TString("panties_d"), &tc.textures[6]);


	tc.textures[7].GenTexture();
	tc.textures[7].SetIndex(0);
	tc.textures[7].SetTarget(GL_TEXTURE_2D);
	tc.textures[7].ActiveTexture();
	tc.textures[7].BindTexture();
	tc.textures[7].TextureParameter();

	tc.textures[7].typeName = decalmap;
	LoadSingleTexture(".\\_Texture\\BlackNet.dds", tc.textures[7]);
	tc.textureIndices.Add(TString("obi_d"), &tc.textures[7]);

	tc.textures[8].GenTexture();
	tc.textures[8].SetIndex(0);
	tc.textures[8].SetTarget(GL_TEXTURE_2D);
	tc.textures[8].ActiveTexture();
	tc.textures[8].BindTexture();
	tc.textures[8].TextureParameter();

	tc.textures[8].typeName = decalmap;
	LoadSingleTexture(".\\_Texture\\MetalGold.dds", tc.textures[8]);
	tc.textureIndices.Add(TString("claws_d"), &tc.textures[8]);
	tc.textureIndices.Add(TString("necklace2_d"), &tc.textures[8]);
	tc.textureIndices.Add(TString("necklace1_d"), &tc.textures[8]);


	tc.textures[9].GenTexture();
	tc.textures[9].SetIndex(1);
	tc.textures[9].SetTarget(GL_TEXTURE_2D);
	tc.textures[9].ActiveTexture();
	tc.textures[9].BindTexture();
	tc.textures[9].TextureParameter();

	tc.textures[9].typeName = heightmap;
	LoadSingleTexture(".\\_Texture\\BlackNet.dds", tc.textures[9]);
	tc.textureIndices.Add(TString("Hand_h"), &tc.textures[9]);
	tc.textureIndices.Add(TString("face_h"), &tc.textures[9]);
	tc.textureIndices.Add(TString("eyes_h"), &tc.textures[9]);
	tc.textureIndices.Add(TString("hair1_h"), &tc.textures[9]);
	tc.textureIndices.Add(TString("decor2_h"), &tc.textures[9]);
	tc.textureIndices.Add(TString("hair2_h"), &tc.textures[9]);
	tc.textureIndices.Add(TString("Hand2_h"), &tc.textures[9]);
	tc.textureIndices.Add(TString("stockings1_h"), &tc.textures[9]);
	tc.textureIndices.Add(TString("stockings2_h"), &tc.textures[9]);
	tc.textureIndices.Add(TString("stockings3_h"), &tc.textures[9]);
	tc.textureIndices.Add(TString("gloves_h"), &tc.textures[9]);
	tc.textureIndices.Add(TString("legs_h"), &tc.textures[9]);
	tc.textureIndices.Add(TString("foot_h"), &tc.textures[9]);
	tc.textureIndices.Add(TString("body_h"), &tc.textures[9]);
	tc.textureIndices.Add(TString("Legs01_h"), &tc.textures[9]);
	tc.textureIndices.Add(TString("highheels_h"), &tc.textures[9]);
	tc.textureIndices.Add(TString("dress_h"), &tc.textures[9]);
	tc.textureIndices.Add(TString("sleeves_h"), &tc.textures[9]);
	tc.textureIndices.Add(TString("panties_h"), &tc.textures[9]);
	tc.textureIndices.Add(TString("obi_h"), &tc.textures[9]);
	tc.textureIndices.Add(TString("claws_h"), &tc.textures[9]);
	tc.textureIndices.Add(TString("necklace2_h"), &tc.textures[9]);
	tc.textureIndices.Add(TString("necklace1_h"), &tc.textures[9]);


	tc.textures[10].GenTexture();
	tc.textures[10].SetIndex(2);
	tc.textures[10].SetTarget(GL_TEXTURE_2D);
	tc.textures[10].ActiveTexture();
	tc.textures[10].BindTexture();
	tc.textures[10].TextureParameter();

	tc.textures[10].typeName = normalmap;
	LoadSingleTexture(".\\_Texture\\handfemale_n.dds", tc.textures[10]);
	tc.textureIndices.Add(TString("Hand_n"), &tc.textures[10]);

	tc.textures[11].GenTexture();
	tc.textures[11].SetIndex(2);
	tc.textures[11].SetTarget(GL_TEXTURE_2D);
	tc.textures[11].ActiveTexture();
	tc.textures[11].BindTexture();
	tc.textures[11].TextureParameter();

	tc.textures[11].typeName = normalmap;
	LoadSingleTexture(".\\_Texture\\zhh_head_n.dds", tc.textures[11]);
	tc.textureIndices.Add(TString("face_n"), &tc.textures[11]);
	tc.textureIndices.Add(TString("eyes_n"), &tc.textures[11]);
	tc.textureIndices.Add(TString("hair1_n"), &tc.textures[11]);
	tc.textureIndices.Add(TString("decor2_n"), &tc.textures[11]);
	tc.textureIndices.Add(TString("hair2_n"), &tc.textures[11]);


	tc.textures[12].GenTexture();
	tc.textures[12].SetIndex(2);
	tc.textures[12].SetTarget(GL_TEXTURE_2D);
	tc.textures[12].ActiveTexture();
	tc.textures[12].BindTexture();
	tc.textures[12].TextureParameter();

	tc.textures[12].typeName = normalmap;
	LoadSingleTexture(".\\_Texture\\PantyHose03_n.dds", tc.textures[12]);
	tc.textureIndices.Add(TString("Hand2_n"), &tc.textures[12]);
	tc.textureIndices.Add(TString("stockings1_n"), &tc.textures[12]);
	tc.textureIndices.Add(TString("stockings2_n"), &tc.textures[12]);
	tc.textureIndices.Add(TString("stockings3_n"), &tc.textures[12]);
	tc.textureIndices.Add(TString("gloves_n"), &tc.textures[12]);


	tc.textures[13].GenTexture();
	tc.textures[13].SetIndex(2);
	tc.textures[13].SetTarget(GL_TEXTURE_2D);
	tc.textures[13].ActiveTexture();
	tc.textures[13].BindTexture();
	tc.textures[13].TextureParameter();

	tc.textures[13].typeName = normalmap;
	LoadSingleTexture(".\\_Texture\\footfemale_n.dds", tc.textures[13]);
	tc.textureIndices.Add(TString("legs_n"), &tc.textures[13]);
	tc.textureIndices.Add(TString("foot_n"), &tc.textures[13]);
	tc.textureIndices.Add(TString("body_n"), &tc.textures[13]);
	tc.textureIndices.Add(TString("Legs01_n"), &tc.textures[13]);


	tc.textures[14].GenTexture();
	tc.textures[14].SetIndex(2);
	tc.textures[14].SetTarget(GL_TEXTURE_2D);
	tc.textures[14].ActiveTexture();
	tc.textures[14].BindTexture();
	tc.textures[14].TextureParameter();

	tc.textures[14].typeName = normalmap;
	LoadSingleTexture(".\\_Texture\\shinyblackheels_n.dds", tc.textures[14]);
	tc.textureIndices.Add(TString("highheels_n"), &tc.textures[14]);

	tc.textures[15].GenTexture();
	tc.textures[15].SetIndex(2);
	tc.textures[15].SetTarget(GL_TEXTURE_2D);
	tc.textures[15].ActiveTexture();
	tc.textures[15].BindTexture();
	tc.textures[15].TextureParameter();

	tc.textures[15].typeName = normalmap;
	LoadSingleTexture(".\\_Texture\\blackandgold_n.dds", tc.textures[15]);
	tc.textureIndices.Add(TString("dress_n"), &tc.textures[15]);
	tc.textureIndices.Add(TString("sleeves_n"), &tc.textures[15]);

  
	tc.textures[16].GenTexture();
	tc.textures[16].SetIndex(2);
	tc.textures[16].SetTarget(GL_TEXTURE_2D);
	tc.textures[16].ActiveTexture();
	tc.textures[16].BindTexture();
	tc.textures[16].TextureParameter();

	tc.textures[16].typeName = normalmap;
	LoadSingleTexture(".\\_Texture\\PantyHose03_n.dds", tc.textures[16]);
	tc.textureIndices.Add(TString("panties_n"), &tc.textures[16]);


	tc.textures[17].GenTexture();
	tc.textures[17].SetIndex(2);
	tc.textures[17].SetTarget(GL_TEXTURE_2D);
	tc.textures[17].ActiveTexture();
	tc.textures[17].BindTexture();
	tc.textures[17].TextureParameter();

	tc.textures[17].typeName = normalmap;
	LoadSingleTexture(".\\_Texture\\BlackNet_n.dds", tc.textures[17]);
	tc.textureIndices.Add(TString("obi_n"), &tc.textures[17]);

	tc.textures[18].GenTexture();
	tc.textures[18].SetIndex(2);
	tc.textures[18].SetTarget(GL_TEXTURE_2D);
	tc.textures[18].ActiveTexture();
	tc.textures[18].BindTexture();
	tc.textures[18].TextureParameter();

	tc.textures[18].typeName = normalmap;
	LoadSingleTexture(".\\_Texture\\MetalGold_n.dds", tc.textures[18]);
	tc.textureIndices.Add(TString("claws_n"), &tc.textures[18]);
	tc.textureIndices.Add(TString("necklace2_n"), &tc.textures[18]);
	tc.textureIndices.Add(TString("necklace1_n"), &tc.textures[18]);


	tc.ActiveTexture0();
}


void Init_LC(TLightController &lc) {
	lc.lights.Resize(1);
	lc.lights.CreateAll();

	TLightObject *lo = &lc.lights[0];
	lo->directionParamName = light;
	lo->halfAngleParamName = halfangle;

	lc.lightIndices.Add(TString("SIMPLELIGHT"), lo);
}
void Init_MC(TMeshController &mc) {
	Vector3f *bodyV = NULL;
	Vector3f *bodyN = NULL;
	Vector3f *bodyT = NULL;
	Vector3f *bodyB = NULL;
	unsigned short *bodyBone = NULL;
	float *bodyWeight = NULL;
	TexCoord2f *bodyU = NULL;
	Triangle *bodyTri = NULL;

	TMesh *bodyData = NULL;

	unsigned int numMeshes = 0;//(mobj.GetModels()[0]).GetMeshes().GetLength();

	//unsigned int i7 = 7;//0,3,5
	//mc.meshes.Resize(1);
	mc.meshes.Resize(numMeshes);
	mc.meshes.CreateAll();

	GLenum err;
	TString _d("_d");
	TString _h("_h");
	TString _n("_n");
	for ( unsigned int i7 = 0 ; i7 < numMeshes ; i7 ++ ) {
//		bodyData = &((mobj.GetModels()[0]).GetMeshes()[i7]);//17=leg;7=stocking;14=body
		bodyData->BuildTangentsBinormals();
		bodyData->GetBoneMatrices().Resize(70);
		bodyU = (TexCoord2f*)(bodyData->GetUVMap().GetBuffer());
		bodyV = (Vector3f*)(bodyData->GetVertices().GetBuffer());
		bodyN = (Vector3f*)(bodyData->GetNormals().GetBuffer());
		bodyT = (Vector3f*)(bodyData->GetTangents().GetBuffer());
		bodyB = (Vector3f*)(bodyData->GetBinormals().GetBuffer());
		bodyTri = (Triangle*)(bodyData->GetTriangles().GetBuffer());
		TSkin *s = &(bodyData->GetSkins()[0]);
		bodyBone = (unsigned short*)(s->GetBoneIndices().GetBuffer());
		bodyWeight = (float*)(s->GetVertexWeights().GetBuffer());


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

		mo->SetTangentsBuffer(bodyT, GL_ARRAY_BUFFER);
		mo->GenTangentsBuffer();
		mo->BindTangentsBuffer();
		mo->TangentsBufferData(GL_STATIC_DRAW);

		mo->SetBinormalsBuffer(bodyB, GL_ARRAY_BUFFER);
		mo->GenBinormalsBuffer();
		mo->BindBinormalsBuffer();
		mo->BinormalsBufferData(GL_STATIC_DRAW);

		mo->SetTexCoordsBuffer(bodyU, GL_ARRAY_BUFFER);
		mo->GenTexCoordsBuffer();
		mo->BindTexCoordsBuffer();
		mo->TexCoordsBufferData(GL_STATIC_DRAW);

		mo->SetIndicesBuffer((unsigned short*)bodyTri, GL_ELEMENT_ARRAY_BUFFER);
		mo->SetNumIndices(bodyData->GetNumTriangles() * 3);
		mo->GenIndicesBuffer();
		mo->BindIndicesBuffer();
		mo->IndicesBufferData(GL_STATIC_DRAW);

		mo->SetBoneIndicesBuffer(bodyBone, GL_ARRAY_BUFFER);
		mo->GenBoneIndicesBuffer();
		mo->BindBoneIndicesBuffer();
		mo->BoneIndicesBufferData(GL_STATIC_DRAW);

		mo->SetVertexWeightsBuffer(bodyWeight, GL_ARRAY_BUFFER);
		mo->GenVertexWeightsBuffer();
		mo->BindVertexWeightsBuffer();
		mo->VertexWeightsBufferData(GL_STATIC_DRAW);

		BOOL32 isok = mc.meshIndices.Add(bodyData->GetName(), mo);
		//assert(isok);
		err = glGetError();
		if (err != GL_NO_ERROR) {
			printf("ERROR1000(Init_MC): OpenGL error: 0x%X, %s \n" , err, gluErrorString(err));
		}

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
void Init_MDLC(TModelController &mdlc, TModel &mdl) {
	mdlc.modelPrototype = &mdl;
	mdlc.animationController = ac;
	mdlc.renderMeshUnit = _mc;
}
void TestCDM(TCollisionDetectingMatrices &cdm, TMesh &mesh) {
	mesh.BuildTangentsBinormals();
	cdm.BuildCollisionDetectingMatrices(mesh);
}
void Init_ALL() {
	_tc = new TTextureController();
	_sc = new TShaderController();
	_lc = new TLightController();
	_mc = new TMeshController();
	view = new TViewPort();
	_mdlc = new TModelController();

	_wtc = new TTextureController();
	_wmc = new TMeshController();
	_wmdlc = new TModelController();

	_archtc = new TTextureController();
	_archmc = new TMeshController();
	_archmdlc = new TModelController();


	GLenum err;
	printf("Hardware Skinning ZNW\n\n");

	Init_SC(*_sc);

	err = glGetError();
	if (err != GL_NO_ERROR) {
		printf("ERROR0013: OpenGL error: 0x%X, %s \n" , err, gluErrorString(err));
	}

//	glDepthMask(FALSE);
//	glDisable(GL_LIGHTING);
	glClearColor(0.2f, 0.8f, 0.2f, 0.0f);
	glAlphaFunc(GL_GREATER, 0.1f);   
	glEnable(GL_ALPHA_TEST);   
	glEnable(GL_DEPTH_TEST);
	//GL_TEXTURE_RECTANGLE_NV
	//GL_REGISTER_COMBINERS_NV
	glEnable(GL_BLEND);
	//glDisable(GL_DEPTH_TEST);
	//	4. set additive blending
	//glColor4f(1.0f,1.0f,1.0f,0.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	TConfigFile znwtf;
	TConfigFile znwmt;
	area = new TArea();
	area->LoadConfigFile(TString(".\\ZNWTF.ini"), znwtf);
	area->LoadConfigFile(TString(".\\ZNWMT.ini"), znwmt);
	area->LoadTextureController(znwtf, znwmt, *_tc);

	//Init_TC(_tc);
	TConfigFile hstf;
	TConfigFile hsmt;
	area->LoadConfigFile(TString(".\\HSTF.ini"), hstf);
	area->LoadConfigFile(TString(".\\HSMT.ini"), hsmt);
	area->LoadTextureController(hstf, hsmt, *_wtc);

	_sc->shaders[0].UseProgram();

	//_sc.shaders[0].SetParameter(decalmap, _tc.textures[0].GetIndex());
	//_sc.shaders[0].SetParameter(heightmap, _tc.textures[1].GetIndex());
	//_sc.shaders[0].SetParameter(normalmap, _tc.textures[2].GetIndex());

	_sc->shaders[0].SetParameter(isparallax, 0);

	Init_LC(*_lc);
	
	err = glGetError();
	if (err != GL_NO_ERROR) {
		printf("ERROR0014: OpenGL error: 0x%X, %s \n" , err, gluErrorString(err));
	}

	TModel *_mdl = NULL;
//	LoadMesh(mobj);
	area->LoadModelData(TString(".\\_Model\\ZNW_SW2T.dat"), _mdl);
//	LoadAni1(mani1);
//	LoadAni2(mani2);
	ac = new Sync();
	wac = new Sync();
	DoAni(*_mdl, *ac, *wac);

	//Init_MC(_mc);
	area->LoadMeshController(*_mc, *_mdl);

	Init_MDLC(*_mdlc, *_mdl);

	area->LoadModelData(TString(".\\_Model\\HeavenlySword.dat"), _mdl);
	area->LoadMeshController(*_wmc, *_mdl);
	_mdl->BuildAnimationController(wac->boneController, TString("Weapon"), Transform(), Transform());
	unsigned int nummeshobjects = _wmc->meshes.GetLength();
	for (unsigned int i2 = 0 ; i2 < nummeshobjects ; i2 ++ ) {
		_wmc->meshes[i2].shaderName = TString("STRANS");
		_wmc->meshes[i2].SetBoneMatrices(&_wmat, 1);
	}
	_wmdlc->modelPrototype = _mdl;
	_wmdlc->animationController = wac;
	_wmdlc->renderMeshUnit = _wmc;

	TConfigFile archtf;
	TConfigFile archmt;
	area->LoadConfigFile(TString(".\\SCTF.ini"), archtf);
	area->LoadConfigFile(TString(".\\SCMT.ini"), archmt);
	area->LoadTextureController(archtf, archmt, *_archtc);
	TModel *_archmdl = NULL;
	area->LoadModelData(TString(".\\_Model\\Arch.dat"), _archmdl);
	area->LoadMeshController(*_archmc, *_archmdl);
//	_archmdl->BuildAnimationController(*_archmdl, TString("Location"), Transform(), Transform());
	nummeshobjects = _archmc->meshes.GetLength();
	for (unsigned int i3 = 0 ; i3 < nummeshobjects ; i3 ++ ) {
		_archmc->meshes[i3].shaderName = TString("STRANS");
		_archmc->meshes[i3].SetBoneMatrices(&_archmat, 1);
	}

	TModel *_cmdl = NULL;
	area->LoadModelData(TString(".\\BOX.cdm"), _cmdl);
//	TCollisionDetectingMatrices _cdm;
//	TestCDM(_cdm, _cmdl->GetMeshes()[0]);
	area->LoadCollisionDetectingMatricesControllerData(TString(".\\_Model\\CDM1.cdm"), _cdm1);
	area->LoadCollisionDetectingMatricesControllerData(TString(".\\_Model\\CDM2.cdm"), _cdm2);
	unsigned int numcdmos = _cdm1->GetCDMObjects().GetLength();
	for (unsigned int i5 = 0 ; i5 < numcdmos ; i5 ++ ) {
		_cdm1->GetCDMObjects()[i5].SetOuterFlag(TRUE);
	}
	_cdm1->Scale(0.015f);
	Transform ttr1(_cdm1->GetCDMObjects()[numcdmos - 1].GetCDMs()[0].GetTranslation(), 
		_cdm1->GetCDMObjects()[numcdmos - 1].GetCDMs()[0].GetRotation(), 1.0f);
	ttr1 = ttr1.Inverse();
	_cdm1->GetCDMObjects()[numcdmos - 1].GetRecommendation() = ttr1.toMatrix4();

	numcdmos = _cdm2->GetCDMObjects().GetLength();
	for (unsigned int i6 = 0 ; i6 < numcdmos ; i6 ++ ) {
		_cdm2->GetCDMObjects()[i6].SetOuterFlag(TRUE);
	}
	_cdm2->Scale(0.015f);

	Vector3f eye(3.0f , 0.0f , 0.0f);                           // infinite viewer
	view->camera = eye;
	view->center = Vector3f();
	view->cameraup = Vector3f(0.0f, 0.0f, 1.0f);
	view->GenViewCoordinate();

	view->imvParamName = modelview;


}

