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
#include <netdb.h> //getprotobyname

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
# include "c_autoindex.hpp"
#include "c_server.hpp"
#include "c_location.hpp"
# include "c_debugger.hpp"

#include "parse_conf.hpp"
#include "exception.hpp"
#include "utils.hpp"
#include "c_syntax.hpp"
#include "server.hpp"
#include "c_client.hpp"
#include "request_op.hpp"
#include "startServer.hpp"

# define MAX_CLIENT 		128
# define MAX_EVENTS 		100
# define BUFFER_SIZE 		4096

#endif
