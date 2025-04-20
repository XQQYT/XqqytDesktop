#include "SdpObserver.h"
#include "WebRTC.h"
#include <iostream>

void SDPO::OnSuccess(webrtc::SessionDescriptionInterface* desc)
{
    std::cout<<"sdpo success"<<std::endl;
    std::string desc_str;
    desc->ToString(&desc_str);
    webrtc_instance.setLocalSDP(desc);
    switch(webrtc_instance.currentRole){
        case WebRTC::Role::SENDER:
            webrtc_instance.display_string("/webrtc/create_sdp_offer",std::move(desc_str)); 
            break;
        case WebRTC::Role::RECEIVER:
            webrtc_instance.display_string("/webrtc/create_sdp_answer",std::move(desc_str)); 
            break;
        case WebRTC::Role::UN_DEFINED:
            break;
        default:
            break;
    }
        
    
}

void SDPO::OnFailure(webrtc::RTCError error)
{

}

void SSDO::OnSuccess()
{
    switch(webrtc_instance.currentRole)
    {
        case WebRTC::Role::RECEIVER:
            // webrtc_instance.display_void("/webrtc/set_remote_sdp_offer_done");
            webrtc_instance.createSDP(WebRTC::SDPType::ANSWER);
            std::cout<<"set remote sdp successed"<<std::endl;
            break;
        case WebRTC::Role::SENDER:
            std::cout<<"set local sdp successed"<<std::endl;
    }
}
void SSDO::OnFailure(webrtc::RTCError error)
{

}