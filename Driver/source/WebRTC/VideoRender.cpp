/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "VideoRender.h"
#include <iostream>

void VideoRender::setRenderInstance(RenderInterface* instance)
{
    this->instance = instance;
}

void VideoRender::OnFrame(const webrtc::VideoFrame& frame)
{
    if(!instance)
    {
        std::cout<<"instance is nullptr"<<std::endl;
        return;
    }
        
    const webrtc::I420BufferInterface* buffer = frame.video_frame_buffer()->GetI420();
    RenderInterface::VideoFrame render_frame;
    render_frame.y_plane = buffer->DataY();
    render_frame.u_plane = buffer->DataU();
    render_frame.v_plane = buffer->DataV();
    render_frame.width = buffer->width();
    render_frame.height = buffer->height();
    render_frame.stride_y = buffer->StrideY();
    render_frame.stride_u = buffer->StrideU();
    render_frame.stride_v = buffer->StrideV();
    instance->addRenderFrame(std::move(render_frame));
}

void VideoRender::closeRender()
{
    instance = nullptr;
}