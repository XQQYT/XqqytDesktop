#ifndef FILERECEIVER_H
#define FILERECEIVER_H

#include <functional>
#include <stdint.h>
#include <fstream>
#include <memory>

class FileReceiver
{
public:
    FileReceiver();
    ~FileReceiver();
    void startReceiveFile(std::shared_ptr<std::ofstream> instance);
    void hasFileHeader(const uint8_t* header, uint16_t length);
    void hasFileData(const uint8_t* data, size_t length );
private:
    std::shared_ptr<std::ofstream> out;
    uint32_t file_total_size;
    uint32_t receive_size;
};

#endif //FILERECEIVER_H