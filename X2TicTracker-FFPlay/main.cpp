#include <stdio.h>
#include "IX2TikTracker.h"
#include "kbhit.h"

#define APP_ID "your app id"	

class X2TikTrackerEvent : X2TikTrackerEventHanlder
{
public:
	X2TikTrackerEvent() {
	};
	virtual ~X2TikTrackerEvent() {
	};
	//* For X2TikTrackerEventHanlder
	virtual void OnShareResult(TKT_CODE nCode) {
	};
	/**
	jsStats.allHttpDownload: Download from HTTP(CDN), (Unit: KB)
	jsStats.allShareDownload: Download from Peer(Sharer), (Unit: KB)
	jsStats.allShareUpload: Upload to Peer, (Unit: KB)
	jsStats.shareDownloadSpeed: The speed of sharing, (Unit: KB/s)
	*/
	virtual void OnLoadDataStats(const char*jsStats) {
	};
	/**
	*/
	virtual void OnPeerOn(const char* strPeerUId, const char* strPeerUData) {
	};
	/**
	*/
	virtual void OnPeerOff(const char* strPeerUId, const char* strPeerUData) {
	};
	/**
	*/
	virtual void OnRenewTokenResult(const char* token, RENEW_TOKEN_ERR_CODE errorCode)
	{
		(const char*) token;
		(RENEW_TOKEN_ERR_CODE) errorCode;
	}
	/**
	*/
	virtual void OnTokenWillExpired()
	{
	}
	/**
	*/
	virtual void OnTokenExpired()
	{
	}
};

int main(int argc, char* argv[])
{
	IX2TikTracker* x2TikTracker = createX2TikTracker();
	x2TikTracker->initialize(APP_ID, NULL);

	{
		int ret = x2TikTracker->startPlay("https://stream-tiktraker.tikcdn.cn/live/WhatIsTikcdn.m3u8", true);
		char strUrl[1024] = { 0 };
		x2TikTracker->getExPlayUrl(strUrl, 1024);
		printf("ExUrl: %s \r\n", strUrl);
		char strCmd[2048];
		sprintf(strCmd, "ffplay.exe -i %s", strUrl);
		system(strCmd);
	}

	x2TikTracker->stopPlay();
	x2TikTracker->release(true);
	x2TikTracker = NULL;
	return 0;
	}