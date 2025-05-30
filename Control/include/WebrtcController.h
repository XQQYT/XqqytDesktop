/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef _WEBRTCCONTROLLER_H
#define _WEBRTCCONTROLLER_H
#include <vector>
#include "EventBus.h"
#include "WebRTC.h"
#include "Operator.h"
#include "Render.h"
#include "GlobalEnum.h"
#include "NlohmannJson.h"
#include <fstream>

class WebrtcController : public Operator{
public:
    void dispatch_string(EventBus::EventType event_name,std::string str) override;
    void dispatch_string_string_string(EventBus::EventType event_name, std::string str1, std::string str2, std::string str3) override;
    void dispatch_void(EventBus::EventType event_name) override;
    void dispatch_bool(EventBus::EventType event_name,bool status) override;
public:
    WebrtcController();
    void initWebrtcSubscribe();
    void onInitWebrtc(std::string, bool status);
    void onRecvConnectRequestResult(bool status);
    void onReady();
    void loadSetting();
    void recvSDPOffer(std::string sdp);
    void recvSDPAnswer(std::string sdp);
    void onSendMouseData(MouseEventPacket packet);
    void onSendKeyboardData(KeyEventPacket packet);
    void onSetRemoteSDPOfferDone();
    void onRecvIceCandidate(std::string ice_str,std::string sdp_mid,std::string sdp_mline_index);
    void onRecvIceCandidateDone();
    void onSetRenderInstance(RenderInterface* instance);
    void onCloseControl();
    void onRecvCloseControl();
    void onModuleConfigUpdated(std::string module,std::string key,std::string value);
    void onWriteIntoClipboard(std::string str);

    void onSyncFileInfo(FileSyncType type,std::vector<std::string> args);
    void onSyncFileMsg(std::string msg);
    void onSetFileHolder(std::shared_ptr<std::ofstream> out, std::function<void()> callback);

private:
    void onReceiveProgress(uint16_t id ,uint32_t received_size, uint32_t total_size);
private:
    std::unique_ptr<WebRTCInterface> webrtc_instance;
    std::unique_ptr<JsonFactory> json_instance;
};

#endif