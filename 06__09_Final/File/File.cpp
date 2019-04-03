
#define _BASE_IMPORT
#define _FILE_EXPORT

#include "File.h"
#include "Stdio.h"
#include "String.h"

_FILE_API TFile::TFile() {
	file = NULL;
	accessMode = TFile::modeRead;
	filePathName = NULL;
	isError = TRUE;
}
_FILE_API TFile::~TFile() {
	if (file != NULL) {
		fclose((FILE*)file);
		file = NULL;
	}
	if ( filePathName != NULL ) {
		delete filePathName;
		filePathName = NULL;
	}
}


/**
*����
*/
BOOL32 _FILE_API TFile::Open() {
	if (filePathName == NULL) {
		return FALSE;
	}
	switch (accessMode) {
		case TFile::modeRead | TFile::typeBinary :
			file = fopen(filePathName, "rb");
			break;
		case TFile::modeWrite | TFile::typeBinary :
			file = fopen(filePathName, "wb");
			break;
		case TFile::modeReadWrite | TFile::typeBinary :
			file = fopen(filePathName, "r+b");
			break;
		case TFile::modeCreate | TFile::typeBinary :
			file = fopen(filePathName, "w+b");
			break;
		case TFile::modeRead | TFile::typeText :
			file = fopen(filePathName, "rt");
			break;
		case TFile::modeWrite | TFile::typeText :
			file = fopen(filePathName, "wt");
			break;
		case TFile::modeReadWrite | TFile::typeText :
			file = fopen(filePathName, "r+t");
			break;
		case TFile::modeCreate | TFile::typeText :
			file = fopen(filePathName, "w+t");
			break;
		default:
			return FALSE;
	}
	if (file == NULL) {
		isError = TRUE;
		return FALSE;
	}
	return TRUE;
}

/**
*�ر��� 
*/
void _FILE_API TFile::Close() {
	if ( file == NULL ) {
		return;
	}
	if (fclose((FILE*)file) == 0) {
		isError = FALSE;
	} else {
		file = NULL;
		isError = TRUE;
	}
	if ( filePathName != NULL ) {
		delete filePathName;
		filePathName = NULL;
	}
}

/**
*�����ж�λ��ָ�����ַ� 
*/
BOOL32 _FILE_API TFile::Seek(unsigned int offset, unsigned int type) {
	if (fseek((FILE*)file, offset, type) == 0) {
		isError = FALSE;
		return TRUE;
	} else {
		isError = TRUE;
		return FALSE;
	}
}

/**
*�����ļ�βʱ������ֵ 
*/
BOOL32 _FILE_API TFile::IsEof() {
	if ( feof((FILE*)file) ) {
		return TRUE;
	} else {
		return FALSE;
	}
}

/**
*��������ʱ������ֵ 
*/
BOOL32 _FILE_API TFile::IsError() {
	return isError;
}

/**
*��λ�ļ���λ�����ļ���ʼ�� 
*/
void _FILE_API TFile::Rewind() {
	rewind((FILE*)file);
}

/**
*�����ж�ָ���������ַ� 
*/
unsigned int _FILE_API TFile::Read(const void *buffer, const unsigned int celllength, const unsigned int cells) {
	return fread((void*)buffer, celllength, cells, (FILE*)file);
}

/**
*������дָ���������ַ� 
*/
unsigned int _FILE_API TFile::Write(const void *buffer, const unsigned int celllength, const unsigned int cells) {
	return fwrite(buffer, celllength, cells, (FILE*)file);
}

/**
*
*/
void _FILE_API TFile::Flush() {
	fflush((FILE*)file);
}
	
void _FILE_API TFile::GetFileNameASC(const char* fileName) {
}
void _FILE_API TFile::GetFilePathASC(const char* filePath) {
}
void _FILE_API TFile::GetFileTitleASC(const char* fileTitle) {
}

void _FILE_API TFile::SetFilePathNameASC(const char* fileName) {
	if (fileName != NULL ) {
		filePathName = new char[strlen(fileName) + 1];
		strcpy(filePathName, fileName);
	}
}

void _FILE_API TFile::SetOpenMode(unsigned int mode) {
	accessMode = mode;
}

int _FILE_API TFile::GetLength() {
	if ( file!= NULL ) {
		return ((FILE*)file)->_bufsiz;
	}
	return 0;
}
int _FILE_API TFile::GetPosition() {
	return (int)ftell((FILE*)file);
}

