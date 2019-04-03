
#define _BASE_IMPORT
#define _MATHTOOL_IMPORT
#define _FILE_EXPORT

#include "Stdio.h"
#include "String.h"
#include "..\Base\Type.h"
#include "..\Base\Base.h"
#undef _ARRAY_API
#define _ARRAY_API _FILE_API
#include "..\Base\Array.h"
#include "..\Base\Array.hpp"
#include "..\Base\RefArray.h"
#include "..\Base\RefArray.hpp"
#include "Config.h"
extern "C" template _FILE_API TRefArray<TConfig>;
#include "ConfigFile.h"

_FILE_API TConfigFile::TConfigFile() {
	errorLine = 0;
	isError = FALSE;
	names.Resize(0);
	values.Resize(0);
}
_FILE_API TConfigFile::~TConfigFile() {
	names.DeleteAll();
	names.Resize(0);
	values.DeleteAll();
	values.Resize(0);
}
char _FILE_API *TConfigFile::GetClassName() {
	return "TConfigFile";
}
int _FILE_API TConfigFile::GetClassCode() {
	return CLSID_TConfigFile;
}
int _FILE_API TConfigFile::GetHashCode() {
	return 1;
}
BOOL32 _FILE_API TConfigFile::IsInstanceof(const char* className) {
	if ( strcmp("TConfigFile", className) == 0 ) {
		return TRUE;
	}
	if ( strcmp("IObject", className) == 0 ) {
		return TRUE;
	}
	return FALSE;
}
BOOL32 _FILE_API TConfigFile::IsEqualto(IObject &obj) {
	return FALSE;
}
void _FILE_API TConfigFile::Serialize(IIOStream &iio) {
	if ( iio.GetLoadStore() == IIOStream::load ) {
		unsigned short nonwidthspace = 0;
		iio.Read(&nonwidthspace, sizeof(unsigned short));
		if ( nonwidthspace == 0xFEFF ) {
		} else if ( nonwidthspace == 0xFFFE ) {
			iio.SetEndian(IIOStream::big_endian);
		}
		Parse(iio);
	} else {
		TString se(" = ");
		TString enter(";\r\n");
		TString oneline;
		TString l("[");
		TString r("]");
		unsigned short f = 0xFEFF;
		iio.Write(&f, sizeof(unsigned short));
		unsigned int cl = names.GetLength();
		for ( unsigned int i2 = 0 ; i2 < cl ; i2 ++ ) {
			oneline = l + names[i2] + r + enter;
			oneline.Write(iio, oneline.GetLength());
			TConfig *cv = &values[i2];
			unsigned int vl = cv->GetValues().GetLength();
			TRefArray<TString> &cnames = cv->GetNames();
			TRefArray<TString> &cvalues = cv->GetValues();
			for ( unsigned int i3 = 0 ; i3 < vl ; i3 ++ ) {
				oneline = cnames[i3] + se + cvalues[i3] + enter;
				oneline.Write(iio, oneline.GetLength());
			}			
		}
	}
}
void _FILE_API TConfigFile::Wait() {
}
void _FILE_API TConfigFile::Notify() {
}

TRefArray<TString> _FILE_API &TConfigFile::GetNames() {
	return names;
}
TRefArray<TConfig> _FILE_API &TConfigFile::GetValues() {
	return values;
}
TConfig _FILE_API &TConfigFile::GetValue(TString &name) {
	return *(TConfig*)nameIndices.Get(name);
}
BOOL32 _FILE_API TConfigFile::IsError(unsigned short &eline) {
	eline = errorLine;
	return isError;
}

inline int _IsSpace(unsigned short chr) {
	if ( chr == 0x0020 ) {
		return TRUE;
	}
	if ( chr == 0x000B ) {
		return TRUE;
	}
	return FALSE;
}

inline int _IsAZaz(unsigned short chr) {
	if ( ( chr >= 0x0041 ) && ( chr <= 0x005A ) ) {
		return TRUE;
	}
	if ( ( chr >= 0x0061 ) && ( chr <= 0x007A ) ) {
		return TRUE;
	}
	return FALSE;
}

inline int _IsAZaz_(unsigned short chr) {
	if ( ( chr >= 0x0041 ) && ( chr <= 0x005A ) ) {
		return TRUE;
	}
	if ( ( chr >= 0x0061 ) && ( chr <= 0x007A ) ) {
		return TRUE;
	}
	if ( chr == '_' ) {
		return TRUE;
	}
	return FALSE;
}

