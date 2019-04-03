///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

//
//		Sound Package import
//

#ifndef _SOUNDIMPORT_H_
#define _SOUNDIMPORT_H_

#include "../Sound/AudioDevice.h"

#include "../Sound/WaveDataObject.h"
#include "../Sound/WaveSourceObject.h"
#include "../Sound/WaveSourceController.h"

#ifdef _ARRAY_API
#ifdef TArray
extern "C" template class _SOUND_API TArray<TAudioDeviceInfo>;
#endif
#ifdef TRefArray
extern "C" template class _SOUND_API TRefArray<TWaveDataObject>;
extern "C" template class _SOUND_API TRefArray<TWaveSourceObject>;
extern "C" template class _SOUND_API TRefArray<TWaveSourceController>;
#endif
#endif

#endif