/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef _RENDER_H
#define _RENDER_H

#include <stdint.h>

class RenderInterface
{
public:
    class VideoFrame {
    public:
        VideoFrame() = default;
        VideoFrame(VideoFrame&& obj)
        {
            y_plane = obj.y_plane;
            u_plane = obj.u_plane;
            v_plane = obj.v_plane;
            width = obj.width;
            height = obj.height;
            stride_y = obj.stride_y;
            stride_u = obj.stride_u;
            stride_v = obj.stride_v;
            timestamp = obj.timestamp;
        }
        VideoFrame& operator=(const VideoFrame& obj)
        {
            y_plane = obj.y_plane;
            u_plane = obj.u_plane;
            v_plane = obj.v_plane;
            width = obj.width;
            height = obj.height;
            stride_y = obj.stride_y;
            stride_u = obj.stride_u;
            stride_v = obj.stride_v;
            timestamp = obj.timestamp;
        }
    public:
        const uint8_t* y_plane;   // Y 分量
        const uint8_t* u_plane;   // U 分量
        const uint8_t* v_plane;   // V 分量
        int width;                // 图像宽度
        int height;               // 图像高度
        int stride_y;             // Y 分量的跨度
        int stride_u;             // U 分量的跨度
        int stride_v;             // V 分量的跨度
        uint64_t timestamp;       // 时间戳（可选）
    };
public:
    RenderInterface() = default;
    virtual ~RenderInterface(){};
    virtual void addRenderFrame(VideoFrame&&) = 0;
};

#endif
