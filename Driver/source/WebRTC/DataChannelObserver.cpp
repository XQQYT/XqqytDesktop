#include "DataChannelObserver.h"
#include <iostream>
#include "MouseKeyboardType.h"

#include <unordered_map>

static std::string KeyToString(uint32_t key)
{
    static const std::unordered_map<uint32_t, std::string> key_map = {
        {0x20, "Space"},
        {0x0D, "Enter"},
        {0x08, "Backspace"},
        {0x09, "Tab"},
        {0x1B, "Escape"},
        {0x25, "Left Arrow"},
        {0x26, "Up Arrow"},
        {0x27, "Right Arrow"},
        {0x28, "Down Arrow"},
        {0x41, "A"},
        {0x42, "B"},
        {0x43, "C"},
        {0x44, "D"},
        {0x45, "E"},
        {0x46, "F"},
        {0x47, "G"},
        {0x48, "H"},
        {0x49, "I"},
        {0x4A, "J"},
        {0x4B, "K"},
        {0x4C, "L"},
        {0x4D, "M"},
        {0x4E, "N"},
        {0x4F, "O"},
        {0x50, "P"},
        {0x51, "Q"},
        {0x52, "R"},
        {0x53, "S"},
        {0x54, "T"},
        {0x55, "U"},
        {0x56, "V"},
        {0x57, "W"},
        {0x58, "X"},
        {0x59, "Y"},
        {0x5A, "Z"},
        {0x30, "0"},
        {0x31, "1"},
        {0x32, "2"},
        {0x33, "3"},
        {0x34, "4"},
        {0x35, "5"},
        {0x36, "6"},
        {0x37, "7"},
        {0x38, "8"},
        {0x39, "9"},
        // 你可以继续加需要的键
    };

    auto it = key_map.find(key);
    if (it != key_map.end()) {
        return it->second;
    }
    // 默认直接返回十六进制数
    char buf[16];
    snprintf(buf, sizeof(buf), "Unknown(0x%X)", key);
    return std::string(buf);
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

        std::ostringstream oss;
        oss << "Received MouseEventPacket: { ";
        
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

        std::ostringstream oss;
        oss << "Received KeyEventPacket: { ";
        oss << "key: " << KeyToString(packet.key) << ", ";
        oss << "modifiers: " << packet.modifiers << ", ";
        oss << "is_pressed: " << (packet.is_pressed ? "true" : "false");
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