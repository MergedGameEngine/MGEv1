
#include "ALee.h"

LPALENABLE					palEnable			=	NULL;
LPALDISABLE					palDisable			=	NULL;
LPALISENABLED				palIsEnabled		=	NULL;
LPALGETBOOLEAN				palGetBoolean		=	NULL;
LPALGETINTEGER				palGetInteger		=	NULL;
LPALGETFLOAT				palGetFloat			=	NULL;
LPALGETDOUBLE				palGetDouble		=	NULL;
LPALGETBOOLEANV				palGetBooleanv		=	NULL;
LPALGETINTEGERV				palGetIntegerv		=	NULL;
LPALGETFLOATV				palGetFloatv		=	NULL;
LPALGETDOUBLEV				palGetDoublev		=	NULL;
LPALGETSTRING				palGetString		=	NULL;
LPALGETERROR				palGetError			=	NULL;
LPALISEXTENSIONPRESENT		palIsExtensionPresent	=	NULL;
LPALGETPROCADDRESS			palGetProcAddress	=	NULL;
LPALGETENUMVALUE			palGetEnumValue		=	NULL;
LPALLISTENERI				palListeneri		=	NULL;
LPALLISTENERF				palListenerf		=	NULL;
LPALLISTENER3F				palListener3f		=	NULL;
LPALLISTENERFV				palListenerfv		=	NULL;
LPALGETLISTENERI			palGetListeneri		=	NULL;
LPALGETLISTENERF			palGetListenerf		=	NULL;
LPALGETLISTENER3F			palGetListener3f	=	NULL;
LPALGETLISTENERFV			palGetListenerfv	=	NULL;
LPALGENSOURCES				palGenSources		=	NULL;
LPALDELETESOURCES			palDeleteSources	=	NULL;
LPALISSOURCE				palIsSource			=	NULL;
LPALSOURCEI					palSourcei			=	NULL;
LPALSOURCEF					palSourcef			=	NULL;
LPALSOURCE3F				palSource3f			=	NULL;
LPALSOURCEFV				palSourcefv			=	NULL;
LPALGETSOURCEI				palGetSourcei		=	NULL;
LPALGETSOURCEF				palGetSourcef		=	NULL;
LPALGETSOURCEFV				palGetSourcefv		=	NULL;
LPALSOURCEPLAYV				palSourcePlayv		=	NULL;
LPALSOURCESTOPV				palSourceStopv		=	NULL;
LPALSOURCEPLAY				palSourcePlay		=	NULL;
LPALSOURCEPAUSE				palSourcePause		=	NULL;
LPALSOURCESTOP				palSourceStop		=	NULL;
LPALGENBUFFERS				palGenBuffers		=	NULL;
LPALDELETEBUFFERS			palDeleteBuffers	=	NULL;
LPALISBUFFER				palIsBuffer			=	NULL;
LPALBUFFERDATA				palBufferData		=	NULL;
LPALGETBUFFERI				palGetBufferi		=	NULL;
LPALGETBUFFERF				palGetBufferf		=	NULL;
LPALSOURCEQUEUEBUFFERS		palSourceQueueBuffers	=	NULL;
LPALSOURCEUNQUEUEBUFFERS	palSourceUnqueueBuffers	=	NULL;
LPALDISTANCEMODEL			palDistanceModel	=	NULL;
LPALDOPPLERFACTOR			palDopplerFactor	=	NULL;
LPALDOPPLERVELOCITY			palDopplerVelocity	=	NULL;
LPALCGETSTRING				palcGetString		=	NULL;
LPALCGETINTEGERV			palcGetIntegerv		=	NULL;
LPALCOPENDEVICE				palcOpenDevice		=	NULL;
LPALCCLOSEDEVICE			palcCloseDevice		=	NULL;
LPALCCREATECONTEXT			palcCreateContext	=	NULL;
LPALCMAKECONTEXTCURRENT		palcMakeContextCurrent	=	NULL;
LPALCPROCESSCONTEXT			palcProcessContext	=	NULL;
LPALCGETCURRENTCONTEXT		palcGetCurrentContext	=	NULL;
LPALCGETCONTEXTSDEVICE		palcGetContextsDevice	=	NULL;
LPALCSUSPENDCONTEXT			palcSuspendContext	=	NULL;
LPALCDESTROYCONTEXT			palcDestroyContext	=	NULL;
LPALCGETERROR				palcGetError		=	NULL;
LPALCISEXTENSIONPRESENT		palcIsExtensionPresent	=	NULL;
LPALCGETPROCADDRESS			palcGetProcAddress	=	NULL;
LPALCGETENUMVALUE			palcGetEnumValue	=	NULL;

// Effect objects
LPALGENEFFECTS				palGenEffects		=	NULL;
LPALDELETEEFFECTS			palDeleteEffects	=	NULL;
LPALISEFFECT				palIsEffect			=	NULL;
LPALEFFECTI					palEffecti			=	NULL;
LPALEFFECTIV				palEffectiv			=	NULL;
LPALEFFECTF					palEffectf			=	NULL;
LPALEFFECTFV				palEffectfv			=	NULL;
LPALGETEFFECTI				palGetEffecti		=	NULL;
LPALGETEFFECTIV				palGetEffectiv		=	NULL;
LPALGETEFFECTF				palGetEffectf		=	NULL;
LPALGETEFFECTFV				palGetEffectfv		=	NULL;

