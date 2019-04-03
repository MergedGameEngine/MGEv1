// TTestThread.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"

#define _BASE_IMPORT
#define _MATHTOOL_IMPORT
#define _THREAD_IMPORT
#define _MODEL_IMPORT
#define _RENDERER_IMPORT
#define _FILE_IMPORT
#define _CORE_IMPORT

#include "../Base/Type.h"
#include "../Base/Base.h"
#define _ARRAY_API __declspec(dllimport)
#include "../Base/Array.h"
#include "../Base/RefArray.h"

#include "../File/File.h"
#include "../File/FileIOStream.h"
#include "../File/Config.h"
#include "../File/ConfigFile.h"
#include "../Thread/Thread.h"
#include "../SSE2Tool/SSE2Tool.h"
#include "../Model/ModelObject.h"
#include "../Model/BoneTreeNode.h"
#include "../Core/EventListener.h"
#include "../Core/EventProcessor.h"
#include "../Core/AnimationController.h"
#include "../Core/ModelController.h"
#include "../Core/Character.h"
#include "windows.h"

extern "C" template class _CORE_API TArray<TEvent>;
extern "C" template class _CORE_API TRefArray<TEventListener>;
extern "C" template class _BASE_API TRefArray<TString>;

class TH2 : public TThread {
public:
	TH2() {};
	virtual ~TH2() {};
public:
	virtual void Run() {
		unsigned int i1 = 0;
		for ( i1 = 0 ; i1 < 200 ; i1 ++ ) {
			printf ("%d\n", i1);
			Delay(0, 1000000);
		}
	}
};

int _tmain(int argc, _TCHAR* argv[]) {
	TH2 th;
	th.Start();
	th.Cancel();
	th.Join();

	return 0;
}

