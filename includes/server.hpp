#ifndef SERVER_HPP
#define SERVER_HPP
#include "webserv.hpp"


std::map<int, server *> createServerSockets(std::vector<server>& serverlist);

#endif
