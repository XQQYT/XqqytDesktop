#ifndef _WEBSOCKET_H
#define _WEBSOCKET_H

#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <stdexcept>
#include <memory>
#include "Network.h"

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace websocket = beast::websocket;
using tcp = asio::ip::tcp;

class WebSocket : public NetworkInterface , public std::enable_shared_from_this<WebSocket>{
public:
    static std::shared_ptr<WebSocket> create() {
        return std::shared_ptr<WebSocket>(new WebSocket());
    }
    WebSocket(const WebSocket& obj) = delete;
    WebSocket(WebSocket&& obj) noexcept;
    WebSocket& operator=(WebSocket&& obj) noexcept;
    void initSocket(const std::string& address,const std::string& port) override;
    void connectToServer(std::function<void(bool)> callback = nullptr) override;
    void sendMsg(std::string msg) override;
    void recvMsg(std::function<void(std::string&&)> callback) override;
    void closeSocket() override;
    ~WebSocket();
private:
    WebSocket();
    std::unique_ptr<asio::io_context> ioc;
    std::unique_ptr<websocket::stream<tcp::socket>> ws_socket;
    std::unique_ptr<tcp::resolver> resolver;
};

#endif