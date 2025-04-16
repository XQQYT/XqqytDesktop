#ifndef _WEBRTCINTERFACE_H
#define _WEBRTCINTERFACE_H

class WebRTCInterface
{
public:
    virtual void initWebRTC() = 0;
    virtual void createSDP() = 0;
};

#endif