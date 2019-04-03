#ifndef _ALEE_H_
#define _ALEE_H_

// Open AL Function table definition
#include "windows.h"
#include "stdio.h"
#include "io.h"
#include "fcntl.h"
#include "conio.h"
#include "al.h"
#include "alc.h"
#include "efx.h"
#include "efx-creative.h"
#include "xram.h"

#ifndef _OPENALFNTABLE
#define _OPENALFNTABLE

//
extern HMODULE g_hOpenALDLL;

// Type difinitions

#ifndef ALchar
#define ALchar char
#endif

#ifndef ALCchar
#define ALCchar char
#endif

// AL 1.0 API Prototypes

typedef void           (ALAPIENTRY *LPALENABLE)( ALenum capability );
typedef void           (ALAPIENTRY *LPALDISABLE)( ALenum capability ); 
typedef ALboolean      (ALAPIENTRY *LPALISENABLED)( ALenum capability ); 
typedef const ALchar*  (ALAPIENTRY *LPALGETSTRING)( ALenum param );
typedef void           (ALAPIENTRY *LPALGETBOOLEANV)( ALenum param, ALboolean* data );
typedef void           (ALAPIENTRY *LPALGETINTEGERV)( ALenum param, ALint* data );
typedef void           (ALAPIENTRY *LPALGETFLOATV)( ALenum param, ALfloat* data );
typedef void           (ALAPIENTRY *LPALGETDOUBLEV)( ALenum param, ALdouble* data );
typedef ALboolean      (ALAPIENTRY *LPALGETBOOLEAN)( ALenum param );
typedef ALint          (ALAPIENTRY *LPALGETINTEGER)( ALenum param );
typedef ALfloat        (ALAPIENTRY *LPALGETFLOAT)( ALenum param );
typedef ALdouble       (ALAPIENTRY *LPALGETDOUBLE)( ALenum param );
typedef ALenum         (ALAPIENTRY *LPALGETERROR)( void );
typedef ALboolean      (ALAPIENTRY *LPALISEXTENSIONPRESENT)(const ALchar* extname );
typedef void*          (ALAPIENTRY *LPALGETPROCADDRESS)( const ALchar* fname );
typedef ALenum         (ALAPIENTRY *LPALGETENUMVALUE)( const ALchar* ename );
typedef void           (ALAPIENTRY *LPALLISTENERF)( ALenum param, ALfloat value );
typedef void           (ALAPIENTRY *LPALLISTENER3F)( ALenum param, ALfloat value1, ALfloat value2, ALfloat value3 );
typedef void           (ALAPIENTRY *LPALLISTENERFV)( ALenum param, const ALfloat* values );
typedef void           (ALAPIENTRY *LPALLISTENERI)( ALenum param, ALint value );
typedef void           (ALAPIENTRY *LPALGETLISTENERF)( ALenum param, ALfloat* value );
typedef void           (ALAPIENTRY *LPALGETLISTENER3F)( ALenum param, ALfloat *value1, ALfloat *value2, ALfloat *value3 );
typedef void           (ALAPIENTRY *LPALGETLISTENERFV)( ALenum param, ALfloat* values );
typedef void           (ALAPIENTRY *LPALGETLISTENERI)( ALenum param, ALint* value );
typedef void           (ALAPIENTRY *LPALGENSOURCES)( ALsizei n, ALuint* sources ); 
typedef void           (ALAPIENTRY *LPALDELETESOURCES)( ALsizei n, const ALuint* sources );
typedef ALboolean      (ALAPIENTRY *LPALISSOURCE)( ALuint sid ); 
typedef void           (ALAPIENTRY *LPALSOURCEF)( ALuint sid, ALenum param, ALfloat value); 
typedef void           (ALAPIENTRY *LPALSOURCE3F)( ALuint sid, ALenum param, ALfloat value1, ALfloat value2, ALfloat value3 );
typedef void           (ALAPIENTRY *LPALSOURCEFV)( ALuint sid, ALenum param, const ALfloat* values );
typedef void           (ALAPIENTRY *LPALSOURCEI)( ALuint sid, ALenum param, ALint value); 
typedef void           (ALAPIENTRY *LPALGETSOURCEF)( ALuint sid, ALenum param, ALfloat* value );
typedef void           (ALAPIENTRY *LPALGETSOURCE3F)( ALuint sid, ALenum param, ALfloat* value1, ALfloat* value2, ALfloat* value3);
typedef void           (ALAPIENTRY *LPALGETSOURCEFV)( ALuint sid, ALenum param, ALfloat* values );
typedef void           (ALAPIENTRY *LPALGETSOURCEI)( ALuint sid, ALenum param, ALint* value );
typedef void           (ALAPIENTRY *LPALSOURCEPLAYV)( ALsizei ns, const ALuint *sids );
typedef void           (ALAPIENTRY *LPALSOURCESTOPV)( ALsizei ns, const ALuint *sids );
typedef void           (ALAPIENTRY *LPALSOURCEREWINDV)( ALsizei ns, const ALuint *sids );
typedef void           (ALAPIENTRY *LPALSOURCEPAUSEV)( ALsizei ns, const ALuint *sids );
typedef void           (ALAPIENTRY *LPALSOURCEPLAY)( ALuint sid );
typedef void           (ALAPIENTRY *LPALSOURCESTOP)( ALuint sid );
typedef void           (ALAPIENTRY *LPALSOURCEREWIND)( ALuint sid );
typedef void           (ALAPIENTRY *LPALSOURCEPAUSE)( ALuint sid );
typedef void           (ALAPIENTRY *LPALSOURCEQUEUEBUFFERS)(ALuint sid, ALsizei numEntries, const ALuint *bids );
typedef void           (ALAPIENTRY *LPALSOURCEUNQUEUEBUFFERS)(ALuint sid, ALsizei numEntries, ALuint *bids );
typedef void           (ALAPIENTRY *LPALGENBUFFERS)( ALsizei n, ALuint* buffers );
typedef void           (ALAPIENTRY *LPALDELETEBUFFERS)( ALsizei n, const ALuint* buffers );
typedef ALboolean      (ALAPIENTRY *LPALISBUFFER)( ALuint bid );
typedef void           (ALAPIENTRY *LPALBUFFERDATA)( ALuint bid, ALenum format, const ALvoid* data, ALsizei size, ALsizei freq );
typedef void           (ALAPIENTRY *LPALGETBUFFERF)( ALuint bid, ALenum param, ALfloat* value );
typedef void           (ALAPIENTRY *LPALGETBUFFERI)( ALuint bid, ALenum param, ALint* value );
typedef void           (ALAPIENTRY *LPALDOPPLERFACTOR)( ALfloat value );
typedef void           (ALAPIENTRY *LPALDOPPLERVELOCITY)( ALfloat value );
typedef void           (ALAPIENTRY *LPALDISTANCEMODEL)( ALenum distanceModel );

