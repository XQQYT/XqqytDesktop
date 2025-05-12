/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "DataChannelObserver.h"
#include <iostream>
#include <string>
#include "MouseKeyboardType.h"
#include <unordered_map>
#include "WebRTC.h"

DCO::DCO(WebRTC& instance)
    :webrtc_instance(instance)
{
    driver = std::make_unique<X11KeyboardMouseDriver>();
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

    } else if (size == sizeof(KeyEventPacket)) {
        KeyEventPacket packet;
        std::memcpy(&packet, data, sizeof(KeyEventPacket));
        driver->syncKeyboard(packet);

        // 打印 KeyEventPacket 信息
        std::ostringstream oss;
        oss << "Received KeyEventPacket: { ";

        oss << "key: 0x" << std::hex << packet.key << std::dec << ", ";
        oss << "modifiers: 0x" << std::hex << packet.modifiers << std::dec << ", ";
        oss << "is_pressed: " << static_cast<int>(packet.is_pressed);

        oss << " }";

        std::cout << oss.str() << std::endl;
    } else {
        // 处理字符串消息
        std::string msg(reinterpret_cast<const char*>(data), size-1); // 直接构造
        if (msg == "close_webrtc") 
        {
            // webrtc_instance.clipboard_monitor->stopMonitor();
            webrtc_instance.display_void("/control/recv_close_control");
            std::cout << "Received close_webrtc command, closing connection..." << std::endl;
        } 
        else 
        {
            std::cerr << "Received unknown text message: " << msg << std::endl;
        }
    }
}

void DCO::OnBufferedAmountChange(uint64_t sent_data_size) 
{

}
   
bool DCO::IsOkToCallOnTheNetworkThread() 
{ 
    return false; 
}