#include <tacopie/utils/error.hpp>

namespace tacopie{

tacopie_error:tacopie_erro(std::string const& what, std::string const& file,std::size_t line)
:std::runtime_error(what),
m_file(file),
m_line(line){}




}