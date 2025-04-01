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
    WebSocket();
    WebSocket(const WebSocket& obj) = delete;
    WebSocket(WebSocket&& obj);
    WebSocket& WebSocket::operator=(WebSocket&& obj);
    void initSocket(const std::string& address,const std::string& port) override;
    void connectToServer() override;
    void sendMsg(const std::string& msg) override;
    void recvMsg(std::function<void(std::string)> callback) override;
    void closeSocket() override;
    ~WebSocket();
private:
    std::shared_ptr<websocket::stream<tcp::socket>> ws_socket;
    std::shared_ptr<asio::io_context> ioc;
    std::shared_ptr<tcp::resolver> resolver;
};