typedef ALCcontext *   (ALCAPIENTRY *LPALCCREATECONTEXT) (ALCdevice *device, const ALCint *attrlist);
typedef ALCboolean     (ALCAPIENTRY *LPALCMAKECONTEXTCURRENT)( ALCcontext *context );
typedef void           (ALCAPIENTRY *LPALCPROCESSCONTEXT)( ALCcontext *context );
typedef void           (ALCAPIENTRY *LPALCSUSPENDCONTEXT)( ALCcontext *context );
typedef void           (ALCAPIENTRY *LPALCDESTROYCONTEXT)( ALCcontext *context );
typedef ALCcontext *   (ALCAPIENTRY *LPALCGETCURRENTCONTEXT)( ALCvoid );
typedef ALCdevice *    (ALCAPIENTRY *LPALCGETCONTEXTSDEVICE)( ALCcontext *context );
typedef ALCdevice *    (ALCAPIENTRY *LPALCOPENDEVICE)( const ALCchar *devicename );
typedef ALCboolean     (ALCAPIENTRY *LPALCCLOSEDEVICE)( ALCdevice *device );
typedef ALCenum        (ALCAPIENTRY *LPALCGETERROR)( ALCdevice *device );
typedef ALCboolean     (ALCAPIENTRY *LPALCISEXTENSIONPRESENT)( ALCdevice *device, const ALCchar *extname );
typedef void *         (ALCAPIENTRY *LPALCGETPROCADDRESS)(ALCdevice *device, const ALCchar *funcname );
typedef ALCenum        (ALCAPIENTRY *LPALCGETENUMVALUE)(ALCdevice *device, const ALCchar *enumname );
typedef const ALCchar* (ALCAPIENTRY *LPALCGETSTRING)( ALCdevice *device, ALCenum param );
typedef void           (ALCAPIENTRY *LPALCGETINTEGERV)( ALCdevice *device, ALCenum param, ALCsizei size, ALCint *dest );

