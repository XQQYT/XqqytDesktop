#ifndef _WEBRTCCONTROLLER_H
#define _WEBRTCCONTROLLER_H
#include "EventBus.h"
#include "WebRTC.h"

class WebrtcController{
public:
    WebrtcController();
    void initWebrtcSubscribe();
    void createSDP();
private:
    std::unique_ptr<WebRTCInterface> webrtc_instance;
};

#endif