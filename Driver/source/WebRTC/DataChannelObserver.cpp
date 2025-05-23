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
    keyboard_mouse_driver = std::make_unique<X11KeyboardMouseDriver>();
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
        keyboard_mouse_driver->syncMouseEvent(packet);

    } else if (size == sizeof(KeyEventPacket)) {
        KeyEventPacket packet;
        std::memcpy(&packet, data, sizeof(KeyEventPacket));
        keyboard_mouse_driver->syncKeyboard(packet);

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
        std::string msg(reinterpret_cast<const char*>(data), size); // 直接构造
        if (msg == "_close_webrtc_") 
        {
            webrtc_instance.clipboard_driver->stopMonitor();
            webrtc_instance.display_void(EventBus::EventType::Control_RecvCloseControl);
            std::cout << "Received close_webrtc command, closing connection..." << std::endl;
        } 
        else if (msg.size() >= 10 && msg.substr(0, 10) == "[filesync]") 
        {
            std::string payload = msg.substr(10);
            webrtc_instance.sync_file_callback(std::move(payload));
        }
        else if(msg.size() >= 11 && msg.substr(0,11) == "[clipboard]")
        {
            webrtc_instance.clipboard_driver->setClipboardText(msg.substr(11));
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