//	Basic AL 1.0 API

extern LPALENABLE					palEnable;
extern LPALDISABLE					palDisable;
extern LPALISENABLED				palIsEnabled;
extern LPALGETBOOLEAN				palGetBoolean;
extern LPALGETINTEGER				palGetInteger;
extern LPALGETFLOAT					palGetFloat;
extern LPALGETDOUBLE				palGetDouble;
extern LPALGETBOOLEANV				palGetBooleanv;
extern LPALGETINTEGERV				palGetIntegerv;
extern LPALGETFLOATV				palGetFloatv;
extern LPALGETDOUBLEV				palGetDoublev;
extern LPALGETSTRING				palGetString;
extern LPALGETERROR					palGetError;
extern LPALISEXTENSIONPRESENT		palIsExtensionPresent;
extern LPALGETPROCADDRESS			palGetProcAddress;
extern LPALGETENUMVALUE				palGetEnumValue;
extern LPALLISTENERI				palListeneri;
extern LPALLISTENERF				palListenerf;
extern LPALLISTENER3F				palListener3f;
extern LPALLISTENERFV				palListenerfv;
extern LPALGETLISTENERI				palGetListeneri;
extern LPALGETLISTENERF				palGetListenerf;
extern LPALGETLISTENER3F			palGetListener3f;
extern LPALGETLISTENERFV			palGetListenerfv;
extern LPALGENSOURCES				palGenSources;
extern LPALDELETESOURCES			palDeleteSources;
extern LPALISSOURCE					palIsSource;
extern LPALSOURCEI					palSourcei;
extern LPALSOURCEF					palSourcef;
extern LPALSOURCE3F					palSource3f;
extern LPALSOURCEFV					palSourcefv;
extern LPALGETSOURCEI				palGetSourcei;
extern LPALGETSOURCEF				palGetSourcef;
extern LPALGETSOURCEFV				palGetSourcefv;
extern LPALSOURCEPLAYV				palSourcePlayv;
extern LPALSOURCESTOPV				palSourceStopv;
extern LPALSOURCEPLAY				palSourcePlay;
extern LPALSOURCEPAUSE				palSourcePause;
extern LPALSOURCESTOP				palSourceStop;
extern LPALGENBUFFERS				palGenBuffers;
extern LPALDELETEBUFFERS			palDeleteBuffers;
extern LPALISBUFFER					palIsBuffer;
extern LPALBUFFERDATA				palBufferData;
extern LPALGETBUFFERI				palGetBufferi;
extern LPALGETBUFFERF				palGetBufferf;
extern LPALSOURCEQUEUEBUFFERS		palSourceQueueBuffers;
extern LPALSOURCEUNQUEUEBUFFERS		palSourceUnqueueBuffers;
extern LPALDISTANCEMODEL			palDistanceModel;
extern LPALDOPPLERFACTOR			palDopplerFactor;
extern LPALDOPPLERVELOCITY			palDopplerVelocity;

extern LPALCGETSTRING				palcGetString;
extern LPALCGETINTEGERV				palcGetIntegerv;
extern LPALCOPENDEVICE				palcOpenDevice;
extern LPALCCLOSEDEVICE				palcCloseDevice;
extern LPALCCREATECONTEXT			palcCreateContext;
extern LPALCMAKECONTEXTCURRENT		palcMakeContextCurrent;
extern LPALCPROCESSCONTEXT			palcProcessContext;
extern LPALCGETCURRENTCONTEXT		palcGetCurrentContext;
extern LPALCGETCONTEXTSDEVICE		palcGetContextsDevice;
extern LPALCSUSPENDCONTEXT			palcSuspendContext;
extern LPALCDESTROYCONTEXT			palcDestroyContext;
extern LPALCGETERROR				palcGetError;
extern LPALCISEXTENSIONPRESENT		palcIsExtensionPresent;
extern LPALCGETPROCADDRESS			palcGetProcAddress;
extern LPALCGETENUMVALUE			palcGetEnumValue;

// EFX Extension function pointer variables

// Effect objects
extern LPALGENEFFECTS				palGenEffects;
extern LPALDELETEEFFECTS			palDeleteEffects;
extern LPALISEFFECT					palIsEffect;
extern LPALEFFECTI					palEffecti;
extern LPALEFFECTIV					palEffectiv;
extern LPALEFFECTF					palEffectf;
extern LPALEFFECTFV					palEffectfv;
extern LPALGETEFFECTI				palGetEffecti;
extern LPALGETEFFECTIV				palGetEffectiv;
extern LPALGETEFFECTF				palGetEffectf;
extern LPALGETEFFECTFV				palGetEffectfv;

