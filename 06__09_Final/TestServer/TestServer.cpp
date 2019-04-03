// TestServer.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"

#define _BASE_IMPORT
#define _MATHTOOL_IMPORT
#define _THREAD_IMPORT
#define _NETWORK_IMPORT
#define _CORE_IMPORT
#include "stdio.h"
#include "winsock.h"
#undef GetClassName
#undef SetPort
#include "..\Base\Type.h"
#include "..\Base\Base.h"
#include "..\MathTool\MathTool.h"
#include "..\Thread\Thread.h"
#include "..\Network\TSocket.h"
#undef _ARRAY_API
#define _ARRAY_API _BASE_API
#include "..\Base\Array.h"
#include "..\Base\RefArray.h"
#include "..\Network\Packet.h"
#include "..\Network\ClientHandler.h"
#include "..\Network\Server.h"
#include "..\Core\EventListener.h"
#include "..\Core\EventProcessor.h"

struct PEvent {
	short uid;
	short actionCode;
	float hp;
	float exp;
	Vector3f position;
};

class EPlayer : public TEventListener {
public:
	EPlayer(){
		isDead = false; 
		isShield = false; 
		pevent.actionCode = 0; 
		pevent.exp = 0.0f; 
		pevent.hp = 100.0f;
	};
	virtual ~EPlayer(){};
	PEvent pevent;
	bool isDead;
	bool isShield;
public:
	virtual void EventHandler(TEvent &e) {
		if ( e.subject != NULL ) {
			if ( e.subject->GetClassCode() == 8192 ) {
				EPlayer *subject = (EPlayer*)e.subject;
				switch (e.actionCode) {
					case 20:
						{
							if ( uid == e.uid ) {
								if ( !isDead ) {
									pevent.position += Vector3f(0.0f, 0.5f, 0.0f);
								}
							}
						}
						break;
					case 21:
						{
							if ( uid == e.uid ) {
								if ( !isDead ) {
									pevent.position -= Vector3f(0.0f, 0.5f, 0.0f);
								}
							}
						}
						break;
					case 22:
						{
							if ( uid == e.uid ) {
								if ( !isDead ) {
									pevent.position -= Vector3f(0.5f, 0.0f, 0.0f);
								}
							}
						}
						break;
					case 23:
						{
							if ( uid == e.uid ) {
								if ( !isDead ) {
									pevent.position += Vector3f(0.5f, 0.0f, 0.0f);
								}
							}
						}
						break;
					case 24:
						{
							if ( uid == e.uid ) {
							} else {
								if ( (!isDead) && (!isShield) ) {
									if ( (!subject->isDead) && (!subject->isShield) ) {
										if ( (pevent.position - subject->pevent.position).Magnitude() <= 1.0f ) {
											TEvent e;
											e.uid = uid;
											e.actionCode = 25;
											e.subject = this;
											eventProc->PostEvent(e);
											subject->pevent.exp += 0.5f;
										}
									}
								}
							}
						}
						break;
					case 25:
						{
							if ( uid == e.uid ) {
								if ( isDead ) {
									pevent.hp = 0.0f;
								} else {
									pevent.hp -= 0.5f;
									if ( pevent.hp <= 0.0f ) {
										isDead = true;
										TEvent e;
										e.uid = uid;
										e.actionCode = 28;
										e.subject = this;
										eventProc->PostEvent(e);
									}
								}
							} else {
							}
						}
						break;
					case 26:
						{
							if ( uid == e.uid ) {
								if ( !isDead ) {
									isShield = true;
								}
							}
						}
						break;
					case 27:
						{
							if ( uid == e.uid ) {
								if ( !isDead ) {
									isShield = false;
								}
							}
						}
						break;
					case 28:
						{
							if ( uid == e.uid ) {
								isDead = true;
							}
						}
						break;
					case 29:
						{
							if ( uid == e.uid ) {
								isDead = false;
								pevent.hp = 100.0f;
								pevent.exp = 0.0f;
							}
						}
						break;
					case 1:
						{
						}
						break;
					default:
						{
						}
						break;
				}
				if ( uid == e.uid ) {
					if ( e.actionCode != 2 ) {
						if ( !isDead ) {
							TEvent e;
							e.uid = uid;
							e.actionCode = 2;
							e.subject = this;
							eventProc->PostEvent(e);
						}
					}
				}
			}
		}
	};
	virtual int GetClassCode() {
		return 8192;
	};
};


class EPlayerClient : public TClientHandler {
public:
	EPlayerClient() {};
	virtual ~EPlayerClient() {};
public:
	PEvent event;
	EPlayer *player;
	virtual void PacketHandler(char *buf) {
		event = *(PEvent*)buf;
		TEvent e;
		e.uid = player->uid;
		e.actionCode = event.actionCode;
		e.subject = player;
		printf("New Message from Internet : uid = [%2X] action = [%2X]\n", e.uid, e.actionCode);
		player->eventProc->PostEvent(e);
	};
};


class Router : public TEventListener {
public:
	Router() {};
	virtual ~Router() {};
public:
	TServer *server;
public:
	virtual void EventHandler(TEvent &e) {
		server->arrayLock.ReadLock();
		unsigned int i7 = server->clientHandlers.GetLength();
		for(unsigned int i1 = 0 ; i1 < i7 ; i1 ++ ) {
			PEvent event;
			event.uid = e.uid;
			event.actionCode = e.actionCode;
			EPlayer *player = (EPlayer*)e.subject;
			event.position = player->pevent.position;
			event.exp = player->pevent.exp;
			event.hp = player->pevent.hp;
			if ( e.actionCode == 1 ) {
				if ( e.uid == ((EPlayerClient*)&server->clientHandlers[i1])->player->uid ) {
					server->clientHandlers[i1].clientSocket.Send((char*)&event, sizeof(PEvent), 0);
				}
			} else {
				server->clientHandlers[i1].clientSocket.Send((char*)&event, sizeof(PEvent), 0);
			}
		}
		server->arrayLock.Unlock();
	};
};

TRWLock gslock;
unsigned int gsuid = 20;
Vector3f gsposition(0.0f, 0.0f, 0.0f);

TEventProcessor ep;

class TEGameServer : public TServer {
public:
	TEGameServer() {};
	virtual ~TEGameServer() {};
public:
	virtual TClientHandler *NewClientHandler() {
		EPlayerClient *newpc = new EPlayerClient();
		newpc->player = new EPlayer();
		newpc->player->eventProc = &ep;
		ep.AddListener(*(newpc->player));
		gslock.WriteLock();
		newpc->player->uid = gsuid;
		gsuid ++;
		newpc->player->pevent.position = gsposition;
		gsposition += Vector3f(0.1f, 0.0f, 0.0f);
		gslock.Unlock();
		return newpc;
	}
};

TEGameServer server;
Router router;

int _tmain(int argc, _TCHAR* argv[]) {
	router.server = &server;
	ep.AddListener(router);
	ep.interval = 10;
	ep.Start();
	server.serverSocket.SetFamily(AF_INET);
	server.serverSocket.SetPort(2106);
	server.serverSocket.SetAddress("0.0.0.0");
	server.Startup();
	server.Join();
	ep.Join();
	return 0;
}

