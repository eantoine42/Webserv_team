#include "../../includes/startServer.hpp"

void	start_server(std::map<int, server *> &serverFd)
{
	int cs;
	struct sockaddr_in csin;
	unsigned int cslen;
	std::map<int, ClientInfo> fd_of_clients;
	std::map<int, server *>::iterator server_it;
	server_it = serverFd.begin();

	cs = accept(server_it->first, (struct sockaddr *)&csin, &cslen);
	if (cs != -1)
		fd_of_clients.insert(std::make_pair(cs, ClientInfo((*(serverFd[server_it->first])))));
	std::map<int, ClientInfo>::iterator client_it;
	client_it = fd_of_clients.begin();
	read_request(client_it);
	DEBUG_COUT("got from client :" + client_it->second.get_request());
	close (cs);
}

