///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _BASE_IMPORT
#define _SOUND_EXPORT

#include "string.h"
#include "ALee.h"
#undef GetClassName
#include "..\Base\Type.h"
#include "..\Base\Base.h"

#undef _ARRAY_API
#define _ARRAY_API _SOUND_API
#include "AudioDevice.hpp"

_SOUND_API TAudioDevice::TAudioDevice() {
}
_SOUND_API TAudioDevice::~TAudioDevice() {
}

char _SOUND_API *TAudioDevice::GetClassName() {
	return "TAudioDevice";
}
int _SOUND_API TAudioDevice::GetClassCode() {
	return CLSID_TAudioDevice;
}
int _SOUND_API TAudioDevice::GetHashCode() {
	return 1;
}
BOOL32 _SOUND_API TAudioDevice::IsInstanceof(const char* className) {
	if ( strcmp("TAudioDevice", className) == 0 ) {
		return TRUE;
	}
	if ( strcmp("IObject", className) == 0 ) {
		return TRUE;
	}
	return FALSE;
}
BOOL32 _SOUND_API TAudioDevice::IsEqualto(IObject &obj) {
	return FALSE;
}
void _SOUND_API TAudioDevice::Serialize(IIOStream &iio) {
}
void _SOUND_API TAudioDevice::Wait() {
}
void _SOUND_API TAudioDevice::Notify() {
}

TArray<TAudioDeviceInfo> _SOUND_API &TAudioDevice::GetDevices() {
	// grab function pointers for 1.0-API functions, and if successful proceed to enumerate all devices
	if (ALeeInit() == TRUE) {
		if (palcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT")) {
			char *deviceString = (char *)palcGetString(NULL, ALC_DEVICE_SPECIFIER);
			while (*deviceString != 0) {
				ALCdevice *device = palcOpenDevice(deviceString);
				if (device) {
					ALCcontext *context = palcCreateContext(device, NULL);
					if (context) {
						palcMakeContextCurrent(context);
						// if new actual device name isn't already in the list, then add it...
						const ALCchar *actualDeviceName = palcGetString(device, ALC_DEVICE_SPECIFIER);
						BOOL32 bNewName = TRUE;
						if ((bNewName) && (actualDeviceName != NULL) && (strlen(actualDeviceName) > 0)) {
							unsigned int i1 = devices.GetLength();
							devices.Resize(i1 + 1);
							devices[i1].bSelected = TRUE;
							strcpy(devices[i1].strDeviceName, actualDeviceName);
							palcGetIntegerv(device, ALC_MAJOR_VERSION, sizeof(int), &devices[i1].iMajorVersion);
							palcGetIntegerv(device, ALC_MINOR_VERSION, sizeof(int), &devices[i1].iMinorVersion);

							// Check for ALC Extensions
							devices[i1].pvstrExtensions = 0;
							if (palcIsExtensionPresent(device, "ALC_EXT_CAPTURE") == AL_TRUE) {
								devices[i1].pvstrExtensions |= 0x00000001;
							}
							if (palcIsExtensionPresent(device, "ALC_EXT_EFX") == AL_TRUE) {
								devices[i1].pvstrExtensions |= 0x00000002;
							}

							// Check for AL Extensions
							if (palIsExtensionPresent("AL_EXT_OFFSET") == AL_TRUE) {
								devices[i1].pvstrExtensions |= 0x00000004;
							}

							if (palIsExtensionPresent("AL_EXT_LINEAR_DISTANCE") == AL_TRUE) {
								devices[i1].pvstrExtensions |= 0x00000008;
							}
							if (palIsExtensionPresent("AL_EXT_EXPONENT_DISTANCE") == AL_TRUE) {
								devices[i1].pvstrExtensions |= 0x00000010;
							}
							if (palIsExtensionPresent("EAX2.0") == AL_TRUE) {
								devices[i1].pvstrExtensions |= 0x00000100;
							}
							if (palIsExtensionPresent("EAX3.0") == AL_TRUE) {
								devices[i1].pvstrExtensions |= 0x00000200;
							}
							if (palIsExtensionPresent("EAX4.0") == AL_TRUE) {
								devices[i1].pvstrExtensions |= 0x00000400;
							}
							if (palIsExtensionPresent("EAX5.0") == AL_TRUE) {
								devices[i1].pvstrExtensions |= 0x00000800;
							}
							if (palIsExtensionPresent("EAX-RAM") == AL_TRUE) {
								devices[i1].pvstrExtensions |= 0x00001000;
							}

							// Get Source Count
							devices[i1].uiSourceCount = GetMaxNumSources();
						}
						palcMakeContextCurrent(NULL);
						palcDestroyContext(context);
					}
					palcCloseDevice(device);
				}
				deviceString += strlen(deviceString) + 1;
			}
		}
	}

	return devices;
}

unsigned int _SOUND_API TAudioDevice::GetMaxNumSources() {
	ALuint *uiSources = new ALuint[1024];
	unsigned int iSourceCount = 0;

	// Clear AL Error Code
	palGetError();

	// Generate up to 256 Sources, checking for any errors
	for ( iSourceCount = 0 ; iSourceCount < 1024 ; iSourceCount ++ ) {
		palGenSources( 1 , &uiSources[iSourceCount] );
		if (palGetError() != AL_NO_ERROR) {
			break;
		}
	}

	// Release the Sources
	palDeleteSources(iSourceCount, uiSources);
	if (palGetError() != AL_NO_ERROR) {
		for (unsigned int i = 0; i < 1024; i++) {
			palDeleteSources(1, &uiSources[i]);
		}
	}
	
	delete []uiSources;
	return iSourceCount;
}

ALboolean _SOUND_API TAudioDevice::Open(unsigned int idx) {
	ALCcontext *pContext = NULL;
	ALCdevice *pDevice = NULL;
	ALboolean bReturn = AL_FALSE;

	if ( idx < devices.GetLength())	{
		pDevice = palcOpenDevice(devices[idx].strDeviceName);
		if (pDevice) {
			pContext = alcCreateContext(pDevice, NULL);
			if (pContext) {
				palcMakeContextCurrent(pContext);
				bReturn = AL_TRUE;
			} else {
				palcCloseDevice(pDevice);
			}
		}
	}

	return bReturn;
}

ALboolean _SOUND_API TAudioDevice::Close() {
	ALCcontext *pContext;
	ALCdevice *pDevice;

	pContext = palcGetCurrentContext();
	pDevice = palcGetContextsDevice(pContext);
	
	palcMakeContextCurrent(NULL);
	palcDestroyContext(pContext);
	palcCloseDevice(pDevice);

	return AL_TRUE;
}
