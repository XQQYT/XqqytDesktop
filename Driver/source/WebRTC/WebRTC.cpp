/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "WebRTC.h"

#include "api/audio_codecs/builtin_audio_decoder_factory.h"
#include "api/audio_codecs/builtin_audio_encoder_factory.h"
#include "api/video_codecs/video_decoder_factory_template.h"
#include "api/video_codecs/video_decoder_factory_template_dav1d_adapter.h"
#include "api/video_codecs/video_decoder_factory_template_libvpx_vp8_adapter.h"
#include "api/video_codecs/video_decoder_factory_template_libvpx_vp9_adapter.h"
#include "api/video_codecs/video_decoder_factory_template_open_h264_adapter.h"
#include "api/video_codecs/video_encoder_factory_template.h"
#include "api/video_codecs/video_encoder_factory_template_libaom_av1_adapter.h"
#include "api/video_codecs/video_encoder_factory_template_libvpx_vp8_adapter.h"
#include "api/video_codecs/video_encoder_factory_template_libvpx_vp9_adapter.h"
#include "api/video_codecs/video_encoder_factory_template_open_h264_adapter.h"
#include "api/task_queue/default_task_queue_factory.h"

#include <string.h>
#include "PulseAudioCapture.h"
#include "ClipboardDriver/X11ClipboardDriver.h"

WebRTC::WebRTC(Operator& base_operator):
  webrtc_operator(base_operator)
{
  pco = std::make_unique<PCO>(*this);
  dco = std::make_unique<DCO>(*this);
  clipboard_driver = std::make_unique<X11ClipboardDriver>(*this);
  sdpo = new rtc::RefCountedObject<SDPO>(*this);
  ssdo = new rtc::RefCountedObject<SSDO>(*this);
  currentRole = Role::UN_DEFINED; 
  set_sdp_type = SetSDPType::UNDEFINED;
  ice_candidate_list.reserve(5);
  hasSetRemoteSdp = false;
  ice_status = WebRTCInterface::ConnectionStatus::UN_DEFINED;
  peerconnection_status = WebRTCInterface::ConnectionStatus::UN_DEFINED;
  webrtc_ready = false;
  adm = nullptr;
}

void WebRTC::initWebRTC(bool is_offer)
{
    std::cout << "init WebRTC"<<std::endl;

    network_thread = rtc::Thread::CreateWithSocketServer();
    network_thread->Start();
    worker_thread = rtc::Thread::Create();
    worker_thread->Start();
    signaling_thread = rtc::Thread::Create();
    signaling_thread->Start();

    if(!is_offer)
    {
      auto task_queue_factory = webrtc::CreateDefaultTaskQueueFactory();
      adm = PulseAudioCapture::Create(webrtc::AudioDeviceModule::kLinuxPulseAudio, task_queue_factory.get());
    }
    peer_connection_factory = webrtc::CreatePeerConnectionFactory(
      network_thread.get(),
      worker_thread.get(),
      signaling_thread.get(),
      adm,
      webrtc::CreateBuiltinAudioEncoderFactory(),
      webrtc::CreateBuiltinAudioDecoderFactory(),
      std::make_unique<webrtc::VideoEncoderFactoryTemplate<
        webrtc::LibvpxVp8EncoderTemplateAdapter,
        webrtc::LibvpxVp9EncoderTemplateAdapter,
        webrtc::OpenH264EncoderTemplateAdapter,
        webrtc::LibaomAv1EncoderTemplateAdapter>>(),
        std::make_unique<webrtc::VideoDecoderFactoryTemplate<
        webrtc::LibvpxVp8DecoderTemplateAdapter,
        webrtc::LibvpxVp9DecoderTemplateAdapter,
        webrtc::OpenH264DecoderTemplateAdapter,
        webrtc::Dav1dDecoderTemplateAdapter>>(),
      nullptr, // audio_mixer
      nullptr  // audio_processing
  );

    
    if (peer_connection_factory.get() == nullptr) {
      std::cout << "Error on CreateModularPeerConnectionFactory." << std::endl;
      exit(EXIT_FAILURE);
    }
    
    configuration.sdp_semantics = webrtc::SdpSemantics::kUnifiedPlan;

    signaling_thread->PostTask([this](){
      // 创建音频 track
      cricket::AudioOptions audio_options;
      rtc::scoped_refptr<webrtc::AudioSourceInterface> audio_source =
      peer_connection_factory->CreateAudioSource(audio_options);
      desktop_audio_track = peer_connection_factory->CreateAudioTrack("desktop_audio_track", audio_source.get());

      auto capture_option = webrtc::DesktopCaptureOptions::CreateDefault();
      std::unique_ptr<webrtc::DesktopCapturer> capturer = webrtc::DesktopCapturer::CreateScreenCapturer(capture_option);
      if (!capturer) {
        std::cerr << "Failed to create DesktopCapturer!" << std::endl;
      } else {
        std::cout << "DesktopCapturer created successfully!" << std::endl;
      }
      desktop_source = rtc::make_ref_counted<DesktopCaptureSource>(std::move(capturer));
      desktop_video_track = peer_connection_factory->CreateVideoTrack(desktop_source,"desktop_video_track");
  });
  std::cout << "init WebRTC done"<<std::endl;

  if(!is_offer)
    webrtc_operator.dispatch_void(EventBus::EventType::WebRTC_InitWebrtcDone);
  webrtc_ready = true;
}