inline int _Is09(unsigned short chr) {
	if ( ( chr >= 0x0030 ) && ( chr <= 0x0039 ) ) {
		return TRUE;
	}
	return FALSE;
}

inline int _Is_(unsigned short chr) {
	if ( chr == '_' ) {
		return TRUE;
	}
	return FALSE;
}

inline int _IsEnter(unsigned short chr) {
	if ( chr == 0x000D ) {
		return TRUE;
	}
	if ( chr == 0x000A ) {
		return TRUE;
	}
	return FALSE;
}

void _FILE_API TConfigFile::Parse(IIOStream &iio) {
	unsigned short achar = 0;
	unsigned short oneline[256];
	unsigned short linecount = 0;
	unsigned short innerstate = 1;
	TConfig *current = NULL;
	TString *name = NULL;
	TString *value = NULL;
	oneline[linecount] = 0;
	while(!iio.IsEoF()){
		iio.Read(&achar, sizeof(unsigned short));
		if ( iio.IsEoF() ) {
			achar = '\n';
		}
		if ( achar == '\r' ) {
			continue;
		}	//	Filter '\r'
		if ( achar == '\n' ) {
			errorLine ++;
		}
		switch (innerstate) {
			case 1:
				{
					if ( _IsSpace(achar) ) {
						innerstate = 1;
					} else if ( _IsEnter(achar) ) {
						innerstate = 1;
					} else if ( achar == '[' ) {
						innerstate = 2;
					} else if ( achar == ';' ) {
						innerstate = 18;
					} else {
						innerstate = 0xFFFF;
					}
				}
				break;
			case 2:
				{
					if ( _IsSpace(achar) ) {
						innerstate = 2;
					} else if ( _IsAZaz_(achar) ) {
						linecount = 0;
						innerstate = 3;
						oneline[linecount] = achar;
						linecount ++;
					} else {
						innerstate = 0xFFFF;
					}
				}
				break;
			case 3:
				{
					if ( _IsAZaz_(achar) ) {
						innerstate = 3;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( _Is09(achar) ) {
						innerstate = 3;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( _IsSpace(achar) ) {
						innerstate = 4;
						oneline[linecount] = 0;
						linecount = 0;
					} else if ( achar == ']' ) {
						innerstate = 5;
						oneline[linecount] = 0;
						linecount = 0;
					} else {
						innerstate = 0xFFFF;
					}
				}
				break;
			case 4:
				{
					if ( _IsSpace(achar) ) {
						innerstate = 4;
					} else if ( achar == ']' ) {
						innerstate = 5;
					} else {
						innerstate = 0xFFFF;
					}
				}
				break;
			case 5:
				{
					current = new TConfig;
					values.Resize(values.GetLength() + 1);
					values.Set(values.GetLength() - 1, current);
					name = new TString(oneline);
					names.Resize(values.GetLength());
					names.Set(values.GetLength() - 1, name);
					nameIndices.Add(*name, current);
					if ( _IsEnter(achar) ) {
						innerstate = 6;
					} else if ( _IsSpace(achar) ) {
						innerstate = 17;
					} else if ( achar == ';' ) {
						innerstate = 14;
					} else {
						innerstate = 0xFFFF;
					}
				}
				break;
			case 6:
				{
					if ( _IsSpace(achar) ) {
						innerstate = 6;
					} else if ( _IsEnter(achar) ) {
						innerstate = 6;
					} else if ( _IsAZaz_(achar) ) {
						linecount = 0;
						innerstate = 7;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( achar == ';') {
						innerstate = 14;
					} else if ( achar == '[') {
						innerstate = 2;
					} else {
						innerstate = 0xFFFF;
					}
				}
				break;
			case 7:
				{
					if ( _IsAZaz_(achar) ) {
						innerstate = 7;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( _Is09(achar) ) {
						innerstate = 7;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( _IsSpace(achar) ) {
						innerstate = 8;
					} else if ( achar == '=' ) {
						innerstate = 9;
						oneline[linecount] = 0;
						current->GetNames().Resize(current->GetNames().GetLength() + 1);
						current->GetValues().Resize(current->GetValues().GetLength() + 1);
						name = new TString(oneline);
						linecount = 0;
					} else {
						innerstate = 0xFFFF;
					}
				}
				break;
			case 8:
				{
					if ( _IsSpace(achar) ) {
						innerstate = 8;
					} else if ( achar == '=' ) {
						innerstate = 9;
						oneline[linecount] = 0;
						current->GetNames().Resize(current->GetNames().GetLength() + 1);
						current->GetValues().Resize(current->GetValues().GetLength() + 1);
						name = new TString(oneline);
						linecount = 0;
					} else {
						innerstate = 0xFFFF;
					}
				}
				break;
			case 9:
				{
					if ( _IsSpace(achar) ) {
						innerstate = 9;
					} else if ( _IsAZaz_(achar) ) {
						linecount = 0;
						innerstate = 10;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( _Is09(achar) ) {
						linecount = 0;
						innerstate = 10;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( achar == '(' ) {
						linecount = 0;
						innerstate = 10;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( achar == ')' ) {
						linecount = 0;
						innerstate = 10;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( achar == ',' ) {
						linecount = 0;
						innerstate = 10;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( achar == '.' ) {
						linecount = 0;
						innerstate = 10;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( achar == '\\' ) {
						linecount = 0;
						innerstate = 10;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( achar == ':' ) {
						linecount = 0;
						innerstate = 10;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( achar == '-' ) {
						linecount = 0;
						innerstate = 10;
						oneline[linecount] = achar;
						linecount ++;
					} else {
						innerstate = 0xFFFF;
					}
				}
				break;
			case 10:
				{
					if ( _IsSpace(achar) ) {
						innerstate = 10;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( _IsAZaz_(achar) ) {
						innerstate = 10;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( _Is09(achar) ) {
						innerstate = 10;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( achar == '(' ) {
						innerstate = 10;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( achar == ')' ) {
						innerstate = 10;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( achar == ',' ) {
						innerstate = 10;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( achar == '.' ) {
						innerstate = 10;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( achar == '\\' ) {
						innerstate = 10;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( achar == ':' ) {
						innerstate = 10;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( achar == '-' ) {
						innerstate = 10;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( _IsEnter(achar) ) {
						innerstate = 11;
						oneline[linecount] = 0;
						value = new TString(oneline);
						current->GetNames().Set(current->GetNames().GetLength() - 1, name);
						current->GetValues().Set(current->GetValues().GetLength() - 1, value);
						current->GetNameIndices().Add(*name, value);
						linecount = 0;
					} else if ( achar == ';' ) {
						innerstate = 12;
						oneline[linecount] = 0;
						value = new TString(oneline);
						current->GetNames().Set(current->GetNames().GetLength() - 1, name);
						current->GetValues().Set(current->GetValues().GetLength() - 1, value);
						current->GetNameIndices().Add(*name, value);
						linecount = 0;
					} else {
						innerstate = 0xFFFF;
					}
				}
				break;
			case 11:
				{
					if ( _IsSpace(achar) ) {
						innerstate = 6;
					} else if ( _IsEnter(achar) ) {
						innerstate = 6;
					} else if ( _IsAZaz_(achar) ) {
						linecount = 0;
						innerstate = 7;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( achar == ';' ) {
						innerstate = 14;
					} else if ( achar == '[' ) {
						innerstate = 2;
					} else {
						innerstate = 0xFFFF;
					}
				}
				break;
			case 12:
				{
					if ( _IsEnter(achar) ) {
						innerstate = 16;
					} else {
						innerstate = 15;
					}
				}
				break;
			case 14:
				{
					if ( _IsEnter(achar) ) {
						innerstate = 16;
					} else {
						innerstate = 15;
					}
				}
				break;
			case 15:
				{
					if ( _IsEnter(achar) ) {
						innerstate = 16;
					} else {
						innerstate = 15;
					}
				}
				break;
			case 16:
				{
					if ( _IsSpace(achar) ) {
						innerstate = 6;
					} else if ( _IsEnter(achar) ) {
						innerstate = 6;
					} else if ( _IsAZaz_(achar) ) {
						linecount = 0;
						innerstate = 7;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( achar == '[' ) {
						innerstate = 2;
					} else if ( achar == ';' ) {
						innerstate = 14;
					} else {
						innerstate = 0xFFFF;
					}
				}
				break;
			case 17:
				{
					if ( _IsSpace(achar) ) {
						innerstate = 17;
					} else if ( _IsEnter(achar) ) {
						innerstate = 6;
					} else if ( achar == ';' ) {
						innerstate = 14;
					} else {
						innerstate = 0xFFFF;
					}
				}
				break;
			case 18:
				{
					if ( _IsEnter(achar) ) {
						innerstate = 1;
					} else {
						innerstate = 18;
					}
				}
				break;
			case 0xFFFF:
				{
					isError = TRUE;
				}
				break;
			default:
				{
				}
				break;
		}
	}
}
