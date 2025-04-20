#include "WebRTC.h"

WebRTC::WebRTC(Operator& base_operator):
  webrtc_operator(base_operator)
{
  pco = std::make_unique<PCO>(*this);
  sdpo = new rtc::RefCountedObject<SDPO>(*this);
  ssdo = new rtc::RefCountedObject<SSDO>(*this);
  currentRole = Role::UN_DEFINED; 
}

void WebRTC::initWebRTC()
{
    std::cout << "init WebRTC"<<std::endl;

    network_thread = rtc::Thread::CreateWithSocketServer();
    network_thread->Start();
    worker_thread = rtc::Thread::Create();
    worker_thread->Start();
    signaling_thread = rtc::Thread::Create();
    signaling_thread->Start();
    webrtc::PeerConnectionFactoryDependencies dependencies;
    dependencies.network_thread   = network_thread.get();
    dependencies.worker_thread    = worker_thread.get();
    dependencies.signaling_thread = signaling_thread.get();
    peer_connection_factory = webrtc::CreatePeerConnectionFactory(
      network_thread.get(),
      worker_thread.get(),
      signaling_thread.get(),
      nullptr, // default audio device module
      webrtc::CreateBuiltinAudioEncoderFactory(),
      webrtc::CreateBuiltinAudioDecoderFactory(),
      nullptr, // default video encoder factory
      nullptr, // default video decoder factory
      nullptr, // audio_mixer
      nullptr  // audio_processing
  );
    if (peer_connection_factory.get() == nullptr) {
      std::cout << "Error on CreateModularPeerConnectionFactory." << std::endl;
      exit(EXIT_FAILURE);
    }
    configuration.sdp_semantics = webrtc::SdpSemantics::kUnifiedPlan;
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
    
    // 创建音频 track 并添加
    cricket::AudioOptions audio_options;
    rtc::scoped_refptr<webrtc::AudioSourceInterface> audio_source =
        peer_connection_factory->CreateAudioSource(audio_options);

    rtc::scoped_refptr<webrtc::AudioTrackInterface> audio_track =
        peer_connection_factory->CreateAudioTrack("audio_track", audio_source.get());
    
    if (audio_track) {
        auto result = peer_connection->AddTrack(audio_track, {"media_stream"});
        if (!result.ok()) {
            std::cerr << "Failed to add audio track: " << result.error().message() << std::endl;
        } else {
            std::cout << "Audio track added successfully." << std::endl;
        }
    }
  
      webrtc::DataChannelInit config;
      data_channel = peer_connection->CreateDataChannel("data_channel", &config);
      data_channel->RegisterObserver(&dco);
      
      signaling_thread->PostTask([this](){
        webrtc::PeerConnectionInterface::RTCOfferAnswerOptions option;
        peer_connection->CreateOffer(sdpo.get(), option);
      });
      break;
    }
    case SDPType::ANSWER:
    {
      if (!peer_connection || !sdpo) {
        std::cerr << "Error: peer_connection or sdpo is null" << std::endl;
        return;
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
  peer_connection->SetLocalDescription(ssdo.get(),desc);
}

void WebRTC::setRemoteSDP(std::string remote_sdp)
{
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
    webrtc::SdpType::kOffer,remote_sdp, &error);
  std::cout<<remote_sdp<<std::endl;
  if (!session_description) {
      std::cerr << "Failed to parse SDP: " << error.description << std::endl;
      return;
  }
  signaling_thread->PostTask([this, sd = std::move(session_description)]() mutable {
  // 正确调用 SetRemoteDescription
    peer_connection->SetRemoteDescription(ssdo.get(), sd.release());
  });

}

void WebRTC::display_string(std::string event_name,std::string str)
{
  webrtc_operator.dispatch_string(std::move(event_name),std::move(str));
}

void WebRTC::display_void(std::string event_name)
{
  webrtc_operator.dispatch_void(event_name);
}
