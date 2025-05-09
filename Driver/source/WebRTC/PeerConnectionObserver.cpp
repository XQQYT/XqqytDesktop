/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "PeerConnectionObserver.h"
#include "WebRTC.h"
#include "PulseAudioPlayer.h"
#include <iostream>

void PCO::OnSignalingChange(webrtc::PeerConnectionInterface::SignalingState new_state)
{

}

void PCO::OnAddStream(rtc::scoped_refptr<webrtc::MediaStreamInterface> stream)
{

}

void PCO::OnRemoveStream(rtc::scoped_refptr<webrtc::MediaStreamInterface> stream)
{

}

void PCO::OnDataChannel(rtc::scoped_refptr<webrtc::DataChannelInterface> data_channel)
{
    webrtc_instance.data_channel = data_channel;
    webrtc_instance.data_channel->RegisterObserver(webrtc_instance.dco.get());
}

void PCO::OnRenegotiationNeeded() 
{

}

void PCO::OnNegotiationNeededEvent(uint32_t event_id) 
{

}

void PCO::OnIceConnectionChange(webrtc::PeerConnectionInterface::IceConnectionState new_state)
{
    bool status_has_changed = false;
    switch (new_state) {
        case webrtc::PeerConnectionInterface::IceConnectionState::kIceConnectionNew:
            std::cout << "状态：新建 ICE 连接" << std::endl;
            break;
        case webrtc::PeerConnectionInterface::IceConnectionState::kIceConnectionChecking:
            std::cout << "状态：正在检查候选对" << std::endl;
            break;
        case webrtc::PeerConnectionInterface::IceConnectionState::kIceConnectionConnected:
            webrtc_instance.ice_status = WebRTCInterface::ConnectionStatus::SUCCESSED;
            status_has_changed = true;
            std::cout << "✅ ICE 连接已建立" << std::endl;
            break;
        case webrtc::PeerConnectionInterface::IceConnectionState::kIceConnectionCompleted:
            std::cout << "🎉 ICE 连接已完成（收集完成并绑定）" << std::endl;
            break;
        case webrtc::PeerConnectionInterface::IceConnectionState::kIceConnectionDisconnected:
            webrtc_instance.ice_status = WebRTCInterface::ConnectionStatus::FAILED;
            status_has_changed = true;
            std::cout << "⚠️ ICE 连接断开（可能会恢复）" << std::endl;
            break;
        case webrtc::PeerConnectionInterface::IceConnectionState::kIceConnectionFailed:
            webrtc_instance.ice_status = WebRTCInterface::ConnectionStatus::FAILED;
            status_has_changed = true;
            std::cout << "❌ ICE 连接失败" << std::endl;
            break;
        case webrtc::PeerConnectionInterface::IceConnectionState::kIceConnectionClosed:
            webrtc_instance.ice_status = WebRTCInterface::ConnectionStatus::FAILED;
            status_has_changed = true;
            std::cout << "🔒 ICE 连接关闭" << std::endl;
            break;
        default:
            std::cout << "未知 ICE 状态" << std::endl;
            break;
    }
    //check connection status only when ice status and peerconnection status is ready
    if(status_has_changed && webrtc_instance.peerconnection_status != WebRTCInterface::ConnectionStatus::UN_DEFINED)
    {
        webrtc_instance.checkConnectionStatus();
    }
}

void PCO::OnStandardizedIceConnectionChange(webrtc::PeerConnectionInterface::IceConnectionState new_state) 
{

}

void PCO::OnConnectionChange(webrtc::PeerConnectionInterface::PeerConnectionState new_state) 
{
    bool status_has_changed = false;
    switch (new_state) {
        case webrtc::PeerConnectionInterface::PeerConnectionState::kNew:
            std::cout << "状态：新建连接" << std::endl;
            break;
        case webrtc::PeerConnectionInterface::PeerConnectionState::kConnecting:
            std::cout << "状态：正在连接..." << std::endl;
            break;
        case webrtc::PeerConnectionInterface::PeerConnectionState::kConnected:
            webrtc_instance.peerconnection_status = WebRTCInterface::ConnectionStatus::SUCCESSED;
            status_has_changed = true;
            std::cout << "✅ PeerConnection 已建立连接" << std::endl;
            break;
        case webrtc::PeerConnectionInterface::PeerConnectionState::kDisconnected:
            webrtc_instance.peerconnection_status = WebRTCInterface::ConnectionStatus::FAILED;
            status_has_changed = true;
            std::cout << "⚠️ 连接中断（可恢复）" << std::endl;
            break;
        case webrtc::PeerConnectionInterface::PeerConnectionState::kFailed:
            webrtc_instance.peerconnection_status = WebRTCInterface::ConnectionStatus::FAILED;
            status_has_changed = true;
            std::cout << "❌ 连接失败" << std::endl;
            break;
        case webrtc::PeerConnectionInterface::PeerConnectionState::kClosed:
            webrtc_instance.peerconnection_status = WebRTCInterface::ConnectionStatus::FAILED;
            status_has_changed = true;
            std::cout << "🔒 连接关闭" << std::endl;
            break;
    }
    if(status_has_changed && webrtc_instance.ice_status != WebRTCInterface::ConnectionStatus::UN_DEFINED)
    {
        webrtc_instance.checkConnectionStatus();
    }
}

void PCO::OnIceGatheringChange(webrtc::PeerConnectionInterface::IceGatheringState new_state)
{
    if (new_state == webrtc::PeerConnectionInterface::kIceGatheringComplete) {
        webrtc_instance.display_void("/webrtc/send_ice_gather_done");
    }
}

void PCO::OnIceCandidate(const webrtc::IceCandidateInterface* candidate)
{
    std::string candidate_str;
    candidate->ToString(&candidate_str);
    std::string sdp_mid = candidate->sdp_mid();
    int sdp_mline_index = candidate->sdp_mline_index();
    webrtc_instance.display_string_string_string("/webrtc/send_ice_candidate", std::move(candidate_str),
                                                std::move(sdp_mid), std::move(std::to_string(sdp_mline_index)));
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
    std::cout<<"onTrack"<<std::endl;
    auto receiver = transceiver->receiver();
    auto track = receiver->track();
    if (track && track->kind() == webrtc::MediaStreamTrackInterface::kVideoKind)
    {
        auto video_track = static_cast<webrtc::VideoTrackInterface*>(track.get());
        video_track->AddOrUpdateSink(webrtc_instance.video_render.get(), rtc::VideoSinkWants());
    }
    else if (track->kind() == webrtc::MediaStreamTrackInterface::kAudioKind)
    {
        auto audio_track = static_cast<webrtc::AudioTrackInterface*>(track.get());
        webrtc_instance.audio_player = std::make_unique<PulseAudioPlayer>();
        // 连接音频 sink
        audio_track->AddSink(webrtc_instance.audio_player.get());
        std::cout << "Audio track added to PulseAudio player." << std::endl;
    }
}

void PCO::OnRemoveTrack(rtc::scoped_refptr<webrtc::RtpReceiverInterface> receiver) 
{

}

void PCO::OnInterestingUsage(int usage_pattern) 
{
    
}