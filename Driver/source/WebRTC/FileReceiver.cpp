#include "FileReceiver.h"
#include <iostream>
#include <cstring>
#include <arpa/inet.h>

const uint16_t FileReceiver::file_head_magic = htons(0xABCD);
const uint16_t FileReceiver::file_block_magic = htons(0xABAB);

FileReceiver::FileReceiver() : running(false), file_total_size(0), receive_size(0) {
    cur_out = nullptr;
    next_out = nullptr;
    file_total_size = 0;
    receive_size = 0;
}

FileReceiver::~FileReceiver() {
    stop();
}

void FileReceiver::start(std::shared_ptr<std::ofstream> file_out) {
    std::lock_guard<std::mutex> lock(mutex);
    if(cur_out)
        next_out = file_out;
    else
        cur_out = file_out;
    running = true;

    if (!worker) {
        worker = std::make_unique<std::thread>(&FileReceiver::processQueue, this);
    }
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
    if (cur_out && cur_out->is_open()) {
        cur_out->close();
    }

    if (next_out && next_out->is_open()) {
        next_out->close();
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
    std::cout<<"have file header"<<std::endl;
    uint16_t id;
    memcpy(&id, data.data() + 2, sizeof(id));
    current_file_id = ntohs(id);
    uint32_t size;
    memcpy(&size, data.data() + 4, sizeof(size));
    file_total_size = ntohl(size);
    receive_size = 0;
}

void FileReceiver::processData(const std::vector<uint8_t>& data) {
    if(!cur_out)
    {
        std::cout<<"out is nullptr"<<std::endl;
    }
    if (cur_out->is_open()) {
        cur_out->write(reinterpret_cast<const char*>(data.data() + 2), data.size() - 2);
        receive_size += (data.size() - 2);
        if(progress_cb)
            progress_cb(current_file_id,receive_size, file_total_size);

        if (receive_size >= file_total_size) {
            std::cout << "File received completely.\n";
            cur_out->close();
            cur_out.reset();
            cur_out = nullptr;
            if(next_out)
            {
                cur_out = next_out;
                next_out = nullptr;
            }
        }
    }
}

void FileReceiver::setProgressCb(std::function<void(uint16_t,uint32_t,uint32_t)> cb)
{
    progress_cb = cb;
}