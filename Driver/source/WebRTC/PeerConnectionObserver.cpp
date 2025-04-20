#include "PeerConnectionObserver.h"
#include "WebRTC.h"
#include <iostream>
void PCO::OnSignalingChange(webrtc::PeerConnectionInterface::SignalingState new_state)
{
    std::cout<<"peer connection status change to "<<static_cast<int>(new_state)<<std::endl;
}

void PCO::OnAddStream(rtc::scoped_refptr<webrtc::MediaStreamInterface> stream)
{

}

void PCO::OnRemoveStream(rtc::scoped_refptr<webrtc::MediaStreamInterface> stream)
{

}

void PCO::OnDataChannel(rtc::scoped_refptr<webrtc::DataChannelInterface> data_channel)
{

}

void PCO::OnRenegotiationNeeded() 
{

}

void PCO::OnNegotiationNeededEvent(uint32_t event_id) 
{

}

void PCO::OnIceConnectionChange(webrtc::PeerConnectionInterface::IceConnectionState new_state)
{

}

void PCO::OnStandardizedIceConnectionChange(webrtc::PeerConnectionInterface::IceConnectionState new_state) 
{

}

void PCO::OnConnectionChange(webrtc::PeerConnectionInterface::PeerConnectionState new_state) 
{

}

void PCO::OnIceGatheringChange(webrtc::PeerConnectionInterface::IceGatheringState new_state)
{

}

void PCO::OnIceCandidate(const webrtc::IceCandidateInterface* candidate)
{

}


void PCO::OnIceCandidateError(const std::string& address,
                                 int port,
                                 const std::string& url,
                                 int error_code,
                                 const std::string& error_text) 
{

}


void PCO::OnIceCandidatesRemoved(const std::vector<cricket::Candidate>& candidates) 
{

}

void PCO::OnIceConnectionReceivingChange(bool receiving)
{

}

void PCO::OnIceSelectedCandidatePairChanged(const cricket::CandidatePairChangeEvent& event) 
{

}

void PCO::OnAddTrack(
    rtc::scoped_refptr<webrtc::RtpReceiverInterface> receiver,
    const std::vector<rtc::scoped_refptr<webrtc::MediaStreamInterface>>& streams) 
{

}

void PCO::OnTrack(rtc::scoped_refptr<webrtc::RtpTransceiverInterface> transceiver) 
{

}

void PCO::OnRemoveTrack(rtc::scoped_refptr<webrtc::RtpReceiverInterface> receiver) 
{

}

void PCO::OnInterestingUsage(int usage_pattern) 
{
    
}