// Filter objects
LPALGENFILTERS				palGenFilters		=	NULL;
LPALDELETEFILTERS			palDeleteFilters	=	NULL;
LPALISFILTER				palIsFilter			=	NULL;
LPALFILTERI					palFilteri			=	NULL;
LPALFILTERIV				palFilteriv			=	NULL;
LPALFILTERF					palFilterf			=	NULL;
LPALFILTERFV				palFilterfv			=	NULL;
LPALGETFILTERI				palGetFilteri		=	NULL;
LPALGETFILTERIV				palGetFilteriv		=	NULL;
LPALGETFILTERF				palGetFilterf		=	NULL;
LPALGETFILTERFV				palGetFilterfv		=	NULL;

// Auxiliary slot object
LPALGENAUXILIARYEFFECTSLOTS		palGenAuxiliaryEffectSlots		=	NULL;
LPALDELETEAUXILIARYEFFECTSLOTS	palDeleteAuxiliaryEffectSlots	=	NULL;
LPALISAUXILIARYEFFECTSLOT		palIsAuxiliaryEffectSlot		=	NULL;
LPALAUXILIARYEFFECTSLOTI		palAuxiliaryEffectSloti			=	NULL;
LPALAUXILIARYEFFECTSLOTIV		palAuxiliaryEffectSlotiv		=	NULL;
LPALAUXILIARYEFFECTSLOTF		palAuxiliaryEffectSlotf			=	NULL;
LPALAUXILIARYEFFECTSLOTFV		palAuxiliaryEffectSlotfv		=	NULL;
LPALGETAUXILIARYEFFECTSLOTI		palGetAuxiliaryEffectSloti		=	NULL;
LPALGETAUXILIARYEFFECTSLOTIV	palGetAuxiliaryEffectSlotiv		=	NULL;
LPALGETAUXILIARYEFFECTSLOTF		palGetAuxiliaryEffectSlotf		=	NULL;
LPALGETAUXILIARYEFFECTSLOTFV	palGetAuxiliaryEffectSlotfv		=	NULL;

// XRAM Extension function pointer variables and enum values
LPEAXSETBUFFERMODE			eaxSetBufferMode	=	NULL;
LPEAXGETBUFFERMODE			eaxGetBufferMode	=	NULL;

// X-RAM Enum values
ALenum		eXRAMSize		=	0;
ALenum		eXRAMFree		=	0;
ALenum		eXRAMAuto		=	0; 
ALenum		eXRAMHardware	=	0; 
ALenum		eXRAMAccessible	=	0;

//

HMODULE g_hOpenALDLL = NULL;

