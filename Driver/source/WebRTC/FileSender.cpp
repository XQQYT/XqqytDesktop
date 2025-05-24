#include "FileSender.h"
#include "WebRTC.h"
#include <filesystem>
#include <arpa/inet.h>

FileSender::FileSender(WebRTC& instance)
    :webrtc_instance(instance)
{

}

FileSender::~FileSender()
{

}

void FileSender::sendFile(uint16_t id, const std::string file_path)
{
    auto header = buildHeader(id, file_path);

    size_t total_header_size = 8;
    size_t offset = 0;
    while (offset < total_header_size) {
        size_t chunk_size = std::min<size_t>(50, total_header_size - offset);
        webrtc_instance.sendToPeer(header.get() + offset, chunk_size);
        offset += chunk_size;
    }

    // 打开文件
    std::ifstream file(file_path, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << file_path << std::endl;
        return;
    }

    const size_t data_payload_size = 48; // 因为我们加2字节magic，最多48字节数据
    uint8_t raw_buffer[data_payload_size];
    uint8_t send_buffer[50]; // 2字节magic + 48字节数据

    uint16_t magic = htons(0xABAB); // 转大端

    while (!file.eof()) {
        file.read(reinterpret_cast<char*>(raw_buffer), data_payload_size);
        std::streamsize bytes_read = file.gcount();
        if (bytes_read > 0) {
            memcpy(send_buffer, &magic, sizeof(magic)); // 写magic
            memcpy(send_buffer + 2, raw_buffer, bytes_read); // 写文件内容
            webrtc_instance.sendToPeer(send_buffer, bytes_read + 2); // 总长：数据长度 + 2
        }
    }

    file.close();
}


uint32_t getSendFileSize(const std::string& file_path) {
    try {
        std::filesystem::path path(file_path);
        if (std::filesystem::exists(path) && std::filesystem::is_regular_file(path)) {
            return static_cast<uint32_t>(std::filesystem::file_size(path));
        } else {
            return 0;
        }
    } catch (const std::filesystem::filesystem_error& e) {
        return 0;
    }
}

std::unique_ptr<uint8_t[]> FileSender::buildHeader(uint16_t id, const std::string& file_path)
{
    std::unique_ptr<uint8_t[]> header(new uint8_t[8]);

    uint16_t magic = htons(0xABCD);
    uint16_t net_id = htons(id);
    uint32_t file_size = getSendFileSize(file_path.c_str());
    uint32_t net_file_size = htonl(file_size);

    int offset = 0;

    memcpy(header.get() + offset, &magic, sizeof(magic)); offset += sizeof(magic);
    memcpy(header.get() + offset, &net_id, sizeof(net_id)); offset += sizeof(net_id);
    memcpy(header.get() + offset, &net_file_size, sizeof(net_file_size)); offset += sizeof(net_file_size);

    return header;
}