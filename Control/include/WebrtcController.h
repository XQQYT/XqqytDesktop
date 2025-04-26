#ifndef _WEBRTCCONTROLLER_H
#define _WEBRTCCONTROLLER_H
#include "EventBus.h"
#include "WebRTC.h"
#include "Operator.h"
#include "Render.h"

class WebrtcController : public Operator{
public:
    void dispatch_string(std::string event_name,std::string str) override;
    void dispatch_string_string_string(std::string event_name, std::string str1, std::string str2, std::string str3) override;
    void dispatch_void(std::string event_name) override;
    void dispatch_bool(std::string event_name,bool status) override;
public:
    WebrtcController();
    void initWebrtcSubscribe();
    void onInitWebrtc();
    void createSDP(bool status);
    void recvSDPOffer(std::string sdp);
    void recvSDPAnswer(std::string sdp);
    void onSendMouseData(const MouseEventPacket packet);
    void onSetRemoteSDPOfferDone();
    void onRecvIceCandidate(std::string ice_str,std::string sdp_mid,std::string sdp_mline_index);
    void onRecvIceCandidateDone();
    void onSetRenderInstance(RenderInterface* instance);
private:
    std::unique_ptr<WebRTCInterface> webrtc_instance;
};

#endif