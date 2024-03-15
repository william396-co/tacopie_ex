#ifdef _WIN32

#include <tacopie/network/self_pipe.hpp>
#include <tacopie/utils/error.hpp>
#include <tacopie/utils/typedefs.hpp>

#include <winsock2.h>
#include <fcntl.h>
#include <iostream>

namespace tacopie{

self_pipe::self_pipe(): m_fd{__TACOPIE_INVALID_FD}{

    m_fd = ::socket(AF_INET,SOCK_DGRAM,0);
    if(m_fd == __TACOPIE_INVALID_FD){
        __TACOPIE_THROW(error,"fail socket()");
    }

    u_long flags = 1;
    ioctlsocket(m_fd,FIONBIO,&flags);

    // bind serve to localhost
    struct sockaddr_in inaddr;
    memset(&inaddr,0,sizeof(inaddr));
    inaddr.sin_family = AF_INET;
    inaddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    inaddr.sin_port = 0;
    if(bind(m_fd,(struct sockaddr*)&inaddr,sizeof(inaddr)) == SOCKET_ERROR){
        __TACOPIE_THROW(error,"failed bind()");
    }

    // retrieve server information
    m_addr_len = sizeof(m_addr);
    memset(&m_addr,0,sizeof(m_addr));
    if(::getsockname(m_fd,&m_addr,&m_addr_len) == SOCKET_ERROR){
        __TACOPIE_THROW(error,"failed getsockname()");
    }

    // connect read fd to the server
    if(::connect(m_fd,&m_addr,m_addr_len) == SOCKET_ERROR){
        __TACOPIE_THROW(error,"failed connect()");
    }
}

self_pipe::~self_pipe(){
    if(m_fd != __TACOPIE_INVALID_FD){
        ::closesocket(m_fd);
    }
}

fd_t self_pipe::get_read_fd()const{
    return m_fd;
}

fd_t self_pipe::get_write_fd()const{
    return m_fd;
}

void self_pipe::notify(){
    ::sendto(m_fd,"a",1,0,&m_addr,m_addr_len);
}

void self_pipe::clr_buffer(){
    char buffer[1024];
    ::recvform(m_fd,buf,sizeof(buffer),0,&m_addr,m_addr_len);
}

}

#endif