#include <tacopie/utils/thread_pool.hpp>
#include <tacopie/utils/logger.hpp>

namespace tacopie
{

    namespace utils
    {
        thread_pool::thread_pool(std::size_t nb_threads)
        {
            __TACOPIE_LOG(debug, "create thread_pool");
            set_nb_threads(nb_threads);
        }

        thread_pool::~thread_pool()
        {
            __TACOPIE_LOG(debug, "destroy thread_pool");
            stop();
        }

        void thread_pool::run()
        {
            while(true){
                auto [stopped,task] = fetch_task_or_stop();
                // if thread has been requested to stop, stop it here
                if(stopped){
                    break;
                }

                // execute task
                if(task){
                    __TACOPIE_LOG(debug,"execute task");

                    try{
                        task();
                    }catch(std::exception const& ){
                        __TACOPIE_LOG(warn,"uncatched exception propagated up to the threadpool");
                    }
                    __TACOPIE_LOG(debug,"execution complete");
                }
            }
            __TACOPIE_LOG(debug,"stop run() worker");
        }

        void thread_pool::stop()
        {
            if(!is_running()){
                return;
            }

            for(auto & worker: m_workers){
                worker.join();
            }
            m_workers.clear();
            __TACOPIE_LOG(debug,"thread_pool stopped");
        }

        std::pair<bool, task_t> thread_pool::fetch_task_or_stop()
        {
            std::unique_lock lock(m_tasks_mtx);

            __TACOPIE_LOG(debug,"waiting to fetch task");
            m_tasks.cv.wait(lock,[&]{return should_stop() || !m_tasks.empty();});

            if(should_stop()){
                --m_nb_running_threads;
                return {true,nullptr};
            }

            auto& task = std::move(m_tasks.front());
            m_tasks.pop();
            return {false, task};
        }

        void thread_pool::add_task(task_t const &task)
        {
            std::lock_guard lock(m_tasks_mtx);
            __TACOPIE_LOG(debug,"add task to thread_pool");

            m_tasks.push(task);
            m_tasks_cv.notify_one();
        }

        thread_pool &thread_pool::operator<<(task_t const &task)
        {
            add_task(task);
            return *this;
        }

        void thread_pool::set_nb_threads(std::size_t nb_threads)
        {
            m_max_nb_threads = nb_threads;
            // if we increased the number of threads, spawn them
            while(!m_nb_running_threads < m_max_nb_threads){
                ++m_nb_running_threads;
                m_workers.push_back(std::thread(std::bind(&sthread_pool:run,this)));
            }
            // otherwise, wake up threads to make them stop if necessary(until we get the right amount of threads)
            if(m_nb_running_threads > m_max_nb_threads){
                m_tasks_cv.notify_all();
            }            
        }
    }

}