void WebRTC::createSDP(SDPType type)
{  
    switch(type){
    case SDPType::OFFER:
    {
      currentRole = Role::SENDER;
      if (!peer_connection) {
        peer_connection = peer_connection_factory->CreatePeerConnection(
            configuration, nullptr, nullptr, pco.get());
      }
      if (!peer_connection) {
        std::cerr << "Error on CreatePeerConnection." << std::endl;
        return;
      }
      video_render = std::make_unique<VideoRender>();
      webrtc::DataChannelInit config;
      data_channel = peer_connection->CreateDataChannel("data_channel", &config);
      data_channel->RegisterObserver(dco.get());
      
      signaling_thread->PostTask([this](){
        webrtc::PeerConnectionInterface::RTCOfferAnswerOptions options;
        options.offer_to_receive_video = 1;  // 接收视频
        options.offer_to_receive_audio = 1;  // 接收音频
        peer_connection->CreateOffer(sdpo.get(), options);
      });
      break;
    }
    case SDPType::ANSWER:
    {
      if (!peer_connection || !sdpo) {
        std::cerr << "Error: peer_connection or sdpo is null" << std::endl;
        return;
      }
      if (desktop_audio_track) {
        auto result = peer_connection->AddTrack(desktop_audio_track, {"desktop_audio_stream"});
        if (!result.ok()) {
            std::cerr << "Failed to add audio track: " << result.error().message() << std::endl;
        } else {
            std::cout << "Audio track added successfully." << std::endl;
        }
      }
      if (desktop_video_track) {
        auto result = peer_connection->AddTrack(desktop_video_track, {"desktop_video_stream"});
        if (!result.ok()) {
            std::cerr << "Failed to add video track: " << result.error().message() << std::endl;
        } else {
            std::cout << "Audio track video successfully." << std::endl;
        }
      }
      signaling_thread->PostTask([this](){
        peer_connection->CreateAnswer(sdpo.get(), webrtc::PeerConnectionInterface::RTCOfferAnswerOptions());
      });
      break;
    }
    default:
      break;
  }
}

void WebRTC::setLocalSDP(webrtc::SessionDescriptionInterface* desc)
{
  signaling_thread->PostTask([this, desc](){
    set_sdp_type = SetSDPType::LOCAL;
    peer_connection->SetLocalDescription(ssdo.get(),desc);
  });
}

void WebRTC::setRemoteSDP(std::string remote_sdp, SDPType type)
{
  //远程SDP为offer，说明角色为receiver
  if(type == SDPType::OFFER)
    currentRole = Role::RECEIVER;
  if(!peer_connection)
  {
    peer_connection = peer_connection_factory->CreatePeerConnection(
      configuration, nullptr, nullptr, pco.get());
  }
  if (!peer_connection) {
      std::cerr << "Error creating PeerConnection" << std::endl;
      return;
  }

  webrtc::SdpParseError error;
  auto session_description = webrtc::CreateSessionDescription(
    type == SDPType::ANSWER?webrtc::SdpType::kAnswer:webrtc::SdpType::kOffer,remote_sdp, &error);
  if (!session_description) {
      std::cerr << "Failed to parse SDP: " << error.description << std::endl;
      return;
  }
  signaling_thread->PostTask([this, sd = std::move(session_description)]() mutable {
    set_sdp_type = SetSDPType::REMOTE;
  // 正确调用 SetRemoteDescription
    peer_connection->SetRemoteDescription(ssdo.get(), sd.release());
  });

}

