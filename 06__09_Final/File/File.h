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
	BOOL32 Open(); //打开流 
	void Close(); //关闭流 
	BOOL32 Seek(unsigned int offset, unsigned int type); //在流中定位到指定的字符 
	BOOL32 IsEof(); //到达文件尾时返回真值 
	BOOL32 IsError(); //发生错误时返回其值 
	void Rewind(); //复位文件定位器到文件开始处 
	unsigned int Read(const void *buffer, const unsigned int celllength, const unsigned int cells); //从流中读指定个数的字符 
	unsigned int Write(const void *buffer, const unsigned int celllength, const unsigned int cells); //向流中写指定个数的字符 
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