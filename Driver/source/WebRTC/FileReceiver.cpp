#include "FileReceiver.h"
#include <memory.h>
#include <iostream>
#include <arpa/inet.h>
#include <cstdint>

FileReceiver::FileReceiver()
{
    file_total_size = 0;
    receive_size = 0;
}

FileReceiver::~FileReceiver()
{

}

void FileReceiver::startReceiveFile(std::ofstream* instance)
{
    out = instance;
}

void FileReceiver::hasFileHeader(const uint8_t* header, uint16_t length)
{
    for (int i = 0; i < 10; ++i)
        printf("%02X ", header[i]);
    printf("\n");

    uint16_t id;
    memcpy(&id, header + 2, sizeof(id));
    id = ntohs(id);

    uint32_t net_size;
    memcpy(&net_size, header + 4, sizeof(net_size));
    file_total_size = ntohl(net_size); 

    std::cout << "id: " << id << ", size: " << file_total_size << std::endl;
}

void FileReceiver::hasFileData(const uint8_t* data, size_t length )
{
    if (length < 2) return;

    out->write(reinterpret_cast<const char*>(data + 2), length - 2);
    receive_size += (length - 2);

    if (receive_size >= file_total_size)
    {
        out->close();
        receive_size = 0;
        file_total_size = 0;
        // delete out;
        // out = nullptr;
    }
}