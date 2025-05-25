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
#include <functional>

class FileReceiver {
public:
    FileReceiver();
    ~FileReceiver();

    void start(std::shared_ptr<std::ofstream> output_path);
    void stop();

    void onHeaderReceived(const uint8_t* data, size_t size);
    void onDataReceived(const uint8_t* data, size_t size);

    void setProgressCb(std::function<void(uint16_t,uint32_t,uint32_t)> cb);
private:
    void processQueue();
    void processHeader(const std::vector<uint8_t>& data);
    void processData(const std::vector<uint8_t>& data);

    std::queue<std::vector<uint8_t>> queue;
    std::mutex mutex;
    std::condition_variable cv;
    std::unique_ptr<std::thread> worker;
    std::shared_ptr<std::ofstream> cur_out;
    std::shared_ptr<std::ofstream> next_out;

    std::atomic<bool> running;

    uint32_t file_total_size;
    uint32_t receive_size;

    static const uint16_t file_head_magic;
    static const uint16_t file_block_magic;

    std::function<void(uint16_t,uint32_t,uint32_t)> progress_cb;

    uint16_t current_file_id; 
};
