#ifndef PARSE_CONF_HPP
#define PARSE_CONF_HPP

# include "webserv.hpp"
# include "c_debugger.hpp"

class c_server;
std::vector<c_server>	parse_conf_file(std::string const &path);

#endif
