/*
*  Copyright (c) 2022 The X2RTC project authors. All Rights Reserved.
*
*  Please visit https://www.x2rtc.com for detail.
*
*  Author: Eric(eric@x2rtc.com)
*  Twitter: @x2rtc
*
* The GNU General Public License is a free, copyleft license for
* software and other kinds of works.
*
* The licenses for most software and other practical works are designed
* to take away your freedom to share and change the works.  By contrast,
* the GNU General Public License is intended to guarantee your freedom to
* share and change all versions of a program--to make sure it remains free
* software for all its users.  We, the Free Software Foundation, use the
* GNU General Public License for most of our software; it applies also to
* any other work released this way by its authors.  You can apply it to
* your programs, too.
* See the GNU LICENSE file for more info.
*/
#ifndef __I_X2_TIK_TRACKER_H__
#define __I_X2_TIK_TRACKER_H__
#include <stdint.h>
#include <string>
#include "X2RtcExport.h"

enum TKT_CODE {
	/**
	0: The method call succeeds, or play succeeds. 
	*/
	TKT_CODE_OK = 0,
	/**
	1: Play fails. The reason is unknown.
	*/
	TKT_CODE_UNKNOWN = 1,
	/**
	2: Play is rejected by the server.
	*/
	TKT_CODE_REJECTED = 2, // Occurs when not initialized or server reject
	/**
	3: Invalid play argument.
	*/
	TKT_CODE_INVALID_ARGUMENT = 3,
	/**
	4: The App ID is invalid.
	*/
	TKT_CODE_INVALID_APP_ID = 4,
	/**
	5: The token is invalid.
	*/
	TKT_CODE_INVALID_TOKEN = 5,
	/**
	6: The token has expired, and hence play is rejected.
	*/
	TKT_CODE_TOKEN_EXPIRED = 6,
	/**
	7: Unauthorized play.
	*/
	TKT_CODE_NOT_AUTHORIZED = 7,
	/**
	8: The user has already played, or the user has not called the \ref stopPlay method to got "PLAY_STATE_CLOSED" state.
	*/
	TKT_CODE_ALREADY_PLAYED = 8,
	/**
	8: The user has already shared, or the user has not called the \ref stopShare method to got "SHARE_STATE_CLOSED" state.
	*/
	TKT_CODE_ALREADY_SHARED = 9,
	/**
	10: The play times out. The current timeout is set as six seconds. 
	*/
	TKT_CODE_TIMEOUT = 10,

	/**
	101: \ref Instance is not initialized.
	*/
	TKT_CODE_NOT_INITIALIZED = 101,
};

/**
@brief Error codes related to renewing the TikTracker Token.
*/
enum RENEW_TOKEN_ERR_CODE {

	/**
	0: The method call succeeds, or the renewing operation succeeds. 
	*/
	RENEW_TOKEN_ERR_OK = 0,

	/**
	1: Common failure. The user fails to renew the token.
	*/
	RENEW_TOKEN_ERR_FAILURE = 1,

	/**
	2: The method call fails. The argument is invalid. 
	*/
	RENEW_TOKEN_ERR_INVALID_ARGUMENT = 2,

	/**
	3: **RESERVED FOR FUTURE USE**
	*/
	RENEW_TOKEN_ERR_REJECTED = 3,

	/**
	4: The method call frequency exceeds the limit of two queries per second.
	*/
	RENEW_TOKEN_ERR_TOO_OFTEN = 4,

	/**
	5: The token has expired.
	*/
	RENEW_TOKEN_ERR_TOKEN_EXPIRED = 5,

	/**
	6: The token is invalid.
	*/
	RENEW_TOKEN_ERR_INVALID_TOKEN = 6,

	/**
	101: \ref The instance is not initialized.
	*/
	RENEW_TOKEN_ERR_NOT_INITIALIZED = 101,
};

enum TrackerZone
{
	kChina = 0, 
	kHongKong = 1,
	kEurope = 2,
	kUSA = 3,
	kAISA = 4,
	kAFRICA = 5,
};

enum TrackerLog
{
	kTRACE = 0,
	kDBG = 1,
	kINF = 2,
	kWARN = 3,
	kERR = 4,
	kCRIT = 5,
	kNONE = 6,
};

