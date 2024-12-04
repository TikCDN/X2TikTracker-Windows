## X2TikTracker-Windows

### 概述

**X2TikTracker** 是一款支持基于 P2P 技术的视频加速工具。它集成了 WebRTC 和 HLS 等技术，旨在降低视频点播或直播的带宽消耗，提升播放体验。X2TikTracker 的核心理念是利用终端设备之间的上传能力，实现带宽共享，从而降低对传统 CDN 的依赖。



#### Demo运行指南

```
./X2TicTracker-FFPlay/main.cpp

在上述文件中找到APP_ID

#define APP_ID "your app id"
```

### 初始化

#### 构造函数

```windows
IX2TikTracker* x2TikTracker = createX2TikTracker();
```

**初始化示例：**

```windows
x2TikTracker->initialize(APP_ID, NULL);
```

**参数说明：**

- `appId`: The App ID issued by TikCdn to you. Apply for a new App ID from X2Rtc if it is missing from your kit.
- `eventHandler`: The X2TikTrackerEventHanlder object that invokes callbacks to be passed to the application on TikTracker SDK runtime events.



### 核心方法


#### 1. **开始播放**

```
int startPlay(const char* strUrl, bool bShare)
```

- **功能**: 开始播放指定地址的视频，并可选择是否启用 P2P 共享。

- **参数**:

  - `url`: 视频播放地址，目前仅支持HLS(m3u8)和MPEG-DASH(mpd)。
  - `share`: 是否启用 P2P 共享。

- **返回值**: 操作结果的状态码。

- **示例**:

  ```
  int ret =x2TikTracker->startPlay("https://stream-tiktraker.tikcdn.cn/live/WhatIsTikcdn.m3u8", true);
  ```

#### 2. **停止播放**

```
int stopPlay()
```

- **功能**: 停止当前播放。
- **返回值**: 操作结果的状态码。

#### 3. **开始共享**

```
int startShare()
```

- **功能**: 开始 P2P 共享。

#### 4. **停止共享**

```
int stopShare()
```

- **功能**: 停止 P2P 共享。

#### 5. **更新令牌**

```
int renewToken(const char* strToken)
```

- **功能**: 更新令牌。
- 参数
  - `token`: 新的授权令牌。

#### 6. **获取 p2p URL 地址**

```
int getExPlayUrl(char* strUrl, int nUrlSize)
```

- **功能**: 获取当前播放的p2p URL 地址。

#### 7. **释放资源**

```
int release(bool sync = false)
```

- **功能**: 释放所有资源并清空监听器。

### 回调接口

### **X2TikTrackerEventHandler**

用于接收播放和共享事件的回调接口：

```
class X2TikTrackerEventHanlder {
    virtual void OnShareResult(TKT_CODE nCode);
    virtual void OnLoadDataStats(const char*jsStats);
    virtual void OnPeerOn(const char* strPeerUId, const char* strPeerUData);
    virtual void OnPeerOff(const char* strPeerUId, const char* strPeerUData);
    virtual void OnRenewTokenResult(const char* token, RENEW_TOKEN_ERR_CODE errorCode);
    virtual void OnTokenWillExpired();
    virtual void OnTokenExpired();
}
```

主要回调方法：

- `OnShareResult(TKT_CODE nCode)`: P2P 共享结果。
- `OnLoadDataStats(const char*jsStats)`: 数据统计信息回调。
- `OnRenewTokenResult(const char* token, RENEW_TOKEN_ERR_CODE errorCode)`: 令牌更新结果。
- `OnTokenWillExpired()`: 令牌即将过期。
- `OnTokenExpired()`: 令牌过期了。
- `OnPeerOn(const char* strPeerUId, const char* strPeerUData)`: 一个新的 P2P 节点成功加入网络时，会触发该回调。此时，P2P 网络中会有新的设备或用户参与共享数据或资源。
- `OnPeerOff(const char* strPeerUId, const char* strPeerUData)`: 一个 P2P 节点或用户从网络中断开时。

