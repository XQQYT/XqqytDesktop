#include "WebRTC.h"

WebRTC::WebRTC():
  sdpo(new rtc::RefCountedObject<SDPO>())
{
  is_first = true;
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
    peer_connection_factory       = webrtc::CreateModularPeerConnectionFactory(std::move(dependencies));

    if (peer_connection_factory.get() == nullptr) {
      std::cout << "Error on CreateModularPeerConnectionFactory." << std::endl;
      exit(EXIT_FAILURE);
    }
}

void WebRTC::createSDP()
{
  if(is_first)
  {
    initWebRTC();
    is_first = false;
  }
  peer_connection =peer_connection_factory->CreatePeerConnection(configuration, nullptr, nullptr, &pco);

    webrtc::DataChannelInit config;

    // Configuring DataChannel.
    data_channel = peer_connection->CreateDataChannel("data_channel", &config);
    data_channel->RegisterObserver(&dco);

    if (peer_connection.get() == nullptr) {
      peer_connection_factory = nullptr;
      std::cout << "Error on CreatePeerConnection." << std::endl;
      exit(EXIT_FAILURE);
    }
    peer_connection->CreateOffer(sdpo.get(), webrtc::PeerConnectionInterface::RTCOfferAnswerOptions());
}
