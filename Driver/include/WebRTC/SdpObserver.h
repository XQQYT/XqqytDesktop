#ifndef _SDPOBSERVER_H
#define _SDPOBSERVER_H

#include <netinet/in.h> 
#include <sys/socket.h>

#include "api/create_peerconnection_factory.h"
#include "rtc_base/platform_thread_types.h"
#include "rtc_base/thread.h"
#include <iostream>
class WebRTC;
class SDPO : public webrtc::CreateSessionDescriptionObserver {
 public:
  SDPO(WebRTC& instance):webrtc_instance(instance){};
  // This callback transfers the ownership of the `desc`.
  // TODO(deadbeef): Make this take an std::unique_ptr<> to avoid confusion
  // around ownership.
  void OnSuccess(webrtc::SessionDescriptionInterface* desc) override;
  // The OnFailure callback takes an RTCError, which consists of an
  // error code and a string.
  // RTCError is non-copyable, so it must be passed using std::move.
  // Earlier versions of the API used a string argument. This version
  // is removed; its functionality was the same as passing
  // error.message.
  void OnFailure(webrtc::RTCError error) override;

 protected:
  ~SDPO() override = default;
private:
    WebRTC& webrtc_instance;
};

class SSDO : public webrtc::SetSessionDescriptionObserver {
  public:
      explicit SSDO(WebRTC& webrtc) : webrtc_instance(webrtc) {}
      void OnSuccess();
      void OnFailure(webrtc::RTCError error);
  protected:
      ~SSDO() = default;
  private:
      WebRTC& webrtc_instance;
  };

#endif