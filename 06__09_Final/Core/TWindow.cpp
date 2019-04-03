///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _CORE_EXPORT

#define _MATHTOOL_IMPORT
#define _BASE_IMPORT
#define _FILE_IMPORT
#define _MODEL_IMPORT
#define _THREAD_IMPORT
#define _RENDERER_IMPORT

#include "string.h"
#include "../Base/Type.h"
#include "../Base/Base.h"
#define _ARRAY_API _CORE_API
#include "TWindow.hpp"

_CORE_API TWindow::TWindow() {
	rwLock.AttribInit();
	rwLock.Init();
}
_CORE_API TWindow::~TWindow() {
	rwLock.Destroy();
	rwLock.AttribDestroy();
	components.Resize(0);
}
char _CORE_API *TWindow::GetClassName() {
	return "TWindow";
}
int _CORE_API TWindow::GetClassCode() {
	return CLSID_TWindow;
}
int _CORE_API TWindow::GetHashCode() {
	return 1;
}
BOOL32 _CORE_API TWindow::IsInstanceof(const char* className) {
	if (strcmp("TWindow", className)) {
		return TRUE;
	}
	return TThread::IsInstanceof(className);
}
BOOL32 _CORE_API TWindow::IsEqualto(IObject &obj) {
	return FALSE;
}
void _CORE_API TWindow::Serialize(IIOStream &iio) {
}
void _CORE_API TWindow::Wait() {
}
void _CORE_API TWindow::Notify() {
}




void _CORE_API TWindow::PostMessage(TMessage &msg) {
}
void _CORE_API TWindow::MessageHandler(TMessage &msg) {
	unsigned int numcoms = 0;
	unsigned int i1 = 0;
	Command(msg);
	rwLock.ReadLock();
	numcoms = components.GetLength();
	for ( i1 = 0 ; i1 < numcoms ; i1 ++ ) {
		TWindow *com = &components[i1];
		if ( com != NULL ) {
			com->MessageHandler(msg);
		}
	}
	rwLock.Unlock();
}
void _CORE_API TWindow::AddComponent(TWindow &src) {
	rwLock.WriteLock();
	unsigned int l = components.GetLength() + 1;
	components.Resize(l);
	components.Set(l - 1, &src);
	rwLock.Unlock();
}

void _CORE_API TWindow::Command(TMessage &msg) {
	switch (msg.message) {
		case GEM_KEYDOWN:
			{
				OnKeyDown((unsigned char)msg.parameter);
			}
			break;
		case GEM_KEYUP:
			{
				OnKeyUp((unsigned char)msg.parameter);
			}
			break;
		case GEM_CHAR:
			{
				OnChar((unsigned short)msg.parameter);
			}
			break;
		case GEM_DEADCHAR:
			{
				OnDeadChar((unsigned short)msg.parameter);
			}
			break;
		case GEM_SYSKEYDOWN:
			{
				OnSysKeyDown((unsigned char)msg.parameter);
			}
			break;
		case GEM_SYSKEYUP:
			{
				OnSysKeyUp((unsigned char)msg.parameter);
			}
			break;
		case GEM_SYSCHAR:
			{
				OnSysChar((unsigned short)msg.parameter);
			}
			break;
		case GEM_SYSDEADCHAR:
			{
				OnSysDeadChar((unsigned short)msg.parameter);
			}
			break;
		case GEM_MOUSEMOVE:
			{
				short x = (short)(msg.parameter >> 16);
				short y = (short)msg.parameter;
				OnMouseMove(x, y);
			}
			break;
		case GEM_LBUTTONDOWN:
			{
				OnLeftButtonDown();
			}
			break;
		case GEM_LBUTTONUP:
			{
				OnLeftButtonUp();
			}
			break;
		case GEM_LBUTTONDBLCLK:
			{
				OnLeftButtonBoubleClick();
			}
			break;
		case GEM_RBUTTONDOWN:
			{
				OnRightButtonDown();
			}
			break;
		case GEM_RBUTTONUP:
			{
				OnRightButtonUp();
			}
			break;
		case GEM_RBUTTONDBLCLK:
			{
				OnRightButtonBoubleClick();
			}
			break;
		case GEM_MBUTTONDOWN:
			{
				OnMiddleButtonDown();
			}
			break;
		case GEM_MBUTTONUP:
			{
				OnMiddleButtonUp();
			}
			break;
		case GEM_MBUTTONDBLCLK:
			{
				OnMiddleButtonBoubleClick();
			}
			break;
		case GEM_MOUSEWHEEL:
			{
				OnMouseWheel((short)msg.parameter);
			}
			break;
		default:
			break;
	}
}

void _CORE_API TWindow::OnKeyDown(unsigned char key) {
}
void _CORE_API TWindow::OnKeyUp(unsigned char key) {
}
void _CORE_API TWindow::OnChar(unsigned short chr) {
}
void _CORE_API TWindow::OnDeadChar(unsigned short chr) {
}
void _CORE_API TWindow::OnSysKeyDown(unsigned char key) {
}
void _CORE_API TWindow::OnSysKeyUp(unsigned char key) {
}
void _CORE_API TWindow::OnSysChar(unsigned short chr) {
}
void _CORE_API TWindow::OnSysDeadChar(unsigned short chr) {
}


void _CORE_API TWindow::OnMouseMove(short x, short y) {
}
void _CORE_API TWindow::OnLeftButtonDown() {
}
void _CORE_API TWindow::OnLeftButtonUp() {
}
void _CORE_API TWindow::OnLeftButtonBoubleClick() {
}
void _CORE_API TWindow::OnRightButtonDown() {
}
void _CORE_API TWindow::OnRightButtonUp() {
}
void _CORE_API TWindow::OnRightButtonBoubleClick() {
}
void _CORE_API TWindow::OnMiddleButtonDown() {
}
void _CORE_API TWindow::OnMiddleButtonUp() {
}
void _CORE_API TWindow::OnMiddleButtonBoubleClick() {
}
void _CORE_API TWindow::OnMouseWheel(short zdelta) {
}
