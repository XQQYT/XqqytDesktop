#ifndef _WEBRTCINTERFACE_H
#define _WEBRTCINTERFACE_H
#include <string>

class WebRTCInterface
{
public:
    virtual void initWebRTC() = 0;
    virtual void createSDP() = 0;
    virtual void setRemoteSDP(std::string remote_sdp) = 0;
};

#endif