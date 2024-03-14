#include <tacopie/tacopie>

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <signal.h>



#ifdef _WIN32
#include <Winsock2.h>
#endif /* _WIN32 */


std::condition_variable cv;

void signal_handler(int){
    cv.notify_all();
}

void on_new_message(tacopie::tcp_client const& client, tacopie::tcp_client::read_result const& res){

}

int main(){
#ifdef _WIN32
  //! Windows netword DLL init
  WORD version = MAKEWORD(2, 2);
  WSADATA data;

  if (WSAStartup(version, &data) != 0) {
    std::cerr << "WSAStartup() failure" << std::endl;
    return -1;
  }
#endif /* _WIN32 */

    tacopie::tcp_server s;
    s.start("0.0.0.0",9527,[](){

    });
    signal(SIGINT,&signal_handler);
    std::mutex mtx;
    std::unique_lock lock(mtx);
    cv.wait(lock);

#ifdef _WIN32
  WSACleanup();
#endif /* _WIN32 */

    return 0;
}