/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 08:37:21 by lfrederi          #+#    #+#             */
/*   Updated: 2023/05/23 09:07:24 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "SocketFd.hpp"
#include <iostream> // cout
#include <strings.h> // bzero
#include <sys/epoll.h> // epoll *
#include <sys/socket.h> // accept
#include <stdio.h> // perror
#include <fcntl.h> // fcntl
#include <unistd.h> // close

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
	std::cout << "Server destructor()" << std::endl;
}

Server::Server(int fd) : _fd(fd)
{}

void	Server::clientConnect(std::map<int, AFileDescriptor *> & map)
{
	int					socketConnect;
	struct epoll_event	ev;

	if ((socketConnect = accept(this->_fd, NULL, NULL)) < 0)
	{
		perror("accept");
		return ;
	}

	if (fcntl(socketConnect, F_SETFL, O_NONBLOCK) < 0)
	{
		perror("fcntl");
		return ;
	}

	bzero(&ev, sizeof(ev));
	ev.data.fd = socketConnect;
	ev.events = EPOLLIN;
	if (epoll_ctl(g_epollFd, EPOLL_CTL_ADD, socketConnect, &ev) < 0)
	{
		close(socketConnect);
		perror("epoll_ctl");
		return ;
	}
	map[socketConnect] = new SocketFd(socketConnect);
}
