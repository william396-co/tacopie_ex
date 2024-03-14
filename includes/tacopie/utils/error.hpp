#pragma once

#include <cstdint>
#include <cstdexcept>
#include <string>

#include <tacopie/utils/logger.hpp>

namespace tacopie{

class tacopie_error: public std::runtime_error{
public:
    tacopie_error(std::string const& what, std::string const& file, std::size_t line);
    ~tacopie_error()=default;

    tacopie_error(tacopie const&) = default;
    tacopie_error& operator=(tacopie const&)=default;

public:
    std::string const& get_file()const{return m_file;}

    std::size_t get_line()const{return m_line;}
private:
    std::string m_file;
    std::size_t m_line;
}; 

}