#ifdef _WIN32

#pragma comment(lib,"ws2_32.lib")

#include <tacopie/network/tcp_socket.hpp>
#include <tacopie/utils/error.hpp>
#include <tacopie/utils/logger.hpp>
#include <tacopie/utils/typedefs.hpp>

#include <cstring>

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

namespace tacopie{


void tcp_socket::connect(std::string const& host,uint32_t port, uint32_t timeout_msecs){

}

void tcp_socket::bind(std::string const& host, uint32_t port){
    // reset host and port
    m_host = host;
    m_port = port;
    create_socket_if_necessary();
    check_or_set_type(socket_type::SERVER);

}

void tcp_socket::close(){
    if(m_fd != __TACOPIE_INVALID_FD){
        __TACOPIE_LOG(debug,"close socket");
        ::closesocket(m_fd);
    }
    m_fd = __TACIPIE_INVALID_FD;
    m_type = socket_type::UNKNOWN;
}

void tcp_socket::create_socket_if_necessary(){

    if(m_fd != __TACOPIE_INVALID_FD){
        return;
    }

    // new TCP Socket
    // handle ipv6 addr
    short family;
    if(is_ipv6()){
        family = AF_INET6;
    }else{
        family = AF_INET;
    }

    m_fd = socket(family, SOCK_STREAM,0);
    m_type = socket_type::UNKNOWN;
}


}

#endif