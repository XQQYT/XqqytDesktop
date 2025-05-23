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

    std::string filename(reinterpret_cast<const char*>(header + 8), 20);
    size_t null_pos = filename.find('\0');
    if (null_pos != std::string::npos)
        filename.erase(null_pos);

    std::cout << "id: " << id << ", size: " << file_total_size << ", filename: " << filename << std::endl;
}

void FileReceiver::hasFileData(const uint8_t* data, size_t length )
{
    out->write(reinterpret_cast<const char*>(data), length);
    receive_size += length;
    if(receive_size >= file_total_size)
    {
        out->close();
        delete out;
        out = nullptr;
    }
}