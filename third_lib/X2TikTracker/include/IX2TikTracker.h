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
	China = 0, 
	HongKong = 1,
	Europe = 2,
	USA = 3,
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
	X2TikTConfig() : logEnabled(false), logLevel(kWARN),trackerZone(China), downloadTimeout(10000)
		, localPortHls(0), localPortDash(0), diskCacheLimit(0), memoryCacheLimit(0), memoryCacheCountLimit(15), autoShare(true)
		, withTag(NULL), webRTCConfig(NULL), maxPeerConnections(25)
		, useHttpRange(true), useStrictHlsSegmentId(true)
		, httpHeadersForHls(NULL), httpHeadersForDash(NULL) 
		, isSetTopBox(false), sharePlaylist(false), prefetchOnly(false), logPersistent(false), geoIpPreflight(true)
		, insertTimeOffsetTag(NULL), mediaFileSeparator(NULL)
	{

	}
	bool logEnabled;					// �Ƿ��ӡ��־, Ĭ�ϣ�false
	int logLevel;						// ��ӡ��־�ļ���, Ĭ�ϣ�WARN
	TrackerZone trackerZone;            // tracker��������ַ���ڹ��ҵ�ö�٣���ΪChina��HongKong��Europe��USA
	int downloadTimeout;				// HTTP����ts�ļ���ʱʱ�䣬��λ���룬Ĭ��10000ms
	int localPortHls;					// HLS���ش���������Ķ˿ں�(Ĭ������˿�)
	int localPortDash;					// DASH���ش���������Ķ˿ں�(Ĭ������˿�)
	int diskCacheLimit;					// �㲥ģʽ��P2P�ڴ��̻�������������(��Ϊ0���Խ��ô��̻���)����λByte��2GΪ(2000*1024*1024)
	int memoryCacheLimit;				// P2P���ڴ滺����������������λByte��2GΪ(2000*1024*1024)
	int memoryCacheCountLimit;			// P2P���ڴ滺����������������ts�ļ�������ʾ��Ĭ��15�������ȣ�
	int autoShare;						// ������ر�p2p engine
	const char* withTag;                // �û��Զ���ı�ǩ�������ڿ���̨�鿴�ֲ�ͼ
	const char* webRTCConfig;           // ͨ��webRTCConfig���޸�WebRTCĬ������
	int maxPeerConnections;             // ������ӽڵ�������Ĭ��25
	bool useHttpRange;                  // �ڿ��ܵ������ʹ��Http Range����������p2p���س�ʱ��ʣ�ಿ�����ݣ�Ĭ��true
	bool useStrictHlsSegmentId;         // ʹ�û���url��SegmentId�����Ĭ�ϻ������кŵ�
	const char* httpHeadersForHls;      // ��������ts��m3u8ʱ��HTTP����ͷ
	const char* httpHeadersForDash;     // ��������Dash�ļ�ʱ��HTTP����ͷ
	bool isSetTopBox;                   // ��������ڻ����������ó�true��Ĭ�ϣ�false
	bool sharePlaylist;                 // �Ƿ�����m3u8�ļ���P2P���䣬Ĭ�ϣ�false
	bool prefetchOnly;                  // HLSģʽ��ֻ����Ԥ���صķ�ʽ����P2P���أ�Ĭ�ϣ�false
	bool logPersistent;                 // �Ƿ���־�־û����ⲿ�洢��Environment.getExternalStorageDirectory()·���µ�logger�ļ��У���Ĭ�ϣ�false
	bool geoIpPreflight;                // ������IP���ݿ�����ASN����Ϣ���Ӷ���ø�׼ȷ�ĵ��ȣ�Ĭ�ϣ�true
	const char* insertTimeOffsetTag;    // ����ֱ��ģʽ��Ч����m3u8�ļ��в��� "#EXT-X-START:TIME-OFFSET=[timeOffset]"��ǿ�Ʋ�������ĳ��λ�ÿ�ʼ���أ����� [timeOffset] ���ڲ����б��ƫ���������Ϊ����Ӳ����б��β��ǰƫ�ƣ���λ���룩
	const char* mediaFileSeparator;     // ý���ļ���׺�ָ���

	// ֧�ֵ�HLSý���ļ���׺("mp4", "fmp4", "ts","m4s","m4v"))            
	// ֧�ֵ�DASHý���ļ���׺("mp4", "fmp4", "webm", "m4s", "m4v"))      
};

class X2TikTrackerEventHanlder
{
public:
	X2TikTrackerEventHanlder() {};
	virtual ~X2TikTrackerEventHanlder() {};

	/**
	*/
	virtual void OnShareResult(TKT_CODE nCode) = 0;
	/**
	jsStats.allHttpDownload: Download from HTTP(CDN), (Unit: KB)
	jsStats.allShareDownload: Download from Peer(Sharer), (Unit: KB)
	jsStats.allShareUpload: Upload to Peer, (Unit: KB)
	jsStats.shareDownloadSpeed: The speed of sharing, (Unit: KB/s)
	*/
	virtual void OnLoadDataStats(const char*jsStats) {};
	/**
	*/
	virtual void OnPeerOn(const char* strPeerUId, const char* strPeerUData) {};
	/**
	*/
	virtual void OnPeerOff(const char* strPeerUId, const char* strPeerUData) {};
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