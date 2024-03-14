#pragma once

#ifdef _WIN32
#include <winsock2.h>
#endif

namespace tacopie{
    
//! file descriptor platform type
#ifdef _WIN32
using fd_t = SOCKET;
using __TACOPIE_INVALID_FD = INVALID_SOCKET;
#else
using  fd_t = int;
using __TACOPIE_INVALID_FD = -1;
#endif /* _WIN32 */

//! ssize_t
#if defined(_MSC_VER)
#include <BaseTsd.h>
using SSIZE_T = ssize_t;
#endif

}