///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _BASE_EXPORT


#include "Type.h"
#include "Base.h"
#include "stdio.h"
#include "string.h"
#include "CRC32.h"


_BASE_API THashtable::THashtable() {
	for (int i = 0 ; i < ONE_BLOCK_SIZE ; i ++ ) {
		items[i].keyHash = 0;
		items[i].obj = NULL;
	}
	itemCount = 0;
	nextTable = NULL;
}

_BASE_API THashtable::~THashtable() {
	if ( nextTable != NULL ) {
		delete nextTable;
	}
}


BOOL32 _BASE_API THashtable::Add(TString &key, const IObject *obj) {
	if (key.GetHashCode() == 0) {
		return FALSE;
	}
	if (obj == NULL) {
		return FALSE;
	}
	const IObject *object = Get(key);
	if (object == NULL) {
		if (itemCount == ONE_BLOCK_SIZE) {
			if (nextTable == NULL) {
				nextTable = new THashtable();
			}
			return nextTable->Add(key, obj);
		}
	} else {
		return FALSE;	//	Already has
	}
	unsigned int i = 0;
	for (i = 0 ; i < ONE_BLOCK_SIZE ; i ++ ) {
		if(items[i].keyHash == 0) {
			break;
		}
	}
	items[i].key = key;
	items[i].keyHash = key.GetHashCode();
	items[i].obj = (IObject*)obj;
	itemCount ++;
	return TRUE;
}


const IObject _BASE_API *THashtable::Get(TString &key) {
	int keyHash = key.GetHashCode();
	if ( keyHash == 0 ) {
		return NULL;
	}
	for (unsigned int i = 0 ; i < ONE_BLOCK_SIZE ; i ++) {
		if ( keyHash == items[i].keyHash ) {
			if (items[i].key.Equals(key)) {
				return items[i].obj;
			}
		}
	}
	if (nextTable != NULL) {
		return nextTable->Get(key);
	}
	return NULL;
}



BOOL32 _BASE_API THashtable::Set(TString &key, const IObject *obj) {
	if (obj == NULL) {
		return FALSE;
	}
	int keyHash = key.GetHashCode();
	if ( keyHash == 0 ) {
		return FALSE;
	}
	for (unsigned int i = 0 ; i < ONE_BLOCK_SIZE ; i++) {
		if ( keyHash == items[i].keyHash ) {
			if (items[i].key.Equals(key)) {
				items[i].obj = (IObject*)obj;
				return TRUE;
			}
		}
	}
	if (nextTable != NULL) {
		return nextTable->Set(key, obj);
	}
	return FALSE;
}

BOOL32 _BASE_API THashtable::Del(TString &key) {
	int keyHash = key.GetHashCode();
	if ( keyHash == 0 ) {
		return FALSE;
	}
	for (unsigned int i = 0 ; i < ONE_BLOCK_SIZE ; i++) {
		if ( keyHash == items[i].keyHash ) {
			if (items[i].key.Equals(key)) {
				items[i].key = TString();	//	Empty String
				items[i].keyHash = 0;
				items[i].obj = NULL;
				itemCount --;
				return TRUE;
			}
		}
	}
	if (nextTable != NULL) {
		return nextTable->Del(key);
	}
	return FALSE;
}

unsigned int _BASE_API THashtable::GetCount() {
	unsigned int sum = itemCount ;
	if (nextTable != NULL) {
		return sum + nextTable->GetCount();
	}
	return sum;
}

const IObject _BASE_API *THashtable::operator[](TString &key) {
	return Get(key);
}

THashitem _BASE_API *THashtable::NextEmptyItem(unsigned int &index, THashtable *&loc) {
	THashtable *curtab = this;
	while (curtab != NULL) {
		for (unsigned int i1 = index ; i1 <  ONE_BLOCK_SIZE ; i1 ++) {
			if ( curtab->items[i1].keyHash == 0 ) {
				loc = curtab;
				index = i1;
				return &curtab->items[i1];
			}
		}
		curtab = curtab->nextTable;
	}
	return NULL;
}
THashitem _BASE_API *THashtable::NextNonEmptyItem(unsigned int &index, THashtable *&loc) {
	THashtable *curtab = this;
	while (curtab != NULL) {
		for (unsigned int i1 = index ; i1 <  ONE_BLOCK_SIZE ; i1 ++) {
			if ( curtab->items[i1].keyHash != 0 ) {
				loc = curtab;
				index = i1;
				return &curtab->items[i1];
			}
		}
		curtab = curtab->nextTable;
	}
	return NULL;
}

unsigned int _BASE_API THashtable::Pack() {
	THashitem *packhead = NULL;
	THashitem *packtail = NULL;
	THashtable *lpackhead = this;
	THashtable *lpacktail = this;
	for ( unsigned int i0 = 0, i1 = 0, i2 = 0 ; i0 < ONE_BLOCK_SIZE ; i0 ++ ) {
		lpackhead = this;
		if ( lpackhead->itemCount == ONE_BLOCK_SIZE ) {
			break;
		}
		packhead = NextEmptyItem(i1, lpackhead);
		i2 = i1;
		lpacktail = lpackhead;
		packtail = lpacktail->NextNonEmptyItem(i2, lpacktail);
		if ( ( packhead != NULL ) && ( packtail != NULL ) ) {
			packhead->key = packtail->key; packtail->key = TString();
			packhead->keyHash = packtail->keyHash; packtail->keyHash = 0;
			packhead->obj = packtail->obj; packtail->obj = NULL;
			packhead->objHash = packtail->objHash; packtail->objHash = 0;
			lpackhead->itemCount ++;
			lpacktail->itemCount --;
		}
	}
	if ( nextTable != NULL ) {
		nextTable->Pack();
	}
	THashtable *nt = this;
	while ( nt->nextTable != NULL ) {
		if ( nt->nextTable->itemCount == 0 ) {
			delete nt->nextTable;
			nt->nextTable = NULL;
		} else {
			nt = nt->nextTable;
		}
	}
	return GetCount();
}

char _BASE_API *THashtable::GetClassName() {
	return "THashtable";
}

int _BASE_API THashtable::GetClassCode() {
	return CLSID_THashtable;
}

int _BASE_API THashtable::GetHashCode() {
	int hashCode = (int)CRC32::GetCRC32(items, sizeof(THashitem)*ONE_BLOCK_SIZE);
	if (nextTable != NULL) {
		hashCode = hashCode ^ nextTable->GetHashCode();
	}
	return hashCode;
}

BOOL32 _BASE_API THashtable::IsInstanceof(const char* className) {
	if ( strcmp(className, "THashtable") == 0 ) {
		return TRUE;
	}
	return FALSE;
}
	
BOOL32 _BASE_API THashtable::IsEqualto(IObject &obj) {
	if(GetClassCode() == obj.GetClassCode()) {
		if(GetHashCode() == obj.GetHashCode()) {
			return TRUE;
		}
	}
	return FALSE;
}

void _BASE_API THashtable::Serialize(IIOStream &iio) {
}

void _BASE_API THashtable::Wait() {
}
void _BASE_API THashtable::Notify() {
}

