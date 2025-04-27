#include "DataChannelObserver.h"
#include <iostream>
#include "MouseKeyboardType.h"
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <unordered_map>

DCO::DCO()
{
    driver = std::make_unique<X11Driver>();
}

void DCO::OnStateChange()
{

}
void DCO::OnMessage(const webrtc::DataBuffer& buffer)
{
    const uint8_t* data = buffer.data.data();
    size_t size = buffer.data.size();

    if (size == sizeof(MouseEventPacket)) {
        // 处理 MouseEventPacket
        MouseEventPacket packet;
        std::memcpy(&packet, data, sizeof(MouseEventPacket));
        driver->syncMouseEvent(packet);
        std::ostringstream oss;
        oss << "Received MouseEventPacket: { ";
        
        oss << "type: ";
        switch (packet.type) {
            case MouseEventType::Move: oss << "Move"; break;
            case MouseEventType::Press: oss << "Press"; break;
            case MouseEventType::Release: oss << "Release"; break;
            case MouseEventType::Wheel: oss << "Wheel"; break;
            default: oss << "Unknown"; break;
        }
        oss << ", ";

        oss << "button: ";
        switch (packet.button) {
            case MouseButton::NoButton: oss << "NoButton"; break;
            case MouseButton::LeftButton: oss << "LeftButton"; break;
            case MouseButton::RightButton: oss << "RightButton"; break;
            case MouseButton::MiddleButton: oss << "MiddleButton"; break;
            default: oss << "Unknown"; break;
        }
        oss << ", ";

        oss << "x: " << packet.x << ", ";
        oss << "y: " << packet.y << ", ";
        oss << "wheelDelta: " << packet.wheelDelta;

        oss << " }";

        std::cout << oss.str() << std::endl;

    } else if (size == sizeof(KeyEventPacket)) {
        KeyEventPacket packet;
        std::memcpy(&packet, data, sizeof(KeyEventPacket));
        driver->syncKeyboard(packet);
    } else {
        std::cerr << "Received unknown data size: " << size << std::endl;
    }
}

void DCO::OnBufferedAmountChange(uint64_t sent_data_size) 
{

}
   
bool DCO::IsOkToCallOnTheNetworkThread() 
{ 
    return false; 
}