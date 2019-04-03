// TestClient.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#define _BASE_IMPORT
#define _FILE_IMPORT
#define _SOUND_IMPORT
#define _MATHTOOL_IMPORT
#define _THREAD_IMPORT
#define _NETWORK_IMPORT
#define _CORE_IMPORT
#include "stdio.h"
#include "conio.h"
#include "winsock.h"
#include "..\Sound\ALee.h"
#undef GetClassName
#include "..\Base\Type.h"
#include "..\Base\Base.h"
#include "..\MathTool\MathTool.h"
#include "..\Thread\Thread.h"
#include "..\Network\TSocket.h"
#undef _ARRAY_API
//#define _ARRAY_API
#define _ARRAY_API _BASE_API
#include "..\Base\Array.h"
#include "..\Base\RefArray.h"
#include "..\Network\Packet.h"
#include "..\Network\Client.h"
#include "..\Network\Blowfish.h"
#include "..\Core\SoundImport.h"
#include "..\Core\FileImport.h"

struct PEvent {
	short uid;
	short actionCode;
	float hp;
	float exp;
	Vector3f position;
};

class EPlayer : public TClient {
public:
	EPlayer() {isDead = false; isShield = false;};
	virtual ~EPlayer() {};
public:
	PEvent event;
	char buffer[1024];
	short uid;
	bool isDead;
	bool isShield;
public:
	virtual void Run() {
		int rcv = 0;
		clientSocket.SetInterval(0, 0);
		while(TRUE) {
			clientSocket.Select(TRUE, FALSE, FALSE, TRUE);
			if(clientSocket.IsReadable()) {
				rcv = clientSocket.Receive(buffer, 1024, 0);
				if ( rcv >= 0 ) {
					event = *(PEvent*)buffer;
					switch ( event.actionCode ) {
						case 1:
							{
								uid = event.uid;
								printf("System: Assign you uid = [%4X]\n", uid);
								printf("Now you can play\n");
							}
							break;
						case 2:
							{
								if ( uid == event.uid ) {
									printf("You're @ vector3f(%f, %f, %f) Now\n", event.position.x, event.position.y, event.position.z);
								} else {
									printf("Character uid = [%4X] is @vector3f(%f, %f, %f) Now\n", event.position.x, event.position.y, event.position.z);
								}
							}
							break;
						case 20:
						case 21:
						case 22:
						case 23:
							{
								if ( uid == event.uid ) {
									printf ("You've moved , vector3f(%f, %f, %f)\n", event.position.x, event.position.y, event.position.z);
								} else {
									printf ("Character uid = [%4X] has moved , vector3f(%f, %f, %f)\n", event.uid, event.position.x, event.position.y, event.position.z);
								}
							}
							break;
						case 24:
							{
								if ( uid == event.uid ) {
									printf ("You would attack someone, exp = [%f]\n", event.exp);
								} else {
									printf ("Character uid = [%4X], exp = [%f] has attacked someone\n", event.uid, event.exp);
								}
							}
							break;
						case 25:
							{
								if ( uid == event.uid ) {
									printf ("You have been attacked, hp = [%f]\n", event.hp);
								} else {
									printf ("Character uid = [%4X], hp = [%f] has been attacked\n", event.uid, event.hp);
								}
							}
							break;
						case 26:
							{
								if ( uid == event.uid ) {
									printf ("You have shield on\n");
								} else {
									printf ("Character uid = [%4X] has shield on\n", event.uid);
								}
							}
							break;
						case 27:
							{
								if ( uid == event.uid ) {
									printf ("You have shield off\n");
								} else {
									printf ("Character uid = [%4X] has shield off\n", event.uid);
								}
							}
							break;
						case 28:
							{
								if ( uid == event.uid ) {
									printf ("You died\n");
									isDead = true;
								} else {
									printf ("Character uid = [%4X] died\n", event.uid);
								}
							}
							break;
						case 29:
							{
								if ( uid == event.uid ) {
									if ( isDead ) {
										printf ("You have resurrected, hp = [%f], exp = [%f]\n", event.hp, event.exp);
										isDead = false;
									}
								} else {
									printf ("Character uid = [%4X], hp = [%f], exp = [%f] has resurrected\n", event.uid, event.hp, event.exp);
								}
							}
							break;
						default:
							break;
					}
				} else {
				}
			} else {
			}
			Delay(0, 50000);
		}
	};
};


