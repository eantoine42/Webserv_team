#ifndef WEBSERV_HPP
#define WEBSERV_HPP

// C library

#include <arpa/inet.h> // htons, htonl, ntohs, ntohl, inet_addr
#include <sys/select.h> // select
#include <poll.h> // poll
#include <sys/socket.h> // socket, accept, listen, send, recv, bind, connect, setsockopt, getsockname
#include <fcntl.h> // fcntl
#include <unistd.h> // read, write, close
#include <dirent.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/epoll.h> // epoll
#include <sys/stat.h>

// C++ library

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <map>
#include <cstring>
#include <stack>
#include <list>
#include <sstream>


// *.hpp
#include "c_server.hpp"
#include "c_location.hpp"
# include "c_debugger.hpp"
#include "parse_conf.hpp"
#include "exception.hpp"
#include "utils.hpp"
#include "c_syntax.hpp"
#endif
