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