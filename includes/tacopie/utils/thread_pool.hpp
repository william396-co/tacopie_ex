#pragma once

#include <atomic>
#include <thread>
#include <condition_variable>
#include <queue>
#include <mutex>
#include <vector>
#include <list>
#include <functional>

namespace tacopie
{

    using task_t = std::function<void()>;

    class thread_pool
    {
    public:
        explicit thread_pool(std::size_t nb_threads);
        ~thread_pool();

        thread_pool(thread_pool const &) = delete;
        thread_pool &operator=(thread_pool const &) = delete;

    public:
        thread_pool& operator<<(task_t const& task);
        void add_task(task_t const &task);
        void stop();
        bool is_running() const { return !m_should_stop; }
        void set_nb_threads(std::size_t nb_threads);

    public:
        void run();
        std::pair<bool, task_t> fetch_task_or_stop();
        bool should_stop() const { return m_should_stop || m_nb_running_threads > m_max_nb_threads; }

    private:
        std::list<std::thread> m_workers;
        std::atomic<std::size_t> m_max_nb_threads = ATOMIC_VAR_INIT{};
        std::atomic<std::size_t> m_nv_running_threads = ATOMIC_VAR_INIT{};
        std::atomic<bool> m_should_stop = ATOMIC_VAR_INIT{};
        std::queue<task_t> m_tasks;
        std::mutex m_tasks_mtx;
        std::condition_variable m_tasks_cv;
    };

}