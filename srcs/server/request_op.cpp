#include "../../includes/request_op.hpp"

int	read_request(std::map<int, ClientInfo>::iterator &it)
{
	int	ret = 0;
	int	len;
	std::string str;

	while (1)
	{
		char	buf[BUFFER_SIZE];
		len = recv(it->first, buf, BUFFER_SIZE - 1, 0);
		if (len <= 0)
			break ;
		ret += len;
		buf[len] = 0;
		str += buf;
	}
	if (ret > 0)
		it->second.add_request(str);
	return ret;
}

static void addSocket(int epoll_fd, int socket_fd)
{
	struct epoll_event	event;
	std::memset(&event, 0, sizeof(event));
	event.events = EPOLLIN;
	event.data.fd = socket_fd;
	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socket_fd, &event) == -1)
		throw(epollFail("Problem affecting epoll"));
}
/*
static void editSocket(int epoll_fd, int socket_fd) {
	struct epoll_event	event;

	memset(&event, 0, sizeof(epoll_event));
	event.data.fd = socket_fd;
	event.events = EPOLLOUT;
	if (epoll_ctl(epoll_fd, EPOLL_CTL_MOD, socket_fd, &event) < 0)
		throw(epollFail("Problem editing socket in epoll"));
}

static void removeSocket(int epoll_fd, int socket_fd) {
	if (epoll_ctl(epoll_fd, EPOLL_CTL_DEL, socket_fd, 0) < 0)
		throw(epollFail("Problem Removing socket in epoll"));
}*/

int	createEpoll(std::map<int, server *> &serverFd)
{
	int epoll_fd = epoll_create(1);
	if (epoll_fd == -1)
		throw(epollFail("failed to create epoll"));
	for (std::map<int, server *>::iterator it = serverFd.begin() ; it != serverFd.end() ; ++it)
		addSocket(epoll_fd, it->first);
	return (epoll_fd);
}

