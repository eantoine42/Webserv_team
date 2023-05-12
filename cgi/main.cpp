/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:42:00 by lfrederi          #+#    #+#             */
/*   Updated: 2023/05/12 20:24:05 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

#include <iostream>
#include <unistd.h>
#include <poll.h>

int main()
{
	Server			server;
	int				nFds;
	struct pollfd	*firstFd;

	try
	{
		server.serverInit(18000);
	}
	catch (Server::ServerInitException & e) {
		std::cout << e.what() << std::endl;
		return (1);
	}
	
	/* server.listening(); */

	while (1)
	{
		nFds = server.getFds().size();
		firstFd = &server.getFds().front();
		poll(firstFd, nFds, -1);

		int i = 0;
		while (i < nFds)
		{
			switch (firstFd[i].revents) 
			{
				case NO_EVENTS:
					break;
				case POLLIN:
					server.readRequest(firstFd[i]);
					firstFd = &server.getFds().front();
					break;
				case POLLOUT:
					server.writeResponse(firstFd[i]);
					break;
				case POLLNVAL:
					// Server close socket
					std::cout << "Server close connection" << std::endl;
					if (!server.getConnections()[firstFd[i].fd].getOpen())
						server.getConnections().erase(firstFd[i].fd);
					server.getFds().erase(server.getFds().begin() + i);
					firstFd = &server.getFds().front();
					nFds--;
					i--;
					break ;
				case POLLRDHUP:
					// Client close socket
					std::cout << "Client close connection" << std::endl;
					close(firstFd[i].fd);
					server.getConnections().erase(firstFd[i].fd);
					server.getFds().erase(server.getFds().begin() + i);
					firstFd = &server.getFds().front();
					nFds--;
					i--;
					break ;
				default:
					std::cout << "Default" << std::endl;
					break ;
			}
			i++;
		}
	}

	return (0);
}
