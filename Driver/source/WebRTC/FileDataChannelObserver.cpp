/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "FileDataChannelObserver.h"
#include <iostream>
#include <string>
#include "MouseKeyboardType.h"
#include <unordered_map>
#include "WebRTC.h"
#include <arpa/inet.h>

static uint16_t file_head_magic = htons(0xABCD);
static uint16_t file_block_magic = htons(0xABAB);

FileDCO::FileDCO(WebRTC& instance)
    :webrtc_instance(instance)
{

}

void FileDCO::OnStateChange()
{

}

void FileDCO::OnMessage(const webrtc::DataBuffer& buffer)
{
    const uint8_t* data = buffer.data.data();
    size_t size = buffer.data.size();

    if(memcmp(data,&file_head_magic,2) == 0)
    {
        webrtc_instance.file_receiver->onHeaderReceived(data, size);
    } 
    if(memcmp(data,&file_block_magic,2) == 0)
    {
        webrtc_instance.file_receiver->onDataReceived(data, size);
    }
    else {
        std::cout<<"unknow binary"<<std::endl;
    }
}

void FileDCO::OnBufferedAmountChange(uint64_t sent_data_size) 
{

}
   
bool FileDCO::IsOkToCallOnTheNetworkThread() 
{ 
    return false; 
}