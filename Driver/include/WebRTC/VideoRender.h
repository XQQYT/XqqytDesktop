/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef _VIDEORENDER_H
#define _VIDEORENDER_H

#include "modules/video_capture/video_capture.h"
#include "Render.h"

class VideoRender : public rtc::VideoSinkInterface<webrtc::VideoFrame>{
    public:
        VideoRender(){}
        void OnDiscardedFrame() override {}
        // Called on the network thread when video constraints change.
        // TODO(crbug/1255737): make pure virtual once downstream project adapts.
        virtual void OnConstraintsChanged(
            const webrtc::VideoTrackSourceConstraints& constraints) {}

        void OnFrame(const webrtc::VideoFrame& frame) override;
        void setRenderInstance(RenderInterface* instance);
        void closeRender();
    private:
        RenderInterface* instance;
    };
    

#endif