/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "SdpObserver.h"
#include "WebRTC.h"
#include <iostream>

void SDPO::OnSuccess(webrtc::SessionDescriptionInterface* desc)
{
    std::string desc_str;
    desc->ToString(&desc_str);
    webrtc_instance.setLocalSDP(desc);
    switch(webrtc_instance.currentRole){
        case WebRTC::Role::SENDER:
            webrtc_instance.display_string(EventBus::EventType::WebRTC_CreateSdpOffer,std::move(desc_str)); 
            break;
        case WebRTC::Role::RECEIVER:
            webrtc_instance.display_string(EventBus::EventType::WebRTC_CreateSdpAnswer,std::move(desc_str)); 
            break;
        case WebRTC::Role::UN_DEFINED:
            break;
        default:
            break;
    }
        
    
}

void SDPO::OnFailure(webrtc::RTCError error)
{
    std::cout<<"create SDP failed"<<error.message()<<std::endl;
}

void SSDO::OnSuccess()
{
    if(webrtc_instance.set_sdp_type == WebRTC::SetSDPType::REMOTE)
    {
        webrtc_instance.hasSetRemoteSdp = true;
        webrtc_instance.startAddIceCandidateIntoPeer();
    }
    switch(webrtc_instance.currentRole)
    {
        case WebRTC::Role::RECEIVER:
            //当前设置的是远程SDP，需要发送事件
            if(webrtc_instance.set_sdp_type == WebRTC::SetSDPType::REMOTE)
            {
                webrtc_instance.display_void(EventBus::EventType::WebRTC_SetRemoteSdpOfferDone);
            }
            break;
        case WebRTC::Role::SENDER:
            break;
        case WebRTC::Role::UN_DEFINED:
            break;
    }
}
void SSDO::OnFailure(webrtc::RTCError error)
{
    std::cout<<"set SDP failed: "<<error.message()<<std::endl;
}