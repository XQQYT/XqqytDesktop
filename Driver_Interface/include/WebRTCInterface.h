#ifndef _WEBRTCINTERFACE_H
#define _WEBRTCINTERFACE_H
#include <string>
#include "Render.h"
#include "MouseKeyboardType.h"

class WebRTCInterface
{
public:
    enum class SDPType
    {
        UNDEFINED,
        OFFER,
        ANSWER
    };
    //for offer/answer SDP direction
    enum class Role
    {
        UN_DEFINED,
        SENDER,
        RECEIVER
    };
    enum class SetSDPType
    {
        UNDEFINED,
        REMOTE,
        LOCAL
    };
    enum class ConnectionStatus
    {
        UN_DEFINED,
        FAILED,
        SUCCESSED
    };
    virtual void initWebRTC() = 0;
    virtual void createSDP(SDPType type) = 0;
    virtual void setRemoteSDP(std::string remote_sdp, SDPType type) = 0;
    virtual void addIceCandidateIntoBuffer(std::string ice_str,std::string sdp_mid,int sdp_mline_index) = 0;
    virtual void startCaptureDesktop() = 0;
    virtual void stopCaptureDesktop() = 0;
    virtual void setRenderInstance(RenderInterface* instance) = 0;
    virtual void sendMouseEventPacket(const MouseEventPacket packet) = 0;
    virtual void sendKeyboardEventPacket(const KeyEventPacket packet) = 0;
    virtual void closeWebRTC() = 0;
};

#endif