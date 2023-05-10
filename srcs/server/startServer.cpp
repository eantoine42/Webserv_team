#include "../../includes/startServer.hpp"

void	start_server(std::map<int, server *> &serverFd)
{
	int	epoll_fd = create_epoll(serverFd);
	struct epoll_event	eventlist[MAX_EVENTS];
	std::map<int, ClientInfo> fd_of_clients;

	for (;;) // infinite loop for new event
	{
		int event_amount = epoll_wait(epoll_fd, eventlist, MAX_EVENTS, -1);
		if (event_amount == -1)
			throw(FailToWaitEpoll());
		for (int i = 0 ; i < event_amount ; ++i)
		{
			if ((eventlist[i].events & EPOLLRDHUP)
				|| (eventlist[i].events & EPOLLHUP)
				|| (eventlist[i].events & EPOLLERR)) // client quit
				delete_client_from_epoll(fd_of_clients, epoll_fd, eventlist[i].data.fd);
			else if (serverFd.find(eventlist[i].data.fd) != serverFd.end()) // event of server means new client connected
				accept_new_client(epoll_fd, eventlist[i].data.fd, fd_of_clients, serverFd);
			else if (eventlist[i].events & EPOLLIN) // there is new input from old client
			{
				std::map<int, ClientInfo>::iterator it = fd_of_clients.find(eventlist[i].data.fd);
				if (it == fd_of_clients.end())
					throw(ClientNotInMap());
				if (read_request(it) <= 0) // no request sent
					delete_client_from_epoll(fd_of_clients, epoll_fd, eventlist[i].data.fd);
				else
				{
					deal_with_request(it);
					delete_client_from_epoll(fd_of_clients, epoll_fd, eventlist[i].data.fd);
				}
			}
			else // Neet to deal with Write Event ?
			{
				delete_client_from_epoll(fd_of_clients, epoll_fd, eventlist[i].data.fd);
			}
		}
	}
}
