///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _AUDIODEVICE_H_
#define _AUDIODEVICE_H_

struct TAudioDeviceInfo {
	char			strDeviceName[64];
	int				iMajorVersion;
	int				iMinorVersion;
	unsigned int	uiSourceCount;
	unsigned int	pvstrExtensions;
	BOOL8			bSelected;
};

extern "C" class _SOUND_API TAudioDevice : public IObject {
public:
	TAudioDevice();
	virtual ~TAudioDevice();
public:
	TArray<TAudioDeviceInfo> devices;
	TAudioDeviceInfo *currentDevice;
public:
	TArray<TAudioDeviceInfo> &GetDevices();
	unsigned int GetMaxNumSources();
	ALboolean Open(unsigned int idx);
	ALboolean Close();
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