#ifndef _RENERERWIN_H_
#define _RENERERWIN_H_

void ChangeSize(GLsizei w, GLsizei h);
void RenderScene();
void Initialization();
void Init_SC(TShaderController &sc);
void LoadSingleTexture(const char * filepathname, TTextureObject &tar);
void Init_TC(TTextureController &tc);
void Init_LC(TLightController &lc);
void Init_MC(TMeshController &mc);
void Init_MDLC(TModelController &mdlc);
void Init_ALL();

extern bool isOneFrameFinished;
extern bool isShutDown;

class Sync : public TAnimationController {
public:
	Sync();
	virtual ~Sync();
public:
	virtual void Run();
	virtual void Flush(float delta);
public:
	unsigned int selector;
	unsigned int dselector;
	float dratio;
public:
};

class ANCSync : public TAnimator {
public:
	MSG		msg;
	HWND	hWnd;
	HDC		hDC;
	PAINTSTRUCT ps;
public:
	ANCSync();
	virtual ~ANCSync();
public:
	virtual void RendererHandler();
};

class CoreSync : public TCore {
public:
public:
	short _x;
	short _y;
	short _dx;
	short _dy;
	float _oha;
	float _ova;
	float _dist;
	Vector3f objpos;
	Vector3f bak;
public:
	CoreSync();
	virtual ~CoreSync();
public:
	virtual void OnMouseMove(short x, short y);
	virtual void OnKeyDown(unsigned char key);
	virtual void OnMouseWheel(short zdelta);
};

extern class Sync *ac;
extern class Sync *wac;
extern class ANCSync *ant;
extern class CoreSync *cs;
extern class TModelController *_mdlc;

#endif