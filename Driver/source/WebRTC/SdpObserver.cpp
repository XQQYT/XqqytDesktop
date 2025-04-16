#include "SdpObserver.h"
#include "WebRTC.h"
#include <iostream>

SDPO::SDPO(WebRTC& instance):
    webrtc_instance(instance)
{

}

void SDPO::OnSuccess(webrtc::SessionDescriptionInterface* desc)
{
    std::string desc_str;
    desc->ToString(&desc_str);
    std::cout<<"===  sdp  ==="<<desc_str<<std::endl;
    webrtc_instance.display_string("/webrtc/create_sdp",std::move(desc_str));
}

void SDPO::OnFailure(webrtc::RTCError error)
{

}