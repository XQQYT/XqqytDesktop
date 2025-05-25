#include "FileSender.h"
#include "WebRTC.h"
#include <filesystem>
#include <arpa/inet.h>
#include <thread>
#include <future>
#include <iostream>
#include <fstream>

constexpr size_t MAX_BUFFERED_CONTROL_BYTES = 64 * 1024;

FileSender::FileSender(WebRTC& instance)
    :webrtc_instance(instance)
{
    file_total_size = 0;
    send_size = 0;
}

FileSender::~FileSender()
{
}

void FileSender::sendFile(uint16_t id, const std::string file_path)
{
    // 启动单独线程发送
    std::thread([this, id, file_path]() {
        auto header = buildHeader(id, file_path);
        size_t total_header_size = 8;
        size_t offset = 0;

        while (offset < total_header_size) {
            size_t chunk_size = std::min<size_t>(50, total_header_size - offset);
            webrtc_instance.sendToPeer(header.get() + offset, chunk_size);
            offset += chunk_size;
        }

        std::ifstream file(file_path, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << file_path << std::endl;
            return;
        }

        const size_t data_payload_size = 48 * 1024;
        uint8_t raw_buffer[data_payload_size];
        uint8_t send_buffer[50];
        uint16_t magic = htons(0xABAB);

        while (!file.eof()) {
            // 检查缓冲区状态
            while (webrtc_instance.file_data_channel->buffered_amount() > MAX_BUFFERED_CONTROL_BYTES) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }

            file.read(reinterpret_cast<char*>(raw_buffer), data_payload_size);
            std::streamsize bytes_read = file.gcount();
            if (bytes_read > 0) {
                memcpy(send_buffer, &magic, sizeof(magic));
                memcpy(send_buffer + 2, raw_buffer, bytes_read);
                webrtc_instance.sendToPeer(send_buffer, bytes_read + 2);
                send_size += bytes_read;
                if(progress_cb)
                    progress_cb(id, send_size, file_total_size);
            }
        }

        file.close();
        std::cout << "FileSender: Finished sending file " << file_path << std::endl;

    }).detach(); // 可考虑用 std::future/promise 代替 detach
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
    send_size = 0;
    file_total_size = file_size;
    current_id = id;
    uint32_t net_file_size = htonl(file_size);

    int offset = 0;

    memcpy(header.get() + offset, &magic, sizeof(magic)); offset += sizeof(magic);
    memcpy(header.get() + offset, &net_id, sizeof(net_id)); offset += sizeof(net_id);
    memcpy(header.get() + offset, &net_file_size, sizeof(net_file_size)); offset += sizeof(net_file_size);

    return header;
}

void FileSender::setProgressCb(std::function<void(uint16_t,uint32_t,uint32_t)> cb)
{
    progress_cb = cb;
}