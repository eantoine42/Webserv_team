#include "../../includes/startServer.hpp"

void	startServer(std::map<int, server *> &serverFd)
{
	int cs;
	struct sockaddr_in csin;
	unsigned int cslen;
	std::map<int, ClientInfo> clients;
	std::map<int, server *>::iterator server_it;
	server_it = serverFd.begin();

	cs = accept(server_it->first, (struct sockaddr *)&csin, &cslen);
	if (cs != -1)
		clients.insert(std::make_pair(cs, ClientInfo((*(serverFd[server_it->first])))));
	std::map<int, ClientInfo>::iterator client_it;
	client_it = clients.begin();
	read_request(client_it);
	DEBUG_COUT("got from client :" + client_it->second.get_request());
	close (cs);
}

void	startEpollServer(std::map<int, server *> &serverFd)
{
	int	epoll_fd = createEpoll(serverFd);
	epoll_event	eventlist[MAX_EVENTS];
	std::map<int, ClientInfo> clients;
	while (1)
	{
		int nbEvents = epoll_wait(epoll_fd, eventlist, MAX_EVENTS, -1);
		if (nbEvents == -1)
			throw(epollFail("problem with epoll wait"));
		for (int i = 0; i < nbEvents; i++) {
			std::map<int, ClientInfo>::iterator c_it;
			c_it = clients.find(eventlist[i].data.fd);
			read_request(c_it);
		}
			
	
	}
	if (close (epoll_fd) < 0)
		throw(epollFail("problem with closing epoll fd"));
}