ALboolean ALeeInit() {
	g_hOpenALDLL = LoadLibrary("openal32.dll");
	
	if (!g_hOpenALDLL) {
		return AL_FALSE;
	}

	palEnable = (LPALENABLE)GetProcAddress(g_hOpenALDLL, "alEnable");
	if (palEnable == NULL) {
		//OutputDebugString("Failed to retrieve 'alEnable' function address\n");
		return AL_FALSE;
	}
	palDisable = (LPALDISABLE)GetProcAddress(g_hOpenALDLL, "alDisable");
	if (palDisable == NULL) {
		//OutputDebugString("Failed to retrieve 'alDisable' function address\n");
		return AL_FALSE;
	}
	palIsEnabled = (LPALISENABLED)GetProcAddress(g_hOpenALDLL, "alIsEnabled");
	if (palIsEnabled == NULL) {
		//OutputDebugString("Failed to retrieve 'alIsEnabled' function address\n");
		return AL_FALSE;
	}
	palGetBoolean = (LPALGETBOOLEAN)GetProcAddress(g_hOpenALDLL, "alGetBoolean");
	if (palGetBoolean == NULL) {
		//OutputDebugString("Failed to retrieve 'alGetBoolean' function address\n");
		return AL_FALSE;
	}
	palGetInteger = (LPALGETINTEGER)GetProcAddress(g_hOpenALDLL, "alGetInteger");
	if (palGetInteger == NULL) {
		//OutputDebugString("Failed to retrieve 'alGetInteger' function address\n");
		return AL_FALSE;
	}
	palGetFloat = (LPALGETFLOAT)GetProcAddress(g_hOpenALDLL, "alGetFloat");
	if (palGetFloat == NULL) {
		//OutputDebugString("Failed to retrieve 'alGetFloat' function address\n");
		return AL_FALSE;
	}
	palGetDouble = (LPALGETDOUBLE)GetProcAddress(g_hOpenALDLL, "alGetDouble");
	if (palGetDouble == NULL) {
		//OutputDebugString("Failed to retrieve 'alGetDouble' function address\n");
		return AL_FALSE;
	}
	palGetBooleanv = (LPALGETBOOLEANV)GetProcAddress(g_hOpenALDLL, "alGetBooleanv");
	if (palGetBooleanv == NULL) {
		//OutputDebugString("Failed to retrieve 'alGetBooleanv' function address\n");
		return AL_FALSE;
	}
	palGetIntegerv = (LPALGETINTEGERV)GetProcAddress(g_hOpenALDLL, "alGetIntegerv");
	if (palGetIntegerv == NULL) {
		//OutputDebugString("Failed to retrieve 'alGetIntegerv' function address\n");
		return AL_FALSE;
	}
	palGetFloatv = (LPALGETFLOATV)GetProcAddress(g_hOpenALDLL, "alGetFloatv");
	if (palGetFloatv == NULL) {
		//OutputDebugString("Failed to retrieve 'alGetFloatv' function address\n");
		return AL_FALSE;
	}
	palGetDoublev = (LPALGETDOUBLEV)GetProcAddress(g_hOpenALDLL, "alGetDoublev");
	if (palGetDoublev == NULL) {
		//OutputDebugString("Failed to retrieve 'alGetDoublev' function address\n");
		return AL_FALSE;
	}
	palGetString = (LPALGETSTRING)GetProcAddress(g_hOpenALDLL, "alGetString");
	if (palGetString == NULL) {
		//OutputDebugString("Failed to retrieve 'alGetString' function address\n");
		return AL_FALSE;
	}
	palGetError = (LPALGETERROR)GetProcAddress(g_hOpenALDLL, "alGetError");
	if (palGetError == NULL) {
		//OutputDebugString("Failed to retrieve 'alGetError' function address\n");
		return AL_FALSE;
	}
	palIsExtensionPresent = (LPALISEXTENSIONPRESENT)GetProcAddress(g_hOpenALDLL, "alIsExtensionPresent");
	if (palIsExtensionPresent == NULL) {
		//OutputDebugString("Failed to retrieve 'alIsExtensionPresent' function address\n");
		return AL_FALSE;
	}
	palGetProcAddress = (LPALGETPROCADDRESS)GetProcAddress(g_hOpenALDLL, "alGetProcAddress");
	if (palGetProcAddress == NULL) {
		//OutputDebugString("Failed to retrieve 'alGetProcAddress' function address\n");
		return AL_FALSE;
	}
	palGetEnumValue = (LPALGETENUMVALUE)GetProcAddress(g_hOpenALDLL, "alGetEnumValue");
	if (palGetEnumValue == NULL) {
		//OutputDebugString("Failed to retrieve 'alGetEnumValue' function address\n");
		return AL_FALSE;
	}
	palListeneri = (LPALLISTENERI)GetProcAddress(g_hOpenALDLL, "alListeneri");
	if (palListeneri == NULL) {
		//OutputDebugString("Failed to retrieve 'alListeneri' function address\n");
		return AL_FALSE;
	}
	palListenerf = (LPALLISTENERF)GetProcAddress(g_hOpenALDLL, "alListenerf");
	if (palListenerf == NULL) {
		//OutputDebugString("Failed to retrieve 'alListenerf' function address\n");
		return AL_FALSE;
	}
	palListener3f = (LPALLISTENER3F)GetProcAddress(g_hOpenALDLL, "alListener3f");
	if (palListener3f == NULL) {
		//OutputDebugString("Failed to retrieve 'alListener3f' function address\n");
		return AL_FALSE;
	}
	palListenerfv = (LPALLISTENERFV)GetProcAddress(g_hOpenALDLL, "alListenerfv");
	if (palListenerfv == NULL) {
		//OutputDebugString("Failed to retrieve 'alListenerfv' function address\n");
		return AL_FALSE;
	}
	palGetListeneri = (LPALGETLISTENERI)GetProcAddress(g_hOpenALDLL, "alGetListeneri");
	if (palGetListeneri == NULL) {
		//OutputDebugString("Failed to retrieve 'alGetListeneri' function address\n");
		return AL_FALSE;
	}
	palGetListenerf =(LPALGETLISTENERF)GetProcAddress(g_hOpenALDLL, "alGetListenerf");
	if (palGetListenerf == NULL) {
		//OutputDebugString("Failed to retrieve 'alGetListenerf' function address\n");
		return AL_FALSE;
	}
	palGetListener3f = (LPALGETLISTENER3F)GetProcAddress(g_hOpenALDLL, "alGetListener3f");
	if (palGetListener3f == NULL) {
		//OutputDebugString("Failed to retrieve 'alGetListener3f' function address\n");
		return AL_FALSE;
	}
	palGetListenerfv = (LPALGETLISTENERFV)GetProcAddress(g_hOpenALDLL, "alGetListenerfv");
	if (palGetListenerfv == NULL) {
		//OutputDebugString("Failed to retrieve 'alGetListenerfv' function address\n");
		return AL_FALSE;
	}
	palGenSources = (LPALGENSOURCES)GetProcAddress(g_hOpenALDLL, "alGenSources");
	if (palGenSources == NULL) {
		//OutputDebugString("Failed to retrieve 'alGenSources' function address\n");
		return AL_FALSE;
	}
	palDeleteSources = (LPALDELETESOURCES)GetProcAddress(g_hOpenALDLL, "alDeleteSources");
	if (palDeleteSources == NULL) {
		//OutputDebugString("Failed to retrieve 'alDeleteSources' function address\n");
		return AL_FALSE;
	}
	palIsSource = (LPALISSOURCE)GetProcAddress(g_hOpenALDLL, "alIsSource");
	if (palIsSource == NULL) {
		//OutputDebugString("Failed to retrieve 'alIsSource' function address\n");
		return AL_FALSE;
	}
	palSourcei = (LPALSOURCEI)GetProcAddress(g_hOpenALDLL, "alSourcei");
	if (palSourcei == NULL) {
		//OutputDebugString("Failed to retrieve 'alSourcei' function address\n");
		return AL_FALSE;
	}
	palSourcef = (LPALSOURCEF)GetProcAddress(g_hOpenALDLL, "alSourcef");
	if (palSourcef == NULL) {
		//OutputDebugString("Failed to retrieve 'alSourcef' function address\n");
		return AL_FALSE;
	}
	palSource3f = (LPALSOURCE3F)GetProcAddress(g_hOpenALDLL, "alSource3f");
	if (palSource3f == NULL) {
		//OutputDebugString("Failed to retrieve 'alSource3f' function address\n");
		return AL_FALSE;
	}
	palSourcefv = (LPALSOURCEFV)GetProcAddress(g_hOpenALDLL, "alSourcefv");
	if (palSourcefv == NULL) {
		//OutputDebugString("Failed to retrieve 'alSourcefv' function address\n");
		return AL_FALSE;
	}
	palGetSourcei = (LPALGETSOURCEI)GetProcAddress(g_hOpenALDLL, "alGetSourcei");
	if (palGetSourcei == NULL) {
		//OutputDebugString("Failed to retrieve 'alGetSourcei' function address\n");
		return AL_FALSE;
	}
	palGetSourcef = (LPALGETSOURCEF)GetProcAddress(g_hOpenALDLL, "alGetSourcef");
	if (palGetSourcef == NULL) {
		//OutputDebugString("Failed to retrieve 'alGetSourcef' function address\n");
		return AL_FALSE;
	}
	palGetSourcefv = (LPALGETSOURCEFV)GetProcAddress(g_hOpenALDLL, "alGetSourcefv");
	if (palGetSourcefv == NULL) {
		//OutputDebugString("Failed to retrieve 'alGetSourcefv' function address\n");
		return AL_FALSE;
	}
	palSourcePlayv = (LPALSOURCEPLAYV)GetProcAddress(g_hOpenALDLL, "alSourcePlayv");
	if (palSourcePlayv == NULL) {
		//OutputDebugString("Failed to retrieve 'alSourcePlayv' function address\n");
		return AL_FALSE;
	}
	palSourceStopv = (LPALSOURCESTOPV)GetProcAddress(g_hOpenALDLL, "alSourceStopv");
	if (palSourceStopv == NULL) {
		//OutputDebugString("Failed to retrieve 'alSourceStopv' function address\n");
		return AL_FALSE;
	}
	palSourcePlay = (LPALSOURCEPLAY)GetProcAddress(g_hOpenALDLL, "alSourcePlay");
	if (palSourcePlay == NULL) {
		//OutputDebugString("Failed to retrieve 'alSourcePlay' function address\n");
		return AL_FALSE;
	}
	palSourcePause = (LPALSOURCEPAUSE)GetProcAddress(g_hOpenALDLL, "alSourcePause");
	if (palSourcePause == NULL) {
		//OutputDebugString("Failed to retrieve 'alSourcePause' function address\n");
		return AL_FALSE;
	}
	palSourceStop = (LPALSOURCESTOP)GetProcAddress(g_hOpenALDLL, "alSourceStop");
	if (palSourceStop == NULL) {
		//OutputDebugString("Failed to retrieve 'alSourceStop' function address\n");
		return AL_FALSE;
	}
	palGenBuffers = (LPALGENBUFFERS)GetProcAddress(g_hOpenALDLL, "alGenBuffers");
	if (palGenBuffers == NULL) {
		//OutputDebugString("Failed to retrieve 'alGenBuffers' function address\n");
		return AL_FALSE;
	}
	palDeleteBuffers = (LPALDELETEBUFFERS)GetProcAddress(g_hOpenALDLL, "alDeleteBuffers");
	if (palDeleteBuffers == NULL) {
		//OutputDebugString("Failed to retrieve 'alDeleteBuffers' function address\n");
		return AL_FALSE;
	}
	palIsBuffer = (LPALISBUFFER)GetProcAddress(g_hOpenALDLL, "alIsBuffer");
	if (palIsBuffer == NULL) {
		//OutputDebugString("Failed to retrieve 'alIsBuffer' function address\n");
		return AL_FALSE;
	}
	palBufferData = (LPALBUFFERDATA)GetProcAddress(g_hOpenALDLL, "alBufferData");
	if (palBufferData == NULL) {
		//OutputDebugString("Failed to retrieve 'alBufferData' function address\n");
		return AL_FALSE;
	}
	palGetBufferi = (LPALGETBUFFERI)GetProcAddress(g_hOpenALDLL, "alGetBufferi");
	if (palGetBufferi == NULL) {
		//OutputDebugString("Failed to retrieve 'alGetBufferi' function address\n");
		return AL_FALSE;
	}
	palGetBufferf = (LPALGETBUFFERF)GetProcAddress(g_hOpenALDLL, "alGetBufferf");
	if (palGetBufferf == NULL) {
		//OutputDebugString("Failed to retrieve 'alGetBufferf' function address\n");
		return AL_FALSE;
	}
	palSourceQueueBuffers = (LPALSOURCEQUEUEBUFFERS)GetProcAddress(g_hOpenALDLL, "alSourceQueueBuffers");
	if (palSourceQueueBuffers == NULL) {
		//OutputDebugString("Failed to retrieve 'alSourceQueueBuffers' function address\n");
		return AL_FALSE;
	}
	palSourceUnqueueBuffers = (LPALSOURCEUNQUEUEBUFFERS)GetProcAddress(g_hOpenALDLL, "alSourceUnqueueBuffers");
	if (palSourceUnqueueBuffers == NULL) {
		//OutputDebugString("Failed to retrieve 'alSourceUnqueueBuffers' function address\n");
		return AL_FALSE;
	}
	palDistanceModel = (LPALDISTANCEMODEL)GetProcAddress(g_hOpenALDLL, "alDistanceModel");
	if (palDistanceModel == NULL) {
		//OutputDebugString("Failed to retrieve 'alDistanceModel' function address\n");
		return AL_FALSE;
	}
	palDopplerFactor = (LPALDOPPLERFACTOR)GetProcAddress(g_hOpenALDLL, "alDopplerFactor");
	if (palDopplerFactor == NULL) {
		//OutputDebugString("Failed to retrieve 'alDopplerFactor' function address\n");
		return AL_FALSE;
	}
	palDopplerVelocity = (LPALDOPPLERVELOCITY)GetProcAddress(g_hOpenALDLL, "alDopplerVelocity");
	if (palDopplerVelocity == NULL) {
		//OutputDebugString("Failed to retrieve 'alDopplerVelocity' function address\n");
		return AL_FALSE;
	}
	palcGetString = (LPALCGETSTRING)GetProcAddress(g_hOpenALDLL, "alcGetString");
	if (palcGetString == NULL) {
		//OutputDebugString("Failed to retrieve 'alcGetString' function address\n");
		return AL_FALSE;
	}
	palcGetIntegerv = (LPALCGETINTEGERV)GetProcAddress(g_hOpenALDLL, "alcGetIntegerv");
	if (palcGetIntegerv == NULL) {
		//OutputDebugString("Failed to retrieve 'alcGetIntegerv' function address\n");
		return AL_FALSE;
	}
	palcOpenDevice = (LPALCOPENDEVICE)GetProcAddress(g_hOpenALDLL, "alcOpenDevice");
	if (palcOpenDevice == NULL) {
		//OutputDebugString("Failed to retrieve 'alcOpenDevice' function address\n");
		return AL_FALSE;
	}
	palcCloseDevice = (LPALCCLOSEDEVICE)GetProcAddress(g_hOpenALDLL, "alcCloseDevice");
	if (palcCloseDevice == NULL) {
		//OutputDebugString("Failed to retrieve 'alcCloseDevice' function address\n");
		return AL_FALSE;
	}
	palcCreateContext = (LPALCCREATECONTEXT)GetProcAddress(g_hOpenALDLL, "alcCreateContext");
	if (palcCreateContext == NULL) {
		//OutputDebugString("Failed to retrieve 'alcCreateContext' function address\n");
		return AL_FALSE;
	}
	palcMakeContextCurrent = (LPALCMAKECONTEXTCURRENT)GetProcAddress(g_hOpenALDLL, "alcMakeContextCurrent");
	if (palcMakeContextCurrent == NULL) {
		//OutputDebugString("Failed to retrieve 'alcMakeContextCurrent' function address\n");
		return AL_FALSE;
	}
	palcProcessContext = (LPALCPROCESSCONTEXT)GetProcAddress(g_hOpenALDLL, "alcProcessContext");
	if (palcProcessContext == NULL) {
		//OutputDebugString("Failed to retrieve 'alcProcessContext' function address\n");
		return AL_FALSE;
	}
	palcGetCurrentContext = (LPALCGETCURRENTCONTEXT)GetProcAddress(g_hOpenALDLL, "alcGetCurrentContext");
	if (palcGetCurrentContext == NULL) {
		//OutputDebugString("Failed to retrieve 'alcGetCurrentContext' function address\n");
		return AL_FALSE;
	}
	palcGetContextsDevice = (LPALCGETCONTEXTSDEVICE)GetProcAddress(g_hOpenALDLL, "alcGetContextsDevice");
	if (palcGetContextsDevice == NULL) {
		//OutputDebugString("Failed to retrieve 'alcGetContextsDevice' function address\n");
		return AL_FALSE;
	}
	palcSuspendContext = (LPALCSUSPENDCONTEXT)GetProcAddress(g_hOpenALDLL, "alcSuspendContext");
	if (palcSuspendContext == NULL) {
		//OutputDebugString("Failed to retrieve 'alcSuspendContext' function address\n");
		return AL_FALSE;
	}
	palcDestroyContext = (LPALCDESTROYCONTEXT)GetProcAddress(g_hOpenALDLL, "alcDestroyContext");
	if (palcDestroyContext == NULL) {
		//OutputDebugString("Failed to retrieve 'alcDestroyContext' function address\n");
		return AL_FALSE;
	}
	palcGetError = (LPALCGETERROR)GetProcAddress(g_hOpenALDLL, "alcGetError");
	if (palcGetError == NULL) {
		//OutputDebugString("Failed to retrieve 'alcGetError' function address\n");
		return AL_FALSE;
	}
	palcIsExtensionPresent = (LPALCISEXTENSIONPRESENT)GetProcAddress(g_hOpenALDLL, "alcIsExtensionPresent");
	if (palcIsExtensionPresent == NULL) {
		//OutputDebugString("Failed to retrieve 'alcIsExtensionPresent' function address\n");
		return AL_FALSE;
	}
	palcGetProcAddress = (LPALCGETPROCADDRESS)GetProcAddress(g_hOpenALDLL, "alcGetProcAddress");
	if (palcGetProcAddress == NULL) {
		//OutputDebugString("Failed to retrieve 'alcGetProcAddress' function address\n");
		return AL_FALSE;
	}
	palcGetEnumValue = (LPALCGETENUMVALUE)GetProcAddress(g_hOpenALDLL, "alcGetEnumValue");
	if (palcGetEnumValue == NULL) {
		//OutputDebugString("Failed to retrieve 'alcGetEnumValue' function address\n");
		return AL_FALSE;
	}

	return AL_TRUE;
}

