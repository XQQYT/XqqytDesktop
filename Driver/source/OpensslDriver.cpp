#include "OpensslDriver.h"
#include <arpa/inet.h>
#include <openssl/aes.h>
#include <openssl/sha.h>
#include <openssl/rand.h>
#include <zlib.h>
#include <string>
#include <cstring>
#include <iostream>

OpensslDriver::OpensslDriver()
{
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    const SSL_METHOD* method = TLS_client_method();
    ctx = SSL_CTX_new(method);
    
    SSL_CTX_set_verify(ctx, SSL_VERIFY_NONE, nullptr);
}

uint8_t* OpensslDriver::getAesKey(int socket)
{
    SSL* ssl = SSL_new(ctx);
    SSL_set_fd(ssl, socket);
    try {
        if (SSL_connect(ssl) <= 0) throw std::runtime_error("SSL_connect failed");
    
        uint8_t* buffer = new uint8_t[32];
        int total_read = 0;
        while (total_read < 32) {
            int n = SSL_read(ssl, buffer + total_read, 32 - total_read);
            if (n <= 0) throw std::runtime_error("SSL_read failed");
            total_read += n;
        }
    
        SSL_shutdown(ssl);
        SSL_free(ssl);
        return buffer;
    
    } catch (...) {
        SSL_free(ssl);
        throw;
    }
}


void resizeData(std::vector<uint8_t>& data) {
    size_t remainder = data.size() % 16;
    if (remainder != 0) {
        data.resize(data.size() + (16 - remainder));
    }
}



uint8_t* OpensslDriver::aesEncrypt(std::vector<uint8_t>& data, const uint8_t* key)
{
    // 1. 计算 CRC32 并附加到数据末尾
    uLong crc = crc32(0L, Z_NULL, 0);
    crc = crc32(crc, data.data(), data.size());

    uint8_t* crc_bytes = reinterpret_cast<uint8_t*>(&crc);
    data.insert(data.end(), crc_bytes, crc_bytes + sizeof(crc));

    // 2. 添加 PKCS#7 填充（正确的填充方式）
    size_t blockSize = AES_BLOCK_SIZE;
    size_t paddingLength = blockSize - (data.size() % blockSize);
    data.insert(data.end(), paddingLength, static_cast<uint8_t>(paddingLength));

    size_t paddedLen = data.size();

    // 3. 生成随机 IV
    uint8_t* iv = new uint8_t[blockSize];
    if (RAND_bytes(iv, blockSize) != 1) {
        std::cerr << "Failed to generate IV" << std::endl;
        delete[] iv;
        return nullptr;
    }

    AES_KEY aesKey;
    if (AES_set_encrypt_key(key, 256, &aesKey) < 0) {
        std::cerr << "Failed to set AES key" << std::endl;
        delete[] iv;
        return nullptr;
    }

    std::vector<uint8_t> encrypted(paddedLen);
    uint8_t iv_copy[AES_BLOCK_SIZE];
    std::memcpy(iv_copy, iv, AES_BLOCK_SIZE);

    AES_cbc_encrypt(data.data(), encrypted.data(), paddedLen, &aesKey, iv_copy, AES_ENCRYPT);

    data = std::move(encrypted);

    return iv;
}

uint8_t* OpensslDriver::sha256(uint8_t* str, size_t length)
{
    uint8_t* digest = new uint8_t[SHA256_DIGEST_LENGTH];

    if (!SHA256(str, length, digest)) {
        std::cerr << "SHA256 calculation failed" << std::endl;
        delete[] digest;
        return nullptr;
    }

    return digest;
}