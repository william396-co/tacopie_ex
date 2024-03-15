#pragma once

#include <cstdint>
#include <stdexcept>
#include <string>

#include <tacopie/utils/logger.hpp>

namespace tacopie{

class tacopie_error: public std::runtime_error{
public:
    tacopie_error(std::string const& what, std::string const& file, std::size_t line);
    ~tacopie_error()=default;

    tacopie_error(tacopie_error const&) = default;
    tacopie_error& operator=(tacopie_error const&)=default;

public:
    std::string const& get_file()const{return m_file;}

    std::size_t get_line()const{return m_line;}
private:
    std::string m_file;
    std::size_t m_line;
}; 

}
//! macro for convenience
#define __TACOPIE_THROW(level, what)                          \
  {                                                           \
    __TACOPIE_LOG(level, (what));                             \
    throw tacopie::tacopie_error((what), __FILE__, __LINE__); \
  }
