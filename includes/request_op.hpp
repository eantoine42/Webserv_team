#ifndef REQUEST_OP_HPP
#define REQUEST_OP_HPP

# include "webserv.hpp"
# include "c_client.hpp"

class ClientInfo;
int	read_request(std::map<int, ClientInfo>::iterator &it);

#endif
