#pragma once

#include <memory>
#include <mutex>
#include <string>

namespace tacopie{

/*
* logger_iface
* should be inherited by any class intended to be used for logging
*/
class logger_iface{
public:
    logger_iface()=default;
    virtual ~logger_iface()=default;

    logger_iface(logger_iface const&)=default;
    logger_iface& operator=(logger_iface const&)=default;
public:
    virtual void debug(std::string const& msg, std::string const& file, std::size_t line) = 0;
    virtual void info(std::string const& msg, std::string const& file, std::size_t line) = 0;
    virtual void warn(std::string const& msg, std::string const& file, std::size_t line) = 0;
    virtual void error(std::string const& msg, std::string const& file, std::size_t line) = 0;
};


/*
* default logger class provided by the library
*/

class logger: public logger_iface{
public:
    enum class log_level{
        error = 0,
        warn = 1,
        info = 2,
        debug = 3
    };
public:
    logger(log_level level = log_level::info);
    ~logger()=default;

    logger(logger const&)=default;
    logger& operator=(logger const&)=default;

public:
    void debug(std::string const& msg, std::string const& file, std::size_t line) override;
    void info(std::string const& msg, std::string const& file, std::size_t line) override;
    void warn(std::string const& msg, std::string const& file, std::size_t line) override;
    void error(std::string const& msg, std::string const& file, std::size_t line) override;

private:
    log_level m_level;
    std::mutex m_mutex;
};

extern std::unique_ptr<logger_iface> active_logger;

void debug(std::string const& msg, std::string const& file, std::size_t line);
void info(std::string const& msg, std::string const& file, std::size_t line);
void warn(std::string const& msg, std::string const& file, std::size_t line);
void error(std::string const& msg, std::string const& file, std::size_t line);

/*
* convenience macro to log with file and line information
*/
#ifdef __TACOPIE_LOGGING_ENABLED
#define __TACOPIE_LOG(level,msg) tacopie::level(msg,__FILE__,__LINE__);
#else
#define __TACOPIE_LOG(level,msg)
#endif

}
