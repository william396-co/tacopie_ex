#include <tacopie/utils/logger.hpp>

namespace tacopie
{

  std::unique_ptr<logger_iface> active_logger = nullptr;

  static const char black[] = {0x1b, '[', '1', ';', '3', '0', 'm', 0};
  static const char red[] = {0x1b, '[', '1', ';', '3', '1', 'm', 0};
  static const char yellow[] = {0x1b, '[', '1', ';', '3', '3', 'm', 0};
  static const char blue[] = {0x1b, '[', '1', ';', '3', '4', 'm', 0};
  static const char normal[] = {0x1b, '[', '0', ';', '3', '9', 'm', 0};

  logger::logger(log_level level) : m_level{level} {}

  void logger::debug(std::string const &msg, std::string const &file, std::size_t line)
  {
    if (m_level >= log_level::debug)
    {
      std::lock_guard lock(m_mutex);
      std::cout << "[" << black << "DEBUG" << normal << "][tacopie][" << file << ":" << line << "] " << msg << std::endl;
    }
  }

  void logger::info(std::string const &msg, std::string const &file, std::size_t line)
  {
    if (m_level >= log_level::info)
    {
      std::lock_guard lock(m_mutex);
      std::cout << "[" << blue << "INFO" << normal << "][tacopie][" << file << ":" << line << "] " << msg << std::endl;
    }
  }

  void logger::warn(std::string const &msg, std::string const &file, std::size_t line)
  {
    if (m_level >= log_level::warn)
    {
      std::lock_guard lock(m_mutex);
      std::cout << "[" << yellow << "WARN" << normal << "][tacopie][" << file << ":" << line << "] " << msg << std::endl;
    }
  }

  void logger::error(std::string const &msg, std::string const &file, std::size_t line)
  {
    if (m_level >= log_level::error)
    {
      std::lock_guard lock(m_mutex);
      std::cout << "[" << read << "ERROR" << normal << "][tacopie][" << file << ":" << line << "] " << msg << std::endl;
    }
  }

  void debug(const std::string &msg, const std::string &file, std::size_t line)
  {
    if (active_logger)
    {
      active_logger->debug(msg, file, line);
    }
  }

  void info(const std::string &msg, const std::string &file, std::size_t line)
  {
    if (active_logger)
    {
      active_logger->info(msg, file, line);
    }
  }

  void warn(const std::string &msg, const std::string &file, std::size_t line)
  {
    if (active_logger)
    {
      active_logger->warn(msg, file, line);
    }
  }

  void error(const std::string &msg, const std::string &file, std::size_t line)
  {
    if (active_logger)
    {
      active_logger->error(msg, file, line);
    }
  }

}