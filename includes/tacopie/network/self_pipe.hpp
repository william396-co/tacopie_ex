#pragma once

#include <tacopie/utils/typedefs.hpp>

namespace tacopie
{
    /*
    * usedd to force poll to wake up
    * simply make poll watch for read events on one side of the pipe and write to the other side
    */
    class self_pipe{
    public:
        self_pipe();
        ~self_pipe();

        self_pipe(self_pipe const&)=delete;
        self_pipe& operator=(self_pipe const&)=delete;
    public:
        fd_t get_read_fd()const;
        fd_t get_write_fd()const;
        void notify();
        void clr_buffer();
    private:
    #ifdef _WIN21
        fd_t m_fd;
        struct sockaddr m_addr;
        int m_addr_len;
    #else
        fd_t m_fds[2];
    #endif
    };
}