ALboolean ALEFXInit() {
	ALCdevice *pDevice = NULL;
	ALCcontext *pContext = NULL;
	ALboolean bEFXSupport = AL_FALSE;

	pContext = palcGetCurrentContext();
	pDevice = palcGetContextsDevice(pContext);

	if (palcIsExtensionPresent(pDevice, (ALCchar*)ALC_EXT_EFX_NAME)) {
		// Get function pointers
		palGenEffects = (LPALGENEFFECTS)palGetProcAddress("alGenEffects");
		palDeleteEffects = (LPALDELETEEFFECTS)palGetProcAddress("alDeleteEffects");
		palIsEffect = (LPALISEFFECT)palGetProcAddress("alIsEffect");
		palEffecti = (LPALEFFECTI)palGetProcAddress("alEffecti");
		palEffectiv = (LPALEFFECTIV)palGetProcAddress("alEffectiv");
		palEffectf = (LPALEFFECTF)palGetProcAddress("alEffectf");
		palEffectfv = (LPALEFFECTFV)palGetProcAddress("alEffectfv");
		palGetEffecti = (LPALGETEFFECTI)palGetProcAddress("alGetEffecti");
		palGetEffectiv = (LPALGETEFFECTIV)palGetProcAddress("alGetEffectiv");
		palGetEffectf = (LPALGETEFFECTF)palGetProcAddress("alGetEffectf");
		palGetEffectfv = (LPALGETEFFECTFV)palGetProcAddress("alGetEffectfv");
		palGenFilters = (LPALGENFILTERS)palGetProcAddress("alGenFilters");
		palDeleteFilters = (LPALDELETEFILTERS)palGetProcAddress("alDeleteFilters");
		palIsFilter = (LPALISFILTER)palGetProcAddress("alIsFilter");
		palFilteri = (LPALFILTERI)palGetProcAddress("alFilteri");
		palFilteriv = (LPALFILTERIV)palGetProcAddress("alFilteriv");
		palFilterf = (LPALFILTERF)palGetProcAddress("alFilterf");
		palFilterfv = (LPALFILTERFV)palGetProcAddress("alFilterfv");
		palGetFilteri = (LPALGETFILTERI)palGetProcAddress("alGetFilteri");
		palGetFilteriv= (LPALGETFILTERIV)palGetProcAddress("alGetFilteriv");
		palGetFilterf = (LPALGETFILTERF)palGetProcAddress("alGetFilterf");
		palGetFilterfv= (LPALGETFILTERFV)palGetProcAddress("alGetFilterfv");
		palGenAuxiliaryEffectSlots = (LPALGENAUXILIARYEFFECTSLOTS)palGetProcAddress("alGenAuxiliaryEffectSlots");
		palDeleteAuxiliaryEffectSlots = (LPALDELETEAUXILIARYEFFECTSLOTS)palGetProcAddress("alDeleteAuxiliaryEffectSlots");
		palIsAuxiliaryEffectSlot = (LPALISAUXILIARYEFFECTSLOT)palGetProcAddress("alIsAuxiliaryEffectSlot");
		palAuxiliaryEffectSloti = (LPALAUXILIARYEFFECTSLOTI)palGetProcAddress("alAuxiliaryEffectSloti");
		palAuxiliaryEffectSlotiv = (LPALAUXILIARYEFFECTSLOTIV)palGetProcAddress("alAuxiliaryEffectSlotiv");
		palAuxiliaryEffectSlotf = (LPALAUXILIARYEFFECTSLOTF)palGetProcAddress("alAuxiliaryEffectSlotf");
		palAuxiliaryEffectSlotfv = (LPALAUXILIARYEFFECTSLOTFV)palGetProcAddress("alAuxiliaryEffectSlotfv");
		palGetAuxiliaryEffectSloti = (LPALGETAUXILIARYEFFECTSLOTI)palGetProcAddress("alGetAuxiliaryEffectSloti");
		palGetAuxiliaryEffectSlotiv = (LPALGETAUXILIARYEFFECTSLOTIV)palGetProcAddress("alGetAuxiliaryEffectSlotiv");
		palGetAuxiliaryEffectSlotf = (LPALGETAUXILIARYEFFECTSLOTF)palGetProcAddress("alGetAuxiliaryEffectSlotf");
		palGetAuxiliaryEffectSlotfv = (LPALGETAUXILIARYEFFECTSLOTFV)palGetProcAddress("alGetAuxiliaryEffectSlotfv");

		if (palGenEffects &&	
			palDeleteEffects && 
			palIsEffect && 
			palEffecti && 
			palEffectiv &&	
			palEffectf &&
			palEffectfv && 
			palGetEffecti && 
			palGetEffectiv && 
			palGetEffectf && 
			palGetEffectfv &&	
			palGenFilters &&
			palDeleteFilters && 
			palIsFilter && 
			palFilteri && 
			palFilteriv &&	
			palFilterf && 
			palFilterfv &&
			palGetFilteri &&	
			palGetFilteriv && 
			palGetFilterf && 
			palGetFilterfv && 
			palGenAuxiliaryEffectSlots &&
			palDeleteAuxiliaryEffectSlots &&	
			palIsAuxiliaryEffectSlot && 
			palAuxiliaryEffectSloti &&
			palAuxiliaryEffectSlotiv && 
			palAuxiliaryEffectSlotf && 
			palAuxiliaryEffectSlotfv &&
			palGetAuxiliaryEffectSloti && 
			palGetAuxiliaryEffectSlotiv && 
			palGetAuxiliaryEffectSlotf &&
			palGetAuxiliaryEffectSlotfv) 
		{
			bEFXSupport = AL_TRUE;
		}
	}

	return bEFXSupport;
}