struct X2TikTConfig
{
	X2TikTConfig() : logEnabled(false), logLevel(kWARN),trackerZone(kChina), downloadTimeout(10000)
		, localPortHls(0), localPortDash(0), diskCacheLimit(0), memoryCacheLimit(0), memoryCacheCountLimit(15), autoShare(true)
		, withTag(NULL), webRTCConfig(NULL), maxPeerConnections(25)
		, useHttpRange(true), httpHeadersForHls(NULL), httpHeadersForDash(NULL) 
		, isSetTopBox(false), sharePlaylist(false), logPersistent(false), geoIpPreflight(true)
		, mediaFileSeparator(NULL)
	{

	}
	bool logEnabled;					// Enbable/Disable log, default: false
	int logLevel;						// Log's level, default: kWARN(TrackerLog)
	TrackerZone trackerZone;            // The zone of tracker, like: China¡¢HongKong¡¢Europe¡¢USA etc...
	int downloadTimeout;				// The timeout time of downloading ts files by HTTP. default: 10000ms
	int localPortHls;					// The port of local proxy for HLS, default: 0(Random)
	int localPortDash;					// The port of local proxy for DASH, default: 0(Random)
	int diskCacheLimit;					// The maximum amount of data cached on disk in VOD mode. default: 0(disable)£¬unit: Byte£¬2G(2000*1024*1024)
	int memoryCacheLimit;				// The maximum amount of data cached in memory. default: 0£¬unit: Byte£¬2G(2000*1024*1024), checking second.
	int memoryCacheCountLimit;			// The maximum count of data cached in memory, default: 15, checking first.
	int autoShare;						// Auto share.
	const char* withTag;                // User self defined tag, it's used in console for user distribution map.
	const char* webRTCConfig;           // The config of webRTC.
	int maxPeerConnections;             // The maximum amount of P2P connections, default: 25.
	bool useHttpRange;                  // It's download the remain part of Ts file usd Http Range when P2P load failed, default: false.
	const char* httpHeadersForHls;      // Set the header of HTTP when request for ts/m3u8.
	const char* httpHeadersForDash;     // Set the header of HTTP when request for dash.
	bool isSetTopBox;                   // Set it to true when running on Set-top box, default: false
	bool sharePlaylist;                 // Is allow sharing m3u8 file, default: false
	bool logPersistent;                 // Is save the log file on disk, default: false, Android:(Environment.getExternalStorageDirectory()/logger)
	bool geoIpPreflight;                // Get ASN information from the IP database, default: true
	const char* mediaFileSeparator;     // The suffixes of media file.
	// Supported HLS media file suffixes("mp4", "fmp4", "ts","m4s","m4v"))            
	// Supported DASH media file suffixes("mp4", "fmp4", "webm", "m4s", "m4v"))      
};

class X2TikTrackerEventHanlder
{
public:
	X2TikTrackerEventHanlder() {};
	virtual ~X2TikTrackerEventHanlder() {};

	/**
	* Callback the result of P2P share.
	*/
	virtual void OnShareResult(TKT_CODE nCode) = 0;
	/**
	* Got stats of the session.
	* jsStats.allHttpDownload: Download from HTTP(CDN), (Unit: KB)
	* jsStats.allShareDownload: Download from Peer(Sharer), (Unit: KB)
	* jsStats.allShareUpload: Upload to Peer, (Unit: KB)
	* jsStats.shareDownloadSpeed: The speed of sharing, (Unit: KB/s)
	*/
	virtual void OnLoadDataStats(const char*jsStats) {};
	/**
	* Peer online.
	*/
	virtual void OnPeerOn(const char* strPeerUId, const char* strPeerUData) {};
	/**
	* Peer offline.
	*/
	virtual void OnPeerOff(const char* strPeerUId, const char* strPeerUData) {};
	/**
	* Got the result of renew token.
	*/
	virtual void OnRenewTokenResult(const char* token, RENEW_TOKEN_ERR_CODE errorCode)
	{
		(const char*) token;
		(RENEW_TOKEN_ERR_CODE) errorCode;
	}
	/**
	* Token will expired.
	*/
	virtual void OnTokenWillExpired()
	{
	}
	/**
	* Token is expried.
	*/
	virtual void OnTokenExpired()
	{
	}
};

class IX2TikTracker
{
public:
	IX2TikTracker() {};
protected:
	virtual ~IX2TikTracker() {};
public:
	/** Creates an IX2TikTracker instance.

	The TikTracker SDK supports multiple {@link IX2TikTracker} instances.

	All methods in the {@link RtmClient} class are executed asynchronously.

	@param appId The App ID issued by TikCdn to you. Apply for a new App ID from TikCdn if it is missing from your kit.
	@param eventHandler The X2TikTrackerEventHanlder object that invokes callbacks to be passed to the application on TikTracker SDK runtime events.
	*/
	virtual int initialize(const char* strAppId, X2TikTrackerEventHanlder *eventHandler) = 0;

	/** Releases all resources used by the IX2TikTracker instance.
	*/
	virtual int release(bool sync = false) = 0;

	/** Start play, url must be support Hls or Dash.
	*/
	virtual int startPlay(const char* strUrl, bool bShare) = 0;

	/** Stop play and releases all resources.
	*/
	virtual int stopPlay() = 0;

	/** Get url internal.
	*/
	virtual int getExPlayUrl(char* strUrl, int nUrlSize) = 0;

	/** Set config.
	*/
	virtual int setConfig(X2TikTConfig* x2Config) = 0;

	/** Start share stream each other.
	*/
	virtual int startShare() = 0;

	/** Stop share stream.
	*/
	virtual int stopShare() = 0;

	/** Renew token when it's expired.
	*/
	virtual int renewToken(const char* strToken) = 0;

	/**
	* Set private paramters, format is json like: "{cmd:"", "key":"", "val":""}".
	*
	* @param [in] strParam: The parameters to set.
	* @return
	* - 0: Success.
	* - < 0: Failure.
	*/
	virtual int setParameters(const char*strParam) = 0;
};

X2RTC_API IX2TikTracker* X2RTC_CALL createX2TikTracker();

#endif	// __I_X2_TIK_TRACKER_H__