// Filter objects
extern LPALGENFILTERS				palGenFilters;
extern LPALDELETEFILTERS			palDeleteFilters;
extern LPALISFILTER					palIsFilter;
extern LPALFILTERI					palFilteri;
extern LPALFILTERIV					palFilteriv;
extern LPALFILTERF					palFilterf;
extern LPALFILTERFV					palFilterfv;
extern LPALGETFILTERI				palGetFilteri;
extern LPALGETFILTERIV				palGetFilteriv;
extern LPALGETFILTERF				palGetFilterf;
extern LPALGETFILTERFV				palGetFilterfv;

// Auxiliary slot object
extern LPALGENAUXILIARYEFFECTSLOTS		palGenAuxiliaryEffectSlots;
extern LPALDELETEAUXILIARYEFFECTSLOTS	palDeleteAuxiliaryEffectSlots;
extern LPALISAUXILIARYEFFECTSLOT		palIsAuxiliaryEffectSlot;
extern LPALAUXILIARYEFFECTSLOTI			palAuxiliaryEffectSloti;
extern LPALAUXILIARYEFFECTSLOTIV		palAuxiliaryEffectSlotiv;
extern LPALAUXILIARYEFFECTSLOTF			palAuxiliaryEffectSlotf;
extern LPALAUXILIARYEFFECTSLOTFV		palAuxiliaryEffectSlotfv;
extern LPALGETAUXILIARYEFFECTSLOTI		palGetAuxiliaryEffectSloti;
extern LPALGETAUXILIARYEFFECTSLOTIV		palGetAuxiliaryEffectSlotiv;
extern LPALGETAUXILIARYEFFECTSLOTF		palGetAuxiliaryEffectSlotf;
extern LPALGETAUXILIARYEFFECTSLOTFV		palGetAuxiliaryEffectSlotfv;

// XRAM Extension function pointer variables and enum values

typedef ALboolean (__cdecl *LPEAXSETBUFFERMODE)(ALsizei n, ALuint *buffers, ALint value);
typedef ALenum    (__cdecl *LPEAXGETBUFFERMODE)(ALuint buffer, ALint *value);

extern LPEAXSETBUFFERMODE eaxSetBufferMode;
extern LPEAXGETBUFFERMODE eaxGetBufferMode;

// X-RAM Enum values
extern ALenum eXRAMSize, eXRAMFree;
extern ALenum eXRAMAuto, eXRAMHardware, eXRAMAccessible;

//


ALboolean ALeeInit();
ALboolean ALEFXInit();
ALboolean ALXRAMInit();



