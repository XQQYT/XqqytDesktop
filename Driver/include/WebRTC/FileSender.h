#ifndef _FILESENDER_H
#define _FILESENDER_H

#include <string>
#include <memory>
#include <vector>
#include <filesystem>

class WebRTC;
class FileSender
{
public:
    FileSender(WebRTC& instance);
    ~FileSender();
    void sendFile(uint16_t id,std::string file_path);
private:
    std::unique_ptr<uint8_t[]> buildHeader(uint16_t id,const std::string& file_path);
    WebRTC& webrtc_instance;
};



#endif //_FILESENDER_H