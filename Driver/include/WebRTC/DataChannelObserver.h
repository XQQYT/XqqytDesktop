/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef _DATACHANNELOBSERVER_H
#define _DATACHANNELOBSERVER_H

#include "api/create_peerconnection_factory.h"
#include "KeyboardMouseDriver/X11.h"
#include <memory>

class WebRTC;
class DCO : public webrtc::DataChannelObserver {
    public:
    DCO(WebRTC& instance);
     // The data channel state have changed.
     void OnStateChange() override;
     //  A data buffer was successfully received.
     void OnMessage(const webrtc::DataBuffer& buffer) override;
     // The data channel's buffered_amount has changed.
     void OnBufferedAmountChange(uint64_t sent_data_size) override;
   
     // Override this to get callbacks directly on the network thread.
     // An implementation that does that must not block the network thread
     // but rather only use the callback to trigger asynchronous processing
     // elsewhere as a result of the notification.
     // The default return value, `false`, means that notifications will be
     // delivered on the signaling thread associated with the peerconnection
     // instance.
     // TODO(webrtc:11547): Eventually all DataChannelObserver implementations
     // should be called on the network thread and this method removed.
     bool IsOkToCallOnTheNetworkThread() override;
   
     ~DCO() = default;
    private:
      std::unique_ptr<KeyboardMouseInterface> driver; 
      WebRTC& webrtc_instance;
   };


   #endif