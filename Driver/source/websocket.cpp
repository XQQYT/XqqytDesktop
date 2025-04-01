#include "websocket.h"

WebSocket::WebSocket()
    : ioc(std::make_unique<asio::io_context>()),
      ws_socket(std::make_unique<websocket::stream<tcp::socket>>(*ioc)),
      resolver(std::make_unique<tcp::resolver>(*ioc))
{
}

WebSocket::~WebSocket()
{
    closeSocket();
}

WebSocket::WebSocket(WebSocket&& obj) noexcept
    : ioc(std::move(obj.ioc)),
      ws_socket(std::move(obj.ws_socket)),
      resolver(std::move(obj.resolver))
{
    this->address = std::move(obj.address);
    this->port = std::move(obj.port);
}

WebSocket& WebSocket::operator=(WebSocket&& obj) noexcept
{
    if (this != &obj) {
        ioc = std::move(obj.ioc);
        ws_socket = std::move(obj.ws_socket);
        resolver = std::move(obj.resolver);
        address = std::move(obj.address);
        port = std::move(obj.port);
    }
    return *this;
}

void WebSocket::initSocket(const std::string& address, const std::string& port)
{
    this->address = address;
    this->port = port;
}

void WebSocket::connectToServer()
{
    try {
        auto self = shared_from_this(); // 确保 `this` 对象在异步操作完成前不会被销毁
        resolver->async_resolve(address, port,
            [this, self](beast::error_code ec, tcp::resolver::results_type results) {
                if (!ec) {
                    asio::async_connect(ws_socket->next_layer(), results.begin(), results.end(),
                        [this, self](beast::error_code ec, const tcp::endpoint&) {
                            if (!ec) {
                                ws_socket->async_handshake(address, "/",
                                    [this, self](beast::error_code ec) {
                                        if (!ec) {
                                            std::cout << "Connected to WebSocket server.\n";
                                        } else {
                                            std::cerr << "Handshake failed: " << ec.message() << std::endl;
                                        }
                                    });
                            } else {
                                std::cerr << "Connection failed: " << ec.message() << std::endl;
                            }
                        });
                } else {
                    std::cerr << "Resolve failed: " << ec.message() << std::endl;
                }
            });

        std::thread([this]() { this->ioc->run(); }).detach();
    } catch (const std::exception& e) {
        std::cerr << "Failed to connect: " << e.what() << std::endl;
    }
}

void WebSocket::sendMsg(const std::string& msg)
{
    if (!ws_socket || !ioc || !resolver) {
        throw std::runtime_error("WebSocket is not initialized");
    }

    auto self = shared_from_this();
    asio::post(*ioc, [this, self, msg]() {
        try {
            ws_socket->write(asio::buffer(msg));
        } catch (const std::exception& e) {
            std::cerr << "Send failed: " << e.what() << std::endl;
        }
    });
}

void WebSocket::recvMsg(std::function<void(std::string)> callback)
{
    auto self = shared_from_this();
    auto buffer = std::make_shared<beast::flat_buffer>();

    ws_socket->async_read(*buffer,
        [this, self, buffer, callback](beast::error_code ec, std::size_t bytes_transferred) {
            if (!ec) {
                callback(beast::buffers_to_string(buffer->data()));
            } else {
                std::cerr << "Receive failed: " << ec.message() << std::endl;
            }
        });
}

void WebSocket::closeSocket()
{
    if (ws_socket && ws_socket->is_open()) {
        try {
            ws_socket->close(websocket::close_code::normal);
        } catch (const std::exception& e) {
            std::cerr << "Error while closing WebSocket: " << e.what() << std::endl;
        }
    }
}
