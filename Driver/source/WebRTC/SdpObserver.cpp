#include "SdpObserver.h"
#include "WebRTC.h"
#include <iostream>

void SDPO::OnSuccess(webrtc::SessionDescriptionInterface* desc)
{
    std::string desc_str;
    desc->ToString(&desc_str);
    webrtc_instance.display_string("/webrtc/create_sdp",std::move(desc_str));
}

void SDPO::OnFailure(webrtc::RTCError error)
{

}

void SRDO::OnSuccess()
{
    std::cout<<"set remote sdp success"<<std::endl;
}
void SRDO::OnFailure(webrtc::RTCError error)
{

}