void WebRTC::display_string(EventBus::EventType event_name,std::string str)
{
  webrtc_operator.dispatch_string(event_name,std::move(str));
}

void WebRTC::display_string_string_string(EventBus::EventType event_name,std::string str1,std::string str2,std::string str3)
{
  webrtc_operator.dispatch_string_string_string(event_name,std::move(str1),std::move(str2),std::move(str3));
}


void WebRTC::display_void(EventBus::EventType event_name)
{
  webrtc_operator.dispatch_void(event_name);
}

void WebRTC::dispatch_bool(EventBus::EventType event_name,bool status)
{
  webrtc_operator.dispatch_bool(event_name,status);
}

void WebRTC::AddIceCandidate(std::string ice_str,std::string sdp_mid,int sdp_mline_index)
{
  webrtc::SdpParseError error;
  webrtc::IceCandidateInterface* candidate =
  webrtc::CreateIceCandidate(sdp_mid, sdp_mline_index, ice_str, &error);
  if (!candidate)
  {
    std::cerr << "Failed to parse ICE candidate: " << error.description << std::endl;
  }

  if (!peer_connection->AddIceCandidate(candidate))
  {
    std::cerr << "Failed to add ICE candidate." << std::endl;
  }
}

void WebRTC::addIceCandidateIntoBuffer(std::string ice_str,std::string sdp_mid,int sdp_mline_index)
{
  if(!hasSetRemoteSdp)
  {    
    ice_candidate_list.emplace_back(std::move(ice_str), std::move(sdp_mid), sdp_mline_index);
  }
  else
  {
    AddIceCandidate(ice_str,sdp_mid,sdp_mline_index);
  }
}

void WebRTC::startAddIceCandidateIntoPeer()
{
  std::cout<<"startAddIceCandidateIntoPeer  "<<ice_candidate_list.size()<<std::endl;
  for (auto& ice : ice_candidate_list)
  {
    AddIceCandidate(ice.ice_str,ice.sdp_mid,ice.sdp_mline_index);
  }
  ice_candidate_list.clear();
}

void WebRTC::checkConnectionStatus()
{
  if (!peer_connection) {
    std::cerr << "checkConnectionStatus called before PeerConnection is created." << std::endl;
    webrtc_operator.dispatch_bool(EventBus::EventType::WebRTC_ConnectionStatus, false);
    return;
  }
  bool connection_status = peer_connection->ice_connection_state() == webrtc::PeerConnectionInterface::IceConnectionState::kIceConnectionConnected && 
    peer_connection->peer_connection_state() == webrtc::PeerConnectionInterface::PeerConnectionState::kConnected;
  webrtc_operator.dispatch_bool(EventBus::EventType::WebRTC_ConnectionStatus,connection_status);
  if(connection_status)
  {
    clipboard_driver->startMonitor();
    if(currentRole == Role::RECEIVER)
      startCaptureDesktop();
  }
}

void WebRTC::startCaptureDesktop()
{
  auto desktop_source_ptr = dynamic_cast<DesktopCaptureSource*>(desktop_source.get());
    if (desktop_source_ptr) {
      desktop_source_ptr->setCaptureRate(webrtc_capture_rate);
      desktop_source_ptr->Start();
    } else {
        std::cerr << "Failed to cast to DesktopCaptureSource" << std::endl;
    }
}

void WebRTC::stopCaptureDesktop()
{
  auto desktop_source_ptr = dynamic_cast<DesktopCaptureSource*>(desktop_source.get());
    if (desktop_source_ptr) {
        desktop_source_ptr->Stop();
    } else {
        std::cerr << "Failed to cast to DesktopCaptureSource" << std::endl;
    }
}

void WebRTC::setRenderInstance(RenderInterface* instance)
{
  video_render->setRenderInstance(instance);
}

void WebRTC::sendMouseEventPacket(const MouseEventPacket packet)
{

  if (data_channel->state() == webrtc::DataChannelInterface::kOpen) 
  {
    const char* data = reinterpret_cast<const char*>(&packet);
    size_t size = sizeof(packet);
    rtc::CopyOnWriteBuffer buffer(data, size);
    webrtc::DataBuffer data_buffer(buffer, true);
    data_channel->Send(data_buffer);
  } else 
  {
    std::cerr << "DataChannel is not open, state: " << data_channel->state() << std::endl;
  }
}