ALboolean ALXRAMInit() {
	ALboolean bXRAM = AL_FALSE;
	
	if (palIsExtensionPresent("EAX-RAM") == AL_TRUE) {
		// Get X-RAM Function pointers
		eaxSetBufferMode = (EAXSetBufferMode)palGetProcAddress("EAXSetBufferMode");
		eaxGetBufferMode = (EAXGetBufferMode)palGetProcAddress("EAXGetBufferMode");

		if (eaxSetBufferMode && eaxGetBufferMode) {
			eXRAMSize = palGetEnumValue("AL_EAX_RAM_SIZE");
			eXRAMFree = palGetEnumValue("AL_EAX_RAM_FREE");
			eXRAMAuto = palGetEnumValue("AL_STORAGE_AUTOMATIC");
			eXRAMHardware = palGetEnumValue("AL_STORAGE_HARDWARE");
			eXRAMAccessible = palGetEnumValue("AL_STORAGE_ACCESSIBLE");

			if (eXRAMSize && eXRAMFree && eXRAMAuto && eXRAMHardware && eXRAMAccessible) {
				bXRAM = AL_TRUE;
			}
		}
	}

	return bXRAM;
}

//AL_API	void	AL_APIENTRY	alEnable( ALenum capability ) { if ( palEnable ) alEnable( capability ); };
//void	AL_APIENTRY	alDisable( ALenum capability ) { if ( palDisable ) alDisable( capability ); }; 
//ALboolean	AL_APIENTRY	alIsEnabled( ALenum capability ) { if ( palIsEnabled ); }; 
//const	ALchar	AL_APIENTRY	*  alGetString( ALenum param ) { if ( palGetString ); }; 
//void	AL_APIENTRY	alGetBooleanv( ALenum param, ALboolean* data ) { if ( palGetBooleanv ); }; 
//void	AL_APIENTRY	alGetIntegerv( ALenum param, ALint* data ) { if ( palGetIntegerv ); }; 
//void	AL_APIENTRY	alGetFloatv( ALenum param, ALfloat* data ) { if ( palGetFloatv ); }; 
//void	AL_APIENTRY	alGetDoublev( ALenum param, ALdouble* data ) { if ( palGetDoublev ); }; 
//ALboolean	AL_APIENTRY	alGetBoolean( ALenum param ) { if ( palGetBoolean ); }; 
//ALint	AL_APIENTRY	alGetInteger( ALenum param ) { if ( palGetInteger ); }; 
//ALfloat	AL_APIENTRY	alGetFloat( ALenum param ) { if ( palGetFloat ); }; 
//ALdouble	AL_APIENTRY	alGetDouble( ALenum param ) { if ( palGetDouble ); }; 
//ALenum	AL_APIENTRY	alGetError( void ) { if ( palGetError ); }; 
//ALboolean	AL_APIENTRY	alIsExtensionPresent(const ALchar* extname ) { if ( palIsExtensionPresent ); }; 
//void	AL_APIENTRY	*	alGetProcAddress( const ALchar* fname ) { if ( palGetProcAddress ); }; 
//ALenum	AL_APIENTRY	alGetEnumValue( const ALchar* ename ) { if ( palGetEnumValue ); }; 
//void	AL_APIENTRY	alListenerf( ALenum param, ALfloat value ) { if ( palListenerf ); }; 
//void	AL_APIENTRY	alListener3f( ALenum param, ALfloat value1, ALfloat value2, ALfloat value3 ) { if ( palListener3f ); }; 
//void	AL_APIENTRY	alListenerfv ALenum param, const ALfloat* values ) { if ( palListenerfv ); }; 
//void	AL_APIENTRY	alListeneri( ALenum param, ALint value ) { if ( palListeneri ); }; 
//void	AL_APIENTRY	alGetListenerf( ALenum param, ALfloat* value ) { if ( palGetListenerf ); }; 
//void	AL_APIENTRY	alGetListener3f( ALenum param, ALfloat *value1, ALfloat *value2, ALfloat *value3 ) { if ( palGetListener3f ); }; 
//void	AL_APIENTRY	alGetListenerfv( ALenum param, ALfloat* values ) { if ( palGetListenerfv ); }; 
//void	AL_APIENTRY	alGetListeneri( ALenum param, ALint* value ) { if ( palGetListeneri ); }; 
//void	AL_APIENTRY	alGenSources( ALsizei n, ALuint* sources ) { if ( palGenSources ); }; 
//void	AL_APIENTRY	alDeleteSources( ALsizei n, const ALuint* sources ) { if ( palDeleteSources ); }; 
//ALboolean	AL_APIENTRY	alIsSource( ALuint sid ) { if ( palIsSource ); }; 
//void	AL_APIENTRY	alSourcef( ALuint sid, ALenum param, ALfloat value) { if ( palSourcef ); }; 
//void	AL_APIENTRY	alSource3f( ALuint sid, ALenum param, ALfloat value1, ALfloat value2, ALfloat value3 ) { if ( palSource3f ); }; 
//void	AL_APIENTRY	alSourcefv( ALuint sid, ALenum param, const ALfloat* values ) { if ( palSourcefv ); }; 
//void	AL_APIENTRY	alSourcei( ALuint sid, ALenum param, ALint value) { if ( palSourcei ); }; 
//void	AL_APIENTRY	alGetSourcef( ALuint sid, ALenum param, ALfloat* value ) { if ( palGetSourcef ); }; 
////void           (ALAPIENTRY *LPALGETSOURCE3F)( ALuint sid, ALenum param, ALfloat* value1, ALfloat* value2, ALfloat* value3);
//void	AL_APIENTRY	alGetSourcefv( ALuint sid, ALenum param, ALfloat* values ) { if ( palGetSourcefv ); }; 
//void	AL_APIENTRY	alGetSourcei( ALuint sid, ALenum param, ALint* value ) { if ( palGetSourcei ); }; 
//void	AL_APIENTRY	alSourcePlayv( ALsizei ns, const ALuint *sids ) { if ( palSourcePlayv ); }; 
//void	AL_APIENTRY	alSourceStopv( ALsizei ns, const ALuint *sids ) { if ( palSourceStopv ); }; 
////void           (ALAPIENTRY *LPALSOURCEREWINDV)( ALsizei ns, const ALuint *sids );
////void           (ALAPIENTRY *LPALSOURCEPAUSEV)( ALsizei ns, const ALuint *sids );
//void	AL_APIENTRY	alSourcePlay( ALuint sid ) { if ( palSourcePlay ); }; 
//void	AL_APIENTRY	alSourceStop( ALuint sid ) { if ( palSourceStop ); }; 
////void           (ALAPIENTRY *LPALSOURCEREWIND)( ALuint sid );
//void	AL_APIENTRY	alSourcePause( ALuint sid ) { if ( palSourcePause ); }; 
////void           (ALAPIENTRY *LPALSOURCEQUEUEBUFFERS)(ALuint sid, ALsizei numEntries, const ALuint *bids );
////void           (ALAPIENTRY *LPALSOURCEUNQUEUEBUFFERS)(ALuint sid, ALsizei numEntries, ALuint *bids );
//void	AL_APIENTRY	alGenBuffers( ALsizei n, ALuint* buffers ) { if ( palGenBuffers ); }; 
//void	AL_APIENTRY	alDeleteBuffers( ALsizei n, const ALuint* buffers ) { if ( palDeleteBuffers ); }; 
//ALboolean	AL_APIENTRY	alIsBuffer( ALuint bid ) { if ( palIsBuffer ); }; 
//void	AL_APIENTRY	alBufferData( ALuint bid, ALenum format, const ALvoid* data, ALsizei size, ALsizei freq ) { if ( palBufferData ); }; 
//void	AL_APIENTRY	alGetBufferf( ALuint bid, ALenum param, ALfloat* value ) { if ( palGetBufferf ); }; 
//void	AL_APIENTRY	alGetBufferi( ALuint bid, ALenum param, ALint* value ) { if ( palGetBufferi ); }; 
//void	AL_APIENTRY	alDopplerFactor( ALfloat value ) { if ( palDopplerFactor ); }; 
//void	AL_APIENTRY	alDopplerVelocity( ALfloat value ) { if ( palDopplerVelocity ); }; 
////void           (ALAPIENTRY *LPALDISTANCEMODEL)( ALenum distanceModel );
//
//ALCcontext *	AL_APIENTRY	alcCloseDevice (ALCdevice *device, const ALCint *attrlist) { if ( palcCloseDevice ); }; 
//ALCboolean	AL_APIENTRY	alcMakeContextCurrent( ALCcontext *context ) { if ( palcMakeContextCurrent ); }; 
//void	AL_APIENTRY	alcProcessContext( ALCcontext *context ) { if ( palcProcessContext ); }; 
//void	AL_APIENTRY	alcSuspendContext( ALCcontext *context ) { if ( palcSuspendContext ); }; 
//void	AL_APIENTRY	alcDestroyContext( ALCcontext *context ) { if ( palcDestroyContext ); }; 
//ALCcontext *	AL_APIENTRY	alcGetCurrentContext( ALCvoid ) { if ( palcGetCurrentContext ); }; 
//ALCdevice *	AL_APIENTRY	alcGetContextsDevice( ALCcontext *context ) { if ( palcGetContextsDevice ); }; 
////ALCdevice *    (ALCAPIENTRY *LPALCOPENDEVICE)( const ALCchar *devicename );
//ALCboolean	AL_APIENTRY	alcCloseDevice( ALCdevice *device ) { if ( palcCloseDevice ); }; 
//ALCenum	AL_APIENTRY	alcGetError( ALCdevice *device ) { if ( palcGetError ); }; 
//ALCboolean	AL_APIENTRY	alcIsExtensionPresent( ALCdevice *device, const ALCchar *extname ) { if ( palcIsExtensionPresent ); }; 
//void *	AL_APIENTRY	alcGetProcAddress(ALCdevice *device, const ALCchar *funcname ) { if ( palcGetProcAddress ); }; 
//ALCenum	AL_APIENTRY	alcGetEnumValue(ALCdevice *device, const ALCchar *enumname ) { if ( palcGetEnumValue ); }; 
////const ALCchar* (ALCAPIENTRY *LPALCGETSTRING)( ALCdevice *device, ALCenum param );
////void           (ALCAPIENTRY *LPALCGETINTEGERV)( ALCdevice *device, ALCenum param, ALCsizei size, ALCint *dest );
