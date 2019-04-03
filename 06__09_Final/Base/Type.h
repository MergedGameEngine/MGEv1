///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

//
//	Definitions &
//	Macros
//

#ifndef _TYPE_H_
#define _TYPE_H_


#ifdef _BASE_EXPORT
#define _BASE_API __declspec(dllexport)
#else
#ifdef _BASE_IMPORT
#define _BASE_API __declspec(dllimport)
#endif
#endif

#ifdef _FILE_EXPORT
#define _FILE_API __declspec(dllexport)
#else
#ifdef _FILE_IMPORT
#define _FILE_API __declspec(dllimport)
#endif
#endif

#ifdef _SOUND_EXPORT
#define _SOUND_API __declspec(dllexport)
#else
#ifdef _SOUND_IMPORT
#define _SOUND_API __declspec(dllimport)
#endif
#endif

#ifdef _MATHTOOL_EXPORT
#define _MATHTOOL_API __declspec(dllexport)
#else
#ifdef _MATHTOOL_IMPORT
#define _MATHTOOL_API __declspec(dllimport)
#endif
#endif

#ifdef _MODEL_EXPORT
#define _MODEL_API __declspec(dllexport)
#else
#ifdef _MODEL_IMPORT
#define _MODEL_API __declspec(dllimport)
#endif
#endif

#ifdef _RENDERER_EXPORT
#define _RENDERER_API __declspec(dllexport)
#else
#ifdef _RENDERER_IMPORT
#define _RENDERER_API __declspec(dllimport)
#endif
#endif

#ifdef _THREAD_EXPORT
#define _THREAD_API __declspec(dllexport)
#else
#ifdef _THREAD_IMPORT
#define _THREAD_API __declspec(dllimport)
#endif
#endif

#ifdef _NETWORK_EXPORT
#define _NETWORK_API __declspec(dllexport)
#else
#ifdef _NETWORK_IMPORT
#define _NETWORK_API __declspec(dllimport)
#endif
#endif

#ifdef _CORE_EXPORT
#define _CORE_API __declspec(dllexport)
#else
#ifdef _CORE_IMPORT
#define _CORE_API __declspec(dllimport)
#endif
#endif

typedef unsigned int BOOL32;
typedef unsigned char BOOL8;
#ifndef byte
typedef unsigned char byte;
#endif

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

//	.Base Package Classes
#define CLSID_TString				5
#define CLSID_THashtable			6
#define CLSID_TArray				7
#define CLSID_TRefArray				8
#define CLSID_TObjectArray			9

//	.File Package Classes
#define CLSID_TFileIOStream			128
#define	CLSID_TFile					129
#define	CLSID_TConfig				150
#define	CLSID_TConfigFile			151

//	.Network Package Classes
#define	CLSID_TNetworkIOStream		192
#define	CLSID_TPacket				193
#define	CLSID_TServer				194
#define	CLSID_TServerHandler		195
#define	CLSID_TClient				196
#define	CLSID_TClientHandler		197

//	.Thread Package Classes
#define	CLSID_TThread				256
#define CLSID_TSemaphore			257
#define CLSID_TRWLock				258
#define CLSID_TSpinLock				259
#define CLSID_TMutex				260
#define CLSID_TBarrier				261

//	.Sound Package Classes
#define CLSID_TAudioDevice			400
#define CLSID_TWaveDataObject		401
#define CLSID_TWaveSourceObject		402
#define CLSID_TWaveSourceController	403

//	.Model Package Classes
#define CLSID_TModelObject			1024
#define CLSID_TMesh					1025
#define CLSID_TSkin					1026
#define CLSID_TBone					1027
#define CLSID_TBoneController		1028		
#define CLSID_TBoneTreeNode			1029

#define CLSID_TSequence				1030
#define CLSID_TKeyFrame				1031

#define CLSID_TCollisionDetectingMatrices				1050
#define CLSID_TCollisionDetectingMatricesController		1051
#define CLSID_TModel				1100
#define CLSID_TModelGlobal			1101

#define CLSID_TTexture				1200
#define CLSID_TTGATexture			1201
#define CLSID_TDDSTexture			1202

//	.Renderer Package Classes
#define CLSID_TViewPort				2048
#define CLSID_TLightController		2049
#define CLSID_TLightObject			2050
#define CLSID_TMeshController		2051
#define CLSID_TMeshObject			2052
#define CLSID_TShaderController		2054
#define CLSID_TShaderObject			2055
#define CLSID_TShaderParameter		2056
#define CLSID_TTextureController	2057
#define CLSID_TTextureObject		2058
#define CLSID_TMultiTexture			2059
#define CLSID_TMultiPassShader		2060
#define CLSID_TFrameObject			2061
#define CLSID_TFrameController		2062

//	.Core Package Classes
#define	CLSID_TCore					4096
#define	CLSID_TModelController		4097
#define	CLSID_TAnimationController	4098
#define CLSID_TAnimator				4099
#define	CLSID_TCharacter			4100
#define	CLSID_TNPC					4101
#define	CLSID_TPlayer				4102
#define	CLSID_TDevice				4103
#define	CLSID_TChest				4104
#define	CLSID_TWeapon				4105
#define	CLSID_TEvent				4500
#define	CLSID_TEventProcessor		4501
#define	CLSID_TEventListener		4502
#define	CLSID_TEventFilter			4503
#define CLSID_TLevel				4600
#define	CLSID_TArea					4601
#define	CLSID_TSection				4602
#define CLSID_TWindow				4300

#endif