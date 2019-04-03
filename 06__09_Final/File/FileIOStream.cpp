#define _BASE_IMPORT
#define _FILE_EXPORT

#include "FileIOStream.h"
#include "String.h"

_FILE_API TFileIOStream::TFileIOStream() {
	file = NULL;
}
_FILE_API TFileIOStream::TFileIOStream(TFile *f) {
	file = f;
}

_FILE_API TFileIOStream::~TFileIOStream() {
}

void _FILE_API TFileIOStream::SetFile(TFile *f) {
	file = f;
}


BOOL32 _FILE_API TFileIOStream::Open() {
	if ( file != NULL ) {
		return file->Open();
	} else {
		return FALSE;
	}
}
void _FILE_API TFileIOStream::Close() {
	if ( file != NULL ) {
		file->Close();
		file = NULL;
	}
}
void _FILE_API TFileIOStream::SetEndian(unsigned int e) {
	if ( ( e == TFileIOStream::big_endian ) || ( e == TFileIOStream::little_endian ) ) {
		endian = e;
	} else {
		endian = TFileIOStream::big_endian;
	}
}
unsigned int _FILE_API TFileIOStream::GetEndian() {
	return endian;
}
void _FILE_API TFileIOStream::SetLoadStore(unsigned int ls) {
	if ( ( ls == TFileIOStream::load ) || ( ls == TFileIOStream::store ) ) {
		loadstoreType = ls;
	} else {
		loadstoreType = TFileIOStream::load;
	}
}
unsigned int _FILE_API TFileIOStream::GetLoadStore() {
	return loadstoreType;
}

void _FILE_API TFileIOStream::swapEndian(const void* buffer, unsigned int length) {
	unsigned char* buf = (unsigned char*)buffer;
	unsigned char temp;
	int l = length / 2;
	for (int i = 0 ; i < l ; i ++ ) {
		temp = buf[i];
		buf[i] = buf[length - i - 1];
		buf[length - i - 1] = temp;
	}
}

unsigned int _FILE_API TFileIOStream::Read(const void* buf, const unsigned int length) {
	if ( file == NULL ) { return 0xFFFFFFFF;}
	int retcode = (int)file->Read(buf, length, 1);
	if (endian != LOCAL_MACHINE_ENDIAN) {
		swapEndian(buf, length);
	}
	return retcode;
}
unsigned int _FILE_API TFileIOStream::Write(const void* buf, const unsigned int length) {
	if ( file == NULL ) { return 0xFFFFFFFF;}
	if (endian != LOCAL_MACHINE_ENDIAN) {
		swapEndian(buf, length);
	}
	return (int)file->Write(buf, length, 1);
}
unsigned int _FILE_API TFileIOStream::ReadBuffer(const void* buf, const unsigned int cells, const unsigned int celllength) {
	if ( file == NULL ) { return 0xFFFFFFFF;}
	int retcode = file->Read(buf, celllength, cells);
	if (endian != LOCAL_MACHINE_ENDIAN) {
		unsigned char * pBuf = (unsigned char * )buf;
		for ( unsigned int i = 0 ; i < cells ; i ++ ) {
			swapEndian(&(pBuf[celllength * i]), celllength);
		}
	}
	return retcode;
}
unsigned int _FILE_API TFileIOStream::WriteBuffer(const void* buf, const unsigned int cells, const unsigned int celllength) {
	if ( file == NULL ) { return 0xFFFFFFFF;}
	if (endian != LOCAL_MACHINE_ENDIAN) {
		unsigned char * pBuf = (unsigned char * )buf;
		for ( unsigned int i = 0 ; i < cells ; i ++ ) {
			swapEndian(&(pBuf[celllength * i]), celllength);
		}
	}
	return file->Write(buf, celllength, cells);
}
unsigned int _FILE_API TFileIOStream::Seek(unsigned int length) {
	if ( file == NULL ) { return 0xFFFFFFFF;}
	return (int)file->Seek(length, TFile::seek_cur);
}
unsigned int _FILE_API TFileIOStream::Seek(unsigned int begin, unsigned int length) {
	if ( file == NULL ) { return 0xFFFFFFFF;}
	file->Seek(begin, TFile::seek_set);
	return (int)file->Seek(length, TFile::seek_cur);
}
BOOL32 _FILE_API TFileIOStream::IsEoF() {
	if ( file == NULL ) { return 0xFFFFFFFF;}
	return file->IsEof();
}

unsigned int _FILE_API TFileIOStream::GetPosition() {
	if ( file == NULL ) { return 0xFFFFFFFF;}
	return file->GetPosition();
}

char _FILE_API *TFileIOStream::GetClassName() {
	return "TFileIOStream";
}
int _FILE_API TFileIOStream::GetClassCode() {
	return CLSID_TFileIOStream;
}
int _FILE_API TFileIOStream::GetHashCode() {
	return 1;
}
BOOL32 _FILE_API TFileIOStream::IsInstanceof(const char* className) {
	if ( strcmp("TFileIOStream", className) == 0 ) {
		return TRUE;
	}
	return FALSE;
}
BOOL32 _FILE_API TFileIOStream::IsEqualto(IObject &obj) {
	return FALSE;
}
void _FILE_API TFileIOStream::Serialize(IIOStream &iio) {
}
void _FILE_API TFileIOStream::Wait() {
}
void _FILE_API TFileIOStream::Notify() {
}