#include "SdpObserver.h"
#include <iostream>

void SDPO::OnSuccess(webrtc::SessionDescriptionInterface* desc)
{
    std::string desc_str;
    desc->ToString(&desc_str);
    std::cout<<"===  sdp  ==="<<desc_str<<std::endl;
}

void SDPO::OnFailure(webrtc::RTCError error)
{

}