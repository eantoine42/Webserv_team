/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:52:30 by lfrederi          #+#    #+#             */
/*   Updated: 2023/05/22 19:20:36 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Debugger.hpp"
#include "SocketFd.hpp"

#include <cstddef>
#include <iostream>
#include <sys/socket.h> // accept
#include <unistd.h> // read
#include <cstdio> // perror
#include <sys/epoll.h> // epoll *
#include <strings.h> // bzero
#include <fcntl.h> // fcntl

extern int g_epollFd;

Server::Server(void)
{}

Server::Server(Server const & copy) : _fd(copy._fd)
{}

Server & Server::operator=(Server const & rhs)
{
	if (this != &rhs)
	{
		this->_fd = rhs._fd;
	}

	return (*this);

}

Server::~Server()
{
	std::cout << "ServerFd destructor()" << std::endl;
}

Server::Server(int fd) : _fd(fd)
{}

void	Server::clientConnect(std::map<int, AFileDescriptor *> & map)
{
	struct epoll_event ev;
	int socketConnect;

	socketConnect = accept(this->_fd, NULL, NULL);
	if (socketConnect < 0)
	{
		DEBUG_COUT("Error while accept called");
		return ;
	}
	
	if (fcntl(socketConnect, F_SETFL, O_NONBLOCK) < 0)
		perror("fcntl");
	
	bzero(&ev, sizeof(ev));
	ev.events = EPOLLIN;
	ev.data.fd = socketConnect;
	if (epoll_ctl(g_epollFd, EPOLL_CTL_ADD, socketConnect, &ev) < 0)
	{
		close(socketConnect);
		DEBUG_COUT("Error while epoll_ctl called");
	}

	map[socketConnect] = new SocketFd(socketConnect);
}
