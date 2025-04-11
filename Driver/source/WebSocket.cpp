#include "WebSocket.h"

WebSocket::WebSocket()
    : ioc(std::make_unique<asio::io_context>()),
      ws_socket(std::make_unique<websocket::stream<tcp::socket>>(*ioc)),
      resolver(std::make_unique<tcp::resolver>(*ioc))
{
    work_guard.emplace(asio::make_work_guard(*ioc));  // 防止 ioc 退出
    io_thread = std::thread([this]() { ioc->run(); });  // 启动 ioc 线程
}

WebSocket::~WebSocket()
{
    if(ws_socket && ws_socket->is_open())
        closeSocket();
    if (work_guard) {
        work_guard.reset();  // 允许 ioc 退出
    }
    if (io_thread.joinable()) {
        io_thread.join();    // 等待线程结束
    }
}

void WebSocket::initSocket(const std::string& address, const std::string& port)
{
    this->address = address;
    this->port = port;
}

void WebSocket::connectToServer(std::function<void(bool)> callback)
{
    try {
        auto self = shared_from_this(); // 确保 `this` 对象在异步操作完成前不会被销毁
        resolver->async_resolve(address, port,
            [this, self, callback](beast::error_code ec, tcp::resolver::results_type results) {
                if (!ec) {
                    asio::async_connect(ws_socket->next_layer(), results.begin(), results.end(),
                        [this, self, callback](beast::error_code ec, const boost::asio::ip::basic_resolver_iterator<boost::asio::ip::tcp>
                        ) {
                            if (!ec) {
                                ws_socket->async_handshake(address, "/",
                                    [this, self, callback](beast::error_code ec) {
                                        if (!ec) {
                                            callback(true);
                                        } else {
                                            callback(false);
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

    } catch (const std::exception& e) {
        std::cerr << "Failed to connect: " << e.what() << std::endl;
    }
}

void WebSocket::sendMsg(std::string msg) {
    if (!ws_socket || !ioc || !resolver) {
        throw std::runtime_error("WebSocket is not initialized");
    }

    auto self = shared_from_this();
    auto msg_ptr = std::make_shared<std::string>(std::move(msg));

    asio::post(*ioc, [this, self, msg_ptr]() {
        try {
            if (!ws_socket->is_open()) {
                std::cerr << "WebSocket is closed" << std::endl;
                return;
            }
            ws_socket->write(asio::buffer(*msg_ptr));
            std::cout<<"发送  "<<*msg_ptr<<std::endl<<std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Send failed: " << e.what() << std::endl;
        }
    });
}

void WebSocket::recvMsg(std::function<void(std::string&&)> callback)
{
    auto self = shared_from_this();
    auto buffer = std::make_shared<beast::flat_buffer>();

    ws_socket->async_read(*buffer,
        [this, self, buffer, callback](beast::error_code ec, std::size_t bytes_transferred) {
            if (!ec) {
                callback(beast::buffers_to_string(buffer->data()));
                recvMsg(callback);
                std::cout<<"接收  "<<beast::buffers_to_string(buffer->data())<<std::endl<<std::endl;

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