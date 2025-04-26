#include "DataChannelObserver.h"
#include <iostream>
#include "MouseKeyboardType.h"


void DCO::OnStateChange()
{

}
void DCO::OnMessage(const webrtc::DataBuffer& buffer)
{
    const uint8_t* data = buffer.data.data();
    size_t size = buffer.data.size();

    if (size < sizeof(MouseEventPacket)) {
        std::cerr << "Received data size too small for MouseEventPacket. Size: " << size << std::endl;
        return;
    }

    // 安全地拷贝到结构体
    MouseEventPacket packet;
    std::memcpy(&packet, data, sizeof(MouseEventPacket));

    // 打印结构体内容
    std::ostringstream oss;
    oss << "Received MouseEventPacket: { ";
    
    // 打印事件类型
    oss << "type: ";
    switch (packet.type) {
        case MouseEventType::Move: oss << "Move"; break;
        case MouseEventType::Press: oss << "Press"; break;
        case MouseEventType::Release: oss << "Release"; break;
        case MouseEventType::Wheel: oss << "Wheel"; break;
        case MouseEventType::Hold: oss << "Hold"; break;
        default: oss << "Unknown"; break;
    }
    oss << ", ";

    // 打印按钮
    oss << "button: ";
    switch (packet.button) {
        case MouseButton::NoButton: oss << "NoButton"; break;
        case MouseButton::LeftButton: oss << "LeftButton"; break;
        case MouseButton::RightButton: oss << "RightButton"; break;
        case MouseButton::MiddleButton: oss << "MiddleButton"; break;
        default: oss << "Unknown"; break;
    }
    oss << ", ";

    // 打印坐标和滚轮
    oss << "x: " << packet.x << ", ";
    oss << "y: " << packet.y << ", ";
    oss << "wheelDelta: " << packet.wheelDelta;

    oss << " }";

    std::cout << oss.str() << std::endl;
}

void DCO::OnBufferedAmountChange(uint64_t sent_data_size) 
{

}
   
bool DCO::IsOkToCallOnTheNetworkThread() 
{ 
    return false; 
}