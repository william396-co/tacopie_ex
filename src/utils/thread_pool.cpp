#include <tacopie/utils/thread_pool.hpp>
#include <tacopie/utils/logger.hpp>

namespace tacopie{

namespace utils{
thread_pool::thread_pool(std::size_t nb_threads){
    __TACOPIE_LOG(debug,"create thread_pool");
    set_nb_threads(nb_threaeds);   
}

thread_pool::~thread_pool(){
    __TACOPIE_LOG(debug,"destroy thread_pool");
    stop();
}

void thread_pool::run(){

}

void thread_pool:stop(){

}


std::pair<bool, task_t> thread_pool::fetch_task_or_stop(){

    return {false,{}};
}


void thread_pool::add_task(task_t const& task){

}

thread_pool& thread_pool::operator<<(task_t const& task){
    add_task(task);
    return *this;
}

void thread_pool::set_nb_threads(std::size_t nb_threads){
    
}

}

}