EPlayer client;

int _tmain(int argc, _TCHAR* argv[]) {
	TAudioDevice ad;
	ad.GetDevices();
	if ( !ad.Open(0) ) {
		printf ("OpenAL ERROR\n");
		return 0;
	}
	TFile file;
	file.SetFilePathNameASC("C:\\Program Files\\OpenAL 1.1 SDK\\samples\\media\\stereo.wav");
	file.SetOpenMode(TFile::modeRead | TFile::typeBinary );
	file.Open();
	TFileIOStream fio;
	fio.SetFile(&file);
	fio.SetLoadStore(TFileIOStream::load);
	fio.SetEndian(TFileIOStream::little_endian);
	TWaveDataObject tobj;
	tobj.Serialize(fio);
	fio.Close();
	file.Close();
	TWaveSourceObject wso;
	wso.GenBuffer();
	if (alGetError() != AL_NO_ERROR) {
		return 0;
	}
	wso.BufferData(
		tobj.GetOpenALFormat(),
		tobj.GetDataBuffer(),
		tobj.GetDataSize(), 
		tobj.GetFrequency());
	if (alGetError() != AL_NO_ERROR) {
		return 0;
	}
	wso.GenSource();
	if (alGetError() != AL_NO_ERROR) {
		return 0;
	}
	wso.AttachBuffer();
	if (alGetError() != AL_NO_ERROR) {
		return 0;
	}
	wso.Play();
	if (alGetError() != AL_NO_ERROR) {
		return 0;
	}
	while ( wso.GetIntegerParameter(AL_SOURCE_STATE) == AL_PLAYING ) {
		Sleep(100);
		printf(".");
	};
	wso.Stop();
	wso.DeleteSources();
	wso.DeleteBuffers();
	ad.Close();
	return 0;
	Blowfish fish;
	fish.Init((unsigned char*)"[THISISAKEY]", 12);
	char strbuf[128] = "ARE YOU KIDDING ME NOT ONE OF YOU ...\0\0\0\0\0";
	int slen = (int)( strlen(strbuf) - 1 ) / 4 + 1;
	fish.Encrypt(strbuf, slen);
	fish.Decrypt(strbuf, slen);
	return 0;
	printf("====== Very Simple Internet Game ======\n");
	printf("Please input server IP address:\n");
	char ipaddrbuffer[1024];
	scanf("%s", ipaddrbuffer);
	printf("\nIP address = %s\n", ipaddrbuffer);
	client.clientSocket.addr.sin_addr.S_un.S_addr = inet_addr(ipaddrbuffer);
	if(client.Startup()) {
	} else {
		return 0;
	}
	printf("Client Startup!\n");
	client.Start();
	char key = 0;
	PEvent event;
	event.actionCode = 1;
	client.clientSocket.Send((char*)&event, sizeof(PEvent), 0);
	bool isValid = true;
	while (TRUE) {
		key = (char)getch();
		event.uid = client.uid;
		isValid = true;
		switch(key) {
			case 'w':
				{
					if ( !client.isDead ) {
						event.actionCode = 20;
					}
				}
				break;
			case 's':
				{
					if ( !client.isDead ) {
						event.actionCode = 21;
					}
				}
				break;
			case 'a':
				{
					if ( !client.isDead ) {
						event.actionCode = 22;
					}
				}
				break;
			case 'd':
				{
					if ( !client.isDead ) {
						event.actionCode = 23;
					}
				}
				break;
			case 'f':
				{
					if ( !client.isDead ) {
						event.actionCode = 24;
					}
				}
				break;
			case 'g':
				{
					if ( !client.isDead ) {
						client.isShield = true;
						event.actionCode = 26;
					}
				}
				break;
			case 'u':
				{
					if ( !client.isDead ) {
						client.isShield = false;
						event.actionCode = 27;
					}
				}
				break;
			case 'c':
				{
					if ( client.isDead ) {
						event.actionCode = 29;
						client.isDead = false;
						client.isShield = false;
					} else {
						isValid = false;
					}
				}
				break;
			default:
				isValid = false;
				break;
		}
		if ( isValid ) {
			client.clientSocket.Send((char*)&event, sizeof(PEvent), 0);
		}
	}
	return 0;
}