//void	alEnable( ALenum capability );
//void	alDisable( ALenum capability ); 
//ALboolean	alIsEnabled( ALenum capability ); 
//const	ALchar*  alGetString( ALenum param );
//void	alGetBooleanv( ALenum param, ALboolean* data );
//void	alGetIntegerv( ALenum param, ALint* data );
//void	alGetFloatv( ALenum param, ALfloat* data );
//void	alGetDoublev( ALenum param, ALdouble* data );
//ALboolean	alGetBoolean( ALenum param );
//ALint	alGetInteger( ALenum param );
//ALfloat	alGetFloat( ALenum param );
//ALdouble	alGetDouble( ALenum param );
//ALenum	alGetError( void );
//ALboolean	alIsExtensionPresent(const ALchar* extname );
//void*	alGetProcAddress( const ALchar* fname );
//ALenum	alGetEnumValue( const ALchar* ename );
//void	alListenerf( ALenum param, ALfloat value );
//void	alListener3f( ALenum param, ALfloat value1, ALfloat value2, ALfloat value3 );
//void	alListenerfv ALenum param, const ALfloat* values );
//void	alListeneri( ALenum param, ALint value );
//void	alGetListenerf( ALenum param, ALfloat* value );
//void	alGetListener3f( ALenum param, ALfloat *value1, ALfloat *value2, ALfloat *value3 );
//void	alGetListenerfv( ALenum param, ALfloat* values );
//void	alGetListeneri( ALenum param, ALint* value );
//void	alGenSources( ALsizei n, ALuint* sources ); 
//void	alDeleteSources( ALsizei n, const ALuint* sources );
//ALboolean	alIsSource( ALuint sid ); 
//void	alSourcef( ALuint sid, ALenum param, ALfloat value); 
//void	alSource3f( ALuint sid, ALenum param, ALfloat value1, ALfloat value2, ALfloat value3 );
//void	alSourcefv( ALuint sid, ALenum param, const ALfloat* values );
//void	alSourcei( ALuint sid, ALenum param, ALint value); 
//void	alGetSourcef( ALuint sid, ALenum param, ALfloat* value );
////void           (ALAPIENTRY *LPALGETSOURCE3F)( ALuint sid, ALenum param, ALfloat* value1, ALfloat* value2, ALfloat* value3);
//void	alGetSourcefv( ALuint sid, ALenum param, ALfloat* values );
//void	alGetSourcei( ALuint sid, ALenum param, ALint* value );
//void	alSourcePlayv( ALsizei ns, const ALuint *sids );
//void	alSourceStopv( ALsizei ns, const ALuint *sids );
////void           (ALAPIENTRY *LPALSOURCEREWINDV)( ALsizei ns, const ALuint *sids );
////void           (ALAPIENTRY *LPALSOURCEPAUSEV)( ALsizei ns, const ALuint *sids );
//void	alSourcePlay( ALuint sid );
//void	alSourceStop( ALuint sid );
////void           (ALAPIENTRY *LPALSOURCEREWIND)( ALuint sid );
//void	alSourcePause( ALuint sid );
////void           (ALAPIENTRY *LPALSOURCEQUEUEBUFFERS)(ALuint sid, ALsizei numEntries, const ALuint *bids );
////void           (ALAPIENTRY *LPALSOURCEUNQUEUEBUFFERS)(ALuint sid, ALsizei numEntries, ALuint *bids );
//void	alGenBuffers( ALsizei n, ALuint* buffers );
//void	alDeleteBuffers( ALsizei n, const ALuint* buffers );
//ALboolean	alIsBuffer( ALuint bid );
//void	alBufferData( ALuint bid, ALenum format, const ALvoid* data, ALsizei size, ALsizei freq );
//void	alGetBufferf( ALuint bid, ALenum param, ALfloat* value );
//void	alGetBufferi( ALuint bid, ALenum param, ALint* value );
//void	alDopplerFactor( ALfloat value );
//void	alDopplerVelocity( ALfloat value );
////void           (ALAPIENTRY *LPALDISTANCEMODEL)( ALenum distanceModel );
//
//ALCcontext *	alcCloseDevice (ALCdevice *device, const ALCint *attrlist);
//ALCboolean	alcMakeContextCurrent( ALCcontext *context );
//void	alcProcessContext( ALCcontext *context );
//void	alcSuspendContext( ALCcontext *context );
//void	alcDestroyContext( ALCcontext *context );
//ALCcontext *	alcGetCurrentContext( ALCvoid );
//ALCdevice *	alcGetContextsDevice( ALCcontext *context );
////ALCdevice *    (ALCAPIENTRY *LPALCOPENDEVICE)( const ALCchar *devicename );
//ALCboolean	alcCloseDevice( ALCdevice *device );
//ALCenum	alcGetError( ALCdevice *device );
//ALCboolean	alcIsExtensionPresent( ALCdevice *device, const ALCchar *extname );
//void *	alcGetProcAddress(ALCdevice *device, const ALCchar *funcname );
//ALCenum	alcGetEnumValue(ALCdevice *device, const ALCchar *enumname );
////const ALCchar* (ALCAPIENTRY *LPALCGETSTRING)( ALCdevice *device, ALCenum param );
////void           (ALCAPIENTRY *LPALCGETINTEGERV)( ALCdevice *device, ALCenum param, ALCsizei size, ALCint *dest );