void WebRTC::sendKeyboardEventPacket(const KeyEventPacket packet)
{
  if (data_channel->state() == webrtc::DataChannelInterface::kOpen) 
  {
    const char* data = reinterpret_cast<const char*>(&packet);
    size_t size = sizeof(packet);
    rtc::CopyOnWriteBuffer buffer(data, size);
    webrtc::DataBuffer data_buffer(buffer, true);
    data_channel->Send(data_buffer);
  } else 
  {
    std::cerr << "DataChannel is not open, state: " << data_channel->state() << std::endl;
  }
}

void WebRTC::sendCloseWebRTC()
{
    if (!data_channel || data_channel->state() != webrtc::DataChannelInterface::kOpen) {
        std::cerr << "DataChannel is not open or invalid, state: " 
                  << (data_channel ? std::to_string(data_channel->state()) : "nullptr") 
                  << std::endl;
        return;
    }

    static constexpr char kCloseMessage[] = "_close_webrtc_";
    rtc::CopyOnWriteBuffer buffer(kCloseMessage, strlen(kCloseMessage));
    webrtc::DataBuffer data_buffer(buffer, true);
    data_channel->Send(data_buffer);
}

void WebRTC::closeWebRTC()
{
  std::cout << "Closing WebRTC..." << std::endl;

  if(currentRole == WebRTCInterface::Role::SENDER)
    sendCloseWebRTC();
  if(currentRole == WebRTCInterface::Role::RECEIVER)
    stopCaptureDesktop();

  clipboard_driver->stopMonitor();

  if (video_render.get()) {
    video_render->closeRender();
    video_render.reset();
  }
  if (peer_connection) {
    peer_connection->Close();
    peer_connection = nullptr;
  }

  data_channel = nullptr;
  desktop_video_track = nullptr;
  desktop_audio_track = nullptr;
  desktop_source = nullptr;

  peer_connection_factory = nullptr;

  if (signaling_thread) {
      signaling_thread->Stop();
      signaling_thread = nullptr;
  }
  if (worker_thread) {
      worker_thread->Stop();
      worker_thread = nullptr;
  }
  if (network_thread) {
      network_thread->Stop();
      network_thread = nullptr;
  }

  currentRole = Role::UN_DEFINED; 
  set_sdp_type = SetSDPType::UNDEFINED;
  hasSetRemoteSdp = false;
  ice_status = WebRTCInterface::ConnectionStatus::UN_DEFINED;
  peerconnection_status = WebRTCInterface::ConnectionStatus::UN_DEFINED;
  webrtc_ready = false;
  std::cout << "WebRTC Closed." << std::endl;
}

bool WebRTC::getWebRtcReady()
{
  return webrtc_ready;
}

void WebRTC::setCaptureRate(int rate)
{
  if(desktop_source)
  {
    auto desktop_source_ptr = dynamic_cast<DesktopCaptureSource*>(desktop_source.get());
    desktop_source_ptr->setCaptureRate(rate);
  }
  webrtc_capture_rate = rate;
 
  std::cout<<"set capture rate  "<<rate<<std::endl;
}

void WebRTC::sendClipboardContent(std::string content)
{
    if (content.empty()) return;
    content.insert(0,"[clipboard]");
    sendToPeer(std::move(content));
}

void WebRTC::writeIntoClipboard(std::string str)
{
  clipboard_driver->setClipboardText(std::move(str));
}

void WebRTC::sendToPeer(std::string msg)
{
  if (msg.empty()) return;

  if (!data_channel || data_channel->state() != webrtc::DataChannelInterface::kOpen) {
      std::cerr << "DataChannel is not open\n";
      return;
  }
  rtc::CopyOnWriteBuffer buffer(reinterpret_cast<const uint8_t*>(msg.data()), msg.size());
  webrtc::DataBuffer data_buffer(buffer, true);
  data_channel->Send(data_buffer);
  std::cout<<"send"<<msg<<std::endl;
}

void WebRTC::sendFileSync(std::string msg)
{
  if (msg.empty()) return;
  msg.insert(0,"[filesync]");
  sendToPeer(std::move(msg));
}