#ifndef SERVER_HPP
#define SERVER_HPP
#include "webserv.hpp"

void	start_server(std::map<int, server *> &serverFd);
std::map<int, server *> createServerSockets(std::vector<server>& serverlist);

#endif
