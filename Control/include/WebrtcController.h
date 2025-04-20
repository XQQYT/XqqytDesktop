#ifndef _WEBRTCCONTROLLER_H
#define _WEBRTCCONTROLLER_H
#include "EventBus.h"
#include "WebRTC.h"
#include "Operator.h"

class WebrtcController : public Operator{
public:
    void dispatch_string(std::string event_name,std::string str) override;
    void dispatch_void(std::string event_name) override;
public:
    WebrtcController();
    void initWebrtcSubscribe();
    void onInitWebrtc();
    void createSDP(bool status);
    void recvSDPOffer(std::string sdp);
    void recvSDPAnswer(std::string sdp);
    void onSetRemoteSDPOfferDone();
private:
    std::unique_ptr<WebRTCInterface> webrtc_instance;
};

#endif