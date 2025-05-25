#pragma once
#include <queue>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <fstream>
#include <atomic>
#include <cstdint>
#include <string>

class FileReceiver {
public:
    FileReceiver();
    ~FileReceiver();

    void start(std::shared_ptr<std::ofstream> output_path);
    void stop();

    void onHeaderReceived(const uint8_t* data, size_t size);
    void onDataReceived(const uint8_t* data, size_t size);

private:
    void processQueue();
    void processHeader(const std::vector<uint8_t>& data);
    void processData(const std::vector<uint8_t>& data);

    std::queue<std::vector<uint8_t>> queue;
    std::mutex mutex;
    std::condition_variable cv;
    std::thread worker;
    std::shared_ptr<std::ofstream> out;
    std::atomic<bool> running;

    uint32_t file_total_size;
    uint32_t receive_size;

    static const uint16_t file_head_magic;
    static const uint16_t file_block_magic;
};