//LPALENABLE					alEnable	=	NULL;
//LPALDISABLE					alDisable	=	NULL;
//LPALISENABLED				alIsEnabled	=	NULL;
//LPALGETBOOLEAN				alGetBoolean	=	NULL;
//LPALGETINTEGER				alGetInteger	=	NULL;
//LPALGETFLOAT				alGetFloat	=	NULL;
//LPALGETDOUBLE				alGetDouble	=	NULL;
//LPALGETBOOLEANV				alGetBooleanv	=	NULL;
//LPALGETINTEGERV				alGetIntegerv	=	NULL;
//LPALGETFLOATV				alGetFloatv	=	NULL;
//LPALGETDOUBLEV				alGetDoublev	=	NULL;
//LPALGETSTRING				alGetString	=	NULL;
//LPALGETERROR				alGetError	=	NULL;
//LPALISEXTENSIONPRESENT		alIsExtensionPresent	=	NULL;
//LPALGETPROCADDRESS			alGetProcAddress	=	NULL;
//LPALGETENUMVALUE			alGetEnumValue	=	NULL;
//LPALLISTENERI				alListeneri	=	NULL;
//LPALLISTENERF				alListenerf	=	NULL;
//LPALLISTENER3F				alListener3f	=	NULL;
//LPALLISTENERFV				alListenerfv	=	NULL;
//LPALGETLISTENERI			alGetListeneri	=	NULL;
//LPALGETLISTENERF			alGetListenerf	=	NULL;
//LPALGETLISTENER3F			alGetListener3f	=	NULL;
//LPALGETLISTENERFV			alGetListenerfv	=	NULL;
//LPALGENSOURCES				alGenSources	=	NULL;
//LPALDELETESOURCES			alDeleteSources	=	NULL;
//LPALISSOURCE				alIsSource	=	NULL;
//LPALSOURCEI					alSourcei	=	NULL;
//LPALSOURCEF					alSourcef	=	NULL;
//LPALSOURCE3F				alSource3f	=	NULL;
//LPALSOURCEFV				alSourcefv	=	NULL;
//LPALGETSOURCEI				alGetSourcei	=	NULL;
//LPALGETSOURCEF				alGetSourcef	=	NULL;
//LPALGETSOURCEFV				alGetSourcefv	=	NULL;
//LPALSOURCEPLAYV				alSourcePlayv	=	NULL;
//LPALSOURCESTOPV				alSourceStopv	=	NULL;
//LPALSOURCEPLAY				alSourcePlay	=	NULL;
//LPALSOURCEPAUSE				alSourcePause	=	NULL;
//LPALSOURCESTOP				alSourceStop	=	NULL;
//LPALGENBUFFERS				alGenBuffers	=	NULL;
//LPALDELETEBUFFERS			alDeleteBuffers	=	NULL;
//LPALISBUFFER				alIsBuffer	=	NULL;
//LPALBUFFERDATA				alBufferData	=	NULL;
//LPALGETBUFFERI				alGetBufferi	=	NULL;
//LPALGETBUFFERF				alGetBufferf	=	NULL;
//LPALSOURCEQUEUEBUFFERS		alSourceQueueBuffers	=	NULL;
//LPALSOURCEUNQUEUEBUFFERS	alSourceUnqueueBuffers	=	NULL;
//LPALDISTANCEMODEL			alDistanceModel	=	NULL;
//LPALDOPPLERFACTOR			alDopplerFactor	=	NULL;
//LPALDOPPLERVELOCITY			alDopplerVelocity	=	NULL;
//LPALCGETSTRING				alcGetString	=	NULL;
//LPALCGETINTEGERV			alcGetIntegerv	=	NULL;
//LPALCOPENDEVICE				alcOpenDevice	=	NULL;
//LPALCCLOSEDEVICE			alcCloseDevice	=	NULL;
//LPALCCREATECONTEXT			alcCreateContext	=	NULL;
//LPALCMAKECONTEXTCURRENT		alcMakeContextCurrent	=	NULL;
//LPALCPROCESSCONTEXT			alcProcessContext	=	NULL;
//LPALCGETCURRENTCONTEXT		alcGetCurrentContext	=	NULL;
//LPALCGETCONTEXTSDEVICE		alcGetContextsDevice	=	NULL;
//LPALCSUSPENDCONTEXT			alcSuspendContext	=	NULL;
//LPALCDESTROYCONTEXT			alcDestroyContext	=	NULL;
//LPALCGETERROR				alcGetError	=	NULL;
//LPALCISEXTENSIONPRESENT		alcIsExtensionPresent	=	NULL;
//LPALCGETPROCADDRESS			alcGetProcAddress	=	NULL;
//LPALCGETENUMVALUE			alcGetEnumValue	=	NULL;
//} OPENALFNTABLE, *LPOPENALFNTABLE;
//#endif
//
//ALboolean LoadOAL10Library(char *szOALFullPathName, LPOPENALFNTABLE lpOALFnTable);
//ALvoid UnloadOAL10Library();
#endif

#endif