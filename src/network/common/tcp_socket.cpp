#include <tacopie/network/tcp_socket.hpp>
#include <tacopie/utils/error.hpp>
#include <tacopie/utils/logger.hpp>

#ifdef _WIN32
#ifdef __GNUC__
#   include <Ws2tcpip.h>	   // Mingw / gcc on windows
   #define _WIN32_WINNT 0x0501
   #include <winsock2.h>
   #   include <Ws2tcpip.h>
   extern "C" {
   WINSOCK_API_LINKAGE  INT WSAAPI inet_pton( INT Family, PCSTR pszAddrString, PVOID pAddrBuf);
   WINSOCK_API_LINKAGE  PCSTR WSAAPI inet_ntop(INT  Family, PVOID pAddr, PSTR pStringBuf, size_t StringBufSize);
   }

 #else
   // Windows...
   #include <winsock2.h>
   #include <In6addr.h>
   #include <Ws2tcpip.h>
#endif
#else
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#endif /* _WIN32 */

#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#endif /* SOCKET_ERROR */

#if _WIN32
#define __TACOPIE_LENGTH(size) static_cast<int>(size) // for Windows, convert buffer size to `int`
#pragma warning(disable : 4996)                       // for Windows, `inet_ntoa` is deprecated as it does not support IPv6
#else
#define __TACOPIE_LENGTH(size) size // for Unix, keep buffer size as `size_t`
#endif      

namespace tacopie{

tcp_socket::tcp_socket()
:m_fd{__TACOPIE_INVALID_FD},
m_host{""},
m_port{},
m_type{socket_type::UNKNOWN}{
    __TACOPIE_LOG(debug,"create tcp_socket");
}


void tcp_socket::check_or_set_type(socket_type type){
    if(m_type != socket_type::UNKNOWN && m_type != type){
        __TACOPIE_THROW(error,"trying to perform invalid operation on socket");
    }
    m_type = type;
}

std::string const& tcp_socket::get_host()const{
    return m_host;
}

uint32_t tcp_socket::get_port()const{
    return m_port;
}

void tcp_socket::set_type(socket_type type){
    m_type = type;
}

fd_t tcp_socket::get_fd()const{
    return m_fd;
}

bool tcp_socket::is_ipv6()const{
    return m_host.find(':')!=std::string::npos;
}

bool tcp_socket::operator==(tcp_socket const& other)const{
    return m_fd == other.m_fd && m_type == other.m_type;
}

bool tcp_socket::operator!=(tcp_socket const& other)const{
    return ! operator==(other);
}


}