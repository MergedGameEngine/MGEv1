#ifndef _FILEIOSTREAM_H_
#define _FILEIOSTREAM_H_

#include "File.h"

#define LOCAL_MACHINE_ENDIAN IIOStream::little_endian

extern "C" class _FILE_API TFileIOStream : public IIOStream {
public:
	TFileIOStream();
	TFileIOStream(TFile *file);
	virtual ~TFileIOStream();
public:
	void SetFile(TFile *file);
private:
	TFile *file;
	unsigned int endian;
	unsigned int loadstoreType;

private:
	void swapEndian(const void* buffer, unsigned int length);

public:
public:
	virtual BOOL32 Open();
	virtual void Close();
	virtual void SetEndian(unsigned int endian);
	virtual unsigned int GetEndian();
	virtual void SetLoadStore(unsigned int loadstore);
	virtual unsigned int GetLoadStore();
	virtual unsigned int Read(const void* buf, const unsigned int length);
	virtual unsigned int Write(const void* buf, const unsigned int length);
	virtual unsigned int ReadBuffer(const void* buf, const unsigned int cells, const unsigned int celllength);
	virtual unsigned int WriteBuffer(const void* buf, const unsigned int cells, const unsigned int celllength);
	virtual unsigned int Seek(unsigned int length);
	virtual unsigned int Seek(unsigned int begin, unsigned int length);
	virtual unsigned int GetPosition();
	virtual BOOL32 IsEoF();

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
