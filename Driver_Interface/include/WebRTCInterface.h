#ifndef _WEBRTCINTERFACE_H
#define _WEBRTCINTERFACE_H
#include <string>

class WebRTCInterface
{
public:
    enum class SDPType
    {
        UNDEFINED,
        OFFER,
        ANSWER
    };
    enum class Role
    {
        UN_DEFINED,
        SENDER,
        RECEIVER
    };
    virtual void initWebRTC() = 0;
    virtual void createSDP(SDPType type) = 0;
    virtual void setRemoteSDP(std::string remote_sdp) = 0;
};

#endif