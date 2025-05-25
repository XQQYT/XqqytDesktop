#ifndef _FILESENDER_H
#define _FILESENDER_H

#include <string>
#include <memory>
#include <vector>
#include <filesystem>
#include <functional>

class WebRTC;
class FileSender
{
public:
    FileSender(WebRTC& instance);
    ~FileSender();
    void sendFile(uint16_t id,std::string file_path);
    void setProgressCb(std::function<void(uint16_t,uint32_t,uint32_t)> cb);

private:
    std::unique_ptr<uint8_t[]> buildHeader(uint16_t id,const std::string& file_path);
    WebRTC& webrtc_instance;
    uint32_t file_total_size;
    uint32_t send_size;
    std::function<void(uint16_t,uint32_t,uint32_t)> progress_cb;
    uint16_t current_id;
};



#endif //_FILESENDER_H