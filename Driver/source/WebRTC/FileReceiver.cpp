#include "FileReceiver.h"
#include <iostream>
#include <cstring>
#include <arpa/inet.h>

const uint16_t FileReceiver::file_head_magic = htons(0xABCD);
const uint16_t FileReceiver::file_block_magic = htons(0xABAB);

FileReceiver::FileReceiver() : running(false), file_total_size(0), receive_size(0) {
    out = nullptr;
}

FileReceiver::~FileReceiver() {
    stop();
}

void FileReceiver::start(std::shared_ptr<std::ofstream> file_out) {
    std::lock_guard<std::mutex> lock(mutex);
    if (worker && worker->joinable()) {
        std::cerr << "FileReceiver is already running.\n";
        return;
    }
    out = file_out;
    running = true;
    worker = std::make_unique<std::thread>(&FileReceiver::processQueue, this);
}

void FileReceiver::stop() {
    {
        std::lock_guard<std::mutex> lock(mutex);
        running = false;
        cv.notify_all();
    }
    if (worker && worker->joinable()) {
        worker->join();
        worker.reset();
    }
    if (out && out->is_open()) {
        out->close();
    }
}

void FileReceiver::onHeaderReceived(const uint8_t* data, size_t size) {
    std::vector<uint8_t> header(data, data + size);
    {
        std::lock_guard<std::mutex> lock(mutex);
        queue.push(std::move(header));
    }
    cv.notify_one();
}

void FileReceiver::onDataReceived(const uint8_t* data, size_t size) {
    std::vector<uint8_t> block(data, data + size);
    {
        std::lock_guard<std::mutex> lock(mutex);
        queue.push(std::move(block));
    }
    cv.notify_one();
}

void FileReceiver::processQueue() {
    while (running) {
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock, [this]() { return !queue.empty() || !running; });

        while (!queue.empty()) {
            auto data = std::move(queue.front());
            queue.pop();
            lock.unlock();

            if (memcmp(data.data(), &file_head_magic, 2) == 0) {
                processHeader(data);
            } else if (memcmp(data.data(), &file_block_magic, 2) == 0) {
                processData(data);
            } else {
                std::cerr << "Unknown data format\n";
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            lock.lock();
        }
    }
}

void FileReceiver::processHeader(const std::vector<uint8_t>& data) {
    uint16_t id;
    memcpy(&id, data.data() + 2, sizeof(id));
    id = ntohs(id);
    uint32_t size;
    memcpy(&size, data.data() + 4, sizeof(size));
    file_total_size = ntohl(size);
    receive_size = 0;
    std::cout << "Receiving file id=" << id << " size=" << file_total_size << "\n";
}

void FileReceiver::processData(const std::vector<uint8_t>& data) {
    if (out->is_open()) {
        out->write(reinterpret_cast<const char*>(data.data() + 2), data.size() - 2);
        receive_size += (data.size() - 2);
        std::cout << receive_size << "/" << file_total_size << std::endl;

        if (receive_size >= file_total_size) {
            std::cout << "File received completely.\n";
            out->close();
            out.reset();
            out = nullptr;
        }
    }
}
