/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:44:08 by lfrederi          #+#    #+#             */
/*   Updated: 2023/05/22 20:38:24 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AFileDescriptor.hpp"
#include "Request.hpp"
#include "SocketFd.hpp"
#include "Debugger.hpp"
#include "Server.hpp"

#include <iostream>
#include <strings.h>
#include <cstdlib>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <unistd.h>

#define PORT_LISTEN 18000
#define N_QUEUED	10
#define MAX_FD		1024

int									g_epollFd;

int		couldFailedAndExit(int retFunction, const char *functionName)
{
	if (!(retFunction < 0))
		return (retFunction);
	perror(functionName);
	exit(EXIT_FAILURE);
}

int main()
{
	DEBUG_START(true);

	// Set up the server
	struct sockaddr_in addr;
	int serverFd;

	serverFd = couldFailedAndExit(socket(AF_INET, SOCK_STREAM, 0), "socket");

	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT_LISTEN);
	addr.sin_addr.s_addr = INADDR_ANY;

	couldFailedAndExit(bind(serverFd, (struct sockaddr *) &addr, sizeof(addr)), "bind");
	couldFailedAndExit(listen(serverFd, N_QUEUED), "listen");
	DEBUG_COUT("Server is listenning on port 18000");
	// Server ready to listen

	struct epoll_event					ev, events[MAX_FD];
	int									nfds;
	std::map<int, Server>				mapServerFd;
	std::map<int, AFileDescriptor *>	mapFileDescriptor;

	// Put in mapServerFd the Server object that listening
	mapServerFd[serverFd] = Server(serverFd);

	// Create epoll
	g_epollFd = couldFailedAndExit(epoll_create1(0), "epoll_create1");	

	// Add serverFd in epoll
	bzero(&ev, sizeof(ev));
	ev.events = EPOLLIN;
	ev.data.fd = serverFd;
	couldFailedAndExit(epoll_ctl(g_epollFd, EPOLL_CTL_ADD, serverFd, &ev), "epoll_ctl");

	int j = 0;
	while (j != 1)
	{
		nfds = couldFailedAndExit(epoll_wait(g_epollFd, events, MAX_FD, -1), "epoll_wait");

		for (int i = 0; i < nfds; i++)
		{
			int			fd = events[i].data.fd;
			uint32_t	event = events[i].events;

			if (mapServerFd.find(fd) != mapServerFd.end())
				mapServerFd[fd].clientConnect(mapFileDescriptor);
			else 
			{
				switch (event)
				{
					case EPOLLIN:
						if (mapFileDescriptor[fd]->doOnRead() == Request::requestComplete)
						{
							bzero(&ev, sizeof(ev));
							ev.events = EPOLLOUT;
							ev.data.fd = fd;
							couldFailedAndExit(epoll_ctl(g_epollFd, EPOLL_CTL_MOD, fd, &ev), "epoll_ctl");
						}
						break;
					case EPOLLOUT:
						mapFileDescriptor[fd]->doOnWrite();
						close(fd);
						break;
					default:
						std::cout << "default => event = " << event;
						/* DEBUG_COUT("Error"); */
				}
			}

		}
	}
	close(g_epollFd);

	for (std::map<int, AFileDescriptor *>::iterator it = mapFileDescriptor.begin(); it != mapFileDescriptor.end(); it++)
		delete it->second;

	return 0;
}
