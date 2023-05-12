#ifndef PARSE_CONF_HPP
#define PARSE_CONF_HPP

# include "webserv.hpp"
# include "c_debugger.hpp"
class server;
std::vector<server>	parseConfFile(std::string const &path);

#endif
