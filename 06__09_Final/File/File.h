#ifndef _FILE_H_
#define _FILE_H_

#include "..\Base\Base.h"

extern "C" class _FILE_API TFile {
public:
	TFile();
	virtual ~TFile();
private:
	void *file;
	char *filePathName;
	unsigned int accessMode;
	BOOL32 isError;
public:
	enum { 
		modeRead = 0x01,
		modeWrite = 0x10,
		modeReadWrite = 0x11,
		modeCreate = 0x00,
		typeText = 0x00010000,
		typeBinary = 0x00000000
	};

	enum {
		seek_set = 0x0,
		seek_cur = 0x1,
		seek_end = 0x2,
	};

public:
	BOOL32 Open(); //���� 
	void Close(); //�ر��� 
	BOOL32 Seek(unsigned int offset, unsigned int type); //�����ж�λ��ָ�����ַ� 
	BOOL32 IsEof(); //�����ļ�βʱ������ֵ 
	BOOL32 IsError(); //��������ʱ������ֵ 
	void Rewind(); //��λ�ļ���λ�����ļ���ʼ�� 
	unsigned int Read(const void *buffer, const unsigned int celllength, const unsigned int cells); //�����ж�ָ���������ַ� 
	unsigned int Write(const void *buffer, const unsigned int celllength, const unsigned int cells); //������дָ���������ַ� 
	void Flush();
	
	void GetFileNameASC(const char* fileName);
	void GetFilePathASC(const char* filePath);
	void GetFileTitleASC(const char* fileTitle);

	void SetFilePathNameASC(const char* fileName);
	void SetOpenMode(unsigned int mode);

	int GetLength();
	int GetPosition();
};

#endif