#ifndef STARTSERVER_HPP
#define STARTSERVER_HPP
#include "webserv.hpp"
# include "c_debugger.hpp"

void	startServer(std::map<int, server *> &serverFd);
void	startEpollServer(std::map<int, server *> &serverFd);

#endif
