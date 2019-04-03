///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _WAVEDATAOBJECT_H_
#define _WAVEDATAOBJECT_H_

extern "C" class _SOUND_API TWaveDataObject : public IObject {
public:
	TWaveDataObject();
	virtual ~TWaveDataObject();
public:
protected:
	unsigned long	ulRIFF;			//	RIFF chunk
	unsigned long	ulRIFFSize;
	char			szWAVE[5];

	char			szFormatName[5];//	FORMAT chunk
	unsigned long	ulChunkSize;	//	==	0x10
	unsigned short	usFormatTag;	//	Begin FMT
	unsigned short	usChannels;
	unsigned long	ulSamplesPerSec;
	unsigned long	ulAvgBytesPerSec;
	unsigned short	usBlockAlign;
	unsigned short	usBitsPerSample;//	End FMT

	char			szDataName[5];	//	DATA chunk
	unsigned long	ulDataSize;
	void			*buffer;
	
	char			szListName[5];	//	LIST chunk
	unsigned long	ulListSize;
	void			*listBuffer;

public:
	unsigned short GetFormatTag();
	int GetOpenALFormat();
	unsigned short GetNumChannels();
	unsigned int GetFrequency();
	unsigned int GetAverageBytesPerSecond();
	unsigned short GetNumBlockAlign();
	unsigned short GetBitsPerSample(); 
	const void *GetDataBuffer();
	unsigned int GetDataSize();
	const void *GetListBuffer();

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