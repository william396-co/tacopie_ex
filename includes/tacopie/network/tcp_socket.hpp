#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include <tacopie/utils/typedefs.hpp>

namespace tacopie
{
/*
 * tacopie::tcp_socket is the class providing low-level TCP socket features.
 * The tcp_socket provides a simple but convenient abstraction to unix and windows sockets.
 * It also provides a socket type checker to ensure that server-only operations are only processable on server sockets, and client-only operations are only processable on client sockets.
 */

enum class socket_type{
    CLIENT,
    SERVER,
    UNKNOWN
};

class tcp_socket
{
public:
    tcp_socket();
    ~tcp_socket()=default;    
    tcp_socket(fd_t fd, std::string const& host,uint32_t port, socket_type type);

    tcp_socket(tcp_socket&&);
    tcp_socket(tcp_socket const&)=delete;
    tcp_socket& operator=(tcp_socket const&)=delete;
public:
    bool operator==(tcp_socket const& other )const;
    bool operaror!=(tcp_socket const& other)const;
public:    
    std::vector<char> recv(std::size_t size_to_read);
    std::size_t send(std::vector<char> const& data, std::size_t size_to_write);
    voic connect(std::string const& host, uint32_t port, uint32_t timeout_msecs = 0);
    void bind(std::string const& host,uint32_t port);
    void listen(std::size_t max_connection_queue);
    tcp_socket accept();
    void close();
public:
    std::string const& get_host()const;
    uint32_t get_port()const;
    socket_type get_type()const;
    void set_type(socket_type type);
    fd_t get_fd()const;
public:
    bool is_ipv6()const;
private:
    void create_socket_if_necessary();
    void check_or_set_type(socket_type type);
private:
    fd_t m_fd;
    std::string m_host;
    uint32_t m_port;
    socket_type m_type;
};

}